//�����̻������鵥Ƭ�������壬����11.0592MHz
#include <config.h> 
#include <dht11.h> 

//#include <uart.h>
//#include <1602.h>
#include <led.h>

sbit beep=P2^3;//������

void delay_us(u8 n)//΢����ʱ
{
    while(--n);
}

void delay_ms(u16 x)//������ʱ����
{u16 i,j;
 for(i=0;i<x;i++)
    for(j=0;j<115;j++);
}



void Alarm(u8 t) //����������,����t��
{
 u8 i,j,k; 	
 for(j=0;j<t;j++)
 { for(i=0;i<200;i++)
      {beep=0;delay_us(50);beep=1;delay_us(50);}
   for(k=0;k<100;k++)
      {beep=0;delay_us(110);beep=1;delay_us(110);}
 }
}

void main()
{
	u8 i;
	u8 RHum=0,Temp=0;
	u8 print[20]; 

//	uart_init(9600); //���ڳ�ʼ��
//	LCD1602_Init();	//1602��ʼ��

	while(1)
 	{    
		delay_ms(1500); //DHT11�ϵ��Ҫ�ȴ�1S��Խ�����ȶ�״̬�ڴ��ڼ䲻�ܷ����κ�ָ��
		DHT11_receive(&RHum,&Temp); //��ȡ���������͹�������ʪ������ 
		
//		sprintf(print,"Temp:%bd;RHum:%bd%%",Temp,RHum);
//	    uart_send_str(print);//���������
//		LCD1602_disstr(print,0,0);//�����1602Һ����ʾ��

	
//		sprintf(print,"%bd %bd",Temp,RHum);
//        for(i=0;i<50;i++)
//          Print_str_LED(print);//����������
 
 //	    if(Temp>20) Alarm(5);  //�¶ȳ���20�ȣ�����������
					   
	}
}




 
