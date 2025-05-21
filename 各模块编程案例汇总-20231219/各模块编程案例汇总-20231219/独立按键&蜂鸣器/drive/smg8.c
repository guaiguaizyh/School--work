#include <smg8.h>
#define smg_data P0 //宏定义数码管段码/位码引脚
sbit DX=P2^0;//定义段码锁存器锁存引脚
sbit WX=P2^1;//定义位码锁存器锁存引脚
void smg_dis_str(char *f) //数码管显示字符串（左对齐，从左往右显示） 
{
	u8 t=0xfe;//位码
	u8 i=0;//字符串下标
	u8 n=strlen(f);//字符串长度
	u8 temp;
	while(i<n)
	{	
		smg_data=0xff; //位码消影
		WX=1;//允许更新位码
		smg_data=t;//更新位码
		WX=0;//锁存位码
		   
		smg_data=0x00; //段码消影
		DX=1;//允许更新段码
		switch(f[i]) //设置段码
		{	
			//共阴数码管编码,根据需要添加要显示的字符的编码
			case '0':temp=0x3f;break;
			case '1':temp=0x06;break;
			case '2':temp=0x5b;break;
			case '3':temp=0x4f;break;
			case '4':temp=0x66;break;
			case '5':temp=0x6d;break;
			case '6':temp=0x7d;break;
			case '7':temp=0x07;break;
			case '8':temp=0x7f;break;
			case '9':temp=0x6f;break;
			case 'a':temp=0x77;break;
			case 'b':temp=0x7c;break;
			case 'c':temp=0x39;break;
			case 'd':temp=0x5e;break;
			case 'e':temp=0x79;break;
			case 'f':temp=0x71;break;
			case '-':temp=0x40;break;
			case ' ':temp=0x00;break;			 
		} 
		if(f[i+1]=='.')	{i++;temp=temp+0x80;}
		smg_data=temp;
		DX=0;//锁存段码
		  		 	   
	    i++; //显示下一位
		t=_crol_(t,1);//下一位的位选信号
		delay_ms(3);//延时
	}
}