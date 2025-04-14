//�����̻������е�Ƭ�������壬����12MHz
#include <config.h> 

#include <uart.h> 

sbit beep=P1^5;//������

sbit hall=P1^0;//��������������������ţ��дų����1���������0

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
 { for(i=0;i<200;i++)//��
      {beep=0;delay_us(50);beep=1;delay_us(50);}
   for(j=0;j<100;j++)//��
      {beep=0;delay_us(110);beep=1;delay_us(110);}
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
	
	uart_init(4800); 
	
	while(1)
 	{    
		if(hall==0)
		{
			delay_ms(10);	  //������
			if(hall==0)	  //ȷ�ϴ���
			{
			   uart_send_str("close the door");
			   Alarm(5);//����������5��				
			}
		}

//		if(rain==0)
//		{
//			delay_ms(10);	  //������
//			if(rain==0)	  //ȷ�ϴ���
//			{
//			   uart_send_str("rain");
//			   Alarm(5);//����������5��				
//			}
//		}

				   
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



 
