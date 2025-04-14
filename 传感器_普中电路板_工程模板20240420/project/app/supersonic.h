#ifndef _SUPERSONIC_H_
#define _SUPERSONIC_H_

#include "config.h"

sbit ECHO = P2^0;  //回声接收端口
sbit TRIG = P2^1;  //超声触发端口

//测距前需要对定时器T1进行初始化timer1_init()，用于对ECHO进行计时

u8 Measure_Distance();//超声波测距，返回距离值，单位cm 

#endif