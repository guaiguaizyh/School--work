//ͨ���������жϣ����Ʒ�������������������
#include <config.h>
#include <beep.h>
#include <intr.h>
void main()
{
	INTR_Int();
	while(1)
	{
		switch(mode)//����������ģʽ��0-���졢1-������2-���š����տ��֡���3-���š���ֻ�ϻ���
		{
			case 0:break;
			case 1:alarm();break;//����
			case 2:playmusic(Music2Meter,Music2TONE,Music2Len); break;//���š����տ��֡�
			case 3:playmusic(Music1Meter,Music1TONE,Music1Len); break;//���š���ֻ�ϻ���
		}
	}
}