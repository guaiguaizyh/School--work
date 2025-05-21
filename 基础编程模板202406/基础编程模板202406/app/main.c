//#include <config.h>
//#include <button.h>
//#include <smg1.h>//ʾ
//#include <timer.h>//
//#include <beep.h>//
//#include <1602.h>//


//开关灯
//sbit led=P2^1;
//void main()
//{
//	led=1;
//	while(1)
//	{
//		if(Btn_Press())
//		{led=~led;}
//	}
//}

//走马灯
//void main()
//{
//	u8 mode=0; 
//	while(1)
//		{Led_Ctrl(mode);mode++;if(mode==2) mode=0;}
//}


//void main()
//{
//	while(1)
//	{Led_Ctrl(1);}
//}


//sbit red=P2^0;
//sbit yellow=P2^1;
//sbit green=P2^2;
//u8 t;
////软件延时
//void main()
//{
//	u8 t=0;
//	while(1)
//	{ 
//		//红灯亮
//		yellow=green=0;
//		for(t=0;t<9;t++)
//		{	
//			red=1;
//			if(t<6)
//			{
//				red=1;
//				smg_dis(0,9-t);
//				delay_s(1); 
//			}	
//			else//闪烁
//			{
//				smg_dis(0,9-t);
//				red=0;
//				delay_ms(500);
//				red=1;
//				delay_ms(500);
//			}
//		}
//			//黄灯亮
//		red=green=0;
//		yellow=1;
//		for(t=3;t>0;t--)
//		{
//		smg_dis(0,t);
//		delay_s(1);
//		}
//		//绿灯亮
//		yellow=red=0;
//		for(t=0;t<9;t++)
//		{	
//			green=1;
//			if(t<6)
//			{
//				green=1;
//				smg_dis(0,9-t);
//				delay_s(1); 
//			}	
//			else//闪烁
//			{
//				smg_dis(0,9-t);
//				green=0;
//				delay_s(1);
//				green=1;
//				delay_s(1);
//			}
//		}
//		//黄灯亮
//		red=green=0;
//		yellow=1;
//		for(t=3;t>0;t--)
//		{
//		smg_dis(0,t);
//		delay_s(1);
//		}
//	}
//}

//sbit red=P2^0;
//sbit yellow=P2^1;
//sbit green=P2^2;

//定时器延时,timer.c,smg1.c,
//定时器补充中断函数
/*		x++;
		if(x==9)
		{x=0;}*/
//void main()
//{
//	Timer0_Int();
//	while(1)
//	{
//		//红灯亮9s 
//		yellow=green=0;
//		while(x<6)
//		{
//			red=1;
//			smg_dis(0,9-x);
//		}
//		while(x>=6)
//		{
//			smg_dis(0,9-x);
//			if(count<10)
//			{
//				red=0;
//			}
//			else
//			{
//				red=1;
//			}
//		}
//		//黄灯3s
//		while(x<3)
//		{
//			red=green=0;
//			yellow=1;
//			smg_dis(0,16);
//		}
//		x=0;
//		//绿灯亮9s 
//		yellow=red=0;
//		while(x<6)
//		{
//			green=1;
//			smg_dis(0,9-x);
//		}
//		while(x>=6)
//		{
//			smg_dis(0,9-x);
//			if(count<10)
//			{
//				green=0;
//			}
//			else
//			{
//				green=1;
//			}
//		}
//		//黄灯
//		while(x<3)
//		{
//			red=green=0;
//			yellow=1;
//			smg_dis(0,16);
//		}
//		x=0;
//	}
//}


//红绿灯 软件延时
//sbit red=P2^0;
//sbit yellow=P2^1;
//sbit green=P2^2;

//void main()
//{
//	u8 t;
//	while(1)
//	{
//		//红灯长亮6s
//		yellow=0,green=0;
//		for(t=9;t>0;t--)
//		{
//			red=1;
//			if(t>3)
//			{
//				red=1;
//				smg_dis(0,t);
//				delay_s(1);
//			}
//			else if(t<=3)
//			{
//				smg_dis(0,t);
//				delay_ms(500);
//				red=0;
//				delay_ms(500);
//				red=1;
//			}
//		}
//		
//		//黄灯闪3秒
//		red=0,green=0;
//		for(t=3;t>0;t--)
//		{
//			smg_dis(0,t);
//			yellow=1;
//			delay_s(1);
//		}
//		
//		
//		//绿灯
//		
//		red=0,yellow=0;
//		for(t=9;t>0;t--)
//		{
//			if(t>3)
//			{
//				green=1;
//				smg_dis(0,t);
//				delay_s(1);
//			}
//			else
//			{
//				smg_dis(0,t);
//				delay_ms(500);
//				green=1;
//				delay_ms(500);
//				green=0;
//			}
//		}
//	}
//}

//sbit red=P2^0;
//sbit yellow=P2^1;
//sbit green=P2^2;

//void main()
//{
//	Timer0_Int();
//	while(1)
//	{
//		//红灯
//		yellow=0,green=0;
//		while(x<6)
//		{
//			red=1;
//			smg_dis(0,9-x);
//		}
//		while(x>=6)
//		{
//			smg_dis(0,9-x);
//			delay_ms(500);
//			red=0;
//			delay_ms(500);
//			red=1;
//		}
//		
//		//黄灯亮
//		while(x<3)
//		{
//			red=0,green=0;
//			yellow=1;
//			smg_dis(0,3-x);
//		}
//		
//		yellow=0,red=0;
//		while(x<6)
//		{
//			green=1;
//			smg_dis(0,9-x);
//		}
//		while(x>=6)
//		{
//			smg_dis(0,9-x);
//			delay_ms(500);
//			green=0;
//			delay_ms(500);
//			green=1;
//		}
//			//黄灯亮
//		while(x<3)
//		{
//			red=0,green=0;
//			yellow=1;
//			smg_dis(0,3-x);
//		}
//	}
//}

