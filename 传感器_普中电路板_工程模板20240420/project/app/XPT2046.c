#include "XPT2046.h"

void SPI_Write(u8 dat)//发送命令
{
	u8 i;
	CLK = 0;
	for(i=0; i<8; i++)
	{
		DIN = dat >> 7;  	//放置最高位
		dat <<= 1;
		CLK = 0;		//上升沿放置数据

		CLK = 1;
	}
}

u16 SPI_Read( )//读取12位数字信号
{
	u8  i;
	u16 dat=0;
	CLK = 0;
	for(i=0; i<12; i++)		//接收12位数据
	{
		dat <<= 1;

		CLK = 1;
		CLK = 0;

		dat |= DOUT;

	}
	return dat;	
}

u16 Read_AD_Data(u8 cmd)//将指定通道cmd的模拟信号转换成数字信号，并返回数字信号值
{
	u8 i;
	u16 AD_Value;
	CLK = 0;
	CS  = 0;
	SPI_Write(cmd);
	for(i=6; i>0; i--); 	//延时等待转换结果
	CLK = 1;	  //发送一个时钟周期，清除BUSY
	_nop_();
	_nop_();
	CLK = 0;
	_nop_();
	_nop_();
	AD_Value=SPI_Read();
	CS = 1;
	return AD_Value;	
}
