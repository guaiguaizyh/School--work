//在调用12864ST7920相关函数前，需要做初始化
#ifndef _ST7920_H_
#define _ST7920_H_

#include <config.h>
#include <delay.h>
extern u8 row,col; //当前光标所在位置坐标 ，声明外部变量，供外部源文件调用
void ST7920_Init(void);//初始化函数
void ST7920_pos(u8 X,u8 Y);//设置显示坐标,X行坐标(0-3),Y列坐标(0-7)
void ST7920_str(u8 *p,u8 x,u8 y);//从指定位置开始显示汉字串(字数不超过32)
void ST7920_Clear();//清屏函数
void ST7920_Picture(u8 *pPicture); //显示画图，分辨率128*64，图片点阵阴码、高位在前、逐行
void num_hs_to_fs(u8 *half_str,u8 *full_str);//将半角数字字符串转换成全角数字字符串
#endif