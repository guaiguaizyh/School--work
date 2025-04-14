#ifndef _UART_H_
#define	_UART_H_

#include <config.h>

void uart_init(u16 bps); //串口初始化，串口工作方式1，设置波特率bps
void uart_send_ch(u8 ch);//输出1个字符到串口
void uart_send_str(u8 *str);//输出字符串到串口

#endif