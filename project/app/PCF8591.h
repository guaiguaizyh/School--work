#ifndef _PCF8591_H_
#define	_PCF8591_H_

#include <config.h>
#include <I2C.h>
#define  AddWr 0x90    //PCF8591������ַ
u8 Pcf8591_DA(u8 Val);//����תģ�⣬valΪ�����ź�ֵ��ת���ɹ�����1�����򷵻�0
u8 Pcf8591_AD(u8 channel);//ģ��ת���֣�channelΪģ���ź�ͨ����(0-3)��ת���ɹ��򷵻�����ֵ�����򷵻�0
#endif