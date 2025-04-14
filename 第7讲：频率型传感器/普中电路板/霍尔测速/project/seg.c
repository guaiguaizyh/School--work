#include "seg.h"
//共阴极数码管；位选由P2.4、P2.3、P2.2接译码器输出8个位选信号；段码由P0经锁存器输出，锁存器锁存引脚接VCC。
u8 seg_buf[10];//要显示的字符串
u8 seg_cod[8];//数码管显示编码
u8 seg_pos=0;//数码管位号
u16 count_500ms=0;//数码管刷新定时，500ms
bit seg_update=0;//数码管定时刷新标记
void seg_tran(u8 seg_buf[],u8 seg_cod[])//转码
{
	u8 i,j,temp;
	for(i=0,j=0;i<8;i++,j++)
	{
		switch(seg_buf[j])
		{
			case '0':temp=0x3F;break;
			case '1':temp=0x06;break;
			case '2':temp=0x5B;break;
			case '3':temp=0x4F;break;
			case '4':temp=0x66;break;
			case '5':temp=0x6D;break;
			case '6':temp=0x7D;break;
			case '7':temp=0x07;break;
			case '8':temp=0x7F;break;
			case '9':temp=0x6F;break;
			case 'A':temp=0x77;break;
			case 'B':temp=0x7C;break;
			case 'C':temp=0x39;break;
			case 'D':temp=0x5E;break;
			case 'E':temp=0x79;break;
			case 'F':temp=0x71;break;			
			case 'H':temp=0x76;break;
			case 'L':temp=0x38;break;
			case 'N':temp=0x37;break;
			case 'P':temp=0x73;break;
			case 'U':temp=0x3E;break;
			case '-':temp=0x40;break;
			case ' ':temp=0x00;break;
		}
		if(seg_buf[j+1]=='.')  {temp=temp|0x80;j++;}
		seg_cod[i]=temp;
	}
}

void seg_dis(u8 seg_cod[],u8 seg_pos)//按位显示
{
	P0=0x00;//段码消影
	P2=(P2&0xE3)|((7-seg_pos)<<2);//送位码
	P0=seg_cod[seg_pos];//送段码
}