#include <ds18b20.h> 

sbit ds=P2^2;     //温度传感器信号线 
  
void dsreset()    //18B20复位，初始化
{
  u16 i;
  ds=0;
  i=103;
  while(i>0)i--; //延时
  ds=1;
  i=4;
  while(i>0)i--;   //延时
}

bit tempreadbit()   //读1位数据
{
   u16 i;
   bit dat;
   ds=0;i++;          //i++ 起延时作用
   ds=1;i++;i++;
   dat=ds;
   i=8;while(i>0)i--;	//延时
   return(dat);
}

u8 tempread()   //读8位(1个字节)数据
{
  u8 i,j,dat;
  dat=0;
  for(i=1;i<=8;i++)
  {
    j=tempreadbit();
    dat=(j<<7)|(dat>>1);   //读出的数据最低位在最前面，这样刚好一个字节在DAT里
  }
  return(dat);
}

void tempwritebyte(u8 dat)   //向18B20写一个字节数据
{
  u16 i;
  u8 j;
  bit testb;
  for(j=1;j<=8;j++)
  {
    testb=dat&0x01;
    dat=dat>>1;
    if(testb)     //写 1
    {
      ds=0;
      i++;i++;	 //延时
      ds=1;
      i=8;while(i>0)i--;  //延时长
    }
    else
    {
      ds=0;       //写 0
      i=8;while(i>0)i--;   //延时长
      ds=1;
      i++;i++;			//延时
    }
  }
}

void Ds18b20_Tempchg()  //DS18B20 发送命令开始温度测量（测量并转换）
{
  dsreset();   //复位
  delay_ms(1);
  tempwritebyte(0xcc);  // 写跳过读ROM指令
  tempwritebyte(0x44);  // 写温度转换指令
}

float Ds18b20_Gettemp()  //读取寄存器中存储的温度数据
{
  u8 a,b;
  u16 t;
  int temp;
  float f_temp;
  dsreset();
  delay_ms(1);
  tempwritebyte(0xcc);// 写跳过读ROM指令
  tempwritebyte(0xbe);// 发读数据指令
  a=tempread();         //读低8位
  b=tempread();         //读高8位
  if(b&0x08) b=b|0xf0;
  t=b;
  t*=256;            //两个字节组合为1个字
  t=t|a;  							 
  temp=t;
  f_temp=temp*0.0625;      //温度在寄存器中为12位 分辨率位0.0625°
  return  f_temp; 
} 