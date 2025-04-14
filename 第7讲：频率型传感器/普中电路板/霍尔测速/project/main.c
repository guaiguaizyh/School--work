//本工程基于普中单片机开发板，晶振12MHz
#include <config.h> 
#include "alarm.h"
#include "delay.h"
#include "seg.h"



u8 K=0; //统计T1中断次数，中断20次为1秒
u16 n=0;//1秒后的T0计数值，即1秒后流量传感器转动圈数

//u8 str_buf[20];
//void Alarm(u8 t) //蜂鸣器报警,持续t秒,软件延时
//{
//	u8 k; 
//	u16 i,j; 		
//	for(k=0;k<t;k++)
//	{
//		for(i=0;i<200;i++)//叮
//		{  beep=0;delay_us(50);beep=1;delay_us(50);  }
//		for(j=0;j<100;j++)//咚
//      	{  beep=0;delay_us(110);beep=1;delay_us(110);}
// 	}
//}

void ET_Init()//定时器计数器初始化
{
//T0工作于计数器模式，以流量传感器输出为外部计数脉冲，计数初值为0
//T1工作于定时器模式，定时50ms，中断20次，为1秒
//每隔1秒读出T0的计数值，即为1秒钟流量传感器转动圈数
	K=0;	//统计T1中断次数，中断20次为1秒
	TMOD=0X15;//计数器T0工作方式1、软启动、计数；定时器1工作方式1、软启动、定时 
	TH0=0;	//T0计数初值为0
	TL0=0;
//	TH1=19664/256;//T1计数初值19664，晶振11.0592MHz，定时50ms，计数值45872，计数初值19664
//	TL1=19664%256;
	TH1=0xB0;//定时初值
	TL1=0x3c;
	EA=1;  //中断总允许
	ET1=1; //T1中断允许
	TR0=1;	//启动计数器T0
	TR1=1;	//启动定时器T1  
}

void main()
{	
	
 	float q;//流量，单位：升/分钟
	float total_volume=10.0;//总容量
	float current_volume=0;//当前水量
	u8 percentage_filled=0;//当前水量占比


	while(1) //每隔1s统计一次流量
 	{    
		ET_Init();	//定时器计数器初始化
		while(K<20);//等待1s 
		q=n*60/7.5; //计算流量，单位：转/分钟
		current_volume+=q;//更新当前水量
		percentage_filled = (current_volume / total_volume) * 100;
		sprintf(seg_buf, "%d%%", percentage_filled);//将百分数传到字符串里
		seg_tran(seg_buf,seg_cod);//转码
			if(percentage_filled >= 100) {
            led_ctrl(4,ON);alarm=1;
        } else {
            led_ctrl(4,OFF);alarm=0;
        }
	}
}


void T1_INT() interrupt 3
{
	K++;  //每中断一次(50ms)，计数值加1，中断20次即为1s
	if(K==20) 
	{
		TR0=0; //关闭计数器0
		TR1=0; //关闭定时器1
		n=TH0;
		n=n*256+TL0; //1秒后的T0计数值，即1秒后流量传感器转动圈数	     
	}
	else
	{ 
//        TH1=19664/256;//不足20次时，重装初值，继续计时
//        TL1=19664%256;
		TH1=0xB0;//定时初值
		TL1=0x3c;
    }  				  
}