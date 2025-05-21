///*
//4*4矩阵按键
#include <config.h>
#include <1602.h>
#include <key4x4.h>
#include <beep.h>
void main()
{
   u8 key;
   LCD1602_Init( );//1602初始化函数
   while(1)
   {
		key=key_scan_4X4( );//扫描按键
		if(key!=16)//有键按下
		{
		 	beep_on(100,500);//发出按键音
		 	LCD1602_disch(keyval_4X4[key]);//显示按键对应的字符		
		}
   }
} 
//*/

/*
//4*3矩阵按键
#include <config.h>
#include <1602.h>
#include <key4x4.h>
void main()
{
   u8 key;
   LCD1602_Init( );//1602初始化函数
   while(1)
   {
		key=key_scan_4X3( );//扫描按键
		if(key!=12)//有键按下
		{
		 	LCD1602_disch(keyval_4X3[key]);//显示按键对应的字符		
		}
   }
}
*/