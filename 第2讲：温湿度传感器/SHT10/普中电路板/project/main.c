//�����̻������е�Ƭ�������壬����12MHz
#include <config.h> 
#include <sht10.h> 

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
	u8  i,j,error=0;
	u16 Temp;//�¶Ȳ���ֵ
	u16 RHum;//ʪ�Ȳ���ֵ
	float VTemp=0;//�¶�����ֵ
	float VRHum=0;//ʪ������ֵ
	u8 Check;//У���
	u8 print[20];

//	uart_init(4800); //���ڳ�ʼ��		  12MHzʱ��������ȡ4800������С
//	LCD1602_Init( );
	
	Sht10_Reset(); //��������ʼ������������
	while(1)
 	{    
		error=0;

		error=Sht10_Measure(&Temp,&Check,0);//�����¶�
		error+=Sht10_Measure(&RHum,&Check,1);//����ʪ��
		 
		if(error!=0)  
				Sht10_Reset();//��������������
		else{
				Sht10_Convert(Temp,RHum,&VTemp,&VRHum);//û�г�����ת��Ϊ������
	
				sprintf(print,"Temp:%.1f;RHum:%.0f%%",VTemp,VRHum);
//	    		uart_send_str(print);//���������
//				LCD1602_disstr(print,0,0);//�����1602Һ����ʾ��
//				delay_ms(800); //��ʱ0.8�룬���⴫������������Ƶ������
				
				//�����6λ�����
				sprintf(print,"%3.0f%3.0f",VTemp,VRHum);
				for(i=50;i>0;i--) Print_str_LED(print);

				//�����12864  
		
			}							   
	}
}




 
