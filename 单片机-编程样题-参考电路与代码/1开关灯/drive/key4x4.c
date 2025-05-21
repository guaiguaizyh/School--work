#include <key4x4.h>
#define key_data P2 //宏定义4*4矩阵按键行列引脚
u8 keyval_4X3[]="123456789*0#";	
u8 keyval_4X4[]="789/456*123-c0=+"; 
u8 key_scan_4X4( )//4*4矩阵按键扫描函数，返回按键号（0-16），16表示无按键按下
{
	u8 i,temp,vol,keyvalue=16;
	//先检测是否有键按下
	key_data=0xf0;
	temp=key_data;
	if((temp&0xf0)!=0xf0)
	{
		//去抖
		delay_ms(10);
		key_data=0xf0;
		temp=key_data;		
		if((temp&0xf0)!=0xf0)
		{
			 //确定有键后，逐行扫描哪个键按下
			 vol=0xfe;
			 for(i=0;i<4;i++)
			 {
			 	key_data=vol;
				temp=key_data;
				switch(temp&0xf0)
				{
				 	case 0xe0:keyvalue=4*i+0;break;
					case 0xd0:keyvalue=4*i+1;break;
					case 0xb0:keyvalue=4*i+2;break;
				    case 0x70:keyvalue=4*i+3;break;		
				}
				vol=_crol_(vol,1);
			 }
			 //等待按键释放
			 do{
			 key_data=0xf0;
			 temp=key_data;
			}while((temp&0xf0)!=0xf0);
		}
	}
	//返回按键值
	return 	keyvalue;
}
u8 key_scan_4X3( )//4*3矩阵按键扫描函数，返回按键号（0-11），12表示无按键按下
{
	u8 i,temp,vol,keyvalue=12;
	//先检测是否有键按下
	key_data=0xf0;
	temp=key_data;
	if((temp&0xf0)!=0xf0)
	{
		//去抖
		delay_ms(10);
		key_data=0xf0;
		temp=key_data;		
		if((temp&0xf0)!=0xf0)
		{
			 //确定有键后，逐行扫描哪个键按下
			 vol=0xfe;
			 for(i=0;i<4;i++)
			 {
			 	key_data=vol;
				temp=key_data;
				switch(temp&0xf0)
				{
				 	case 0xe0:keyvalue=3*i+0;break;
					case 0xd0:keyvalue=3*i+1;break;
					case 0xb0:keyvalue=3*i+2;break;		
				}
				vol=_crol_(vol,1);
			 }
			 //等待按键释放
			 do{
			 key_data=0xf0;
			 temp=key_data;
			}while((temp&0xf0)!=0xf0);
		}
	}
	//返回按键值
	return 	keyvalue;
}