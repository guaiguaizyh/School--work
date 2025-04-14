//在调用1602相关函数前，需要做1602的初始化
#ifndef _1602_H_
#define _1602_H_

#include "config.h"

#define LCD1602_DATA P0//1602数据端口
sbit LCDEN=P2^7;//使能引脚
sbit RW=P2^5;//读写引脚
sbit RS=P2^6; //命令/数据引脚

void LCD1602_Init( );//1602初始化函数
void LCD1602_disstr(u8 *p,u8 x,u8 y);//从指定坐标开始显示英文字符串（长度不超过32），自动换行
void LCD1602_clear( );//1602清屏函数

#endif