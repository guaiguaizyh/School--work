#include <smg8.h>
#define smg_data P0 //�궨������ܶ���/λ������
sbit DX=P2^0;//���������������������
sbit WX=P2^1;//����λ����������������
void smg_dis_str(char *f) //�������ʾ�ַ���������룬����������ʾ�� 
{
	u8 t=0xfe;//λ��
	u8 i=0;//�ַ����±�
	u8 n=strlen(f);//�ַ�������
	u8 temp;
	while(i<n)
	{	
		smg_data=0xff; //λ����Ӱ
		WX=1;//�������λ��
		smg_data=t;//����λ��
		WX=0;//����λ��
		   
		smg_data=0x00; //������Ӱ
		DX=1;//������¶���
		switch(f[i]) //���ö���
		{	
			//��������ܱ���,������Ҫ���Ҫ��ʾ���ַ��ı���
			case '0':temp=0x3f;break;
			case '1':temp=0x06;break;
			case '2':temp=0x5b;break;
			case '3':temp=0x4f;break;
			case '4':temp=0x66;break;
			case '5':temp=0x6d;break;
			case '6':temp=0x7d;break;
			case '7':temp=0x07;break;
			case '8':temp=0x7f;break;
			case '9':temp=0x6f;break;
			case 'a':temp=0x77;break;
			case 'b':temp=0x7c;break;
			case 'c':temp=0x39;break;
			case 'd':temp=0x5e;break;
			case 'e':temp=0x79;break;
			case 'f':temp=0x71;break;
			case '-':temp=0x40;break;
			case ' ':temp=0x00;break;			 
		} 
		if(f[i+1]=='.')	{i++;temp=temp+0x80;}
		smg_data=temp;
		DX=0;//�������
		  		 	   
	    i++; //��ʾ��һλ
		t=_crol_(t,1);//��һλ��λѡ�ź�
		delay_ms(3);//��ʱ
	}
}