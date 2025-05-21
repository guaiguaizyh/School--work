#include <config.h>
#include <1602.h>
#include <24C02.h> 
void main()
{
	u8 ch;
	LCD1602_Init( );//1602³õÊ¼»¯º¯Êý
	WriteRom(0,'X');
	ch=ReadRom(0);
	LCD1602_disch(ch);
	while(1)
	{

	}		
}