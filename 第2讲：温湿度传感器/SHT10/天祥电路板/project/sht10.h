#ifndef _SHT10_H_
#define _SHT10_H_

#include <config.h>

void Sht10_Reset();//传感器复位，状态寄存器的值不变
u8 Sht10_Measure(u16 *Value,u8 *Check,u8 mode);//测量温度、湿度;(mode:0温度、1湿度)，成功返回0，不成功返回非0值
void  Sht10_Convert(u16 Temp,u16 RHum,float *VTemp,float *VRHum);//将测量值转换为物理值
#endif