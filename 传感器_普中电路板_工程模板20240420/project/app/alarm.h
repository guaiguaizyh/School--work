#ifndef _ALARM_H
#define _ALARM_H

#include "config.h"

sbit beep=P2^5;//蜂鸣器引脚的定义
extern bit alarm;//报警标记
extern u8 n;//LED闪烁间隔时间
void led_ctrl(u8 pin,u8 sta);//指定灯亮或灭，pin(1、2、6、7、8号灯)，sta(ON、OFF)

#endif