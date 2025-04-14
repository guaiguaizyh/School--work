#ifndef _KEYPAD_H
#define _KEYPAD_H

#include "config.h"

extern u8 count_10ms;//矩阵按键扫描定时，10ms
extern bit key_scan;//定时扫描按键标记
u8 btn_read();//独立按键
u8 kbd_read();//矩阵按键

#endif