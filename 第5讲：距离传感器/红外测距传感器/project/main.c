//���������·��
#include <config.h>
#include <PCF8591.h> 
#include <1602.h> 
u8 disval[]={200,180,170}
disval[0]=200    0=10cm  200=//��ѹ������ֵ
disval[1]=180	 1=11cm  180=//��ѹ������ֵ
disval[2]=170 

  
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
	u8 print[10],DATA;
	float v;  

	LCD1602_Init();//1602��ʼ��

//	Alarm_Init();//������(��ʱ��T0)��ʼ��

	while(1)
 	{ 	
		DATA=Pcf8591_AD(0);  //��ͨ��0�����ģ���ź�ת��Ϊ�����ź�	
		
		for(i=0;i<  ;i++)
			if disval[i]==DATA break; 
		delay_ms(100);	
		sprintf(print,"%bu",i+10);
	  
		LCD1602_disstr(print,0,0);//�����1602Һ����ʾ��
	 
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