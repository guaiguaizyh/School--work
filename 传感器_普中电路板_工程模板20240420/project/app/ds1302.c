#include "ds1302.h"  									


void Write_Ds1302(u8 temp) //写字节
{
	u8 i;
	for (i=0;i<8;i++)     	
	{ 
		SCK = 0;
		SDAT = temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}

void Write_Ds1302_Byte(u8 address,u8 dat )//向DS1302寄存器写入数据     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

u8 Read_Ds1302_Byte (u8 address ) //从DS1302寄存器读出数据
{
 	u8 i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDAT)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDAT=0;	_nop_();
	SDAT=1;	_nop_();
	return (temp);			
}

u8 DECtoBCD(u8 DEC)	//十进制转BCD码
{
	return ((DEC/10)<<4)+DEC%10;
}

u8 BCDtoDEC(u8 BCD) //BCD码转十进制
{
	return ((BCD>>4)*10)+BCD%16;
}

void set_RTC(u8 h,u8 m,u8 s)//设置时间值
{
	Write_Ds1302_Byte(0x8e,0x00);//允许写
	Write_Ds1302_Byte(0x84, DECtoBCD(h));//写小时值
	Write_Ds1302_Byte(0x82, DECtoBCD(m));//写分钟值
	Write_Ds1302_Byte(0x80, DECtoBCD(s));//写秒值
	Write_Ds1302_Byte(0x8e,0x80); //禁止写
}

void read_RTC(u8 *h,u8 *m,u8 *s)//读出时间值
{
	*h=Read_Ds1302_Byte(0x85);//读出小时值
	*h=BCDtoDEC(*h);//BCD码转十进制
	*m=Read_Ds1302_Byte(0x83);//读出分钟值
	*m=BCDtoDEC(*m);
	*s=Read_Ds1302_Byte(0x81);//读出秒值
	*s=BCDtoDEC(*s);
}
