///*
//4*4���󰴼�
#include <config.h>
#include <1602.h>
#include <key4x4.h>
#include <beep.h>
void main()
{
   u8 key;
   LCD1602_Init( );//1602��ʼ������
   while(1)
   {
		key=key_scan_4X4( );//ɨ�谴��
		if(key!=16)//�м�����
		{
		 	beep_on(100,500);//����������
		 	LCD1602_disch(keyval_4X4[key]);//��ʾ������Ӧ���ַ�		
		}
   }
} 
//*/

/*
//4*3���󰴼�
#include <config.h>
#include <1602.h>
#include <key4x4.h>
void main()
{
   u8 key;
   LCD1602_Init( );//1602��ʼ������
   while(1)
   {
		key=key_scan_4X3( );//ɨ�谴��
		if(key!=12)//�м�����
		{
		 	LCD1602_disch(keyval_4X3[key]);//��ʾ������Ӧ���ַ�		
		}
   }
}
*/