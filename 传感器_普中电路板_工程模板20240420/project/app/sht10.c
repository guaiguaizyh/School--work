#include "sht10.h"

#define	NOP5() {_nop_();_nop_();_nop_();_nop_();_nop_();}// 延时5微妙

void Start()//启动传输
{
	SDA = 1;    
  SCL = 0;    //初始状态
	_nop_();
	SCL = 1;    
	_nop_();
	SDA = 0;    
	_nop_();
	SCL = 0;    
	NOP5();
	SCL = 1;     
    _nop_();
	SDA = 1;
	_nop_();
	SCL = 0;
} 

void Sht10_Reset()//传感器复位，状态寄存器的值不变
{	
	u8 i;
	SDA = 1;    
  SCL = 0;    //初始状态
	for(i = 0; i < 9; i++)
	{	SCL = 1;
		SCL = 0;
	} 
	Start();//发启动传输信号
}

u8 WriteByte(u8 SendByte)//写入一个字节并读取应答,返回值为0表示确认，为1表示没有确认
{
	u8 i,error;
	for(i = 0; i < 8; i++)//循环写入8位命令，先写高位
	{
    	SendByte<<=1;
      SDA=CY; 
      SCL = 1;      
   	  NOP5();                 
	    SCL = 0;
	 }
	SDA = 1;//释放SDA，让传感器发应答
	SCL=1;
	error=SDA;//SHT拉低SDA表示测量结束
	SCL=0;
	return error; 
}

u8 ReadByte(u8 Ack) //读取一个字节并发送应答（Ack为0表示应答，为1表示不应答），返回接收到的字节
{
	u8 i,recbyte=0;
	SDA=1;//释放总线，让传感器发数据
	for(i = 0; i < 8; i++)//循环写入8位命令，先写高位
	{
    SCL=1;
		NOP5();
		recbyte=(recbyte<<1)|SDA;
	  SCL = 0;
	 }
	SDA = Ack;//主机向传感器发应答
	SCL=1;
	NOP5();
	SCL=0;
	SDA=1;//释放总线，让传感器继续发数据
	return recbyte; 
}
u8 sht10_measure(u8 cmd)//测温湿度，测温度，命令字为0xF5(TP)；测湿度，命令字为0xF3(RH)
{
	u8 datH,datL;
	u16 date=0;
	
	Sht10_Reset(); //传感器初始化，重置连接
  WriteByte(0x1e);//软件复位传感器，状态寄存器的值也清空，命令为：00011110
	
	Start();//启动	
	WriteByte(cmd);//发测量命令
	delay_ms(400);//等待传感器测量完成，完成时传感器将SDA拉低
	
	datH=ReadByte(0); //读第一个字节（MSB）并应答
	datL=ReadByte(1); //读第二个字节（LSB）发非应答	
	date=datH<<8|datL;  //组合成14/12位数据

	if(cmd==TEMP) //温度转换 
			date=date*0.01-40; 
	
	if(cmd==RHUM) //湿度转换
	{ 
		date=0.0405*date-(2.8E-6)*date*date-4;  
		if(date > 100 ) date = 100;
	}		
	return  date;
}