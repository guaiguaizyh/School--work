#ifndef _TIMER_H
#define _TIMER_H

#include "config.h"
void timer0_init();//定时器0定时1毫秒@12MHz
void timer1_init();//定时器1定时模式计时@12.000MHz，用于超声波测距
#endif