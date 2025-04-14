#include <supersonic.h>
#define VELOCITY_30C	3495  //30摄氏度时的声速，声速V= 331.5 + 0.6*温度；速度扩大了10倍， 
#define VELOCITY_23C	3453  //23摄氏度时的声速，声速V= 331.5 + 0.6*温度；速度扩大了10倍，

sbit ECHO = P2^0;  //回声接收端口
sbit TRIG = P2^1;  //超声触发端口

u8 count;

void Init_Timer0(void)//定时器0初始化
{
	TMOD = TMOD&0xf0;	 //定时器0初始化,设置为：工作方式1(16位计数值)
	TMOD = TMOD|0x01;	 //定时器0初始化,设置为：工作方式1(16位计数值)
 	TL0 = 0x66;
	TH0 = 0xfc;	 //定时1ms
    EA = 1;		 //总中断使能
	ET0 = 1;	 //开定时器0 	
}

void Init_Supersonic()//超声波传感器初始化
{
	 TRIG =0;
	 ECHO = 0;
	 count = 0;
	 Init_Timer0();
}

void Trig_SuperSonic()//发出声波
{
	 TRIG = 1;
	 delay_us(10); //延时10微秒;
	 TRIG = 0;
}


u32 Measure_Distance()//计算距离函数,返回为距离值，单位mm  
{
	u32 distance=0;    //距离变量
	u8 l;
	u16 h,y;


	Trig_SuperSonic(); //发出声波

	while(ECHO == 0);  //等待回声
    
	TR0 = 1;
	while(ECHO);	
	TR0 = 0;

	l = TL0;
	h = TH0;
	y = (h << 8) + l;//将计数值转换为16位
	y = y - 0xfc66;//us部分，不足1ms的时间
	distance = y + 1000 * count;
	count = 0;
//计算总时间(单位us)=若干(count)ms+us(y)
	TL0 = 0x66;
	TH0 = 0xfc;
	delay_us(30);
	distance = VELOCITY_30C * distance / 20000;//距离单位换算成MM
	return distance;
}

void timer0 () interrupt 1//T0中断处理函数  
{
	TL0 = 0x66;
	TH0 = 0xfc;
	count++;
	if(count == 18)//超声波回声脉宽最多18ms
	{
		TR0 =0;
		TL0 = 0x66;
		TH0 = 0xfc;
		count = 0;
	}
}