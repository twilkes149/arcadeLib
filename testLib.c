#include "./lib/video.h"
#include <stdlib.h>
#include <stdint.h>

int main() {
	video_init();
	
	for (uint32_t i = video_getScreenWidth()/4; i < video_getScreenWidth()/2; i++) {
		video_drawPixel(video_getScreenHeight()/2, i, 0x0000FF00);
	}
	
	video_drawLine(video_getScreenHeight()/3, video_getScreenWidth()/2, 40, 0xFF000000);
	
	video_close();
}
