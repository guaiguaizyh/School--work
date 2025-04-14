#include "config.h"
#include "timer.h"
#include "1602.h"
#include "alarm.h"
#include "supersonic.h"
#include "seg.h"

//void main()	//主函数
//{ 
//	float dat;
//	u8 str_buf[30];
//	timer0_init();//定时器初始化，定时1ms
//	LCD1602_Init( );	
//	while(1)
//	{
//		if(measureflag==1)//每隔1秒测温
//		{
//			measureflag=0;
//			dat=ds18b20_TMP();
//			if(dat>35&&dat<45) 	alarm=0,led_ctrl(1,ON);
//			else 				alarm=1;
//			sprintf(str_buf,"P-%7.2f",dat);//将温度保留2位小数存入字符串seg_buf
//			LCD1602_disstr(str_buf,0,0);//1602液晶显示温度
//		}	
//	}			
//}
bit measureflag=0;
u8 str_buf[20];
u16 xtime;
u8 count;
void main()
{
	u8 distance;
	timer0_init();
	timer1_init();
	LCD1602_Init();//1602初始化
	
	while(1)
	{
		if(measureflag==1)
		{
			measureflag=0;
			distance=Measure_Distance();
			sprintf(str_buf,"distance:%3bu",distance);
			LCD1602_disstr(str_buf,0,0);
//			if(seg_update==1)//每隔0.5秒更新数码管显示
//			{
//				seg_update=0;
//				sprintf(seg_buf,"%3bu",distance);//将距离存入字符串seg_buf
//				seg_tran(seg_buf,seg_cod);//转码
//			}
			alarm=1;
			if(distance>30) alarm=0;
			else if(distance<30) (xtime=2500,count=120);
				else if(distance<25) (xtime=2000,count=100);
				else if(distance<20) (xtime=1500,count=80);
				else if(distance<15) (xtime=1000,count=50);
				else if(distance<10) (xtime=600,count=30);		
		}
	}
}
void timer0_int() interrupt 1//定时器0定时1ms中断服务函数
{
	static u16 count_1s=0,n=0;//1秒定时测量计数
//定时器T0工作方式1的16位计数值不能自动重装，需要每次中断设置初值
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;
////数码管间隔1ms轮流显示8位
//	seg_dis(seg_cod,seg_pos);
//	seg_pos++;
//	if(seg_pos==8) seg_pos=0;
//产生1s定时
	if(++count_1s==1000)
	{
		count_1s=0;
		measureflag=1;
	}	
	if(alarm==1)//LED闪烁，蜂鸣器响
	{
		++n;//蜂鸣器报警，频率500
		if(n<=500)
		{
			if(n%2) beep=1,led_ctrl(4,ON);
			else 		beep=0,led_ctrl(4,OFF);
		}		
		else if(n<xtime) beep=1;
		else n=0;
	}
	if(n<=count)
	{led_ctrl(4,ON);}
	else if(n<=count*2)
	{led_ctrl(4,OFF);}
	else n=0;
}
	
