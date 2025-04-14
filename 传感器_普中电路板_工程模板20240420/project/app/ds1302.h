#ifndef __DS1302_H
#define __DS1302_H

#include "config.h"

sbit SCK = P3^6;		
sbit SDAT = P3^4;		
sbit RST = P3^5; 

void set_RTC(u8 h,u8 m,u8 s);//设置时间值
void read_RTC(u8 *h,u8 *m,u8 *s);//读出时间值

#endif