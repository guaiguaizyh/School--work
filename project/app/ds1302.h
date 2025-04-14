#ifndef __DS1302_H
#define __DS1302_H

#include <config.h>
//u8 SetTime[3]={23,57,50};//存放要初始化的时钟值
//u8 SetDate[4]={21,3,26,6};//存放要初始化的日期值
//u8 GetTime[3];//存放读出的时钟值
//u8 GetDate[4];//存放读出的日期值

void SetRTCTime(u8 *SetTime);  //设置时钟，SetTime中依次存放的是小时、分钟、秒值，如{23,59,50}，即23:59:50
void SetRTCDate(u8 *SetDate); //设置日期，SetDate中依次存放的是年、月、日、星期，如{21,3,27,7}，即21年3月27日星期7
void  ReadRTCTime(u8 * GetTime); //读出时钟值存放到GetTime中
void  ReadRTCDate(u8 * GetDate); //读出日期值存放到GetDate中

#endif
