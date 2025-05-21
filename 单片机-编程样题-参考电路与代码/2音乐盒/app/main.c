#include <config.h>
#include <button.h>
#include <beep.h>
	
void main()
{
	while(1){
		if(Btn_Press()){
			while(1){
				playmusic(Music2Meter, Music2TONE, Music2Len);
			}
		}
	}	
}