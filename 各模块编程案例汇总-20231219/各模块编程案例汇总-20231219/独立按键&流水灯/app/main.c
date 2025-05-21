//通过按键（查询）控制流水灯花样
#include <config.h>
#include <led8.h>
#include <button.h>	
void main()
{
 	u8 mode=0; //流水灯花样模式
	while(1)
	{
		if(Btn_Press())//按键按下并释放	
		{
			Led_Ctrl(mode);	//驱动流水灯
			mode++;
			if(mode==2) mode=0;	//切换两种模式0、1			
		}		
	}
}