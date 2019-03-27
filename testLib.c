#include "./lib/video.h"
#include "./lib/color.h"
#include <stdlib.h>
#include <stdint.h>

int main(void) {	
	uint32_t errorCode = 32;	
	color_init("test.color", errorCode);
	
	video_init();
	
	uint32_t color = color_getColor('t');
	
	if (color != errorCode) {				
		video_drawLine(video_getScreenHeight()/3, video_getScreenWidth()/2, 80, color);
	}
	
	video_close();
	return 0;
}
