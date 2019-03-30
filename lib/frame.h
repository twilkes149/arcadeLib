#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifndef __FRAME__
#define __FRAME__
struct frame {
	char* lines; //a c-string that contains color keys for each pixel of this sprite 
	char* resizedLines; //when draw, if the frame needs to be resized, this will hold the resized frame
	uint16_t length;//the number of characters in this frame
	uint8_t scale;
};

//function to init a frame from a file
//@param filePath: the name of the file that defines this frame
//@param _frame: the frame struct to init
void frame_init(char* filePath, struct frame* _frame);

//function to free up a frame
void frame_destroy(struct frame* _frame);
#endif
