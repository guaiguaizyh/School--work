//�������ʾ������С��
#include <config.h>
#include <smg8.h>
void main()
{
   float x=520.1358;
   u16 y=1314;
   u8 buf[10];//���������ַ���
   while(1)
   {
		//������ת�����ַ���
 		sprintf(buf,"%.2f",x); //�������ʾС��������2λС��
//		sprintf(buf,"%9.2f",x);//�Ҷ�����ʾС��������2λС��
//		sprintf(buf,"%u",y);   //�������ʾ����
//		sprintf(buf,"%8u",y);  //�Ҷ�����ʾ����

		smg_dis_str(buf);//��ʾ�����ַ���
   }
}