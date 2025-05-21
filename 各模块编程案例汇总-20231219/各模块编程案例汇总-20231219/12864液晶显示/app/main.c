#include <config.h>	
#include <ST7920.h>
void main()
{
   u8 buf1[9],buf2[17];
   float y=15.387;
   u16 x=520;

   ST7920_Init();//初始化函数
   ST7920_str("湖北襄阳",0,0);//显示汉字
   
   sprintf(buf1,"%u",x);//将整数转换成字符串
   num_hs_to_fs(buf1,buf2);//将半角数字串转换成全角数字串
   ST7920_str(buf2,1,0);//显示
   
   sprintf(buf1,"%.2f",y); //将小数转换成字符串
   num_hs_to_fs(buf1,buf2);//将半角数字串转换成全角数字串
   ST7920_str(buf2,2,0);//显示
   while(1);   
 
}