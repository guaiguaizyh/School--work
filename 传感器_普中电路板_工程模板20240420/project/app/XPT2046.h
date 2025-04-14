#ifndef	  _XPT2046_H_
#define   _XPT2046_H_

#include "config.h"

//---定义使用的IO口---//
sbit DOUT = P3^7;	  //输出
sbit CLK  = P3^6;	  //时钟
sbit DIN  = P3^4;	  //输入
sbit CS   = P3^5;	  //片选

u16 Read_AD_Data(u8 cmd);//将指定通道cmd的模拟信号转换成数字信号，并返回数字信号值

#define AD    0x94
#define NTC   0xD4
#define GR    0xA4
#define AIN   0xE4
//AIN0：检测转换电位器模拟信号，命令字为0x94或者0xB4
//AIN1：检测转换热敏电阻模拟信号，命令字为0xD4
//AIN2：检测转换光敏电阻模拟信号，命令字为0xA4
//AIN3：检测转换AIN3通道上外接的模拟信号，命令字为0xE4

#endif





