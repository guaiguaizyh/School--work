#ifndef __DS1302_H
#define __DS1302_H

#include <config.h>
//u8 SetTime[3]={23,57,50};//���Ҫ��ʼ����ʱ��ֵ
//u8 SetDate[4]={21,3,26,6};//���Ҫ��ʼ��������ֵ
//u8 GetTime[3];//��Ŷ�����ʱ��ֵ
//u8 GetDate[4];//��Ŷ���������ֵ

void SetRTCTime(u8 *SetTime);  //����ʱ�ӣ�SetTime�����δ�ŵ���Сʱ�����ӡ���ֵ����{23,59,50}����23:59:50
void SetRTCDate(u8 *SetDate); //�������ڣ�SetDate�����δ�ŵ����ꡢ�¡��ա����ڣ���{21,3,27,7}����21��3��27������7
void  ReadRTCTime(u8 * GetTime); //����ʱ��ֵ��ŵ�GetTime��
void  ReadRTCDate(u8 * GetDate); //��������ֵ��ŵ�GetDate��

#endif
