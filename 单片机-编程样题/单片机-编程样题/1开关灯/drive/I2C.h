#ifndef _I2C_H_
#define	_I2C_H_

#include <config.h>

sbit scl=P2^0;       //I2C  ʱ�� 
sbit sda=P2^1;       //I2C  ���� 

void I2C_Start(); //����I2C����  
void I2C_Stop();	//ֹͣ(����)I2C����
u8  I2C_SendByte(u8 c);//����1���ֽ����ݣ��ӻ�Ӧ�𷵻�1���ӻ���Ӧ�𷵻�0  
u8 I2C_RcvByte();//����1���ֽ�����
void I2C_Ack(bit a);	// ����Ӧ����Ӧ���ź�(a=0:Ӧ��a=1:��Ӧ��)

#endif