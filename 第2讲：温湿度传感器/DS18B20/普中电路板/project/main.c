//�����̻������е�Ƭ�������壬����12MHz
#include <config.h> 
#include <ds18b20.h> 

//#include <uart.h>
//#include <1602.h>
#include <led.h> 

void delay_ms(u16 x)//������ʱ����
{u16 i,j;
for(i=0;i<x;i++)
    for(j=0;j<115;j++);
}

void main()
{
	u8 i;
	float n;
	u8 print[10];

//	uart_init(4800); //���ڳ�ʼ��		  12MHzʱ��������ȡ4800������С
//	LCD1602_Init( );
	
	while(1)
 	{    
		Ds18b20_Tempchg();	//�����¶ȱ任
		n=Ds18b20_Gettemp();  //��ȡ�¶�
//		sprintf(print,"Temp: %.1f",n);
//	    uart_send_str(print);//���������
//  	LCD1602_disstr(print,0,0);//�����1602Һ����ʾ��
//		delay_ms(800);
		
		sprintf(print,"%.1f",n);
        for(i=0;i<50;i++)
            Print_str_LED(print);//������ִ��������//����������					   
	}
}




 
