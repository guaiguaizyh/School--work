#ifndef _BEEP_H_
#define _BEEP_H_


#include <config.h>

void beep_on(u16 n,u16 f);//�������죺Ƶ��f����λHz����������ʱ��n����λ����	
void alarm();//����������2�ֲ�ͬƵ�ʵ�������0.5�룬����������
void playmusic(u8 *Meter,u8 *TONE,u8 n);//���Ÿ�����*Meterָ������Ľ������飬*TONEָ��������������飬nΪ�����������ĸ���

#endif