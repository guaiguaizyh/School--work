#include <config.h>	
#include <button.h>

sbit led = P2^1;

void main()
{
	led = 1;//�Ƶĳ�ʼ״̬Ϊ�ء�
	while(1){
		if(Btn_Press()){ //���˰�ť
			led = ~led;
		}
	}		
}




void main()
{
	while(1)
	{
		if(btn==0)
		{
			delay_ms(10);
			if(btn==0)
			{
				while(!btn);
			}
		}
	}
}