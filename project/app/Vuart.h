#ifndef _VUART_H_
#define	_VUART_H_

#include <config.h>


sbit Vrxd=P2^0;   //ģ�⴮�ڽ��շ����������� 
sbit Vtxd=P2^1;   //ģ�⴮�ڷ����������� 

void S2INI();//������9600��@11.0592MHz
void WByte(u8 input);
u8 RByte();
void Receive_if(u8 *buf);
#endif