#include <button.h>
					  
sbit btn=P2^4;
bit Btn_Down()//按键按下返回1，否则返回0
{
	if(btn==0)//检测按键是否被按下
	{
	 	delay_ms(10); //延时去抖
		if(btn==0) //确认按键按下
			return 1;				
	}
	return 0;
}
bit Btn_Press()//按键按下后释放返回1，否则返回0
{
	if(btn==0)//检测按键是否被按下
	{
	 	delay_ms(10); //延时去抖
		if(btn==0) //确认按键按下
		{	
			while(!btn);
			return 1;	
		}				
	}
	return 0;
}