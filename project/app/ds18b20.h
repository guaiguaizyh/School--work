#ifndef _DS18B20_H_
#define _DS18B20_H_

#include <config.h>

void Ds18b20_Tempchg();  //DS18B20 发送命令开始温度测量（测量并转换）
float Ds18b20_Gettemp(); //读取寄存器中存储的温度数据

#endif