/******************************包含头文件*******************************/
#include <config.h>
#include <ds18b20.h>
#include <smg.h>
sbit buzzer=P2^5;

sbit Led=P2^0;
float temp=0;
u16 count_1000ms=0;
u8 count_200ms=0;
bit flag=1;
/***********************************主函数***********************************/
void timer0_init()//定时器T0定时1毫秒@12.000MHz
{
    TMOD&= 0xF0;
    TMOD|= 0x01;    //设置定时器T0工作模式：软启动、定时、工作方式1-16位计数值
    TL0 = 0x18;        //设置定时初值，定时1ms
    TH0 = 0xFC;        
    TF0 = 0;        //清除TF0标志
    TR0 = 1;        //定时器0开始计时
    ET0=1;            //允许定时器0中断
    EA=1;            //开中断 
}
void main()    //主函数
{ 
    
    char display[10];
    
    timer0_init();
    while(1)
    {
        sprintf(display,"%.2f",temp);
        smg_str(display);
        if(temp>30 &&temp<45){
            Led=0;
            flag=1;
        }
        else{
            
            flag=0;
        }
        
}      
    
    
}



void timer0_int() interrupt 1//定时器0定时1ms中断服务函数
{
//定时器T0工作方式1的16位计数值不能自动重装，需要每次中断设置初值
    TL0 = 0x18;        //设置定时初值
    TH0 = 0xFC;        
    ++count_200ms;
    if(++count_1000ms==1000)
    {
        count_1000ms=0;
        Ds18b20_Tempchg();
        temp=Ds18b20_Gettemp(); //读取寄存器中存储的温度数据        
        
    }
    //灯
    if(flag==0){
        buzzer=!buzzer;
        
        if(count_200ms==100)
        {
            Led=1;
        }
        if(count_200ms==200)
        {
        
            Led=0;
            
            count_200ms=0;
        }
        
    }
    
}