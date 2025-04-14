#include <uart.h> 

void uart_init(u16 bps)	 //���ڳ�ʼ����@11.0592MHz����׼�����ʣ�1200,2400,4800,9600
{ 
	u8 t;
	//���ڵĳ�ʼ��
	SCON&=0x0f;
	SCON|=0x50;//˫��ͨ�ţ�������ʽ1��8λ�첽�շ��������ʿɱ䣬�����������
	PCON=PCON&0x7f;//SMOD=0��SMOD=1��PCON=PCON|0x80;
	TI=0;//������㣬��ʾδ�������
	ES=1;	//�������ж�
	
	//��ʱ��T1�ĳ�ʼ��
	TMOD&=0x0f;//T1��Ϊ��ʽ2,8λ�Զ�װ��ģʽ
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
	TR1=1;//����T1
	
	EA=1;//�����ж�
}

void uart_init_4800()	 //���ڳ�ʼ����@12MHz��������Ϊ4800ʱ�����С0.16%
{ 
	//���ڵĳ�ʼ��
	SCON&=0x0f;
	SCON|=0x50;//˫��ͨ�ţ�������ʽ1��8λ�첽�շ��������ʿɱ䣬�����������
	PCON=PCON|0x80;//SMOD=1
	TI=0;//������㣬��ʾδ�������
	ES=1;	//�������ж�
	
	//��ʱ��T1�ĳ�ʼ��
	TMOD&=0x0f;//T1��Ϊ��ʽ2,8λ�Զ�װ��ģʽ
	TMOD|=0x20;  
	TH1=0xf3;
	TL1=0xf3;
	TR1=1;//����T1
	
	EA=1;//�����ж�
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
	ES=0;	//�ش����ж�	
	TI=1;
	printf("%s\n",str);
	while(!TI);
	TI=0;
	ES=1;	//�������ж�
}