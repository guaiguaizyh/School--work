#include <led.h>

//数据线接口
#define LEDDAT P0

//通过译码器输出位选
sbit LSA=P2^2; 
sbit LSB=P2^3;
sbit LSC=P2^4; 

u8 code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,0x00}; //共阴数码管编码

void Print_u32_LED(u32 n)//输出6位无符号整数(0-99999999)到8位数码管,不足8位时，前面不显示
{u8 i;
 if(n==0) //若该数为0时直接显示0
 {
 	LSA=0;LSB=0;LSC=0; //位选

	LEDDAT=table[0]; //更新段码
	
	delay_ms(1); //间隔一段时间扫描	
	
	LEDDAT=0x00;//消隐
 }
 else
 {
 	i=0;
	while(n)//若该数不为0，则一位一位的显示
 	{	
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
			case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
			case(3):
				LSA=1;LSB=1;LSC=0; break;//显示第3位
			case(4):
				LSA=0;LSB=0;LSC=1; break;//显示第4位
			case(5):
				LSA=1;LSB=0;LSC=1; break;//显示第5位
			case(6):
				LSA=0;LSB=1;LSC=1; break;//显示第6位
			case(7):
				LSA=1;LSB=1;LSC=1; break;//显示第7位	
		}

		LEDDAT=table[n%10]; //更新段码
		
		delay_ms(1); //间隔一段时间扫描	
	
	    LEDDAT=0x00;//消隐
	  		 	   
    	n=n/10;
		i++;		
 	}
 }
}
void Print_str_LED(u8 *f)//输出数字串到数码管
{
 u8 i,n;
 n=strlen(f);
 for(i=0;i<n;i++)
 {	
 	switch(i)	 //位选，选择点亮的数码管，
	{
		case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
		case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
		case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
		case(3):
				LSA=1;LSB=1;LSC=0; break;//显示第3位
		case(4):
				LSA=0;LSB=0;LSC=1; break;//显示第4位
		case(5):
				LSA=1;LSB=0;LSC=1; break;//显示第5位
		case(6):
				LSA=0;LSB=1;LSC=1; break;//显示第6位
		case(7):
				LSA=1;LSB=1;LSC=1; break;//显示第7位	
	}
		
	switch(f[n-i-1])
	{
	case '.':n--;LEDDAT=table[f[n-i-1]-'0']|0x80;break;
	case '-':LEDDAT=0x40;break;
	case ' ':LEDDAT=0x00;break;
	default :LEDDAT=table[f[n-i-1]-'0']; 
	} 

	delay_ms(1); //间隔一段时间扫描	
	
	LEDDAT=0x00;//消隐
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

void Print_char(u8 n,u8 k)//在指定位置k显示键码n
{
    switch(k)	 //位选，选择点亮的数码管，
	{
		case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
		case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
		case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
		case(3):
				LSA=1;LSB=1;LSC=0; break;//显示第3位
		case(4):
				LSA=0;LSB=0;LSC=1; break;//显示第4位
		case(5):
				LSA=1;LSB=0;LSC=1; break;//显示第5位
		case(6):
				LSA=0;LSB=1;LSC=1; break;//显示第6位
		case(7):
				LSA=1;LSB=1;LSC=1; break;//显示第7位	
	}
    LEDDAT=table[n];//更新段码
	delay_ms(1); //间隔一段时间扫描	
	
	LEDDAT=0x00;//消隐
}

