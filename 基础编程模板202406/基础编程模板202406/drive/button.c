#include <button.h>
					  
sbit btn=P2^4;
bit Btn_Down()//�������·���1�����򷵻�0
{
	if(btn==0)//��ⰴ���Ƿ񱻰���
	{
	 	delay_ms(10); //��ʱȥ��
		if(btn==0) //ȷ�ϰ�������
			return 1;				
	}
	return 0;
}
bit Btn_Press()//�������º��ͷŷ���1�����򷵻�0
{
	if(btn==0)//��ⰴ���Ƿ񱻰���
	{
	 	delay_ms(10); //��ʱȥ��
		if(btn==0) //ȷ�ϰ�������
		{	
			while(!btn);
			return 1;	
		}				
	}
	return 0;
}