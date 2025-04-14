#ifndef __ONEWIRE_H
#define __ONEWIRE_H

#include "config.h"

sbit DQ = P3^7;
float ds18b20_TMP();//测量温度
//根据按键触发测量一次，或在数码管显示中根据条件定时测量
#endif
