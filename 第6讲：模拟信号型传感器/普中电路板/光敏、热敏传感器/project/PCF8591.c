#include <PCF8591.h> 

u8 D[32];

u8 Pcf8591_DA(u8 Val)//数字转模拟，val为数字信号值，转换成功返回1，否则返回0
{
   u8 ack;
   I2C_Start();              //启动总线
   ack=I2C_SendByte(AddWr);   //发送器件地址+写
   if(ack==0)return(0);		//无应答则结束
   ack=I2C_SendByte(0x40);   //使能数字转换模拟
   if(ack==0)return(0);		  //无应答则结束
   ack=I2C_SendByte(Val);     //发送数字信号值  
   if(ack==0)return(0);		  //无应答则结束
   I2C_Stop();               //结束总线
   return(1);
}

u8 Pcf8591_AD(u8 channel)//模拟转数字，channel为模拟信号通道号(0-3)，转换成功则返回数字值，否则返回0
{
   u8 ack,dat;
   //启动转换
   I2C_Start();            //启动总线
   ack=I2C_SendByte(AddWr);            //发送器件地址 +写
   if(ack==0)return(0);		  //无应答则结束
   ack=I2C_SendByte(channel);   //发送通道选择控制字
   if(ack==0)return(0);	   //无应答则结束
   I2C_Stop();             //结束总线

   //读取转换值
   I2C_Start();         //启动总线
   ack=I2C_SendByte(AddWr+1);     //发送器件地址 +读
   if(ack==0)return(0);	   //无应答则结束
   dat=I2C_RcvByte();      //读取转换数字值

   I2C_Ack(1);           //发送非应答信号
   I2C_Stop();           //结束总线
   return(dat);
}
 