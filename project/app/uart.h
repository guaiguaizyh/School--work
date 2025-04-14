#ifndef _UART_H_
#define	_UART_H_

#include <config.h>

void uart_init(u16 bps);	 //串口初始化，@11.0592MHz，标准波特率：1200,2400,4800,9600
void uart_init_4800();	 //串口初始化，@12MHz，波特率为4800时误差最小0.16%
void uart_send_ch(u8 ch);//输出1个字符到串口
void uart_send_str(u8 *str);//输出字符串到串口

#endif