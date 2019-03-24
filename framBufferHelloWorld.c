#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

#define BYTE_SIZE 8

// application entry point
int main(int argc, char* argv[])
{
  int fbfd = 0; // framebuffer filedescriptor
  struct fb_var_screeninfo var_info;
  struct fb_fix_screeninfo finfo;
  long int screensize = 0;
  char *fbp = 0;

  int screenWidth, screenHeight, bytesPerPixel;

  // Open the framebuffer device file for reading and writing
  fbfd = open("/dev/fb0", O_RDWR);
  if (fbfd == -1) {
    printf("Error: cannot open framebuffer device.\n");
    return(1);
  }
  printf("The framebuffer device opened.\n");

  //get fixed screen information
  if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
    printf("Error reading fixed information.\n");
  }

  // Get variable screen information
  if (ioctl(fbfd, FBIOGET_VSCREENINFO, &var_info)) {
    printf("Error reading variable screen info.\n");
  }
  printf("Display info %dx%d, %d bpp\n", 
         var_info.xres, var_info.yres, 
         var_info.bits_per_pixel );

  //save information about the screen size
  screenWidth = var_info.xres;
  screenHeight = var_info.yres;
  bytesPerPixel = var_info.bits_per_pixel/BYTE_SIZE;

  //map the frambuffer to user space memory
  screensize = finfo.smem_len;

  fbp = (char*) mmap(0,screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
  if ((int) fbp == -1) {
    printf("Failed to mmap frame buffer\b");
  }
  else {
   // memset(fbp, 0xff, screensize/2);//write a color to the upper half
   //memset(fbp+screensize/2, 0x18, screensize/2);//write a color to the lower half

    for (int i = 0; i < screenWidth*4; i+=4) {
      fbp[i+ 10*finfo.line_length] = 0x00;//blue
      fbp[i+1 + 10*finfo.line_length] = 0x00;//green
      fbp[i+2 + 10*finfo.line_length] = 0xFF;//red
      fbp[i+3 + 10*finfo.line_length] = 0x00;//alpha
    }
  }

  //unmap the memory
  munmap(fbp, screensize);
  // close file  
  close(fbfd);
  
  return 0;

}

