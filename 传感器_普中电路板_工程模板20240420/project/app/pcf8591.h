#ifndef _PCF8591_H
#define _PCF8591_H

#include "iic.h"

u8 AtoD(u8 channel);//模拟转数字，channel(0-3)对应通道AIN0-AIN3，0-模拟输出、1-光敏、3-可调电阻
void DtoA(u8 dat);//数字转模拟
#endif