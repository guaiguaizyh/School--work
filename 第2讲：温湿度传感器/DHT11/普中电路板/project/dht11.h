#ifndef _DHT11_H_
#define _DHT11_H_

#include <config.h>

void DHT11_receive(u8 *RHum,u8 *Temp);//读取测量数据，并校验，然后将温湿度值返回到形参中

#endif