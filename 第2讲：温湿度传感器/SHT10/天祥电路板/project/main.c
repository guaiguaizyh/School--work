//���������·��
#include <config.h>
#include <sht10.h> 
 
//#include <1602.h> 
//#include <uart.h>	
//#include <led.h>
#include <ST7920.h> 
  

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
	u8 print[20],print2[20];

//	uart_init(9600); //���ڳ�ʼ��
//	LCD1602_Init( );//1602��ʼ��
    ST7920_Init();	//12864(st7920)��ʼ��
	
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
	
//				sprintf(print,"Temp:%.1f;RHum:%.0f%%",VTemp,VRHum);
//	    		uart_send_str(print);//���������
//				LCD1602_disstr(print,0,0);//�����1602Һ����ʾ��
//				delay_ms(800); //��ʱ0.8�룬���⴫������������Ƶ������
				
				//�����6λ�����
//				sprintf(print,"%3.0f%3.0f",VTemp,VRHum);
//				for(i=50;i>0;i--) Print_str_LED(print);

				//�����12864
			 	 sprintf(print,"�¶ȣ�%.0f",VTemp);
				 i=0;while(i<6){print2[i]=print[i];i++;}
				 j=6;while(print[i]){print2[j]=0xa3;j++;print2[j]=print[i]+0x80;i++;j++;} print2[j]='\0';	 //���תȫ��
	    		 ST7920_str(print2,0,0); 
				 sprintf(print,"ʪ�ȣ�%.0f",VRHum);
				 i=0;while(i<6){print2[i]=print[i];i++;}
				 j=6;while(print[i]){print2[j]=0xa3;j++;print2[j]=print[i]+0x80;i++;j++;} print2[j]='\0';	 //���תȫ��
	    		 ST7920_str(print2,1,0); 				 
				 delay_ms(800);   
				   
	        }
	}
}																 