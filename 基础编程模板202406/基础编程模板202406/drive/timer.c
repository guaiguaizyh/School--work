#include <timer.h>
#define NUM (65536-50000) //ÿ��50ms�ж�һ�Σ�����12MHz
u8 x=0;
u8 count=0;
void Timer0_Int()//��ʱ��0��ʼ��
{
   	//���ù�����ʽ
	TMOD=TMOD&0xf0;
	TMOD=TMOD|0x01;	//T0����������ʱ����������ʽ1
	//���ü�����ֵ
	TH0=NUM/256;
	TL0=NUM%256;
	//������ʱ
	TR0=1;
	//�ж�����
	EA=1;//����CPU��Ӧ�ж�
	ET0=1;//����ʱ��T0�ж�
}
void Timer0() interrupt 1  //��ʱ��0�жϷ�����
{
	//��װ��ֵ
	TH0=NUM/256;
	TL0=NUM%256;
	count++;//ÿ��50ms�ж�һ��
	if(count==20) //�ж�20�μ�Ϊ1�룬ȥ����Ӧ�Ĵ���
	{
		count=0;
	//�ڴ˲����жϷ���������
		x++;
		if(x==9) x=0;
	}
}