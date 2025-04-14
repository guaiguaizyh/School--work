//基于天祥电路板
#include <config.h>
#include <ds18b20.h> 
 
#include <1602.h> 
//#include <uart.h>	
//#include <led.h>
//#include <ST7920.h> 
  

void delay_ms(u16 x)//毫秒延时函数
{u16 i,j;
 for(i=0;i<x;i++)
    for(j=0;j<115;j++);
}

void main()
{
	u8 i,j;
	float n;
	u8 print[18],print2[18];

//	uart_init(9600); //串口初始化
	LCD1602_Init( );//1602初始化
//   ST7920_Init();	//12864(st7920)初始化

	while(1)
 	{    
		Ds18b20_Tempchg();	//启动温度变换
		n=Ds18b20_Gettemp();  //读取温度

		sprintf(print,"Temp: %.1f",n);
//	    uart_send_str(print);//输出到串口
		LCD1602_disstr(print,0,0);//输出到1602液晶显示屏
		delay_ms(800);
			
//		for(i=50;i>0;i--) Print_float_LED(n,1);//保留1位小数，输出到6位数码管

//		输出到12864
//		sprintf(print,"温度：%.1f",n);	  
//      i=0;while(i<6){print2[i]=print[i];i++;}
//	    j=6;while(print[i]){print2[j]=0xa3;j++;print2[j]=print[i]+0x80;i++;j++;} print2[j]='\0';	 //半角转全角
//	    ST7920_str(print2,0,0); delay_ms(800);   
				   
	}
}																 