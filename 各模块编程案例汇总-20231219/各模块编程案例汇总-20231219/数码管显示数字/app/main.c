//数码管显示整数、小数
#include <config.h>
#include <smg8.h>
void main()
{
   float x=520.1358;
   u16 y=1314;
   u8 buf[10];//存放输出的字符串
   while(1)
   {
		//将数字转换成字符串
 		sprintf(buf,"%.2f",x); //左对齐显示小数，保留2位小数
//		sprintf(buf,"%9.2f",x);//右对齐显示小数，保留2位小数
//		sprintf(buf,"%u",y);   //左对齐显示整数
//		sprintf(buf,"%8u",y);  //右对齐显示整数

		smg_dis_str(buf);//显示数字字符串
   }
}