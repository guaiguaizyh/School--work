//本工程基于普中单片机开发板，晶振12MHz
#include <config.h> 
#include <ds18b20.h> 

//#include <uart.h>
//#include <1602.h>
#include <led.h> 

void delay_ms(u16 x)//毫秒延时函数
{u16 i,j;
for(i=0;i<x;i++)
    for(j=0;j<115;j++);
}

void main()
{
	u8 i;
	float n;
	u8 print[10];

//	uart_init(4800); //串口初始化		  12MHz时，波特率取4800，误差较小
//	LCD1602_Init( );
	
	while(1)
 	{    
		Ds18b20_Tempchg();	//启动温度变换
		n=Ds18b20_Gettemp();  //读取温度
//		sprintf(print,"Temp: %.1f",n);
//	    uart_send_str(print);//输出到串口
//  	LCD1602_disstr(print,0,0);//输出到1602液晶显示屏
//		delay_ms(800);
		
		sprintf(print,"%.1f",n);
        for(i=0;i<50;i++)
            Print_str_LED(print);//输出数字串到数码管//输出到数码管					   
	}
}




 
