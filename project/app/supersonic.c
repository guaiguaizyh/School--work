#include <supersonic.h>
#define VELOCITY_30C	3495  //30���϶�ʱ�����٣�����V= 331.5 + 0.6*�¶ȣ��ٶ�������10���� 
#define VELOCITY_23C	3453  //23���϶�ʱ�����٣�����V= 331.5 + 0.6*�¶ȣ��ٶ�������10����

sbit ECHO = P2^0;  //�������ն˿�
sbit TRIG = P2^1;  //���������˿�

u8 count;

void Init_Timer0(void)//��ʱ��0��ʼ��
{
	TMOD = TMOD&0xf0;	 //��ʱ��0��ʼ��,����Ϊ��������ʽ1(16λ����ֵ)
	TMOD = TMOD|0x01;	 //��ʱ��0��ʼ��,����Ϊ��������ʽ1(16λ����ֵ)
 	TL0 = 0x66;
	TH0 = 0xfc;	 //��ʱ1ms
    EA = 1;		 //���ж�ʹ��
	ET0 = 1;	 //����ʱ��0 	
}

void Init_Supersonic()//��������������ʼ��
{
	 TRIG =0;
	 ECHO = 0;
	 count = 0;
	 Init_Timer0();
}

void Trig_SuperSonic()//��������
{
	 TRIG = 1;
	 delay_us(10); //��ʱ10΢��;
	 TRIG = 0;
}


u32 Measure_Distance()//������뺯��,����Ϊ����ֵ����λmm  
{
	u32 distance=0;    //�������
	u8 l;
	u16 h,y;


	Trig_SuperSonic(); //��������

	while(ECHO == 0);  //�ȴ�����
    
	TR0 = 1;
	while(ECHO);	
	TR0 = 0;

	l = TL0;
	h = TH0;
	y = (h << 8) + l;//������ֵת��Ϊ16λ
	y = y - 0xfc66;//us���֣�����1ms��ʱ��
	distance = y + 1000 * count;
	count = 0;
//������ʱ��(��λus)=����(count)ms+us(y)
	TL0 = 0x66;
	TH0 = 0xfc;
	delay_us(30);
	distance = VELOCITY_30C * distance / 20000;//���뵥λ�����MM
	return distance;
}

void timer0 () interrupt 1//T0�жϴ�����  
{
	TL0 = 0x66;
	TH0 = 0xfc;
	count++;
	if(count == 18)//�����������������18ms
	{
		TR0 =0;
		TL0 = 0x66;
		TH0 = 0xfc;
		count = 0;
	}
}