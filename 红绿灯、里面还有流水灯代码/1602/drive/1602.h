//在调用1602相关函数前，需要做1602的初始化
#ifndef _1602_H_
#define _1602_H_

#include <config.h>
#include <delay.h>
void LCD1602_Init( );//1602初始化函数
void LCD1602_disstr(u8 *p,u8 x,u8 y);//从指定坐标开始显示英文字符串（长度不超过32），自动换行
void LCD1602_clear( );//1602清屏函数
void LCD1602_backspace( );//向左删除一个字符
void LCD1602_cursor(u8 direct);//光标左右移动，direct=0，左移，direct=1，右移
void LCD1602_screen(u8 direct);//屏幕左右移动，direct=0，左移，direct=1，右移
void LCD1602_disch(u8 ch);//在当前位置显示一个英文字符
void LCD1602_disch_x_y(u8 ch,u8 x,u8 y);//在指定位置显示一个英文字符
#endif