#ifndef _SHT10_H_
#define _SHT10_H_

#include <config.h>

void Sht10_Reset();//��������λ��״̬�Ĵ�����ֵ����
u8 Sht10_Measure(u16 *Value,u8 *Check,u8 mode);//�����¶ȡ�ʪ��;(mode:0�¶ȡ�1ʪ��)���ɹ�����0�����ɹ����ط�0ֵ
void  Sht10_Convert(u16 Temp,u16 RHum,float *VTemp,float *VRHum);//������ֵת��Ϊ����ֵ
#endif