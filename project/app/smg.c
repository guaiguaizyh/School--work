#include <smg.h>

#define smg_data P0 //�궨������ܶ�������
#define smg_bit  P2 //�궨�������λѡ��������������

//����������ܱ���
u8 code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,0x00};

void smg_str(u8 *str)//�������ʾ�ַ��������пɰ���"."��"-"��" "����Ҫ��ʾ������С������������sprintf��ָ����ʽ������ַ������ٵ��ñ�������ʾ���ַ���
{	
	u8 t=0x00,i;//tΪ��ʼλ��ֵ

	i=strlen(str);//��ȡ�ַ������ȣ����ַ������һ���ַ���ʼ������������ʾ
	while(i)
	{
		//��λ��
	    	smg_bit=smg_bit&0xe3; //���P24��P23��P22������λ����
		smg_bit=smg_bit|t; //����P24��P23��P22Ϊ000-111������λ����
	   	
		//�Ͷ���
		smg_data=0x00; //������Ӱ
		switch(str[i-1])
		{
		case '.':	i--;//����һλ��������ʾС����
					smg_data=table[str[i-1]-'0']|0x80;//Ҫ��ʾС����ֻ��Ҫ���������λ��Ϊ1
					break;
		case '-':	smg_data=0x40;//��ʾ��-��
					break;
		case ' ':	smg_data=0x00;//��ʾ�� ��
					break;
		default:	smg_data=table[str[i-1]-'0']; 
		} 
	  		 	   
	    	i--;//���ַ�����ȡ��һλ
		t=t+4;//�γ���һλ����������λ
		delay_ms(3);
	}
}