#ifndef _I2C_H_
#define	_I2C_H_

#include <config.h>

sbit scl=P2^0;       //I2C  时钟 
sbit sda=P2^1;       //I2C  数据 

void I2C_Start(); //启动I2C总线  
void I2C_Stop();	//停止(结束)I2C总线
u8  I2C_SendByte(u8 c);//发送1个字节数据，从机应答返回1，从机不应答返回0  
u8 I2C_RcvByte();//接收1个字节数据
void I2C_Ack(bit a);	// 发送应答或非应答信号(a=0:应答，a=1:非应答)

#endif