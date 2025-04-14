#include <Vuart.h>


//查询计数器溢出标志位
void WaitTF0( void )
{
     while(!TF0);
     TF0=0;
}

//计数器初始化
void S2INI(void)//波特率9600，@11.0592MHz
{
	TMOD &=0x0f;
	TMOD |=0x02;                 //计数器0，方式2
	TH0=0xA0;                     //预值为256-96=140，十六进制A0
	TL0=0xA0;
	TR0=0;                         //开始计数
	TF0=0;
}

void WByte(u8 input)
{
	//发送启始位
	u8 i;
		TL0=TH0;
		TR0=1;
	Vtxd=(bit)0;
	WaitTF0();
	//发送8位数据位
		for(i=0;i<8;i++)
	{
		Vtxd=(bit)(input&0x01);      //先传低位
		WaitTF0();
		input=input>>1;
	}
     //发送校验位(无)

     //发送结束位
     Vtxd=(bit)1;
     WaitTF0();
     TR0=0;
}  

//接收一个字符
u8 RByte()
{
	u8 Output=0;
	u8 i=8;
//	TR0=1; 
	TL0=TH0;
	TR0=1;                          //启动Timer0
 
	while(Vrxd)		WaitTF0();                 //等过起始  ;
//
//	TL0=TH0;
	WaitTF0();                 //等过起始

	//接收8位数据位
	for(i=0;i<8;i++)
	{
		Output >>=1;
		if(Vrxd) Output|=0x80;      //先收低位
		WaitTF0();                 //位间延时
    }	
	while(!Vrxd); 

	TR0=0;//停止 

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

