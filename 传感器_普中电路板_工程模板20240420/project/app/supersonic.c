//测距前需要对定时器T1进行初始化timer1_init()，用于对ECHO进行计时
#include "supersonic.h"

u8 Measure_Distance()//超声波测距，返回距离值，单位cm  
{
	u16 n=0; //距离变量

//Trig引脚发送高电平，触发8个40KHz方波驱动探头，发送超声波	
	TRIG = 0;
	TRIG = 1;
	delay_us(20);//高电平不少于10us
	TRIG = 0;	
//等待回声	
	while(ECHO==0);  
//统计间隔时间		
	TR1 = 1;	
	while(ECHO==1&&TF1==0);	//等待接收引脚Echo为低电平
	TR1 = 0;//接收到回声后，停止定时
//计算距离	
	if(TF1==1)//TF1=1，超出测量范围
	{
		TF1=0;//清除定时器0中断标记
		n=255;
	}
	else//Echo=0，测距正常
	{
		n=TH1*256+TL1;
		n=n/59;//计算距离(单位为CM)：n*1us/1000000s*340m/2*100cm，即n*0.017，等价于n/58.8...
		TL1 = 0x00;//重置定时器1初值
		TH1 = 0x00;
	}

	return n;	
}