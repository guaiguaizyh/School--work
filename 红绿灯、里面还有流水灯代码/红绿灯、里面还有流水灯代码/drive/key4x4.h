#ifndef _KEY4X4_H_

	#define	_KEY4X4_H_
	#include <config.h>
	#include <delay.h>
	extern u8 keyval_4X4[];	
	extern u8 keyval_4X3[]; 
	u8 key_scan_4X4( );//4*4���󰴼�ɨ�躯�������ذ����ţ�0-16����16��ʾ�ް�������
	u8 key_scan_4X3( );//4*3���󰴼�ɨ�躯�������ذ����ţ�0-11����12��ʾ�ް�������
#endif 