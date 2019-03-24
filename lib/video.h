#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

#define VIDEO_ERROR -1
#define VIDEO_SUCCESS 0

/* This module will take care of writing to the screen
* @author: Tucker Wilkes
*/ 

//function to init the video module
uint8_t video_init();

//functions to get information about the screen
int video_getScreenWidth();

int video_getScreenHeight();

//functions to draw to the screen
void video_drawPixelColor(uint16_t row, uint16_t col, char color);

void video_drawPixel(uint16_t row, uint16_t col, uint32_t color);

void video_drawLineColor(uint16_t row, uint16_t col, uint16_t length, char color);

void video_drawLine(uint16_t row, uint16_t col, uint16_t length, uint32_t color);

//function to clean up things with the video module
void video_close();

