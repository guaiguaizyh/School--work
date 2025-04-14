#include <1602.h>
#define DATA P0
sbit LCDEN=P2^7;
sbit RW=P2^5;
sbit RS=P2^6; 

u8 DectectBusyBit( )//״̬�жϺ���(æ/��?)
{   
	u8 result;
	DATA = 0xff;	//��״̬ǰ���øߵ�ƽ����ֹ����
	RS = 0;
	delay_ms(5);
    RW = 1;
	LCDEN = 1;
	delay_ms(5);
	result=DATA&0x80; //ȡ���λ��Ϊæ��ǣ���LCMæ,�򷴸�����,�ڴ˴�ԭ��̤������LCM��ʱ�������¼���
	LCDEN = 0;
	return result;		      
}		

void WrComLCD(u8 ComVal)//д�����
{
	while(DectectBusyBit()==1);         //�ȼ��LCM�Ƿ����
	RS = 0;
	delay_ms(1);
    RW = 0;
	LCDEN = 1;
	DATA = ComVal;
	delay_ms(1);
	LCDEN = 0;	
}

void WrDatLCD(u8 DatVal)//д���ݺ���
{
	while(DectectBusyBit()==1); 
	RS = 1;
	delay_ms(1);
    RW = 0;
	LCDEN = 1;
	DATA = DatVal;
	delay_ms(1);
	LCDEN = 0;	
}

u8 RdACAdr(void)//����ǰ����ַ
{   
	u8 result;
	DATA = 0xff;	//����ַǰ���øߵ�ƽ����ֹ����
	RS = 0;
	delay_ms(5);
    RW = 1;
	LCDEN = 1;
	delay_ms(5);
	result=DATA&0x7f; //ȥ�����λæ�б�ǣ�ֻ������7λ��ֵַ
	LCDEN = 0;
	return result;		      
} 

void retACAdr(u8 add)//���ص�ĳ������ַ
{   
    WrComLCD(0x80+add);       
}

void LCD1602pos(u8 x,u8 y)//1602��ʾ���궨λ������xΪ�б꣬0����һ�У�1���ڶ��У�yΪ�б꣬0-15
{
	u8 t;
	t=x?0x40:0x00;
	WrComLCD(0x80+t+y);  
}

void LCD1602_Init( )//1602��ʼ������
{ 
	WrComLCD(0x38);     // �����趨:16*2�С�5*7����8λ���ݽӿ�
	WrComLCD(0x38);
	WrComLCD(0x38);    
//����ظ��趨����ָ��,��ΪLCD�����󲢲�֪��ʹ�õ���4λ���ݽӿڻ���8λ�ģ����Կ�ʼʱ����Ĭ��Ϊ4λ�������տ�ʼд�빦���趨ָ��ʱ����4λ������,Ϊ�˿ɿ�����ö�д�����ָ�� 
	WrComLCD(0x01);    // ���� 
	WrComLCD(0x06);    // �����������Ļ����  
	delay_ms(1);	      // ��ʱ���ȴ������ָ����Ч����������ʾ����ֹ��������
	WrComLCD(0x0c);    // ����ʾ���ع��
	LCD1602pos(0,0);//�ӵ�һ�е�һ���ַ���ʼ��ʾ
	delay_ms(5);
}

void LCD1602_disstr(u8 *p,u8 x,u8 y)//��ָ�����꿪ʼ��ʾӢ���ַ��������Ȳ�����32�����Զ�����
{	
	u8 i=0;
    LCD1602pos(x,y);
	while(p[i]!='\0')
	{  
	  	WrDatLCD(p[i]);
		i++;
		delay_ms(5);
	
//	    if((y+i)%16==0)  //һ����ʾ��ĩβ
//		{  
//		    x=x^0x01;//�л�����һ�У������1��д�껻�е���2��,�����2��д�껻�е���1��
//		    LCD1602pos(x,0);//������ʾ��ַΪ��һ������
//		}		
	}	
}
void LCD1602_disnum(long n,u8 x,u8 y)//��ָ�����꿪ʼ��ʾ������
{	
	u8 i=0,j=0;
	u8 p[17],q[17]="          ";//������ڶ��С���������������
	long m;
	if(n<0) m=-n;
	else    m=n;  
	while(m)
	{p[i++]=m%10+'0';
	 m=m/10;
	}
	p[i--]='\0';
	if(n<0) q[j++]='-';
	while(i)
		q[j++]=p[i--];
	q[j++]=p[i];
	LCD1602_disstr(q,x,y);
}
void LCD1602_disch_x_y(u8 ch,u8 x,u8 y)//��ָ��λ����ʾһ��Ӣ���ַ�
{	
   	LCD1602pos(x,y);
	WrDatLCD(ch);
	delay_ms(5);	
}
void LCD1602_disch(u8 ch)//�ڵ�ǰλ����ʾһ��Ӣ���ַ�
{	
   	WrDatLCD(ch);
	delay_ms(5);	
}
void LCD1602_clear( )//1602��������
{
 	WrComLCD(0x01);    // ����
} 

void LCD1602_return( )//1602���غ���
{
 	WrComLCD(0x02);    // ����
} 

void LCD1602_backspace( )//����ɾ��һ���ַ�
{
 	WrComLCD(0x10);//�������
	WrDatLCD(' ');//����ո�
	WrComLCD(0x10);//�������
}

void LCD1602_cursor(u8 direct)//��������ƶ���direct=0�����ƣ�direct=1������
{
 	if(direct) WrComLCD(0x14);//�������
    else	   WrComLCD(0x10);//�������	
	
}

void LCD1602_screen(u8 direct)//��Ļ�����ƶ���direct=0�����ƣ�direct=1������
{
 	if(direct) WrComLCD(0x1C);//��Ļ����
    else	   WrComLCD(0x18);//��Ļ����	
	
}
void LCD1602_pow(u8 x)//��(1)��ر�(0)��ʾ
{ 
	if(x==1)WrComLCD(0x0f);	//����ʾ
	if(x==0)WrComLCD(0x08);	//����ʾ
}