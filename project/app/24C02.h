#ifndef _24C02_H_
#define	_24C02_H_

#include <config.h>
#include <I2C.h>
#define  AddWrC 0xA0    //AT24C02������ַ

u8 WriteRom(u8 addr, u8 dat);	//��AT24Cxx��ָ����ַ��Ԫд�����ݣ�addr�洢��Ԫ��ַ��datд������ݣ�д��ɹ�����1�����򷵻�0
u8 ReadRom(u8 addr);//��AT24Cxx��ָ����ַ��Ԫ��ȡ���ݣ�addr�洢��Ԫ��ַ��д��ɹ�����1�����򷵻�0

#endif