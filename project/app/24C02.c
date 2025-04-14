#include <24C02.h> 

u8 WriteRom(u8 addr, u8 dat)	//��AT24Cxx��ָ����ַ��Ԫд�����ݣ�addr�洢��Ԫ��ַ��datд������ݣ�д��ɹ�����1�����򷵻�0
{  
   u8 i=4,ack;//iΪ���������д������������i�β���ʧЧ��������ֹ������������
   while(--i)
   {
      I2C_Start();              //��������
      ack=I2C_SendByte(AddWrC);   //����������ַ+д
      if(ack==0) continue;		//��Ӧ�������¿�ʼ 
      ack=I2C_SendByte(addr);   //���ʹ洢��Ԫ��ַ
      if(ack==0) continue;		//��Ӧ�������¿�ʼ 
      ack=I2C_SendByte(dat);   //д������
      if(ack==0) continue;		//��Ӧ�������¿�ʼ 
      break; //д��ɹ������
   }
   I2C_Stop();         //��������
   delay_ms(4);	       //1���ֽڵ�д������Ϊ1ms, �����ʱ1ms����
   if(i>0) return 1;
   else    return 0;      
}

u8 ReadRom(u8 addr)//��AT24Cxx��ָ����ַ��Ԫ��ȡ���ݣ�addr�洢��Ԫ��ַ��д��ɹ�����1�����򷵻�0
{ 
  u8 i=4,dat,ack;//iΪ��������ض�������������i�β���ʧЧ��������ֹ������������
  while(--i)
  {	
      I2C_Start();              //��������
      ack=I2C_SendByte(AddWrC);   //����������ַ+д
      if(ack==0) continue;		//��Ӧ�������¿�ʼ 
      ack=I2C_SendByte(addr);   //���ʹ洢��Ԫ��ַ
	  if(ack==0) continue;		//��Ӧ�������¿�ʼ 
	  
	  I2C_Start();              //��������
      ack=I2C_SendByte(AddWrC+1);   //����������ַ+��
	  if(ack==0) continue;		//��Ӧ�������¿�ʼ 
      dat=I2C_RcvByte();      //��ȡָ����ַ��Ԫ�������

      I2C_Ack(1);           //���ͷ�Ӧ���źţ��������ݴ���
      break;
  } 
   I2C_Stop();           //��������
   if(i>0) return dat;
   else    return 0; 
}