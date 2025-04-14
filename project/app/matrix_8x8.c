#include <matrix_8x8.h>
#define	LINE   P0   //行选引脚

sbit DS=P3^4;//行编码移位器串行数据输入引脚
sbit SH=P3^6;//行编码移位器移位脉冲引脚
sbit ST=P3^5;//行编码移位器并行输出锁存脉冲引脚

void hc595send_data(u8 t)//行编码移位器串行输入8位数据t
{	
	u8 i;
	ST=0; //为ST产生上升沿做准备
	for(i=0;i<8;i++)
	{	SH=0;  //为给SH上升沿做准备
		t=t<<1;//判断data最高位为1，就发送1；否则发送0
		DS=CY;
		SH=1;  //SH产生上升沿，左移一位，串行输入DS数据	
	}
	ST=1;	//ST上升沿锁存8位行编码数据
}

void M_LED_8_8(u8 *m)//8*8LED点阵屏显示，指针m指向8*8点阵，需不停循环刷新显示，按行扫描，取模方式：阴码，按行取模，高位在前
{ 
	u8 i,temp;
	temp=0xfe;//按行扫描，行扫描信号
	for (i = 0; i < 8; i++)
	{
		LINE = temp;//行选
		hc595send_data(m[i]);//送行编码
		temp=_crol_(temp,1);//下一行行选
		delay_ms(2);
	} 			
}
