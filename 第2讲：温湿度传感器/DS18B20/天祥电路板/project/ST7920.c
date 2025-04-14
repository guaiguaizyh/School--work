//基于ST7920的12864液晶显示
#include <ST7920.h>

#define DATA P0		 //数据输入输出端口 
#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};	   //延时4us
u8 row=0; //当前光标所在位置行坐标 
u8 col=0; //当前光标所在位置列坐标 

/*12864ST7920端口定义*/
sbit LCD_RS  =  P3^5;            //寄存器选择输入 
sbit LCD_RW  =  P3^6;            //液晶读/写控制
sbit LCD_EN  =  P3^4;            //液晶使能控制
sbit LCD_PSB =  P3^7;            //串/并方式控制
 		
/*******************************************************************/
/*检查LCD忙状态                                                    */
/*lcd_busy为1时，忙，等待。lcd-busy为0时,闲，可写指令与数据。      */
/*******************************************************************/
bit lcd_busy()
 {                          
    bit result;
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 1;
    delayNOP();	 //延时4us
    result = (bit)(DATA&0x80);
    LCD_EN = 0;
    return(result); 
 }
/*******************************************************************/
/*写指令数据到LCD                                                  */
/*RS=L，RW=L，E=高脉冲，D0-D7=指令码。                             */
/*******************************************************************/
void lcd_wcmd(u8 cmd)
{                          
    while(lcd_busy());
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    _nop_();
    _nop_(); 
    DATA = cmd;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0;  
}
/*******************************************************************/
/*写显示数据到LCD                                                  */
/*RS=H，RW=L，E=高脉冲，D0-D7=数据。                               */
/*******************************************************************/
void lcd_wdat(u8 dat)
{                          
    while(lcd_busy());
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    DATA = dat;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0; 
}
/*******************************************************************/
/*  LCD初始化设定                                                  */
/*******************************************************************/
void ST7920_Init() //初始化函数
{ 

    LCD_PSB = 1;         //并口方式
    
//  lcd_wcmd(0x34);      //扩充指令操作
//  delay_ms(5);
    lcd_wcmd(0x30);      //基本指令操作
    delay_ms(5);
    lcd_wcmd(0x0c);      //显示开，关光标
	delay_ms(5);
    lcd_wcmd(0x01);      //清除LCD的显示内容
    delay_ms(5);
}
/*********************************************************/
/* 设定显示位置                                          */
/*********************************************************/
void ST7920_pos(u8 X,u8 Y) //设置显示坐标,X行坐标(0-3),Y列坐标(0-7)
{                          
   u8  pos,a;
   row=X;
   col=Y;
   if (X==0)
     {a=0x80;}
   else if (X==1)
     {a=0x90;}
   else if (X==2)
     {a=0x88;}
   else if (X==3)
     {a=0x98;}
   pos = a+Y ;  
   lcd_wcmd(pos);     //显示地址
}
/*********************************************************/
/* 显示汉字串函数           			  				 */
/*********************************************************/
void ST7920_str(u8 *p,u8 x,u8 y)//从指定位置开始显示汉字串（字数不超过32）
 {
    u8 i;
    ST7920_pos(x,y); //设置起始坐标       
    i = 0;
    while(p[i]!= '\0')
     {                         //显示字符
       lcd_wdat(p[i]);
       i++;
	   lcd_wdat(p[i]);
       i++;
	   col++;
	   if(col%8==0) {row++; row=row%4; col=0; ST7920_pos(row,col);}//写满一行时就跳到下一行；一个汉字占2个字节
 
     }		   
}
void ST7920_word(u8 *p,u8 x,u8 y)//在指定位置显示一个汉字
{
    ST7920_pos(x,y);        
    lcd_wdat(p[0]);
	lcd_wdat(p[1]);
    col++;
	if(col%8==0) {row++; row=row%4; col=0; ST7920_pos(row,col);}//写满一行时就跳到下一行；一个汉字占2个字节
} 
void ST7920_Clear()//清屏函数
{ 
    lcd_wcmd(0x01);      //清除LCD的显示内容
    delay_ms(5);
	ST7920_pos(0,0);     //坐标返回到首行首位
}
void ST7920_del(u8 x,u8 y)//删除指定位置上的汉字,并且光标也移到指定位置
{ 
	ST7920_pos(x,y);  
	lcd_wdat(0xa1);	//写入全角的空格
	lcd_wdat(0xa1);
}
void ST7920_Clrline(u8 x)//清除指定行，并且光标移到行首
{
	u8 i;
	for(i=0;i<8;i++)
		ST7920_del(x,7-i);
}
void ST7920_Backspace()//删除光标前面的一个汉字,并且光标也跟着左移一位
{
 	if(col==0) {if(row>0) {row--;col=7;}}
	else col--;
	ST7920_pos(row,col);  
	lcd_wdat(0xa1);	 //写入全角的空格
	lcd_wdat(0xa1);
}
void ST7920_pow(u8 x)//打开(1)或关闭(0)显示
{ 
	if(x==1)lcd_wcmd(0x0c);	//开显示
	if(x==0)lcd_wcmd(0x08);	//关显示
}