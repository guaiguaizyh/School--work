#include <led8.h>
#define LED_Data P1 //宏定义8个LED灯的引脚
/**********************************************LED流水灯**************************************************/
void Led_Ctrl(u8 mode)//不同花样的流水灯
//mode=0(单个灯亮，从左往右)、1(单个灯亮，从右往左)
//mode=2(相邻2个灯亮，从左往右)、3(相邻2个灯亮，从右往左)
//mode=4(8个灯逐个亮，从左往右)、5(8个灯逐个亮，从右往左)
//mode=6(从两边向中间，每次亮2个灯)、7(从中间向两边逐个亮，每次亮2个灯)
//mode=8(从两边向中间逐个亮)、9(从两边向中间逐个亮)
{
	u8 temp,i,th,tl;
	switch(mode)
	{
		case 0:temp=0x7f;
			   for(i=0;i<8;i++)
			   {
				   LED_Data=temp;
				   temp=_cror_(temp,1);
				   delay_ms(300);
			   }
			   break;
		case 1:temp=0xfe;
			   for(i=0;i<8;i++)
			   {
				   LED_Data=temp;
				   temp=_crol_(temp,1);
				   delay_ms(300);
			   }
			   break;
		case 2:
			   break;
		case 3:
			   break;
		case 4:
			   break;
		case 5:
			   break;
		case 6:
			   break;
		case 7:
			   break;
		case 8:
			   break;
		case 9:
			   break;
	}
	LED_Data=0xff;
}