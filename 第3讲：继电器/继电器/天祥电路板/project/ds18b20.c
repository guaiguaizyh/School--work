#include <ds18b20.h> 

sbit ds=P2^2;     //�¶ȴ������ź��� 
  
void dsreset()    //18B20��λ����ʼ��
{
  u16 i;
  ds=0;
  i=103;
  while(i>0)i--; //��ʱ
  ds=1;
  i=4;
  while(i>0)i--;   //��ʱ
}

bit tempreadbit()   //��1λ����
{
   u16 i;
   bit dat;
   ds=0;i++;          //i++ ����ʱ����
   ds=1;i++;i++;
   dat=ds;
   i=8;while(i>0)i--;	//��ʱ
   return(dat);
}

u8 tempread()   //��8λ(1���ֽ�)����
{
  u8 i,j,dat;
  dat=0;
  for(i=1;i<=8;i++)
  {
    j=tempreadbit();
    dat=(j<<7)|(dat>>1);   //�������������λ����ǰ�棬�����պ�һ���ֽ���DAT��
  }
  return(dat);
}

void tempwritebyte(u8 dat)   //��18B20дһ���ֽ�����
{
  u16 i;
  u8 j;
  bit testb;
  for(j=1;j<=8;j++)
  {
    testb=dat&0x01;
    dat=dat>>1;
    if(testb)     //д 1
    {
      ds=0;
      i++;i++;	 //��ʱ
      ds=1;
      i=8;while(i>0)i--;  //��ʱ��
    }
    else
    {
      ds=0;       //д 0
      i=8;while(i>0)i--;   //��ʱ��
      ds=1;
      i++;i++;			//��ʱ
    }
  }
}

void Ds18b20_Tempchg()  //DS18B20 �������ʼ�¶Ȳ�����������ת����
{
  dsreset();   //��λ
  delay_ms(1);
  tempwritebyte(0xcc);  // д������ROMָ��
  tempwritebyte(0x44);  // д�¶�ת��ָ��
}

float Ds18b20_Gettemp()  //��ȡ�Ĵ����д洢���¶�����
{
  u8 a,b;
  u16 t;
  int temp;
  float f_temp;
  dsreset();
  delay_ms(1);
  tempwritebyte(0xcc);// д������ROMָ��
  tempwritebyte(0xbe);// ��������ָ��
  a=tempread();         //����8λ
  b=tempread();         //����8λ
  if(b&0x08) b=b|0xf0;
  t=b;
  t*=256;            //�����ֽ����Ϊ1����
  t=t|a;  							 
  temp=t;
  f_temp=temp*0.0625;      //�¶��ڼĴ�����Ϊ12λ �ֱ���λ0.0625��
  return  f_temp; 
} 