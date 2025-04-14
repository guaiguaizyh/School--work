#include "pcf8591.h"

u8 AtoD(u8 channel)//模拟转数字，channel(0-3)对应通道AIN0-AIN3，0-模拟输出、1-光敏、3-可调电阻
{
	u8 dat;
	I2CStart();//启动
	I2CSendByte(0x90);//发送地址和写命令
	I2CWaitAck();//等待应答
	I2CSendByte(0x40+channel);//选择通道启动转换，0x40-0x43对应通道AIN0-AIN3
	I2CWaitAck();//等待应答	
	I2CStart();//重新启动
	I2CSendByte(0x91);//发送地址和读命令
	I2CWaitAck();//等待应答
	dat=I2CReceiveByte();//读出数字值 
	I2CSendAck(1);//发送非应答信号
	I2CStop(); //停止	
	return dat;
}

void DtoA(u8 dat)//数字转模拟
{
	I2CStart();//启动
	I2CSendByte(0x90);//发送地址和写命令
	I2CWaitAck();//等待应答
	I2CSendByte(0x40);//使能DA转换
	I2CWaitAck();//等待应答
	I2CSendByte(dat);//发送数字值
	I2CWaitAck();//等待应答
	I2CStop(); //停止
}