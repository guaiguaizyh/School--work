#include <24C02.h> 

u8 WriteRom(u8 addr, u8 dat)	//向AT24Cxx中指定地址单元写入数据，addr存储单元地址，dat写入的数据，写入成功返回1，否则返回0
{  
   u8 i=4,ack;//i为允许最大重写次数，若出现i次操作失效后，则函数中止操作，并返回
   while(--i)
   {
      I2C_Start();              //启动总线
      ack=I2C_SendByte(AddWrC);   //发送器件地址+写
      if(ack==0) continue;		//无应答则重新开始 
      ack=I2C_SendByte(addr);   //发送存储单元地址
      if(ack==0) continue;		//无应答则重新开始 
      ack=I2C_SendByte(dat);   //写入数据
      if(ack==0) continue;		//无应答则重新开始 
      break; //写入成功则结束
   }
   I2C_Stop();         //结束总线
   delay_ms(4);	       //1个字节的写入周期为1ms, 最好延时1ms以上
   if(i>0) return 1;
   else    return 0;      
}

u8 ReadRom(u8 addr)//从AT24Cxx中指定地址单元读取数据，addr存储单元地址，写入成功返回1，否则返回0
{ 
  u8 i=4,dat,ack;//i为允许最大重读次数，若出现i次操作失效后，则函数中止操作，并返回
  while(--i)
  {	
      I2C_Start();              //启动总线
      ack=I2C_SendByte(AddWrC);   //发送器件地址+写
      if(ack==0) continue;		//无应答则重新开始 
      ack=I2C_SendByte(addr);   //发送存储单元地址
	  if(ack==0) continue;		//无应答则重新开始 
	  
	  I2C_Start();              //重启总线
      ack=I2C_SendByte(AddWrC+1);   //发送器件地址+读
	  if(ack==0) continue;		//无应答则重新开始 
      dat=I2C_RcvByte();      //读取指定地址单元里的数据

      I2C_Ack(1);           //发送非应答信号，结束数据传输
      break;
  } 
   I2C_Stop();           //结束总线
   if(i>0) return dat;
   else    return 0; 
}