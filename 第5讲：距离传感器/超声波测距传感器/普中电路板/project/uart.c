#include <uart.h> 

void uart_init(u16 bps)
{ u8 t;
  SCON=0x50;//������ʽһ��8λ�첽�շ��������ʿɱ䣬�����������
  PCON=0x80;//11.0592MHzʱ��SMOD=0��PCON=0x80;     12MHzʱ��SMOD=1��PCON=0x80; 
  TI=0;//������㣬��ʾδ�������
  EA=1;//�����ж�
  ES=1;	//�������ж�
  TMOD&=0x0f;//T1��Ϊ��ʽ2,8λ�Զ�װ��ģʽ
  TMOD|=0x20;  
  switch(bps)
  { case 1200:t=0xe8;break;
    case 2400:t=0xf4;break;
    case 4800:t=0xf3;break;	//11.0592MHzʱ��t=0xfa��������Ϊ4800;     12MHzʱ��t=0xf3��������Ϊ4800����ʱ����С0.16% 
    case 9600:t=0xfd;break;
  }
  TH1=t;
  TL1=t;
  TR1=1;//����T1
}
   
void uart_send_ch(u8 ch)
{
  ES=0;	//�ش����ж�
  SBUF=ch;
  while(TI==0);//�ȴ��������
  TI=0;	 //����жϱ��
  ES=1;	//�������ж�
}

void uart_send_str(u8 *str)//����ַ���������
{
	TI=1;
	printf("%s\n",str);
	while(!TI);
	TI=0;
}