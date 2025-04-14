#include "alarm.h"
u8 count_100ms=0;//LED闪烁间隔时间
bit alarm=0;//报警标记
void led_ctrl(u8 pin,u8 sta)//指定灯亮或灭，pin(1、2、6、7、8号灯)，sta(ON、OFF)
{
	switch(sta)
	{
		case 1:	if(pin)		P1=P1&(~(0x01<<(pin-1)));//指定位置0，灯亮
						break;
		case 0:	if(pin)		P1=P1|(0x01<<(pin-1));//指定位置1，灯灭
						break;
	}
}