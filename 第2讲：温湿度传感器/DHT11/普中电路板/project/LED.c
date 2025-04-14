#include <led.h>

//�����߽ӿ�
#define LEDDAT P0

//ͨ�����������λѡ
sbit LSA=P2^2; 
sbit LSB=P2^3;
sbit LSC=P2^4; 

u8 code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,0x00}; //��������ܱ���

void Print_u32_LED(u32 n)//���6λ�޷�������(0-99999999)��8λ�����,����8λʱ��ǰ�治��ʾ
{u8 i;
 if(n==0) //������Ϊ0ʱֱ����ʾ0
 {
 	LSA=0;LSB=0;LSC=0; //λѡ

	LEDDAT=table[0]; //���¶���
	
	delay_ms(1); //���һ��ʱ��ɨ��	
	
	LEDDAT=0x00;//����
 }
 else
 {
 	i=0;
	while(n)//��������Ϊ0����һλһλ����ʾ
 	{	
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
			case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
			case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
			case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
			case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
			case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
			case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ	
		}

		LEDDAT=table[n%10]; //���¶���
		
		delay_ms(1); //���һ��ʱ��ɨ��	
	
	    LEDDAT=0x00;//����
	  		 	   
    	n=n/10;
		i++;		
 	}
 }
}
void Print_str_LED(u8 *f)//������ִ��������
{
 u8 i,n;
 n=strlen(f);
 for(i=0;i<n;i++)
 {	
 	switch(i)	 //λѡ��ѡ�����������ܣ�
	{
		case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
		case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
		case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
		case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
		case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
		case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
		case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
		case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ	
	}
		
	switch(f[n-i-1])
	{
	case '.':n--;LEDDAT=table[f[n-i-1]-'0']|0x80;break;
	case '-':LEDDAT=0x40;break;
	case ' ':LEDDAT=0x00;break;
	default :LEDDAT=table[f[n-i-1]-'0']; 
	} 

	delay_ms(1); //���һ��ʱ��ɨ��	
	
	LEDDAT=0x00;//����
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

void Print_char(u8 n,u8 k)//��ָ��λ��k��ʾ����n
{
    switch(k)	 //λѡ��ѡ�����������ܣ�
	{
		case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
		case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
		case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
		case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
		case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
		case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
		case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
		case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ	
	}
    LEDDAT=table[n];//���¶���
	delay_ms(1); //���һ��ʱ��ɨ��	
	
	LEDDAT=0x00;//����
}

