#ifndef _UART_H_
#define	_UART_H_

#include <config.h>

void uart_init(u16 bps);	 //���ڳ�ʼ����@11.0592MHz����׼�����ʣ�1200,2400,4800,9600
void uart_init_4800();	 //���ڳ�ʼ����@12MHz��������Ϊ4800ʱ�����С0.16%
void uart_send_ch(u8 ch);//���1���ַ�������
void uart_send_str(u8 *str);//����ַ���������

#endif