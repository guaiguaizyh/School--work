#include <timer.h>
#define NUM (65536-50000) //每个50ms中断一次，晶振12MHz
u8 x=0;
u8 count=0;
void Timer0_Int()//定时器0初始化
{
   	//设置工作方式
	TMOD=TMOD&0xf0;
	TMOD=TMOD|0x01;	//T0软启动、定时器、工作方式1
	//设置计数初值
	TH0=NUM/256;
	TL0=NUM%256;
	//启动定时
	TR0=1;
	//中断允许
	EA=1;//允许CPU响应中断
	ET0=1;//允许定时器T0中断
}
void Timer0() interrupt 1  //定时器0中断服务函数
{
	//重装初值
	TH0=NUM/256;
	TL0=NUM%256;
	count++;//每隔50ms中断一次
	if(count==20) //中断20次即为1秒，去做相应的处理
	{
		count=0;
	//在此补充中断服务函数代码
		x++;
		if(x==9) x=0;
	}
}