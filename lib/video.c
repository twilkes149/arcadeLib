#include "video.h"

#define BYTE_SIZE 8

static int fbfd = 0; // framebuffer filedescriptor
static struct fb_var_screeninfo var_info;
static struct fb_fix_screeninfo finfo;
static long int screensize = 0;
static char *fbp = 0;

static int screenWidth, screenHeight, bytesPerPixel, lineLength;

//function to open the video buffer and map memory to user space
uint8_t video_init() {
  // Open the framebuffer device file for reading and writing
  fbfd = open("/dev/fb0", O_RDWR);
  if (fbfd == -1) {
    printf("Error: cannot open framebuffer device.\n");
    return VIDEO_ERROR;
  }  

  //get fixed screen information
  if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
    printf("Error reading fixed information.\n");
    return VIDEO_ERROR;
  }

  // Get variable screen information
  if (ioctl(fbfd, FBIOGET_VSCREENINFO, &var_info)) {
    printf("Error reading variable screen info.\n");
    return VIDEO_ERROR;
  }

  //save information about the screen size
  screenWidth = var_info.xres;
  screenHeight = var_info.yres;
  bytesPerPixel = var_info.bits_per_pixel/BYTE_SIZE;
  lineLength = finfo.line_length;

  //map the frambuffer to user space memory
  screensize = finfo.smem_len;
  fbp = (char*) mmap(0,screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
  if ((int) fbp == -1) {
    printf("Failed to mmap frame buffer\b");
    return VIDEO_ERROR;
  }
  
  return VIDEO_SUCCESS;
}

//functions to get information about the screen
int video_getScreenWidth() {
	return screenWidth;
}

int video_getScreenHeight() {
	return screenHeight;
}

//function that will write a single pixel of the screen
void video_drawPixel(uint16_t row, uint16_t col, uint32_t color) {
	col *= bytesPerPixel;//make column byte aligned instead of pixel aligned
	
	fbp[col + row*lineLength] = (color & 0x0000FF00) >> 8;//write blue
	fbp[col+1 + row*lineLength] = (color & 0x00FF0000) >> 16;//write green
	fbp[col+2 + row*lineLength] = (color & 0xFF000000) >> 24;//write red
	fbp[col+3 + row*lineLength] = 0x00;//write alpha
}

//function to draw a line of length <length> and color <color>
void video_drawLine(uint16_t row, uint16_t col, uint16_t length, uint32_t color) {
	for (uint32_t i = 0; i < length; i++) {
		video_drawPixel(row, i+col, color);
	}
}

//function to free memory and close the video file
void video_close() {
  //unmap the memory
  munmap(fbp, screensize);
  
  // close file  
  close(fbfd);
}
