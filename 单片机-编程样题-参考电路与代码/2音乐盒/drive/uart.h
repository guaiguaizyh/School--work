#ifndef _UART_H_
#define	_UART_H_

#include <config.h>
extern u8 buf[10],i,flag;//buf[]�洢���յ����ַ�����flagΪ�����ַ�����ǣ�=1ʱ��ʾ������һ���ַ���
void uart_init(u16 bps); //���ڳ�ʼ����@11.0592MHz����׼�����ʣ�1200,2400,4800,9600
void uart_send_ch(u8 ch);//���1���ַ�������
void uart_send_str(u8 *str);//����ַ���������

#endif