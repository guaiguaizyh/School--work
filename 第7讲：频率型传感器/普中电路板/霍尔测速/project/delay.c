#include "delay.h"

void delay_us(u8 n)//微秒延时
{
    while(--n);
}

void delay_ms(u16 x)//毫秒延时函数
{
	u16 i,j;
	for(i=0;i<x;i++)
    for(j=0;j<115;j++);
}