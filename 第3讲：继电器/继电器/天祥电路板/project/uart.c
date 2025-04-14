#include <uart.h> 

void uart_init(u16 bps)
{ u8 t;
  SCON=0x50;//工作方式一：8位异步收发，波特率可变，允许接收数据
  PCON=0x00;//SMOD=0
  TI=0;//软件清零，表示未发送完成
  EA=1;//开总中断
  ES=1;	//开串口中断
  TMOD&=0x0f;//T1设为方式2,8位自动装载模式
  TMOD|=0x20;  
  switch(bps)
  { case 1200:t=0xe8;break;
    case 2400:t=0xf4;break;
    case 4800:t=0xfa;break;
    case 9600:t=0xfd;break;
  }
  TH1=t;
  TL1=t;
  TR1=1;//开启T1
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
	TI=1;
	printf("%s\n",str);
	while(!TI);
	TI=0;
}