////音乐盒
//void main()
//{
//	LCD1602_Init( );
//	while(1)         
//	{if(Btn_Press())
//		{
//			 LCD1602_disstr("Happy birthday",0,0);
//			LCD1602_disstr("To You",1,5);
//			while(1){P1=0x00;delay_ms(500);P1=0xff;delay_ms(500);}
//			//playmusic(Music2Meter,Music2TONE,32);
//		}
//	}
//}



//红绿灯
//#include <config.h>
//#include <smg1.h>
//#include <delay.h>
////没有用到硬件延时

//sbit red=P2^0;
//sbit yellow=P2^1;
//sbit green=P2^2;
//void main()
//{
//	u8 t;//定义一个时间变量
//	while(1)
//	{
//		//红灯亮九秒
//		yellow=0;green=0;
//		for(t=9;t>0;t--)
//		{
//			if(t>3)
//			{
//				red=1;
//				smg_dis(0,t);
//				delay_s(1);
//			}
//			else if(t<=3)
//			{
//				smg_dis(0,t);
//				delay_ms(500);
//				red=0;
//				delay_ms(500);
//				red=1;
//			}
//		}
//		
//		//黄灯
//		green=0,red=0;
//		for(t=3;t>0;t--)
//		{
//			smg_dis(0,t);
//			delay_ms(500);
//			yellow=1;
//			delay_ms(500);
//			yellow=0;
//		}
//		
//		//绿灯
//		yellow=0,red=0;
//		for(t=9;t>0;t--)
//		{
//			if(t>3)
//			{
//				green=1;
//				smg_dis(0,t);
//				delay_s(1);
//			}
//			else
//			{
//				smg_dis(0,t);
//				delay_ms(500);
//				green=0;
//				delay_ms(500);
//				green=1;				
//			}
//		}
//		
//		//再来一个黄灯闪烁
//		red=0;green=0;
//		for(t=3;t>0;t--)
//		{
//			smg_dis(0,t);
//			delay_ms(500);
//			yellow=1;
//			delay_ms(500);
//			yellow=0;
//		}
//	}
//}


////红绿灯使用软件延时
//#include <config.h>
//#include <smg1.h>
//#include <delay.h>
//#include <timer.h>

//sbit red=P2^0;
//sbit yellow=P2^1;
//sbit green=P2^2;
//void main()
//{
//	Timer0_Int();
//	green=0,yellow=0;
//	while(x<=6)//外面6秒常亮
//	{
//		smg_dis(0,9-x);
//		red=1;		
//	}
//	while(x>6)
//	{
//		smg_dis(0,9-x);
//		if(count<=10)
//			red=0;
//		else
//			red=1;
//	}
//	x=0;//清零
//	
//	red=0,green=0;
//	while(x<3)
//	{
//		smg_dis(0,3-x);
//		if(count<=10)
//			yellow=1;
//		else yellow=0;
//	}
//	x=0;
//	red=0,yellow=0;
//	while(x<=6)
//	{
//		smg_dis(0,9-x);
//		green=1;
//	}
//	while(x>6)
//	{
//		smg_dis(0,9-x);
//		if(count<=10)
//			green=0;
//		else green=1;
//	}
//	x=0;
//	while(x<3)
//	{
//		smg_dis(0,3-x);
//		if(count<=10)
//			yellow=1;
//		else yellow=0;
//	}
//	x=0;
//	
//}


//生日歌

#include <config.h>
//#include <smg1.h>
#include <delay.h>
#include <timer.h>
#include <beep.h>
#include <1602.h>
#include <button.h>
#include <led8.h>
//sbit btn=P2^4;
//void main()
//{
//	
//	u8 mode=0;
//	LCD1602_Init( );
//	while(1)
//	{
//		if(btn==0) 
//		{
//			delay_ms(10);
//			if(btn==0)
//			{
//			while(!btn);
//			mode=mode^1;
//			if(mode)
//			{
//				LCD1602_clear();
//			LCD1602_disstr("Happy Birthday",0,0);
//			LCD1602_disstr("To you",1,5);
//			playmusic(Music2Meter,Music2TONE,Music2Len);
//			}
//			else
//			{
//				LCD1602_clear( );
//				playmusic(NULL,NULL,NULL);
//			}
//		}
//		}
//	}
//}

//生日歌
//bit ledkey=1;
//void led(void)
//{
//	while(1)
//	{P1=0x00;delay_ms(500);P1=0xff;delay_ms(500);}
//}
//void main()
//{
//	LCD1602_Init( );
//	while(1)
//	{
//		if(Btn_Press())
//		{
//			LCD1602_disstr("Happy Birthday",0,0);
//			LCD1602_disstr("To you",1,5);
//			led();
//			playmusic(Music2Meter,Music2TONE,Music2Len);
//		}
//		else
//		{LCD1602_clear( );}
//	}
//}
//开关灯
//sbit led=P2^5;
//sbit btn=P2^4;
//void main()
//{
//	led=0;
//	while(1)
//	{
//		if(Btn_Press()) led=~led;
//	}
//}

//走马灯
void main()
{
	u8 mode=0;
	while(1)
	{
		Led_Ctrl(mode);mode++;Led_Ctrl(mode);mode++;if(mode==2) mode=0;
	}
}


