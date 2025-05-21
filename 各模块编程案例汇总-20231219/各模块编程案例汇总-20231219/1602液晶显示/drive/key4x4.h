#ifndef _KEY4X4_H_

	#define	_KEY4X4_H_
	#include <config.h>
	#include <delay.h>
	extern u8 keyval_4X4[];	
	extern u8 keyval_4X3[]; 
	u8 key_scan_4X4( );//4*4矩阵按键扫描函数，返回按键号（0-16），16表示无按键按下
	u8 key_scan_4X3( );//4*3矩阵按键扫描函数，返回按键号（0-11），12表示无按键按下
#endif 