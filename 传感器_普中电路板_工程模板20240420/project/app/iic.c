#include "iic.h"



static void I2C_Delay(unsigned char n)//I2C总线内部延时函数
{
    do
    {
        _nop_();		//此处有修改只保留一个nop操作
    }
    while(n--);		
}
void I2CStart(void)//I2C总线启动信号
{
  sda = 1;
  scl = 1;
	I2C_Delay(DELAY_TIME);
  sda = 0;
	I2C_Delay(DELAY_TIME);
  scl = 0;    
}

void I2CStop(void)//I2C总线停止信号
{
  sda = 0;
  scl = 1;
	I2C_Delay(DELAY_TIME);
  sda = 1;
	I2C_Delay(DELAY_TIME);
}

void I2CSendAck(unsigned char ackbit)//发送应答或非应答信号
{
  scl = 0;
  sda = ackbit; 
	I2C_Delay(DELAY_TIME);
  scl = 1;
	I2C_Delay(DELAY_TIME);
  scl = 0; 
	sda = 1;
	I2C_Delay(DELAY_TIME);
}

unsigned char I2CWaitAck(void) //等待应答
{
	unsigned char ackbit;
	
  scl = 1;
	I2C_Delay(DELAY_TIME);
  ackbit = sda; 
  scl = 0;
	I2C_Delay(DELAY_TIME);
	
	return ackbit;
}

void I2CSendByte(unsigned char byt)//I2C总线发送一个字节数据
{
    unsigned char i;
	
    for(i=0; i<8; i++)
		{
        scl = 0;
				I2C_Delay(DELAY_TIME);
        if(byt & 0x80)
				{
            sda = 1;
        }
        else
				{
            sda = 0;
        }
				I2C_Delay(DELAY_TIME);
				scl = 1;
				byt <<= 1;
				I2C_Delay(DELAY_TIME);
    }	
    scl = 0;  
}
unsigned char I2CReceiveByte(void)//I2C总线接收一个字节数据
{
	unsigned char da;
	unsigned char i;
	for(i=0;i<8;i++)
	{   
		scl = 1;
		I2C_Delay(DELAY_TIME);
		da <<= 1;
		if(sda) da |= 0x01;
		scl = 0;
		I2C_Delay(DELAY_TIME);
	}
	return da;    
}