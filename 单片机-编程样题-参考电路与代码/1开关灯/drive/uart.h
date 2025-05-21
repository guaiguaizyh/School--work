#ifndef _UART_H_
#define	_UART_H_

#include <config.h>
extern u8 buf[10],i,flag;//buf[]存储接收到的字符串；flag为接收字符串标记，=1时表示接收完一条字符串
void uart_init(u16 bps); //串口初始化，@11.0592MHz，标准波特率：1200,2400,4800,9600
void uart_send_ch(u8 ch);//输出1个字符到串口
void uart_send_str(u8 *str);//输出字符串到串口

#endif