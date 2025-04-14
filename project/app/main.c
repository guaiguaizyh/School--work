/******************************����ͷ�ļ�*******************************/
#include <config.h>
#include <ds18b20.h>
#include <smg.h>
sbit buzzer=P2^5;

sbit Led=P2^0;
float temp=0;
u16 count_1000ms=0;
u8 count_200ms=0;
bit flag=1;
/***********************************������***********************************/
void timer0_init()//��ʱ��T0��ʱ1����@12.000MHz
{
    TMOD&= 0xF0;
    TMOD|= 0x01;    //���ö�ʱ��T0����ģʽ������������ʱ��������ʽ1-16λ����ֵ
    TL0 = 0x18;        //���ö�ʱ��ֵ����ʱ1ms
    TH0 = 0xFC;        
    TF0 = 0;        //���TF0��־
    TR0 = 1;        //��ʱ��0��ʼ��ʱ
    ET0=1;            //����ʱ��0�ж�
    EA=1;            //���ж� 
}
void main()    //������
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



void timer0_int() interrupt 1//��ʱ��0��ʱ1ms�жϷ�����
{
//��ʱ��T0������ʽ1��16λ����ֵ�����Զ���װ����Ҫÿ���ж����ó�ֵ
    TL0 = 0x18;        //���ö�ʱ��ֵ
    TH0 = 0xFC;        
    ++count_200ms;
    if(++count_1000ms==1000)
    {
        count_1000ms=0;
        Ds18b20_Tempchg();
        temp=Ds18b20_Gettemp(); //��ȡ�Ĵ����д洢���¶�����        
        
    }
    //��
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