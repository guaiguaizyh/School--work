#include "at24c02.h"

u8 ROM_read(u8 address)//读at24c02
{
	u8 dat;
	I2CStart();//启动
	I2CSendByte(0xa0);//发送器件地址和写命令
	I2CWaitAck();//等待应答
	I2CSendByte(address);//发送存储单元地址
	I2CWaitAck();//等待应答
	I2CStart();//重新启动
	I2CSendByte(0xa1);//发送器件地址和读命令
	I2CWaitAck();//等待应答
	dat = I2CReceiveByte();//读出存储单元数据
	I2CSendAck(1);//发送非应答信号
	I2CStop();//停止
	return dat;
}

void ROM_write(u8 address,u8 dat)//写at24c02
{
	I2CStart();//启动
	I2CSendByte(0xa0);//发送器件地址和写命令
	I2CWaitAck();//等待应答
	I2CSendByte(address);//发送存储单元地址
	I2CWaitAck();//等待应答
	I2CSendByte(dat); //发送存储单元数据
	I2CWaitAck();//等待应答
	I2CStop();//停止
	delay_ms(5);//延时*****需要添加代码*****	
}