#ifndef _DELAY_H_
#define _DELAY_H_

#include "config.h"

void delay_us(u8 n);//微秒延时
void delay_ms(u16 x);//毫秒延时函数
void Delay1ms();		//1毫秒延时@12.000MHz
void Delay5ms();		//5毫秒延时@12.000MHz

#endif