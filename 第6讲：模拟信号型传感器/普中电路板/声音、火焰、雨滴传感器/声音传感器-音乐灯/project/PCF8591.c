#include <PCF8591.h> 

u8 D[32];

u8 Pcf8591_DA(u8 Val)//����תģ�⣬valΪ�����ź�ֵ��ת���ɹ�����1�����򷵻�0
{
   u8 ack;
   I2C_Start();              //��������
   ack=I2C_SendByte(AddWr);   //����������ַ+д
   if(ack==0)return(0);		//��Ӧ�������
   ack=I2C_SendByte(0x40);   //ʹ������ת��ģ��
   if(ack==0)return(0);		  //��Ӧ�������
   ack=I2C_SendByte(Val);     //���������ź�ֵ  
   if(ack==0)return(0);		  //��Ӧ�������
   I2C_Stop();               //��������
   return(1);
}

u8 Pcf8591_AD(u8 channel)//ģ��ת���֣�channelΪģ���ź�ͨ����(0-3)��ת���ɹ��򷵻�����ֵ�����򷵻�0
{
   u8 ack,dat;
   //����ת��
   I2C_Start();            //��������
   ack=I2C_SendByte(AddWr);            //����������ַ +д
   if(ack==0)return(0);		  //��Ӧ�������
   ack=I2C_SendByte(channel);   //����ͨ��ѡ�������
   if(ack==0)return(0);	   //��Ӧ�������
   I2C_Stop();             //��������

   //��ȡת��ֵ
   I2C_Start();         //��������
   ack=I2C_SendByte(AddWr+1);     //����������ַ +��
   if(ack==0)return(0);	   //��Ӧ�������
   dat=I2C_RcvByte();      //��ȡת������ֵ

   I2C_Ack(1);           //���ͷ�Ӧ���ź�
   I2C_Stop();           //��������
   return(dat);
}
 