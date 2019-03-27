#include "color.h"
#include <stdlib.h>
#include <stdio.h>

static uint32_t colors[MAX_COLORS];//hash set to used to save colors by their key
static uint32_t errorCode;
#define WHITESPACE 32
#define START_WORD 33
#define END_WORD 126

//function to parse a line of colors. Returns the hex value of each color and the char key of
//the color. A line is expected to have the following format: <key color char>: <r>,<g>,<b>
//@param key: the address of the key variable
//@param color: the address of the variable to store the resulting color in
//@param line: the string representing the line
//@returns: the address of the token that caused failure of parse, or -1 if success
int16_t parseLine(char* _key, uint32_t* _color, char* line) {
	//parse key
	char key = 0;
	if (line[1] == ':' && line[0] >= START_WORD && line[0] <= END_WORD) {
		key = line[0];//save the key character				
	}
	else {
		printf("Unexpected token\n");
		return 0;
	}
	
	uint32_t color = 0;
	uint16_t prevIndex = 2;
	uint8_t colorIndex = 24;
	char buf[10] = {0};
	
	//parse rbg values
	for (uint16_t i = 0; i < strlen(line); i++) {
		if (line[i] <= WHITESPACE && line[i] != '\n') {//ignore whitespace
			continue;
		}
		
		if (line[i] == ',' || line[i] == '\n') {//we check these characters, because a color always comes before them
			if (i-prevIndex < 10) {
				strncpy(buf, &line[prevIndex+1], i-prevIndex);
				int32_t tempInt = atoi(buf);
				
				if (tempInt < 0 || tempInt > 255) {
					printf("Expected rgb value to be in range 0-255\n");
					return i;
				}				
				
				//save the color
				color = color + (tempInt << colorIndex);
				colorIndex -= 8;
				prevIndex = i;
			}
			else {
				printf("To many characters to parse for rgb value\n");
				return i;
			}
		}
	}
	
	//return values
	*_key = key;
	*_color = color;
	return -1;
}

//function to read the colors in for a particular arcade game
//@param filePath relative path from the lib folder to the color file to be parse
//@param errorCode the number to be returned from getColor if the key doesn't exist
uint8_t color_init(char* filePath, uint32_t _errorCode) {
	errorCode = _errorCode;
    
    for (uint16_t i = 0; i < MAX_COLORS; i++) {
		colors[i] = errorCode;
	}
    
    FILE *fp = fopen(filePath, "r");
	if (!fp)
	{
		fprintf(stderr, "Error opening file '%s'\n", filePath);
		return EXIT_FAILURE;
	}
    
    char* buffer = NULL;
    size_t lineSize = 0;
    int lineNum = 0;
    while (getline(&buffer, &lineSize, fp) > 0) {
		char key;
		uint32_t color = 0;
		int16_t parseResult = parseLine(&key, &color, buffer);
		
		if (parseResult > -1) {
			printf("Parsing %s failed on line: %d (%s) for token %c\n", filePath, lineNum, buffer, buffer[parseResult]);
			return errorCode;
		}
		else {//line was successfully parsed			
			colors[key] = color;
		}		
		lineNum++;
	}
	free(buffer);
	return 0;
}

//function to get the int version of a color given a color key
uint32_t color_getColor(char key) {
	if (key < MAX_COLORS) {		
		return colors[key];
	}
	else {
		return errorCode;
	}
}
