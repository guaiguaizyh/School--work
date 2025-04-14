#ifndef _LED_H_
#define _LED_H_


#include <config.h>	

void Print_u32_LED(u32 n);//输出无符号整数(0-999999)到6位数码管,不足6位时，前面不显示
void Print_float_LED(float n,u8 x);//输出小数(有效数字不超过6位)到6位数码管，保留x(0-3)位小数
void Print_str_LED(u8 *str);//输出数字串到数码管
void Print_char(u8 n,u8 k);//在指定位置k显示键码n

#endif