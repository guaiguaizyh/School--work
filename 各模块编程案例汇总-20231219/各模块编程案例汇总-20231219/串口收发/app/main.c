#include <config.h>
#include <uart.h>
#include <1602.h>
void main()
{
	uart_init(9600);
	LCD1602_Init( );//1602��ʼ������
	uart_send_str("12354");
	while(1)
	{
		if(flag==1) //������'#'��ͷ����'$'��β���ַ����������buf�����У����ս���ʱflag=1  
		{
			flag=0;
			LCD1602_disstr(buf,1,0);
		}	
	}		
}
