#include <delay.h>

void delay_s(u8 x) //x秒延时函数，@11.0592MHz
{
	u16 i,j;
	for(i=0;i<=x*1000;i++)
		for(j=0;j<=110;j++);
}

void delay_ms(u16 x)//x毫秒延时函数，@11.0592MHz
{
	u16 i,j;
	for(i=0;i<x;i++)
    		for(j=0;j<113;j++);
}


void delay_10xus(u16 x) //10*x微秒延时函数，@11.0592MHz
{
	while(x--);
}