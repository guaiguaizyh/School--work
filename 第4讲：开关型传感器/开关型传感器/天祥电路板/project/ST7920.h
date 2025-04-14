//在调用12864ST7920相关函数前，需要做初始化
#ifndef _ST7920_H_
#define _ST7920_H_

#include <config.h>

extern u8 row,col; //当前光标所在位置坐标 ，声明外部变量，供外部源文件调用
void ST7920_Init(void);//初始化函数
void ST7920_pos(u8 X,u8 Y);//设置显示坐标,X行坐标(0-3),Y列坐标(0-7)
void ST7920_str(u8 *p,u8 x,u8 y);//从指定位置开始显示汉字串(字数不超过32)
void ST7920_word(u8 *p,u8 x,u8 y);//在指定位置显示一个汉字
void ST7920_Clear();//清屏函数
void ST7920_del(u8 x,u8 y);//删除指定位置上的汉字
void ST7920_Clrline(u8 x);//清除指定行，并且光标移到行首
void ST7920_Backspace();//向左删除最后一个汉字
void ST7920_pow(u8 x);//打开(1)或关闭(0)显示
#endif