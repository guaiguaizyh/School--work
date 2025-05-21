#include <config.h>
#include <1602.h>
void main()
{
   float y=15.387;
   u16 x=520;
   u8 buf[10];
   LCD1602_Init( );//1602初始化函数
   LCD1602_disstr("hello world!",0,0);//显示字符串
   sprintf(buf,"%u",x);//将整数转换成字符串
   LCD1602_disstr(buf,1,0);//显示
   sprintf(buf,"%.2f",y); //将小数转换成字符串
   LCD1602_disstr(buf,1,8);//显示
   while(1);
}