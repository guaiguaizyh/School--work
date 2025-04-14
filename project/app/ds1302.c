#include <ds1302.h>

sbit SCK=P3^6;		
sbit SDA=P3^4;		
sbit RST=P3^5;   // DS1302��λ												

void Write_Ds1302(u8 temp) 
{
	u8 i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		_nop_();
		SDA=temp&0x01;
		temp>>=1; 
		SCK=1;
		_nop_();
	}
}   

void Write_Ds1302_Byte(u8 address,u8 dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

u8 Read_Ds1302_Byte ( u8 address )
{
 	u8 i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	return (temp);			
}

void  ReadRTCTime(u8 * GetTime) //����ʱ��ֵ��ŵ�GetTime�У����δ�ŵ���Сʱ��ʱ�����ӡ���ֵ����{23,59,50}����23:59:50
{
	u8 temp;
	
	temp = Read_Ds1302_Byte(0x85); // ����Сʱֵ
	GetTime[0] = (temp>>4)*10+(temp&0xf); //��BCD��ת����ʮ������������GetRTC��
	
	temp = Read_Ds1302_Byte(0x83);  // ��������ֵ
	GetTime[1] = (temp>>4)*10+(temp&0xf);

	temp = Read_Ds1302_Byte(0x81); // ������ֵ
	GetTime[2] = (temp>>4)*10+(temp&0xf);

}
void  ReadRTCDate(u8 * GetDate) //��������ֵ��ŵ�GetDate�У����δ�ŵ����ꡢ�¡��ա����ڣ���{21,3,27��7}����21��3��27������7
{
	u8 temp;
	
	temp = Read_Ds1302_Byte(0x8D); // �������ֵ
	GetDate[0] = (temp>>4)*10+(temp&0xf); //��BCD��ת����ʮ������������GetRTC��
	
	temp = Read_Ds1302_Byte(0x89);  // �����·�ֵ
	GetDate[1] = (temp>>4)*10+(temp&0xf);

	temp = Read_Ds1302_Byte(0x87); // ��������ֵ
	GetDate[2] = (temp>>4)*10+(temp&0xf);

	temp = Read_Ds1302_Byte(0x8B); // ��������ֵ
	GetDate[3] = (temp>>4)*10+(temp&0xf);

}
void SetRTCDate(u8 *SetDate) //��������
//SetDate�����δ�ŵ����ꡢ�¡��ա����ڣ���{21,3,27,7}����21��3��27������7
{
	u8 temp;
 	
	Write_Ds1302_Byte(0x8E,0X00);   //����д����
	
	//��������ֵ
	temp = ((SetDate[0]/10)<<4)+SetDate[0]%10;	//������ֵ����ʮ������ת����BCD��
	Write_Ds1302_Byte(0x8C, temp);  //д��

	temp = ((SetDate[1]/10)<<4)+SetDate[1]%10;		 //������ֵ
	Write_Ds1302_Byte(0x88, temp);   //д��

	temp = ((SetDate[2]/10)<<4)+SetDate[2]%10;		  //������ֵ
	Write_Ds1302_Byte(0x86, temp);  //д��

	temp = ((SetDate[3]/10)<<4)+SetDate[2]%10;		  //��������ֵ
	Write_Ds1302_Byte(0x8A, temp);  //д��
	
	Write_Ds1302_Byte(0x8E,0x80);	 //��ֹд����
}
void SetRTCTime(u8 *SetTime) //����ʱ��
//SetTime�����δ�ŵ���Сʱ�����ӡ���ֵ����{23,59,50}����23:59:50
{
	u8 temp;
 	
	Write_Ds1302_Byte(0x8E,0X00);   //����д����
	
	//����ʱ��ֵ
	temp = ((SetTime[0]/10)<<4)+SetTime[0]%10;	//����Сʱֵ����ʮ������ת����BCD��
	Write_Ds1302_Byte(0x84, temp);  //д��

	temp = ((SetTime[1]/10)<<4)+SetTime[1]%10;		 //���÷���ֵ
	Write_Ds1302_Byte(0x82, temp);   //д��

	temp = ((SetTime[2]/10)<<4)+SetTime[2]%10;		  //������ֵ
	Write_Ds1302_Byte(0x80, temp);  //д��	
	
	Write_Ds1302_Byte(0x8E,0x80);	 //��ֹд����
}
