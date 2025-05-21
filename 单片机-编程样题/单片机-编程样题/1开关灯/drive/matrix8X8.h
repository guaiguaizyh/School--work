#ifndef _MATRIX8X8_H_

	#define	_MATRIX8X8_H_
	#include <config.h>
	#include <delay.h>
	extern u8 code picture[];
	extern u8 code font[][8]; 
	void matrix8X8(u8 font[]); //显示8*8点阵font[8]、阴码、低位在前、C51

#endif 