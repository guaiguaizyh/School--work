#ifndef _UART_H_
#define	_UART_H_

#include <config.h>

void uart_init(u16 bps); //���ڳ�ʼ�������ڹ�����ʽ1�����ò�����bps
void uart_send_ch(u8 ch);//���1���ַ�������
void uart_send_str(u8 *str);//����ַ���������

#endif