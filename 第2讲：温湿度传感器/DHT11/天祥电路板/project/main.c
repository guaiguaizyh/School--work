//本工程基于天祥单片机开发板，晶振11.0592MHz
#include <config.h> 
#include <dht11.h> 

//#include <uart.h>
//#include <1602.h>
#include <led.h>

sbit beep=P2^3;//蜂鸣器

void delay_us(u8 n)//微秒延时
{
    while(--n);
}

void delay_ms(u16 x)//毫秒延时函数
{u16 i,j;
 for(i=0;i<x;i++)
    for(j=0;j<115;j++);
}



void Alarm(u8 t) //蜂鸣器报警,持续t秒
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

//	uart_init(9600); //串口初始化
//	LCD1602_Init();	//1602初始化

	while(1)
 	{    
		delay_ms(1500); //DHT11上电后要等待1S以越过不稳定状态在此期间不能发送任何指令
		DHT11_receive(&RHum,&Temp); //读取传感器传送过来的温湿度数据 
		
//		sprintf(print,"Temp:%bd;RHum:%bd%%",Temp,RHum);
//	    uart_send_str(print);//输出到串口
//		LCD1602_disstr(print,0,0);//输出到1602液晶显示屏

	
//		sprintf(print,"%bd %bd",Temp,RHum);
//        for(i=0;i<50;i++)
//          Print_str_LED(print);//输出到数码管
 
 //	    if(Temp>20) Alarm(5);  //温度超过20度，蜂鸣器报警
					   
	}
}




 
