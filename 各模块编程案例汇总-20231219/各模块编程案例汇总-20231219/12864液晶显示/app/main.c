#include <config.h>	
#include <ST7920.h>
void main()
{
   u8 buf1[9],buf2[17];
   float y=15.387;
   u16 x=520;

   ST7920_Init();//��ʼ������
   ST7920_str("��������",0,0);//��ʾ����
   
   sprintf(buf1,"%u",x);//������ת�����ַ���
   num_hs_to_fs(buf1,buf2);//��������ִ�ת����ȫ�����ִ�
   ST7920_str(buf2,1,0);//��ʾ
   
   sprintf(buf1,"%.2f",y); //��С��ת�����ַ���
   num_hs_to_fs(buf1,buf2);//��������ִ�ת����ȫ�����ִ�
   ST7920_str(buf2,2,0);//��ʾ
   while(1);   
 
}