#include <config.h>
#include <1602.h>
#include <led8.h>
#include <button.h>
void main()
{
	LCD1602_Init( );
	while(1)
	{
		if(Btn_Press())
		{
			LCD1602_disstr("Happy Birthday",0,1);
			LCD1602_disstr("To You",1,5);
//			while(1)
//			{
//			Led_Ctrl(0);
//			}
			while(1)
			{
			P1=0x00;
			delay_ms(500);
			P1=0xFF;
			delay_ms(500);
			}
		}
	}
}