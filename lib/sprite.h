#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <dirent.h>
#include <stdio.h>
#include "frame.h"

#define SPRITE_MAX_FRAMES 18
#define SPRITE_MAX_FRAME_NAME_LENGTH 18

struct sprite {
	//Positioning variables
	uint16_t row, col;//the row and col of the top left corner of where to draw the sprite
	uint16_t height, width;
	uint16_t scale;//howw big to draw the sprite compared to what is in the sprite file
	
	uint8_t currentFrame;//the current frame that is being displayed
	uint8_t numFrames;//how many frames are in the sprite's animation sequence
	struct frame* frames;
};

//function to init the sprite with all of the frames in the provided file
void sprite_init(char* directory, struct sprite* _sprite);

//functions to get information about a sprite
uint16_t sprite_getRow();

uint16_t sprite_getCol();

uint16_t sprite_getWidth();

uint16_t sprite_getHeight();

uint16_t sprite_getScale();

struct frame* sprite_getFrame(uint8_t frameIndex);//returns the frame object at a specific index

//function to draw the next frame in the sprite's sequence
void sprite_animate(struct sprite* _sprite);

void sprite_destroy();//function to destroy a sprite
