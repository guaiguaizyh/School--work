#ifndef _AT24C02_H
#define _AT24C02_H

#include "iic.h"
u8 ROM_read(u8 address);//读at24c02
void ROM_write(u8 address,u8 dat);//写at24c02

#endif