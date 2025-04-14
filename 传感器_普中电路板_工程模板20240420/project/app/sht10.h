#ifndef _SHT10_H_
#define _SHT10_H_

#include "config.h"

sbit SDA=P2^0; 
sbit SCL=P2^1; 
u8 sht10_measure(u8 cmd);//测温湿度，测温度，命令字为0x03；测湿度，命令字为0x05
#define TEMP   0x03
#define RHUM   0x05
//TEMP：测温度，命令字为0x03
//RHUM：测湿度，命令字为0x05

#endif