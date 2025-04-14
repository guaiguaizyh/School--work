#ifndef _MATRIX_8X8_H_
#define	_MATRIX_8X8_H_

#include <config.h>


void M_LED_8_8(u8 *m);//8*8LED点阵屏显示，指针m指向8*8点阵，需不停循环刷新显示，按行扫描，取模方式：阴码，按行取模，高位在前


#endif