#include <keypad.h>	

#define MATRIX P1	//宏定义矩阵按键行列引脚，低4位为列线，高4位为行线

u8 keypad4_4()//4行4列矩阵按键扫描函数:要去抖，若有按键按下，返回对应的按键值(0-15),没有按键按下返回16
{
	u8 i,row,temp;
	u8 key=16;//按键号，初值设置为16，目的是：没有按键按下时返回16；
              //注意：若不设初值(默认值为0)，没有按键按下时，将返回0，会误认为0被按下  
	//按列扫描
	row=0xf7; //初始列信号      
	for(i=0;i<4;i++)//循环扫描4列
	{
		MATRIX=0xff;//清除之前的信号  
		MATRIX=row;	//输出列信号，第i列信号，对应第i列为低，其他全为高
		row=_cror_(row,1); 	  //循环左移，生成下一个列信号
		temp=MATRIX; //读入扫描信号
		temp=temp&0xf0; //屏蔽低4位列信号，只保留高4位行信号 
		if(temp!=0xf0)//有按键被按下，因为第i列某行有按键按下，则高4位行信号中有一位为低电平  
	 	{  
			delay_ms(10);  //延时去抖
			temp=MATRIX;   //再次读入扫描信号
			temp=temp&0xf0;  //屏蔽低4位列信号，只保留高4位行信号 
			if(temp!=0xf0)   //再次确认有按键被按下
	  		{  
	        	switch(temp)  //根据低4位行信号，判断哪个按键被按下
	            {  
	            	case 0x70:key=0+i;break; //第i列第1行按键被按下 
	                case 0xb0:key=4+i;break; //第i列第2行按键被按下  
	                case 0xd0:key=8+i;break; //第i列第3行按键被按下
					case 0xe0:key=12+i;      //第i列第4行按键被按下 
	            }
				
				do
				{
					temp=MATRIX;  	    //再次扫描按键，检测按键是否释放
	  				temp=temp&0xf0;  	//屏蔽高4位列信号，只保留低4位行信号
	  			}while(temp!=0xf0); //等待按键释放   
	  		}  
	     }
	}  
	return(key);//扫描结束，返回按键值
}

