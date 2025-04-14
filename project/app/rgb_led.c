#include <rgb_led.h>

sbit SCL= P2^1;   //时钟线
sbit SDA= P2^0;  //数据线

//发送前32位'0'起始帧
void RGBLED_Send32Zero( )
{
	 u8 i;
	
	 SDA = 0;
	 for(i=0;i<32;i++)
	 {
	    SCL = 0;
        delay_10xus(20);
        SCL = 1;
        delay_10xus(20);		
	 } 
}

//反转前两位的灰度值
u8 RGBLED_TakeAntiCode(u8 dat)
{
	 u8 tmp = 0;
	
	 tmp = ((~dat) & 0xC0) >> 6;
	 return tmp;
}

//发送灰度数据
void RGBLED_DatSend(u32 dx)
{
	 u8 i;
	 
	 for(i=0;i<32;i++)
	 {
		if((dx & 0x80000000) !=0)
		 SDA=1;
		else 
	     SDA=0;	
		dx<<=1;
		SCL=0;delay_10xus(20);
		SCL=1;delay_10xus(20);
	 }	
}

//数据处理与发送
//r;红色值 0~255
//g:绿色值 0~255
//b:蓝色值 0~255  
void RGBLED_DataDealWithAndSend(u8 r,u8 g,u8 b)
{ 
	 u32 dx=0;
	
	 dx |= (u32)0x03 << 30;  //前两位'1'位标志位
	 dx |= (u32)RGBLED_TakeAntiCode(b) << 28;
	 dx |= (u32)RGBLED_TakeAntiCode(g) << 26;
	 dx |= (u32)RGBLED_TakeAntiCode(r) << 24;
	 dx |= (u32)b << 16;
	 dx |= (u32)g << 8;
	 dx |= r;
	
	 RGBLED_DatSend(dx);//发送数据	
}
//RGB灯控制函数
//r;红色值 0~255
//g:绿色值 0~255
//b:蓝色值 0~255
void RGBLED_Show(u8 r,u8 g,u8 b)
{
	 RGBLED_Send32Zero();//发送前32位'0'起始帧
	 RGBLED_DataDealWithAndSend(r, g, b);//发送32bit灰度数据
     RGBLED_DataDealWithAndSend(r, g, b);
}