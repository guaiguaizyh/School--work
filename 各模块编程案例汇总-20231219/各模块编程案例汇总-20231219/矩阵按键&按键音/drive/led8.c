#include <led8.h>
#define LED_Data P1 //�궨��8��LED�Ƶ�����
/**********************************************LED��ˮ��**************************************************/
void Led_Ctrl(u8 mode)//��ͬ��������ˮ��
//mode=0(������������������)��1(������������������)
//mode=2(����2����������������)��3(����2����������������)
//mode=4(8�������������������)��5(8�������������������)
//mode=6(���������м䣬ÿ����2����)��7(���м��������������ÿ����2����)
//mode=8(���������м������)��9(���������м������)
{
	u8 temp,i,th,tl;
	switch(mode)
	{
		case 0:temp=0x7f;
			   for(i=0;i<8;i++)
			   {
				   LED_Data=temp;
				   temp=_cror_(temp,1);
				   delay_ms(300);
			   }
			   break;
		case 1:temp=0xfe;
			   for(i=0;i<8;i++)
			   {
				   LED_Data=temp;
				   temp=_crol_(temp,1);
				   delay_ms(300);
			   }
			   break;
		case 2:
			   break;
		case 3:
			   break;
		case 4:
			   break;
		case 5:
			   break;
		case 6:
			   break;
		case 7:
			   break;
		case 8:
			   break;
		case 9:
			   break;
	}
	LED_Data=0xff;
}