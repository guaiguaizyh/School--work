#include <config.h>
#include <1602.h>
void main()
{
   float y=15.387;
   u16 x=520;
   u8 buf[10];
   LCD1602_Init( );//1602��ʼ������
   LCD1602_disstr("hello world!",0,0);//��ʾ�ַ���
   sprintf(buf,"%u",x);//������ת�����ַ���
   LCD1602_disstr(buf,1,0);//��ʾ
   sprintf(buf,"%.2f",y); //��С��ת�����ַ���
   LCD1602_disstr(buf,1,8);//��ʾ
   while(1);
}