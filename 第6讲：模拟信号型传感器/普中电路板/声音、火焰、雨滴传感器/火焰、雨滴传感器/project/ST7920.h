//�ڵ���12864ST7920��غ���ǰ����Ҫ����ʼ��
#ifndef _ST7920_H_
#define _ST7920_H_

#include <config.h>

extern u8 row,col; //��ǰ�������λ������ �������ⲿ���������ⲿԴ�ļ�����
void ST7920_Init(void);//��ʼ������
void ST7920_pos(u8 X,u8 Y);//������ʾ����,X������(0-3),Y������(0-7)
void ST7920_str(u8 *p,u8 x,u8 y);//��ָ��λ�ÿ�ʼ��ʾ���ִ�(����������32)
void ST7920_word(u8 *p,u8 x,u8 y);//��ָ��λ����ʾһ������
void ST7920_Clear();//��������
void ST7920_del(u8 x,u8 y);//ɾ��ָ��λ���ϵĺ���
void ST7920_Clrline(u8 x);//���ָ���У����ҹ���Ƶ�����
void ST7920_Backspace();//����ɾ�����һ������
void ST7920_pow(u8 x);//��(1)��ر�(0)��ʾ
#endif