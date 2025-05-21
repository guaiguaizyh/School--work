#include <I2C.h> 

void I2C_Start() //启动I2C总线  
{
  sda=1;         /*发送起始条件的数据信号*/
  _nop_();
  scl=1;
  _nop_();        /*起始条件建立时间大于4.7us,延时*/
  _nop_();
  _nop_();
  _nop_();
  _nop_();    
  sda=0;         /*发送起始信号*/
  _nop_();        /* 起始条件锁定时间大于4μs*/
  _nop_();
  _nop_();
  _nop_();
  _nop_();       
  scl=0;       /*钳住I2C总线，准备发送或接收数据 */
  _nop_();
  _nop_();
}

void I2C_Stop()	//停止(结束)I2C总线
{
  sda=0;      /*发送结束条件的数据信号*/
  _nop_();    /*发送结束条件的时钟信号*/
  scl=1;      /*结束条件建立时间大于4μs*/
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  sda=1;      /*发送I2C总线结束信号*/
  _nop_();
  _nop_();
  _nop_();
  _nop_();
}

u8  I2C_SendByte(u8 c)//发送1个字节数据，从机应答返回1，从机不应答返回0  
{
 u8  i,ack;
 for(i=0;i<8;i++)  /*要传送的数据长度为8位*/
    {
     if((c<<i)&0x80)sda=1;   /*判断发送位*/
       else  sda=0;                
     _nop_();
     scl=1;               /*置时钟线为高，通知被控器开始接收数据位*/
      _nop_(); 
      _nop_();             /*保证时钟高电平周期大于4μs*/
      _nop_();
      _nop_();
      _nop_();         
     scl=0; 
    }
    
    _nop_();
    _nop_();
    sda=1;                /*8位发送完后释放数据线，准备接收应答位*/
    _nop_();
    _nop_();   
    scl=1;
    _nop_();
    _nop_();
    _nop_();
    if(sda==1)ack=0;     
       else ack=1;        /*判断是否接收到应答信号*/
    scl=0;
    _nop_();
    _nop_();
	return ack;
}
 
u8 I2C_RcvByte()//接收1个字节数据
{
  u8 retc=0,i; 
  sda=1;                     /*置数据线为输入方式*/
  for(i=0;i<8;i++)
      {
        _nop_();           
        scl=0;                  /*置时钟线为低，准备接收数据位*/
        _nop_();
        _nop_();                 /*时钟低电平周期大于4.7μs*/
        _nop_();
        _nop_();
        _nop_();
        scl=1;                  /*置时钟线为高使数据线上数据有效*/
        _nop_();
        _nop_();
        retc=retc<<1;
        if(sda==1)retc=retc+1;  /*读数据位,接收的数据位放入retc中 */
        _nop_();
        _nop_(); 
      }
  scl=0;    
  _nop_();
  _nop_();
  return(retc);
}

void I2C_Ack(bit a)	// 发送应答或非应答信号(a=0:应答，a=1:非应答)
{  
  if(a==0)sda=0;              /*在此发出应答或非应答信号 */
  else sda=1;				  /*0为发出应答，1为非应答信号 */
  _nop_();
  _nop_();
  _nop_();      
  scl=1;
  _nop_();
  _nop_();                    /*时钟低电平周期大于4μs*/
  _nop_();
  _nop_();
  _nop_();  
  scl=0;                     /*清时钟线，住I2C总线以便继续接收*/
  _nop_();
  _nop_();    
}