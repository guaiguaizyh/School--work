#include <config.h>	
#include <button.h>

sbit led = P2^1;

void main()
{
	led = 1;//灯的初始状态为关。
	while(1){
		if(Btn_Press()){ //按了按钮
			led = ~led;
		}
	}		
}




void main()
{
	while(1)
	{
		if(btn==0)
		{
			delay_ms(10);
			if(btn==0)
			{
				while(!btn);
			}
		}
	}
}