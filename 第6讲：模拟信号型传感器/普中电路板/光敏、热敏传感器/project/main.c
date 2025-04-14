//���������·��
#include <config.h>
#include <pcf8591.h> 
#include <uart.h> 
  
sbit beep=P2^3;//������	

u8 flag=0;	//0:��,1:��
u16 n0=0,n1=0;  //n0:�����ڼ�����n1:�����ڼ���

void delay_us(u16 n)//΢����ʱ
{
    while(--n);
}

void delay_ms(u16 x)//������ʱ����
{u16 i,j;
 for(i=0;i<x;i++)
    for(j=0;j<115;j++);
}

void Alarm(u8 t) //����������,����t��,�����ʱ
{
 u8 k; 
 u16 i,j; 		
 for(k=0;k<t;k++)
 { for(i=0;i<100;i++)//��
      {beep=0;delay_us(250);beep=1;delay_us(250);}
   for(j=0;j<50;j++)//��
      {beep=0;delay_us(500);beep=1;delay_us(500);}
 }
}

void Alarm_init() //����������,��ʱ��T0
{
	TMOD&=0xf0;//��ʱ��T0��Ϊ��ʽ2,8λ�Զ�װ��ģʽ
    TMOD|=0x02;  
	TH0=0X00;
	TL0=0X00; //��ʱ250us
	EA=1;
	ET0=1;
}

void Alarm_Power(u8 t) //��/�رշ���������,��ʱ��T0,1���򿪣�0���ر�
{
	TR0=t; 
}

void main()
{
	u8 DATA[3],print[10];
	float value;

	uart_init(4800);//���ڳ�ʼ��

//	Alarm_Init();//������(��ʱ��T0)��ʼ��

	while(1)
 	{ 	
	//���������ͨ����ģ���ź�ת��Ϊ�����ź�ʱ��Ҫע�⣺���ζ���������ֵ����һ�ε�ת�����
		DATA[0]=Pcf8591_AD(0);//ͨ��0������
		DATA[1]=Pcf8591_AD(1);//ͨ��1������  
		DATA[2]=Pcf8591_AD(3);//ͨ��3���ɵ�����
		
		value=(float)DATA[0]*5/256;
		sprintf(print,"res��%.1f",value);
		uart_send_str(print);//���������
		
		value=(float)DATA[1]*5/256;
		sprintf(print,"light��%.1f",value);
		uart_send_str(print);//���������
		
		value=(float)DATA[2]*5/256;
		sprintf(print,"heat��%.1f",value);
	   	uart_send_str(print);//���������

//		if(value>2.5) led=
	 
	}
}

//��(һ�����ڸ�250us��250us����500�����ڣ�0.25��)����(һ�����ڸ�500us��500us����250�����ڣ�0.25��)
void time0() interrupt 1
{
	if(flag==0)
	{  
		n0++;
		if(n0==1000)		
		{
			n0=0;
			flag=1;
		}
		else
		{
			beep=~beep;
		}
	}
	else
	{					   //ͨ���ı䶨ʱ����ʱ����Ըı����������
		n1++;			  //��
		if(n1==1000)
		{
			n1=0;
			TR0=0;
			flag=0;
		}
		else
		{
			if(n1%2==0)	beep=~beep;
		}
	}
}																 