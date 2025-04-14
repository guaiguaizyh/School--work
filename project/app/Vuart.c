#include <Vuart.h>


//��ѯ�����������־λ
void WaitTF0( void )
{
     while(!TF0);
     TF0=0;
}

//��������ʼ��
void S2INI(void)//������9600��@11.0592MHz
{
	TMOD &=0x0f;
	TMOD |=0x02;                 //������0����ʽ2
	TH0=0xA0;                     //ԤֵΪ256-96=140��ʮ������A0
	TL0=0xA0;
	TR0=0;                         //��ʼ����
	TF0=0;
}

void WByte(u8 input)
{
	//������ʼλ
	u8 i;
		TL0=TH0;
		TR0=1;
	Vtxd=(bit)0;
	WaitTF0();
	//����8λ����λ
		for(i=0;i<8;i++)
	{
		Vtxd=(bit)(input&0x01);      //�ȴ���λ
		WaitTF0();
		input=input>>1;
	}
     //����У��λ(��)

     //���ͽ���λ
     Vtxd=(bit)1;
     WaitTF0();
     TR0=0;
}  

//����һ���ַ�
u8 RByte()
{
	u8 Output=0;
	u8 i=8;
//	TR0=1; 
	TL0=TH0;
	TR0=1;                          //����Timer0
 
	while(Vrxd)		WaitTF0();                 //�ȹ���ʼ  ;
//
//	TL0=TH0;
	WaitTF0();                 //�ȹ���ʼ

	//����8λ����λ
	for(i=0;i<8;i++)
	{
		Output >>=1;
		if(Vrxd) Output|=0x80;      //���յ�λ
		WaitTF0();                 //λ����ʱ
    }	
	while(!Vrxd); 

	TR0=0;//ֹͣ 

    return Output;
} 

void Receive_str(u8 *buf)
{
	u8 ch;
	while(1)
	{
		ch=RByte();
		if(ch=='\n')
		{
			*buf='\n';
			break;
		}
		else 
		{
			*buf=ch;
			buf++;
		}
	}
} 

