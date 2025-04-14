#include <led.h>
#define LEDDAT P0
sbit DX=P2^6;   //  P2^0;
sbit WX=P2^7;   //  P2^1;

u8 code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,0x00}; //共阴数码管编码

void Print_u32_LED(u32 n)//输出无符号整数(0-999999)到6位数码管,不足6位时，前面不显示
{u8 t=0xdf;
 if(n==0) //若该数为0时直接显示0
 {
 	LEDDAT=0xff; //位码消影
	WX=1;//允许更新位码
	LEDDAT=t; //更新位码
	WX=0;//锁存位码
	   
	LEDDAT=0x00; //段码消影
	DX=1;//允许更新段码
	LEDDAT=table[0]; //更新段码
	DX=0;//锁存段码
 }
 else
 {
 	while(n)//若该数不为0，则一位一位的显示
 	{	LEDDAT=0xff; //位码消影
		WX=1;//允许更新位码
		LEDDAT=t; //更新位码
		WX=0;//锁存位码
	   
		LEDDAT=0x00; //段码消影
		DX=1;//允许更新段码
		LEDDAT=table[n%10]; //更新段码
		DX=0;//锁存段码
	  		 	   
    	n=n/10;
		t=_cror_(t,1);
		delay_ms(3);
 	}
 }
}
void Print_str_LED(u8 *f)//输出数字串到数码管
{
 u8 t=0xdf,i;
 i=strlen(f);
 while(i)
 {	LEDDAT=0xff; //位码消影
	WX=1;//允许更新位码
	LEDDAT=t; //更新位码
	WX=0;//锁存位码
	   
	LEDDAT=0x00; //段码消影
	DX=1;//允许更新段码
	switch(f[i-1])
	{
	case '.':i--;LEDDAT=table[f[i-1]-'0']|0x80;break;
	case '-':LEDDAT=0x40;break;
	case ' ':LEDDAT=0x00;break;
	default:LEDDAT=table[f[i-1]-'0']; 
	} //更新段码
	DX=0;//锁存段码
	  		 	   
    i--;
	t=_cror_(t,1);
	delay_ms(3);
 }
 }

void Print_float_LED(float n,u8 x)//输出小数(有效数字不超过8位)到8位数码管，保留x(0-3)位小数
{
 u8 prtstr[12];
 switch(x)
 {
 case 0:sprintf(prtstr,"%.0f",n);break;
 case 1:sprintf(prtstr,"%.1f",n);break;
 case 2:sprintf(prtstr,"%.2f",n);break;
 case 3:sprintf(prtstr,"%.3f",n);break;
 } 
 Print_str_LED(prtstr);	
}

void Print_char(u8 n,u8 k)//在最低位显示键码
{
u8 temp;
temp=_cror_(0xdf,k-1);
LEDDAT=0XFF; 	 //位码消影
WX=1;		 //允许更新位码
LEDDAT=temp;	 //更新位码
WX=0;		//锁存位码

LEDDAT=0; 	 //段码消影
DX=1;	//允许更新段码
LEDDAT=table[n];//更新段码
DX=0;		//锁存段码
}

