#include <led.h>
#define LEDDAT P0
sbit DX=P2^6;   //  P2^0;
sbit WX=P2^7;   //  P2^1;

u8 code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,0x00}; //��������ܱ���

void Print_u32_LED(u32 n)//����޷�������(0-999999)��6λ�����,����6λʱ��ǰ�治��ʾ
{u8 t=0xdf;
 if(n==0) //������Ϊ0ʱֱ����ʾ0
 {
 	LEDDAT=0xff; //λ����Ӱ
	WX=1;//�������λ��
	LEDDAT=t; //����λ��
	WX=0;//����λ��
	   
	LEDDAT=0x00; //������Ӱ
	DX=1;//������¶���
	LEDDAT=table[0]; //���¶���
	DX=0;//�������
 }
 else
 {
 	while(n)//��������Ϊ0����һλһλ����ʾ
 	{	LEDDAT=0xff; //λ����Ӱ
		WX=1;//�������λ��
		LEDDAT=t; //����λ��
		WX=0;//����λ��
	   
		LEDDAT=0x00; //������Ӱ
		DX=1;//������¶���
		LEDDAT=table[n%10]; //���¶���
		DX=0;//�������
	  		 	   
    	n=n/10;
		t=_cror_(t,1);
		delay_ms(3);
 	}
 }
}
void Print_str_LED(u8 *f)//������ִ��������
{
 u8 t=0xdf,i;
 i=strlen(f);
 while(i)
 {	LEDDAT=0xff; //λ����Ӱ
	WX=1;//�������λ��
	LEDDAT=t; //����λ��
	WX=0;//����λ��
	   
	LEDDAT=0x00; //������Ӱ
	DX=1;//������¶���
	switch(f[i-1])
	{
	case '.':i--;LEDDAT=table[f[i-1]-'0']|0x80;break;
	case '-':LEDDAT=0x40;break;
	case ' ':LEDDAT=0x00;break;
	default:LEDDAT=table[f[i-1]-'0']; 
	} //���¶���
	DX=0;//�������
	  		 	   
    i--;
	t=_cror_(t,1);
	delay_ms(3);
 }
 }

void Print_float_LED(float n,u8 x)//���С��(��Ч���ֲ�����8λ)��8λ����ܣ�����x(0-3)λС��
{
 u8 prtstr[12];
 switch(x)
 {
 case 0:sprintf(prtstr,"%.0f",n);break;
 case 1:sprintf(prtstr,"%.1f",n);break;
 case 2:sprintf(prtstr,"%.2f",n);break;
 case 3:sprintf(prtstr,"%.3f",n);break;
 } 
 Print_str_LED(prtstr);	
}

void Print_char(u8 n,u8 k)//�����λ��ʾ����
{
u8 temp;
temp=_cror_(0xdf,k-1);
LEDDAT=0XFF; 	 //λ����Ӱ
WX=1;		 //�������λ��
LEDDAT=temp;	 //����λ��
WX=0;		//����λ��

LEDDAT=0; 	 //������Ӱ
DX=1;	//������¶���
LEDDAT=table[n];//���¶���
DX=0;		//�������
}

