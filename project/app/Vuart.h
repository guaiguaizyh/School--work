#ifndef _VUART_H_
#define	_VUART_H_

#include <config.h>


sbit Vrxd=P2^0;   //模拟串口接收发送引脚数据 
sbit Vtxd=P2^1;   //模拟串口发送引脚数据 

void S2INI();//波特率9600，@11.0592MHz
void WByte(u8 input);
u8 RByte();
void Receive_if(u8 *buf);
#endif