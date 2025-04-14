//本代码基于stc89c52，独立按键K1、K2、K3、K4分别接P3.0、P3.1、P3.2、P3.3；矩阵按键行引脚P17、P16、P15、P14，列引脚P13、P12、P11、P10
#include "keypad.h"
u8 count_10ms=0;//矩阵按键扫描定时，10ms
bit key_scan=0;//定时扫描按键标记
u8 btn_read()//独立按键
{
	static u8 sta,key;
	u8 L4;
	L4=P3&0x0f;//扫描是否有按键按下
	switch(sta)
	{
		case 0:	if(L4!=0x0f) sta=1;//第一次检测到按键按下
						break;
		case 1:	if(L4!=0x0f)//去抖，确认按键按下
						{ 
							sta=2;
							switch(L4)
							{
								case  0x0e:key=2;break;
								case  0x0d:key=1;break;
								case  0x0b:key=3;break;
								case  0x07:key=4;break;
							}
						}
						else  sta=0;//抖动
						break;
		case 2:	if(L4==0x0f)//等待按键释放	
						{
							sta=0;			
							return key;
						}	
	}
	return 0;
}
u8 kbd_read()//矩阵按键
{
	static u8 sta,key;
	u8 H4;
	P1=0xF0;
	H4=P1&0xF0;//扫描是否有按键按下
	switch(sta)
	{
		case 0:if(H4!=0xF0) sta=1;//第一次检测到按键按下
		       break;
		case 1:if(H4!=0xF0)//去抖，确认按键按下
			     { 
							sta=2;				 
							P1=0xF7;//扫描第一列
							H4=P1&0xF0;
							switch(H4)
							{
								case  0xe0:key=13;break;
								case  0xd0:key=9;break;
								case  0xb0:key=5;break;
								case  0x70:key=1;break;
							}
							P1=0xFB;//扫描第二列						
							H4=P1&0xF0;
							switch(H4)
							{
								case  0xe0:key=14;break;
								case  0xd0:key=10;break;
								case  0xb0:key=6;break;
								case  0x70:key=2;break;
							}
							P1=0xFD;//扫描第三列							
							H4=P1&0xF0;
							switch(H4)
							{
								case  0xe0:key=15;break;
								case  0xd0:key=11;break;
								case  0xb0:key=7;break;
								case  0x70:key=3;break;
							}
							P1=0xFE;//扫描第四列															
							H4=P1&0xF0;
							switch(H4)
							{
								case  0xe0:key=16;break;
								case  0xd0:key=12;break;
								case  0xb0:key=8;break;
								case  0x70:key=4;break;
							}
					}
					else  sta=0;//抖动
		      break;
		case 2://等待按键释放
					if(H4==0xF0)	
					{
						sta=0;
						return	 key;
					}					
	}
	return 0;
}