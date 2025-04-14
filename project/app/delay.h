#ifndef _DELAY_H_
#define _DELAY_H_

#include <config.h>

void delay_s(u8 x); //x秒延时函数，@11.0592MHz
void delay_ms(u16 x);//x毫秒延时函数，@11.0592MHz
void delay_10xus(u16 x); //10*x微秒延时函数，@11.0592MHz

#endif