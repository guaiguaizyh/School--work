#include <ds1302.h>

sbit SCK=P3^6;		
sbit SDA=P3^4;		
sbit RST=P3^5;   // DS1302复位												

void Write_Ds1302(u8 temp) 
{
	u8 i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		_nop_();
		SDA=temp&0x01;
		temp>>=1; 
		SCK=1;
		_nop_();
	}
}   

void Write_Ds1302_Byte(u8 address,u8 dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

u8 Read_Ds1302_Byte ( u8 address )
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
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	return (temp);			
}

void  ReadRTCTime(u8 * GetTime) //读出时钟值存放到GetTime中，依次存放的是小时、时、分钟、秒值，如{23,59,50}，即23:59:50
{
	u8 temp;
	
	temp = Read_Ds1302_Byte(0x85); // 读出小时值
	GetTime[0] = (temp>>4)*10+(temp&0xf); //将BCD码转换成十进制数，存入GetRTC中
	
	temp = Read_Ds1302_Byte(0x83);  // 读出分钟值
	GetTime[1] = (temp>>4)*10+(temp&0xf);

	temp = Read_Ds1302_Byte(0x81); // 读出秒值
	GetTime[2] = (temp>>4)*10+(temp&0xf);

}
void  ReadRTCDate(u8 * GetDate) //读出日期值存放到GetDate中，依次存放的是年、月、日、星期，如{21,3,27，7}，即21年3月27日星期7
{
	u8 temp;
	
	temp = Read_Ds1302_Byte(0x8D); // 读出年份值
	GetDate[0] = (temp>>4)*10+(temp&0xf); //将BCD码转换成十进制数，存入GetRTC中
	
	temp = Read_Ds1302_Byte(0x89);  // 读出月份值
	GetDate[1] = (temp>>4)*10+(temp&0xf);

	temp = Read_Ds1302_Byte(0x87); // 读出日期值
	GetDate[2] = (temp>>4)*10+(temp&0xf);

	temp = Read_Ds1302_Byte(0x8B); // 读出星期值
	GetDate[3] = (temp>>4)*10+(temp&0xf);

}
void SetRTCDate(u8 *SetDate) //设置日期
//SetDate中依次存放的是年、月、日、星期，如{21,3,27,7}，即21年3月27日星期7
{
	u8 temp;
 	
	Write_Ds1302_Byte(0x8E,0X00);   //允许写操作
	
	//设置日期值
	temp = ((SetDate[0]/10)<<4)+SetDate[0]%10;	//设置年值，将十进制数转换成BCD码
	Write_Ds1302_Byte(0x8C, temp);  //写入

	temp = ((SetDate[1]/10)<<4)+SetDate[1]%10;		 //设置月值
	Write_Ds1302_Byte(0x88, temp);   //写入

	temp = ((SetDate[2]/10)<<4)+SetDate[2]%10;		  //设置日值
	Write_Ds1302_Byte(0x86, temp);  //写入

	temp = ((SetDate[3]/10)<<4)+SetDate[2]%10;		  //设置星期值
	Write_Ds1302_Byte(0x8A, temp);  //写入
	
	Write_Ds1302_Byte(0x8E,0x80);	 //禁止写操作
}
void SetRTCTime(u8 *SetTime) //设置时钟
//SetTime中依次存放的是小时、分钟、秒值，如{23,59,50}，即23:59:50
{
	u8 temp;
 	
	Write_Ds1302_Byte(0x8E,0X00);   //允许写操作
	
	//设置时间值
	temp = ((SetTime[0]/10)<<4)+SetTime[0]%10;	//设置小时值，将十进制数转换成BCD码
	Write_Ds1302_Byte(0x84, temp);  //写入

	temp = ((SetTime[1]/10)<<4)+SetTime[1]%10;		 //设置分钟值
	Write_Ds1302_Byte(0x82, temp);   //写入

	temp = ((SetTime[2]/10)<<4)+SetTime[2]%10;		  //设置秒值
	Write_Ds1302_Byte(0x80, temp);  //写入	
	
	Write_Ds1302_Byte(0x8E,0x80);	 //禁止写操作
}
