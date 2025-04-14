#ifndef _SEG_H
#define _SEG_H

#include "config.h"

extern u8 seg_buf[10];//要显示的字符串
extern u8 seg_cod[8];//数码管显示编码
extern u8 seg_pos;//数码管位号
extern u16 count_500ms;//数码管刷新定时，500ms
extern bit seg_update;//数码管定时刷新标记
void seg_tran(u8 seg_buf[],u8 seg_cod[]);//转码
void seg_dis(u8 seg_cod[],u8 seg_pos);//按位显示

#endif