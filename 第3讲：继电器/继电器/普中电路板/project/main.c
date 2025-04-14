//�����̻������е�Ƭ�������壬����12MHz
#include <config.h> 
#include <ds18b20.h> 

#include <1602.h>

sbit beep=P1^5;//������
sbit relay=P2^0;//�̵���

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

void Alarm_Init() //����������,��ʱ��T0
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
	float n;
	u8 print[10];

	relay=0;
	LCD1602_Init();//1602��ʼ��
	Alarm_Init();//������(��ʱ��T0)��ʼ��
	
	while(1)
 	{    
		Ds18b20_Tempchg();	//�����¶ȱ任
		n=Ds18b20_Gettemp();  //��ȡ�¶�
		
		sprintf(print,"Temp: %.1f",n);
	   	LCD1602_disstr(print,0,0);//�����1602Һ����ʾ��
		if(n>=20) {
						relay=1;
					//	Alarm_Power(1);
						Alarm(3);
						
		          }
		else      {
						relay=0;
					//	Alarm_Power(0);							
				  }
		delay_ms(800); 		
					   
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



 
