#include "frame.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//function to init a frame from a file
//@param filePath: the name of the file that defines this frame
//@param _frame: the frame struct to init
void frame_init(char* filePath, struct frame* _frame) {
	_frame->lines = NULL;
	_frame->resizedLines = NULL;
	
	FILE *fp = fopen(filePath, "r");
	if (!fp)
	{
		fprintf(stderr, "Error opening file '%s'\n", filePath);
		return;
	}
	
	//get size of file, so we know how many bytes to allocate for the frame string
	fseek(fp,0,SEEK_END);//go to end of file
	uint32_t fileSize = ftell(fp);//read bytes
	fseek(fp,0, SEEK_SET);//reset pointer to beginning of file
	
	_frame->lines = malloc(sizeof(char) * fileSize + 1);//malloc enough bytes for each byte in the file plus one for the null terminator  
    
    //read the file
    fread(_frame->lines, sizeof(char), fileSize, fp);    
    _frame->length = fileSize;
}

//function to free up memory used by a frame
void frame_destroy(struct frame* _frame) {
	if (_frame->lines != NULL) {
		free(_frame->lines);
	}
	
	if (_frame->resizedLines != NULL) {
		free(_frame->resizedLines);
	}
}
