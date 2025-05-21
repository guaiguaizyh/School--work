#include <config.h>
#include <uart.h>
#include <1602.h>
void main()
{
	uart_init(9600);
	LCD1602_Init( );//1602初始化函数
	uart_send_str("12354");
	while(1)
	{
		if(flag==1) //接收以'#'开头且以'$'结尾的字符串，存放在buf数组中，接收结束时flag=1  
		{
			flag=0;
			LCD1602_disstr(buf,1,0);
		}	
	}		
}
