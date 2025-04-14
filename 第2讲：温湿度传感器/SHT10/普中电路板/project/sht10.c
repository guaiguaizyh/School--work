#include <sht10.h>

#define	NOP5() {_nop_();_nop_();_nop_();_nop_();_nop_();}// 延时5微妙

//注意SCL、SDA要接上拉点电阻，实际使用时只能接天祥电路板上P0口，这时数码管、1602、12864都不能使用，只能将结果送串口
sbit SDA=P2^1; 
sbit SCL=P2^0; 

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

u8 SoftReset()//软件复位传感器，发命令复位传感器，状态寄存器的值也清空;传感器有应答返回0，无反应返回1
{	
    u8 error;
	Sht10_Reset();
	error=WriteByte(0x1e);//命令为：00011110
    return error;
}	

u8 ReadStatus(u8 *Status,u8 *Check)//读状态寄存器及校验，读成功返回0，不成功返回1
{	
    u8 error;
	Start();
	error=WriteByte(0x07);//发读寄存器命令：00000111
    *Status=ReadByte(0); //读状态寄存器并发应答
	*Check=ReadByte(1); //读校验，发非应答，结束通信
	return error;
}

u8 WriteStatus(u8 *Status)//写状态寄存器，写成功返回0，不成功返回值非0值
{	
    u8 error;
	Start();
	error=WriteByte(0x06);//发写寄存器命令：00000110
    error=error+WriteByte(*Status); //写状态寄存器
	return error;
}

u8 Sht10_Measure(u16 *Value,u8 *Check,u8 mode)//测量温度、湿度;(mode:0温度、1湿度)，成功返回0，不成功返回非0值
{	u8 error=0,VH,VL;
	u16  i;
	Start();//启动
    switch(mode)
	{case 0:error=WriteByte(0x03);break;//发温度测量命令：00000011
	 case 1:error=WriteByte(0x05);break;//发湿度测量命令：00000101	
	 default:break;
	}
	if(error > 0)
        return error;		  //发命令不成功，则退出，返回非0值
	
	for(i = 0; i < 65535; i++)
		if(SDA==0) break;//等待传感器测量完成，完成时传感器将SDA拉低
	if(i==65535)
	{	error++;
        return error;	   //等待传感器测量完成，不成功则退出，返回非0值
	}

	VH=ReadByte(0); //读第一个字节（MSB）并应答
	VL=ReadByte(0); //读第二个字节（LSB）并应答
	
	*Check=ReadByte(1); //读校验和，发非应答，结束通信
	*Value=VH*256+VL;  //通过指针形参返回测量值
	return error;	  //测量完成，返回0
}

void  Sht10_Convert(u16 Temp,u16 RHum,float *VTemp,float *VRHum)//将测量值转换为物理值
{
	float d1 = -40;
    float d2 = 0.01;

	float c1 = -4.0;
	float c2 = +0.0405;
	float c3 = -2.8E-6;   

	float t1 = +0.01;
	float t2 = +0.00008; 
//5V，14位，摄氏温度
	*VTemp = d1 + d2 * Temp;
//12位，相对湿度
	*VRHum=c1+c2*RHum+c3*RHum*RHum; //线性湿度
	*VRHum=*VRHum+(*VTemp-25)*(t1+t2*RHum); //修正湿度
	if( *VRHum > 100 ) *VRHum = 100;
    if( *VRHum < 0.01) *VRHum = 0.01;
}

