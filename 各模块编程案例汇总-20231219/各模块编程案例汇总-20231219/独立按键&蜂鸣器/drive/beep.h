#ifndef _BEEP_H_

	#define	_BEEP_H_
	#include <config.h>
	#include <delay.h>
	extern u8 code Music1TONE[];//��������ֻ�ϻ���������
	extern u8 code Music1Meter[];//��������ֻ�ϻ����Ľ���
	extern u8 code Music1Len;//��������ֻ�ϻ�������������
	extern u8 code Music2TONE[];//������ף�����տ��֡�������
	extern u8 code Music2Meter[];//������ף�����տ��֡��Ľ���
	extern u8 code Music2Len;//������ף�����տ��֡�����������

	void alarm();//����������2�ֲ�ͬƵ�ʵ�����������������
	void playmusic(u8 *Meter,u8 *TONE,u8 n);//���Ÿ�����*Meterָ������Ľ������飬*TONEָ��������������飬nΪ�����������ĸ���
	void beep_on(u16 n,u16 f);//�������죺Ƶ��f����λHz����������ʱ��n����λ����
#endif 