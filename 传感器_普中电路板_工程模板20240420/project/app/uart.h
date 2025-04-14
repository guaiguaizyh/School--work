#ifndef _UART_H
#define _UART_H

#include "config.h"

void uart_init();//4800bps@12MHz，选择定时器1为波特率发生器
void uart_sendstr(u8 *str);//输出字符串到串口

#endif