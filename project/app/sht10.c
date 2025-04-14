#include <sht10.h>

#define	NOP5() {_nop_();_nop_();_nop_();_nop_();_nop_();}// ��ʱ5΢��

//ע��SCL��SDAҪ����������裬ʵ��ʹ��ʱֻ�ܽ������·����P0�ڣ���ʱ����ܡ�1602��12864������ʹ�ã�ֻ�ܽ�����ʹ���
sbit SDA=P2^1; 
sbit SCL=P2^0; 

void Start()//��������
{
	SDA = 1;    
    SCL = 0;    //��ʼ״̬
	_nop_();
	SCL = 1;    
	_nop_();
	SDA = 0;    
	_nop_();
	SCL = 0;    
	NOP5();
	SCL = 1;     
    _nop_();
	SDA = 1;
	_nop_();
	SCL = 0;
} 

void Sht10_Reset()//��������λ��״̬�Ĵ�����ֵ����
{	
	u8 i;
	SDA = 1;    
    SCL = 0;    //��ʼ״̬
	for(i = 0; i < 9; i++)
	{	SCL = 1;
		SCL = 0;
	} 
	Start();//�����������ź�
}

u8 WriteByte(u8 SendByte)//д��һ���ֽڲ���ȡӦ��,����ֵΪ0��ʾȷ�ϣ�Ϊ1��ʾû��ȷ��
{
	u8 i,error;
	for(i = 0; i < 8; i++)//ѭ��д��8λ�����д��λ
	{
    	SendByte<<=1;
        SDA=CY; 
        SCL = 1;      
   	    NOP5();                 
	    SCL = 0;
	 }
	SDA = 1;//�ͷ�SDA���ô�������Ӧ��
	SCL=1;
	error=SDA;//SHT����SDA��ʾ��������
	SCL=0;
	return error; 
}

u8 ReadByte(u8 Ack) //��ȡһ���ֽڲ�����Ӧ��AckΪ0��ʾӦ��Ϊ1��ʾ��Ӧ�𣩣����ؽ��յ����ֽ�
{
	u8 i,recbyte=0;
	SDA=1;//�ͷ����ߣ��ô�����������
	for(i = 0; i < 8; i++)//ѭ��д��8λ�����д��λ
	{
    	SCL=1;
		NOP5();
		recbyte=(recbyte<<1)|SDA;
	    SCL = 0;
	 }
	SDA = Ack;//�����򴫸�����Ӧ��
	SCL=1;
	NOP5();
	SCL=0;
	SDA=1;//�ͷ����ߣ��ô���������������
	return recbyte; 
}

u8 SoftReset()//�����λ�������������λ��������״̬�Ĵ�����ֵҲ���;��������Ӧ�𷵻�0���޷�Ӧ����1
{	
    u8 error;
	Sht10_Reset();
	error=WriteByte(0x1e);//����Ϊ��00011110
    return error;
}

u8 Sht10_Measure(u16 *Value,u8 *Check,u8 mode)//�����¶ȡ�ʪ��;(mode:0�¶ȡ�1ʪ��)���ɹ�����0�����ɹ����ط�0ֵ
{	u8 error=0,VH,VL;
	u16  i;
	Start();//����
    switch(mode)
	{case 0:error=WriteByte(0x03);break;//���¶Ȳ������00000011
	 case 1:error=WriteByte(0x05);break;//��ʪ�Ȳ������00000101	
	 default:break;
	}
	if(error > 0)
        return error;		  //������ɹ������˳������ط�0ֵ
	
	for(i = 0; i < 65535; i++)
		if(SDA==0) break;//�ȴ�������������ɣ����ʱ��������SDA����
	if(i==65535)
	{	error++;
        return error;	   //�ȴ�������������ɣ����ɹ����˳������ط�0ֵ
	}

	VH=ReadByte(0); //����һ���ֽڣ�MSB����Ӧ��
	VL=ReadByte(0); //���ڶ����ֽڣ�LSB����Ӧ��
	
	*Check=ReadByte(1); //��У��ͣ�����Ӧ�𣬽���ͨ��
	*Value=VH*256+VL;  //ͨ��ָ���βη��ز���ֵ
	return error;	  //������ɣ�����0
}

void  Sht10_Convert(u16 Temp,u16 RHum,float *VTemp,float *VRHum)//������ֵת��Ϊ����ֵ
{
	float d1 = -40;
    float d2 = 0.01;

	float c1 = -4.0;
	float c2 = +0.0405;
	float c3 = -2.8E-6;   

	float t1 = +0.01;
	float t2 = +0.00008; 
//5V��14λ�������¶�
	*VTemp = d1 + d2 * Temp;
//12λ�����ʪ��
	*VRHum=c1+c2*RHum+c3*RHum*RHum; //����ʪ��
	*VRHum=*VRHum+(*VTemp-25)*(t1+t2*RHum); //����ʪ��
	if( *VRHum > 100 ) *VRHum = 100;
    if( *VRHum < 0.01) *VRHum = 0.01;
}

void sht10(float *VTemp,float *VRHum)//��ʪ�Ȳ����������βε���ʽ���ز���ֵ
{
	u8 error=0;
	u8 Check;//У��� 
	u16 Temp;//�¶Ȳ���ֵ
	u16 RHum;//ʪ�Ȳ���ֵ

	Sht10_Reset(); //��������ʼ������������
  
	error=0;
	error=Sht10_Measure(&Temp,&Check,0);//�����¶�
	error+=Sht10_Measure(&RHum,&Check,1);//����ʪ��
	 
	if(error!=0)	Sht10_Reset();//��������������
	else     		Sht10_Convert(Temp,RHum,VTemp,VRHum);//û�г�����ת��Ϊ������										   
}