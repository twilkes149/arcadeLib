#include "sprite.h"
#include "video.h"

// Function to init the animation sequences
// ... searches the sprite's root directory
// ... for all of the sub-directories.
void init_sequences(char* rootDirectory) {

  // get a list of all the animation sequences (directories) within
  // ... the sprite's root directory
  DIR *d; // create a pointer to the directory
	struct dirent * dir;
	
	d = opendir(rootDirectory);//open the directory	
	if (d) {		
    while ((dir = readdir(d)) != NULL) {
      printf("%s", dir->d_name);
    }
  } else {		
		printf ("Cannot open directory '%s'\n", rootDirectory);
	}
}

//Reads a directory and inits an array of frames for a particular sprite
void sprite_init(char* directory, sprite_t* _sprite) {
	init_sequences(directory);
	//init sprite
	/*_sprite->numFrames = 0;
	_sprite->frames = malloc(sizeof(struct frame) * SPRITE_MAX_FRAMES);
	
	//read frames from sprite directory
	DIR *d;//create a pointer to the directory
	struct dirent * dir;
	
	d = opendir(directory);//open the directory	
	if (d) {		
    while ((dir = readdir(d)) != NULL && _sprite->numFrames < SPRITE_MAX_FRAMES) {
      if (strstr(dir->d_name, ".frame") != NULL) {//only get .frame files
				char buff[SPRITE_MAX_FRAME_NAME_LENGTH];
				sprintf(buff, "%s/%s", directory, dir->d_name);
				printf("%s\n", buff);
				
				frame_init(buff, &_sprite->frames[_sprite->numFrames]);
				_sprite->numFrames++;
			}
		}
		closedir(d);
	}
	else {		
		printf ("Cannot open directory '%s'\n", directory);
	}*/
}

//function to draw the next frame in the sprite's sequence
void sprite_animate(sprite_t* _sprite) {
	//iterate to the next frame
	if (++(_sprite->currentFrame) > SPRITE_MAX_FRAMES) {
		_sprite->currentFrame = 0;
	}
	
	video_drawFrame(_sprite->row, _sprite->col, &_sprite->sequences[_sprite->currentSequence][_sprite->currentFrame]);
}

void sprite_destroy(sprite_t* _sprite) {
  uint8_t i;
  for (i = 0; i < SPRITE_MAX_SEQUENCES; i++) {
    free(_sprite->sequences[i]);
  }
}
