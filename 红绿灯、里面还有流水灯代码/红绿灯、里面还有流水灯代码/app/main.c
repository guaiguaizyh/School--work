#include <config.h>	
#include <smg1.h>
#include <timer.h>
//#include <led8.h>
//void main()
//{
//	while(1)
//	{
//		Led_Ctrl(0);
//	}
//}



//»Ìº˛—”≥Ÿ∫Ï¬Ãµ∆
sbit red=P2^0;
sbit yellow=P2^1;
sbit green=P2^2;
u8 t;
//void main()
//{
//	while(1)
//	{
////		red=yellow=green=1;//1 «¡¡£¨0 «√  
////		smg_dis(0,9);  ’‚ «≤‚ ‘
//		//∫Ïµ∆9√Î
//		yellow=green=0;
//		for(t=0;t<9;t++)
//		{
//			if(t<6)
//			{
//				red=1;
//				smg_dis(0,9-t);
//				delay_s(1);
//			}
//			else
//			{
//				smg_dis(0,9-t);
//				red=0;
//				delay_ms(500);
//				red=1;
//				delay_ms(500);
//			}
//		}
//		//ª∆µ∆3s
//		red=green=0;
//		smg_dis(0,16);
//		yellow=1;
//		delay_s(3);
//		//¬Ãµ∆9√Î
//		yellow=red=0;
//		for(t=0;t<9;t++)
//		{
//			if(t<6)
//			{
//				green=1;
//				smg_dis(0,9-t);
//				delay_s(1);
//			}
//			else
//			{
//				smg_dis(0,9-t);
//				green=0;
//				delay_ms(500);
//				green=1;
//				delay_ms(500);
//			}
//		}
//		//ª∆µ∆3s
//			red=green=0;
//			smg_dis(0,16);
//			yellow=1;
//			delay_s(3);
//	}
//}



//∂® ±∆˜∫Ï¬Ãµ∆—”≥Ÿ
void main()
{
	Timer0_Int();
	while(1)
	{
		//∫Ïµ∆9s 
		yellow=green=0;
		while(x<6)
		{
			red=1;
			smg_dis(0,9-x);
		}
		while(x>=6)
		{
			smg_dis(0,9-x);
			if(count<10)
			{
				red=0;
			}
			else
			{
				red=1;
			}
		}
		//ª∆µ∆3s
		while(x<3)
		{
			red=green=0;
			yellow=1;
			smg_dis(0,16);
		}
		x=0;
		//¬Ãµ∆9s 
		yellow=red=0;
		while(x<6)
		{
			green=1;
			smg_dis(0,9-x);
		}
		while(x>=6)
		{
			smg_dis(0,9-x);
			if(count<10)
			{
				green=0;
			}
			else
			{
				green=1;
			}
		}
		//ª∆µ∆3s
		while(x<3)
		{
			red=green=0;
			yellow=1;
			smg_dis(0,16);
		}
		x=0;
	}
}