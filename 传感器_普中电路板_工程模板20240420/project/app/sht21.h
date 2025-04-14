#ifndef _SHT21_H
#define _SHT21_H

#include "iic.h"

u8 SHT21_measure(u8 cmd);//测温湿度，测温度，命令字为0xF3；测湿度，命令字为0xF5
#define TP   0xF3
#define RH   0xF5
//TP：测温度，命令字为0xF3
//RH：测湿度，命令字为0xF5

#endif