#include <dht11.h>

sbit Data=P2^0;   //dht11������

void DHT11_start()//����
{
   Data=1;
   delay_us(2);
   Data=0;
   delay_ms(20);   //��ʱ18ms����
   Data=1;
   delay_us(30);
}

u8 DHT11_rec_byte()      //����һ���ֽ�
{
  u8 i,dat=0;
  for(i=0;i<8;i++)    //�Ӹߵ������ν���8λ����
   {          
      while(!Data);   ////�ȴ�50us�͵�ƽ��ȥ
      delay_us(8);     //��ʱ60us�������Ϊ��������Ϊ1������Ϊ0 
      dat<<=1;           //��λʹ��ȷ����8λ���ݣ�����Ϊ0ʱֱ����λ
      if(Data==1)    //����Ϊ1ʱ��ʹdat��1����������1
         dat+=1;
      while(Data);  //�ȴ�����������    
    }  
    return dat;
}

void DHT11_receive(u8 *RHum,u8 *Temp) //��ȡ�������ݣ���У�飬Ȼ����ʪ��ֵ���ص��β���
{
    u8 R_H,R_L,T_H,T_L,revise; 
    DHT11_start();
    if(Data==0)
    {
        while(Data==0);   //�ȴ�����     
        delay_us(40);  //���ߺ���ʱ80us
        R_H=DHT11_rec_byte();    //����ʪ�ȸ߰�λ  
        R_L=DHT11_rec_byte();    //����ʪ�ȵͰ�λ  
        T_H=DHT11_rec_byte();    //�����¶ȸ߰�λ  
        T_L=DHT11_rec_byte();    //�����¶ȵͰ�λ
        revise=DHT11_rec_byte(); //����У��λ

        delay_us(25);    //����

        if((R_H+R_L+T_H+T_L)==revise)      //У��
        {
            *RHum=R_H;            
            *Temp=T_H;             
        }        
    }
}
