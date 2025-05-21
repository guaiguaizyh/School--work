#include <smg1.h>

u8 code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,0x00};

//数码管显示数字函数
//port_no为数码管所接端口编号，0代表P0，1代表P1，2代表P2,3代表P3
//n为需要显示的数字
void smg_dis(u8 port_no, u8 n) 
{
	switch(port_no){
		case 0:	P0=table[n]; break;
		case 1:	P1=table[n]; break;
		case 2:	P2=table[n]; break;
		default: P3=table[n];
	}
}