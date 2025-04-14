#ifndef _PCF8591_H_
#define	_PCF8591_H_

#include <config.h>
#include <I2C.h>
#define  AddWr 0x90    //PCF8591器件地址
u8 Pcf8591_DA(u8 Val);//数字转模拟，val为数字信号值，转换成功返回1，否则返回0
u8 Pcf8591_AD(u8 channel);//模拟转数字，channel为模拟信号通道号(0-3)，转换成功则返回数字值，否则返回0
#endif