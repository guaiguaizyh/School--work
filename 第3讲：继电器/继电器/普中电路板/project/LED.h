#ifndef _LED_H_
#define _LED_H_


#include <config.h>	

void Print_u32_LED(u32 n);//���6λ�޷�������(0-99999999)��8λ�����,����8λʱ��ǰ�治��ʾ
void Print_float_LED(float n,u8 x);//�����С��(��Ч���ֲ�����8λ)��8λ����ܣ�����x(0-3)λС��
void Print_char(u8 n,u8 k);//��ָ��λ��k��ʾ����n
void Print_str_LED(u8 *f);//������ִ��������

#endif