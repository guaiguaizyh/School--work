//基于天祥电路板
#include <config.h>
#include <sht10.h> 
 
//#include <1602.h> 
//#include <uart.h>	
//#include <led.h>
#include <ST7920.h> 
  

void delay_ms(u16 x)//毫秒延时函数
{u16 i,j;
for(i=0;i<x;i++)
    for(j=0;j<115;j++);
}

void main()
{ 	
	u8  i,j,error=0;
	u16 Temp;//温度测量值
	u16 RHum;//湿度测量值
	float VTemp=0;//温度物理值
	float VRHum=0;//湿度物理值
	u8 Check;//校验和
	u8 print[20],print2[20];

//	uart_init(9600); //串口初始化
//	LCD1602_Init( );//1602初始化
    ST7920_Init();	//12864(st7920)初始化
	
	Sht10_Reset(); //传感器初始化，重置连接
	while(1)
 	{	
		error=0;

		error=Sht10_Measure(&Temp,&Check,0);//测量温度
		error+=Sht10_Measure(&RHum,&Check,1);//测量湿度
		 
		if(error!=0)  
				Sht10_Reset();//出错则重新连接
		else{	
				Sht10_Convert(Temp,RHum,&VTemp,&VRHum);//没有出错则转换为物理量
	
//				sprintf(print,"Temp:%.1f;RHum:%.0f%%",VTemp,VRHum);
//	    		uart_send_str(print);//输出到串口
//				LCD1602_disstr(print,0,0);//输出到1602液晶显示屏
//				delay_ms(800); //延时0.8秒，以免传感器工作过于频繁发热
				
				//输出到6位数码管
//				sprintf(print,"%3.0f%3.0f",VTemp,VRHum);
//				for(i=50;i>0;i--) Print_str_LED(print);

				//输出到12864
			 	 sprintf(print,"温度：%.0f",VTemp);
				 i=0;while(i<6){print2[i]=print[i];i++;}
				 j=6;while(print[i]){print2[j]=0xa3;j++;print2[j]=print[i]+0x80;i++;j++;} print2[j]='\0';	 //半角转全角
	    		 ST7920_str(print2,0,0); 
				 sprintf(print,"湿度：%.0f",VRHum);
				 i=0;while(i<6){print2[i]=print[i];i++;}
				 j=6;while(print[i]){print2[j]=0xa3;j++;print2[j]=print[i]+0x80;i++;j++;} print2[j]='\0';	 //半角转全角
	    		 ST7920_str(print2,1,0); 				 
				 delay_ms(800);   
				   
	        }
	}
}																 