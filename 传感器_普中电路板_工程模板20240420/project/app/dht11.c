#include "dht11.h"



void DHT11_start()//启动
{
   Data=1;
   delay_us(2);
   Data=0;
   delay_ms(20);   //延时18ms以上
   Data=1;
   delay_us(30);
}

u8 DHT11_rec_byte()      //接收一个字节
{
  u8 i,dat=0;
  for(i=0;i<8;i++)    //从高到低依次接收8位数据
   {          
      while(!Data);   ////等待50us低电平过去
      delay_us(8);     //延时60us，如果还为高则数据为1，否则为0 
      dat<<=1;           //移位使正确接收8位数据，数据为0时直接移位
      if(Data==1)    //数据为1时，使dat加1来接收数据1
         dat+=1;
      while(Data);  //等待数据线拉低    
    }  
    return dat;
}

void DHT11_receive(u8 *RHum,u8 *Temp) //读取测量数据，并校验，然后将温湿度值返回到形参中
{
    u8 R_H,R_L,T_H,T_L,revise; 
    DHT11_start();
		EA=0;
    if(Data==0)
    {
        while(Data==0);   //等待拉高     
        delay_us(40);  //拉高后延时80us
        R_H=DHT11_rec_byte();    //接收湿度高八位  
        R_L=DHT11_rec_byte();    //接收湿度低八位  
        T_H=DHT11_rec_byte();    //接收温度高八位  
        T_L=DHT11_rec_byte();    //接收温度低八位
        revise=DHT11_rec_byte(); //接收校正位

        delay_us(25);    //结束

        if((R_H+R_L+T_H+T_L)==revise)      //校正
        {
            *RHum=R_H;            
            *Temp=T_H;             
        }        
    }
		EA=1;
}
