#include <smg.h>

#define smg_data P0 //宏定义数码管段码引脚
#define smg_bit  P2 //宏定义数码管位选译码器输入引脚

//共阴极数码管编码
u8 code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,0x00};

void smg_str(u8 *str)//数码管显示字符串，串中可包含"."、"-"、" "。若要显示整数、小数，可以先用sprintf按指定格式输出到字符串，再调用本函数显示该字符串
{	
	u8 t=0x00,i;//t为初始位码值

	i=strlen(str);//获取字符串长度，从字符串最后一个字符开始，从右往左显示
	while(i)
	{
		//送位码
	    	smg_bit=smg_bit&0xe3; //清除P24、P23、P22，其他位不变
		smg_bit=smg_bit|t; //设置P24、P23、P22为000-111，其他位不变
	   	
		//送段码
		smg_data=0x00; //段码消影
		switch(str[i-1])
		{
		case '.':	i--;//再上一位数字上显示小数点
					smg_data=table[str[i-1]-'0']|0x80;//要显示小数点只需要将段码最高位置为1
					break;
		case '-':	smg_data=0x40;//显示“-”
					break;
		case ' ':	smg_data=0x00;//显示“ ”
					break;
		default:	smg_data=table[str[i-1]-'0']; 
		} 
	  		 	   
	    	i--;//从字符串中取下一位
		t=t+4;//形成下一位的译码输入位
		delay_ms(3);
	}
}