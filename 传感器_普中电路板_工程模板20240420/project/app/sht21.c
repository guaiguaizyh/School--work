#include "sht21.h"

u8 SHT21_measure(u8 cmd)////测温湿度，测温度，命令字为0xF3(TP)；测湿度，命令字为0xF5(RH)
{
	u8 datH,datL;
	u16 date=0;
	I2CStart();//启动
	I2CSendByte(0x80);//发送器件地址和写命令
	I2CWaitAck();//等待应答
	I2CSendByte(cmd);//发送测量命令
	I2CWaitAck();//等待应答
	I2CStart();//重新启动
	I2CSendByte(0x81);//发送器件地址和读命令
	I2CWaitAck();//等待应答
	datH = I2CReceiveByte();//读出高8位
	datL = I2CReceiveByte();//读出低8位	
	I2CSendAck(1);//发送非应答信号
	I2CStop();//停止
	date=datH<<8|datL;  //组合成14/12位数据
	date=date&0xFFFC;   //低2位清零
	if(cmd==TP) date=date*175.72/65536-46.85; //温度转换
	if(cmd==RH) date=date*125.0/65536-6;	     //湿度转换
	return date;
}