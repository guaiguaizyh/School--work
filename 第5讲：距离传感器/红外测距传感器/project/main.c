//基于天祥电路板
#include <config.h>
#include <PCF8591.h> 
#include <1602.h> 
u8 disval[]={200,180,170}
disval[0]=200    0=10cm  200=//电压的数字值
disval[1]=180	 1=11cm  180=//电压的数字值
disval[2]=170 

  
sbit beep=P2^3;//蜂鸣器	

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
 { for(i=0;i<100;i++)//叮
      {beep=0;delay_us(250);beep=1;delay_us(250);}
   for(j=0;j<50;j++)//咚
      {beep=0;delay_us(500);beep=1;delay_us(500);}
 }
}

void Alarm_init() //蜂鸣器报警,定时器T0
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
	u8 print[10],DATA;
	float v;  

	LCD1602_Init();//1602初始化

//	Alarm_Init();//蜂鸣器(定时器T0)初始化

	while(1)
 	{ 	
		DATA=Pcf8591_AD(0);  //将通道0输入的模拟信号转换为数字信号	
		
		for(i=0;i<  ;i++)
			if disval[i]==DATA break; 
		delay_ms(100);	
		sprintf(print,"%bu",i+10);
	  
		LCD1602_disstr(print,0,0);//输出到1602液晶显示屏
	 
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