//�ڵ���12864ST7920��غ���ǰ����Ҫ����ʼ��
#ifndef _ST7920_H_
#define _ST7920_H_

#include <config.h>
#include <delay.h>
extern u8 row,col; //��ǰ�������λ������ �������ⲿ���������ⲿԴ�ļ�����
void ST7920_Init(void);//��ʼ������
void ST7920_pos(u8 X,u8 Y);//������ʾ����,X������(0-3),Y������(0-7)
void ST7920_str(u8 *p,u8 x,u8 y);//��ָ��λ�ÿ�ʼ��ʾ���ִ�(����������32)
void ST7920_Clear();//��������
void ST7920_Picture(u8 *pPicture); //��ʾ��ͼ���ֱ���128*64��ͼƬ�������롢��λ��ǰ������
void num_hs_to_fs(u8 *half_str,u8 *full_str);//����������ַ���ת����ȫ�������ַ���
#endif