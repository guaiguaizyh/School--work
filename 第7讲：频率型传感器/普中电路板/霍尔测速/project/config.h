#ifndef _CONFIG_H_
#define	_CONFIG_H_

#include <reg51.h>
#include <stdio.h>
#include <intrins.h>
#include <string.h>

#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long

void delay_ms(u16 x);//毫秒延时函数

#define ON   1//开关、亮灭
#define OFF  0

#endif