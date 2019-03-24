#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "frame.h"

struct sprite {
	uint16_t row, col;
	uint16_t height, width;
	uint16_t scale;
	
	struct frame* frames;
};

//functions to get information about a sprite
uint16_t sprite_getRow();

uint16_t sprite_getCol();

uint16_t sprite_getWidth();

uint16_t sprite_getHeight();

uint16_t sprite_getScale();

struct frame* sprite_getFrame(uint8_t frameIndex);
