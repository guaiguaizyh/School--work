#include "onewire.h"

//单总线内部延时函数
void Delay_OneWire(u16 t)  
{
	while(t--);	   //*****stc89c52不需要加for循环****	
}
//单总线写操作
void Write_DS18B20(u8 dat)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		DQ = 0;
		DQ = dat&0x01;
		Delay_OneWire(5);
		DQ = 1;
		dat >>= 1;
	}
	Delay_OneWire(5);
}
//单总线读操作
u8 Read_DS18B20()
{
	u8 i;
	u8 dat;
  
	for(i=0;i<8;i++)
	{
		DQ = 0;
		dat >>= 1;
		DQ = 1;
		if(DQ)
		{
			dat |= 0x80;
		}	    
		Delay_OneWire(5);
	}
	return dat;
}
//DS18B20初始化
bit init_ds18b20()
{
  	bit initflag = 0;
  	
  	DQ = 1;
  	Delay_OneWire(12);
  	DQ = 0;
  	Delay_OneWire(80);
  	DQ = 1;
  	Delay_OneWire(10); 
    initflag = DQ;     
  	Delay_OneWire(5);
  
  	return initflag;
}
//测量温度
float ds18b20_TMP()
{
	u8 Temp_H8b,Temp_L8b;
	u16 Temp;	
	rep:
	init_ds18b20();//复位
	Write_DS18B20(0xcc);//跳过寻址
	Write_DS18B20(0x44);//发测温命令
	init_ds18b20();//复位
	Write_DS18B20(0xcc);//跳过寻址
	Write_DS18B20(0xbe);//发读命令
	Temp_L8b=Read_DS18B20();//读出温度值的低8位
	Temp_H8b=Read_DS18B20();//读出温度值的高8位
	Temp=Temp_H8b<<8;//合并成16位
	Temp=Temp+Temp_L8b;
	if(Temp>1280) goto rep;	//首次测量不正常，温度为85，需要再测一次
	return Temp/16.0;//转换成浮点值
}