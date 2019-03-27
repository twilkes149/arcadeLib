#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_COLORS 255

//function to read the colors in for a particular arcade game
//@param filePath relative path from the lib folder to the color file to be parse
//@param errorCode the number to be returned from getColor if the key doesn't exist
uint8_t color_init(char* filePath, uint32_t errorCode);

//function to get the int version of a color given a color key
uint32_t color_getColor(char key);
