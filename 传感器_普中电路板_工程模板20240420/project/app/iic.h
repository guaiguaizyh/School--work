#ifndef _IIC_H
#define _IIC_H

#include "config.h"
sbit sda= P2^0;
sbit scl = P2^1;
#define DELAY_TIME 7   //原来是5，需修改为6
void I2CStart(void);//启动
void I2CStop(void);//停止
void I2CSendByte(unsigned char byt);//发送
unsigned char I2CReceiveByte(void);//接收
unsigned char I2CWaitAck(void);//等待应答  
void I2CSendAck(unsigned char ackbit);//发送应答信号，应答ackbit=0，非应答ackbit=1

#endif