#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include <config.h>

u8 keypad4_4();//4行4列矩阵按键扫描函数:要去抖，若有按键按下，返回对应的按键值(0-15),没有按键按下返回16


#endif