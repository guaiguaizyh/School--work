#ifndef _BEEP_H_

	#define	_BEEP_H_
	#include <config.h>
	#include <delay.h>
	extern u8 code Music1TONE[];//歌曲“两只老虎”的音调
	extern u8 code Music1Meter[];//歌曲“两只老虎”的节拍
	extern u8 code Music1Len;//歌曲“两只老虎”的音调个数
	extern u8 code Music2TONE[];//歌曲“祝你生日快乐”的音调
	extern u8 code Music2Meter[];//歌曲“祝你生日快乐”的节拍
	extern u8 code Music2Len;//歌曲“祝你生日快乐”的音调个数

	void alarm();//蜂鸣器发出2种不同频率的声音，即：报警声
	void playmusic(u8 *Meter,u8 *TONE,u8 n);//播放歌曲，*Meter指向歌曲的节拍数组，*TONE指向歌曲的音调数组，n为歌曲中音调的个数
	void beep_on(u16 n,u16 f);//蜂鸣器响：频率f，单位Hz；声音持续时长n，单位毫秒
#endif 