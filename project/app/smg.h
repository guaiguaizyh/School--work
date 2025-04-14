#ifndef _SMG_H_
#define _SMG_H_

#include <config.h>


void smg_str(u8 *str);//数码管显示字符串，串中可包含"."、"-"、" "。若要显示整数、小数，可以先用sprintf按指定格式输出到字符串，再调用本函数显示该字符串


#endif