//���������·��
#include <config.h>
#include <ds18b20.h> 
 
#include <1602.h> 
//#include <uart.h>	
//#include <led.h>
//#include <ST7920.h> 
  

void delay_ms(u16 x)//������ʱ����
{u16 i,j;
 for(i=0;i<x;i++)
    for(j=0;j<115;j++);
}

void main()
{
	u8 i,j;
	float n;
	u8 print[18],print2[18];

//	uart_init(9600); //���ڳ�ʼ��
	LCD1602_Init( );//1602��ʼ��
//   ST7920_Init();	//12864(st7920)��ʼ��

	while(1)
 	{    
		Ds18b20_Tempchg();	//�����¶ȱ任
		n=Ds18b20_Gettemp();  //��ȡ�¶�

		sprintf(print,"Temp: %.1f",n);
//	    uart_send_str(print);//���������
		LCD1602_disstr(print,0,0);//�����1602Һ����ʾ��
		delay_ms(800);
			
//		for(i=50;i>0;i--) Print_float_LED(n,1);//����1λС���������6λ�����

//		�����12864
//		sprintf(print,"�¶ȣ�%.1f",n);	  
//      i=0;while(i<6){print2[i]=print[i];i++;}
//	    j=6;while(print[i]){print2[j]=0xa3;j++;print2[j]=print[i]+0x80;i++;j++;} print2[j]='\0';	 //���תȫ��
//	    ST7920_str(print2,0,0); delay_ms(800);   
				   
	}
}																 