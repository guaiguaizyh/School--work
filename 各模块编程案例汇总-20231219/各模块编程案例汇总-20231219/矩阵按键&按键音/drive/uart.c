#include <uart.h> 
u8 buf[10],i=0;
u8 flag=0;//接收命令标记，=1时表示接收完一条字符串命令
void uart_init(u16 bps)	 //串口初始化，@11.0592MHz，标准波特率：1200,2400,4800,9600
{ 
	u8 t;
	//串口的初始化
	SCON&=0x0f;
	SCON|=0x50;//双机通信，工作方式1：8位异步收发、波特率可变，允许接收数据
	PCON=PCON&0x7f;//SMOD=0
	TI=0;//软件清零，表示未发送完成
	ES=1;	//开串口中断
	
	//定时器T1的初始化
	TMOD&=0x0f;//T1设为方式2,8位自动装载模式
	TMOD|=0x20;  
	switch(bps)
	{
		case 1200:t=0xe8;break;
		case 2400:t=0xf4;break;
		case 4800:t=0xfa;break;
		case 9600:t=0xfd;break;
	}
	TH1=t;
	TL1=t;
	TR1=1;//开启T1
	
	EA=1;//开总中断
}
   
void uart_send_ch(u8 ch)
{
	ES=0;	//关串口中断
	SBUF=ch;
	while(TI==0);//等待发送完成
	TI=0;	 //清除中断标记
	ES=1;	//开串口中断
}

void uart_send_str(u8 *str)//输出字符串到串口
{
	ES=0;	//关串口中断	
	TI=1;
	printf("%s\n",str);
	while(!TI);
	TI=0;
	ES=1;	//开串口中断
}
void uart_rec() interrupt 4//接收以'#'开头且以'$'结尾的字符串，存放在buf数组中，接收结束时flag=1 
{
	u8 ch;
	if(RI==1)
	{
		RI=0;
		ch=SBUF;
		if(ch=='#')	i=0;
		else if(ch=='$') {buf[i]='\0'; flag=1;}
		     else {
			           buf[i]=ch;
					   i++;
				  }			
	}
}