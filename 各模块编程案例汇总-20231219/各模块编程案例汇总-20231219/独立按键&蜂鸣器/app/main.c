//通过按键（中断）控制蜂鸣器报警、播放音乐
#include <config.h>
#include <beep.h>
#include <intr.h>
void main()
{
	INTR_Int();
	while(1)
	{
		switch(mode)//蜂鸣器工作模式：0-不响、1-报警、2-播放“生日快乐“、3-播放”两只老虎”
		{
			case 0:break;
			case 1:alarm();break;//报警
			case 2:playmusic(Music2Meter,Music2TONE,Music2Len); break;//播放“生日快乐“
			case 3:playmusic(Music1Meter,Music1TONE,Music1Len); break;//播放”两只老虎”
		}
	}
}