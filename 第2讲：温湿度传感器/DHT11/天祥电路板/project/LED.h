#ifndef _LED_H_
#define _LED_H_


#include <config.h>	

void Print_u32_LED(u32 n);//����޷�������(0-999999)��6λ�����,����6λʱ��ǰ�治��ʾ
void Print_float_LED(float n,u8 x);//���С��(��Ч���ֲ�����6λ)��6λ����ܣ�����x(0-3)λС��
void Print_str_LED(u8 *str);//������ִ��������
void Print_char(u8 n,u8 k);//��ָ��λ��k��ʾ����n

#endif