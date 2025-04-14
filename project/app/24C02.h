#ifndef _24C02_H_
#define	_24C02_H_

#include <config.h>
#include <I2C.h>
#define  AddWrC 0xA0    //AT24C02器件地址

u8 WriteRom(u8 addr, u8 dat);	//向AT24Cxx中指定地址单元写入数据，addr存储单元地址，dat写入的数据，写入成功返回1，否则返回0
u8 ReadRom(u8 addr);//从AT24Cxx中指定地址单元读取数据，addr存储单元地址，写入成功返回1，否则返回0

#endif