//本工程基于普中单片机开发板，晶振12MHz
#include <config.h> 

#include <uart.h> 

sbit beep=P1^5;//蜂鸣器

sbit hall=P1^0;//霍尔传感器开关输出引脚：有磁场输出1，否则输出0

u8 flag=0;	//0:叮,1:咚
u16 n0=0,n1=0;  //n0:叮周期计数，n1:咚周期计数

void delay_us(u16 n)//微秒延时
{
    while(--n);
}

void delay_ms(u16 x)//毫秒延时函数
{u16 i,j;
for(i=0;i<x;i++)
    for(j=0;j<115;j++);
}

void Alarm(u8 t) //蜂鸣器报警,持续t秒,软件延时
{
 u8 k; 
 u16 i,j; 		
 for(k=0;k<t;k++)
 { for(i=0;i<200;i++)//叮
      {beep=0;delay_us(50);beep=1;delay_us(50);}
   for(j=0;j<100;j++)//咚
      {beep=0;delay_us(110);beep=1;delay_us(110);}
 }
}

void Alarm_Init() //蜂鸣器报警,定时器T0
{
	TMOD&=0xf0;//定时器T0设为方式2,8位自动装载模式
    TMOD|=0x02;  
	TH0=0X00;
	TL0=0X00; //定时250us
	EA=1;
	ET0=1;
}

void Alarm_Power(u8 t) //打开/关闭蜂鸣器报警,定时器T0,1：打开，0：关闭
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
			delay_ms(10);	  //消抖动
			if(hall==0)	  //确认触发
			{
			   uart_send_str("close the door");
			   Alarm(5);//启动报警响5秒				
			}
		}

//		if(rain==0)
//		{
//			delay_ms(10);	  //消抖动
//			if(rain==0)	  //确认触发
//			{
//			   uart_send_str("rain");
//			   Alarm(5);//启动报警响5秒				
//			}
//		}

				   
	}
}

//叮(一个周期高250us低250us，共500个周期，0.25秒)，咚(一个周期高500us低500us，共250个周期，0.25秒)
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
	{					   //通过改变定时计数时间可以改变门铃的声音
		n1++;			  //叮
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



 
