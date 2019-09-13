#include "./lib/video.h"
#include "./lib/color.h"
#include "./lib/frame.h"
#include "./lib/sprite.h"
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>

int main(void) {	
	uint32_t errorCode = 32;	
	color_init("test.color", errorCode);
	/*
	struct frame pacman0, pacman1;
	pacman0.scale = 5;
	pacman1.scale = 5;
	frame_init("./Pacman/pacman0.frame", &pacman0);//read in a cirlce frame
	frame_init("./Pacman/pacman1.frame", &pacman1);//read in a cirlce frame
	
	//init video and draw a line of color t
	
	
	while (1) {
		video_drawFrame(100, 100, &pacman0);
		for (uint64_t i = 0; i < 20000000; i++);
		video_drawFrame(100, 100, &pacman1);
		for (uint64_t i = 0; i < 20000000; i++);
	}
	
	
	
	frame_destroy(&pacman0);
	frame_destroy(&pacman1);
	*/
	video_init();
	
	struct sprite pacman;
	sprite_init("./Pacman", &pacman);
	
	video_close();
	
	return 0;
}
