#include "./lib/video.h"
#include "./lib/color.h"
#include "./lib/frame.h"
#include <stdlib.h>
#include <stdint.h>

int main(void) {	
	uint32_t errorCode = 32;	
	color_init("test.color", errorCode);
	
	struct frame circle;
	circle.scale = 5;
	frame_init("circle.frame", &circle);//read in a cirlce frame
	
	//init video and draw a line of color t
	video_init();		
	
	video_drawFrame(100, 100, &circle);	
	frame_destroy(&circle);
	video_close();
	return 0;
}
