#include <stdio.h>
#include <stdlib.h>


//1280x720
//h263: 128x96, 176x144, 352x288, 704x576, and 1408x1152.
//mpeg4: 1025x768
//"-t", "10", 

char *argv[] = {"ffmpeg", "-f", "rawvideo", "-video_size", "128x96", "-pixel_format", "yuv420p", "-framerate", "30", 
			"-i", "/dev/urandom", "-ar", "48000", "-ac", "2", "-f", "s16le", 
			"-i", "/dev/urandom", "-codec:a", "copy", "-vf", "hue=s=0", 
			"-c:v", "h263", "-map", "0:v", "-map", "1:a",
			"-f", "avi", "/dev/null", "-benchmark",  NULL};

int argc = 33;



void app_main() {
	printf("app main\n");

	extern int ffmpeg_main(int argc, char **argv);
	ffmpeg_main(argc, argv);


}