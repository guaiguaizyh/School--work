#include <intr.h>
u8 mode=0; //蜂鸣器工作模式
void INTR_Int()//外部中断初始化
{
	//设置外部中断触发方式
	IT0=1;//下降沿出发
	IT1=1;//下降沿出发
	//中断允许
	EA=1;//允许CPU响应中断
	EX0=1;//允许外部中断0
	EX1=1;//允许外部中断1
}
void Intr0() interrupt 0  //外部中断0中断服务函数
{
//在此补充中断服务函数代码
	mode++;
	if(mode==4) mode=0;//切换蜂鸣器工作模式：0-3
}
void Intr1() interrupt 2  //外部中断1中断服务函数
{
//在此补充中断服务函数代码
}
					    