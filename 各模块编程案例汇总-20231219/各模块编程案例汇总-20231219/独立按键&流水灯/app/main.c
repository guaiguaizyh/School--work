//ͨ����������ѯ��������ˮ�ƻ���
#include <config.h>
#include <led8.h>
#include <button.h>	
void main()
{
 	u8 mode=0; //��ˮ�ƻ���ģʽ
	while(1)
	{
		if(Btn_Press())//�������²��ͷ�	
		{
			Led_Ctrl(mode);	//������ˮ��
			mode++;
			if(mode==2) mode=0;	//�л�����ģʽ0��1			
		}		
	}
}