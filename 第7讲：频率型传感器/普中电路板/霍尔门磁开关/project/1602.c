#include <1602.h>
#define DATA P0
sbit LCDEN=P2^7;
sbit RW=P2^5;
sbit RS=P2^6; 

u8 DectectBusyBit( )//状态判断函数(忙/闲?)
{   
	u8 result;
	DATA = 0xff;	//读状态前先置高电平，防止误判
	RS = 0;
	delay_ms(5);
    RW = 1;
	LCDEN = 1;
	delay_ms(5);
	result=DATA&0x80; //取最高位即为忙标记，若LCM忙,则反复测试,在此处原地踏步；当LCM闲时，才往下继续
	LCDEN = 0;
	return result;		      
}		

void WrComLCD(u8 ComVal)//写命令函数
{
	while(DectectBusyBit()==1);         //先检测LCM是否空闲
	RS = 0;
	delay_ms(1);
    RW = 0;
	LCDEN = 1;
	DATA = ComVal;
	delay_ms(1);
	LCDEN = 0;	
}

void WrDatLCD(u8 DatVal)//写数据函数
{
	while(DectectBusyBit()==1); 
	RS = 1;
	delay_ms(1);
    RW = 0;
	LCDEN = 1;
	DATA = DatVal;
	delay_ms(1);
	LCDEN = 0;	
}

u8 RdACAdr(void)//读当前光标地址
{   
	u8 result;
	DATA = 0xff;	//读地址前先置高电平，防止误判
	RS = 0;
	delay_ms(5);
    RW = 1;
	LCDEN = 1;
	delay_ms(5);
	result=DATA&0x7f; //去掉最高位忙闲标记，只保留低7位地址值
	LCDEN = 0;
	return result;		      
} 

void retACAdr(u8 add)//返回到某个光标地址
{   
    WrComLCD(0x80+add);       
}

void LCD1602pos(u8 x,u8 y)//1602显示坐标定位函数：x为行标，0：第一行，1：第二行；y为列标，0-15
{
	u8 t;
	t=x?0x40:0x00;
	WrComLCD(0x80+t+y);  
}

void LCD1602_Init( )//1602初始化函数
{ 
	WrComLCD(0x38);     // 功能设定:16*2行、5*7点阵、8位数据接口
	WrComLCD(0x38);
	WrComLCD(0x38);    
//多次重复设定功能指令,因为LCD启动后并不知道使用的是4位数据接口还是8位的，所以开始时总是默认为4位，这样刚开始写入功能设定指令时，低4位被忽略,为了可靠，最好多写几遍该指令 
	WrComLCD(0x01);    // 清屏 
	WrComLCD(0x06);    // 光标自增、屏幕不动  
	delay_ms(1);	      // 延时，等待上面的指令生效，下面再显示，防止出现乱码
	WrComLCD(0x0c);    // 开显示、关光标
	LCD1602pos(0,0);//从第一行第一个字符开始显示
	delay_ms(5);
}

void LCD1602_disstr(u8 *p,u8 x,u8 y)//从指定坐标开始显示英文字符串（长度不超过32），自动换行
{	
	u8 i=0;
    LCD1602pos(x,y);
	while(p[i]!='\0')
	{  
	  	WrDatLCD(p[i]);
		i++;
		delay_ms(5);
	
//	    if((y+i)%16==0)  //一行显示到末尾
//		{  
//		    x=x^0x01;//切换到另一行，如果第1行写完换行到第2行,如果第2行写完换行到第1行
//		    LCD1602pos(x,0);//设置显示地址为另一行行首
//		}		
	}	
}
void LCD1602_disnum(long n,u8 x,u8 y)//从指定坐标开始显示长整数
{	
	u8 i=0,j=0;
	u8 p[17],q[17]="          ";//并清除第二行。。。。。。。。
	long m;
	if(n<0) m=-n;
	else    m=n;  
	while(m)
	{p[i++]=m%10+'0';
	 m=m/10;
	}
	p[i--]='\0';
	if(n<0) q[j++]='-';
	while(i)
		q[j++]=p[i--];
	q[j++]=p[i];
	LCD1602_disstr(q,x,y);
}
void LCD1602_disch_x_y(u8 ch,u8 x,u8 y)//在指定位置显示一个英文字符
{	
   	LCD1602pos(x,y);
	WrDatLCD(ch);
	delay_ms(5);	
}
void LCD1602_disch(u8 ch)//在当前位置显示一个英文字符
{	
   	WrDatLCD(ch);
	delay_ms(5);	
}
void LCD1602_clear( )//1602清屏函数
{
 	WrComLCD(0x01);    // 清屏
} 

void LCD1602_return( )//1602返回函数
{
 	WrComLCD(0x02);    // 清屏
} 

void LCD1602_backspace( )//向左删除一个字符
{
 	WrComLCD(0x10);//光标左移
	WrDatLCD(' ');//输出空格
	WrComLCD(0x10);//光标左移
}

void LCD1602_cursor(u8 direct)//光标左右移动，direct=0，左移，direct=1，右移
{
 	if(direct) WrComLCD(0x14);//光标右移
    else	   WrComLCD(0x10);//光标左移	
	
}

void LCD1602_screen(u8 direct)//屏幕左右移动，direct=0，左移，direct=1，右移
{
 	if(direct) WrComLCD(0x1C);//屏幕右移
    else	   WrComLCD(0x18);//屏幕左移	
	
}
void LCD1602_pow(u8 x)//打开(1)或关闭(0)显示
{ 
	if(x==1)WrComLCD(0x0f);	//开显示
	if(x==0)WrComLCD(0x08);	//关显示
}