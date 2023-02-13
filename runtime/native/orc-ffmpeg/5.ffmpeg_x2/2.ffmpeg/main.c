#include "hostcalls.h"
#include <stdio.h>
#include <stdlib.h>

#define MSG "hello FFMpeg \n"


//local store for capabilitites, relative address usualy provided via AUX
char local_cap_store[0xabba];

#if 0
char *argv[] = {"ffmpeg", "-all", NULL};
int argc = 2;
#endif


#if 0
char *argv[] = {"ffmpeg", "-filters", NULL};
int argc = 2;
#endif

#if 0
char *argv[] = {"ffmpeg", "-codecs", NULL};
int argc = 2;
#endif


//NB: double dev/urandom may not work

//char *argv[] = {"ffmpeg", "-i", "/sound.wav",  "-acodec", "aac", "audio.mp4",  "-benchmark", NULL};
//int argc = 7;

#if 0
//"-re", 
//2700
char *argv[] = {"ffmpeg", "-f", "u16be", "-i", "/dev/urandom", "-f", "u16be", "-i", "/dev/urandom", "-filter_complex", "amerge", "-t", "2700", "-acodec", "aac", "-f", "mp4", "/dev/null", "-benchmark", NULL};
int argc = 19;
#endif

#if 1
//h263 doesn't work with LLVM Pass
//1280x720
//h263: 128x96, 176x144, 352x288, 704x576, and 1408x1152.
//mpeg4: 1025x768
//"-t", "10", 

//

char *argv[] = {"ffmpeg", "-re", "-f", "rawvideo", "-video_size", "128x96", "-pixel_format", "yuv420p", "-framerate", "30", 
			"-i", "/dev/urandom", "-ar", "48000", "-ac", "2", "-f", "s16le", 
			"-i", "/dev/urandom", "-codec:a", "copy", "-vf", "hue=s=0", 
			"-c:v", "mpeg4", "-map", "0:v", "-map", "1:a",
			"-f", "avi", "/dev/null", "-benchmark",  NULL};

int argc = 34;
#endif


//-loglevel debug
#if 0
//ffmpeg -re -f rawvideo -video_size 1024x768 -pixel_format yuv420p -framerate 30 -i /dev/urandom -ar 48000 -ac 2 -f s16le -i /dev/urandom -codec:a copy -vcodec mpeg4 
//-f mpegts tcp://0.0.0.0:2000\?listen -benchmark
ffplay -stats tcp://192.168.159.8:2000/ 
char *argv[] = {"ffmpeg", "-f", "rawvideo", "-video_size", "1024x768", "-pixel_format", "yuv420p", "-framerate", "30", 
			"-i", "/dev/urandom", "-ar", "48000", "-ac", "2", "-f", "s16le", 
			"-c:v", "mpeg4", "-map", "0:v",
			"-f", "mpegts", "tcp://0.0.0.0:2000\?listen", "-benchmark",  NULL}; //"-loglevel", "debug",

int argc = 25;

#endif

#if 0
char *argv[] = {"ffmpeg", "-all", NULL};
int argc = 2;

#endif

void outer_c() {
	host_write_out(MSG, sizeof(MSG));
	host_get_sc_caps(1, //me -- should be cap provided by Intravisor, not just a variable
			 2, //SCO LIbrary I want to use
			 (long) getTLS() + 2 * 32 ); 

	nolibos_init();

	mini_printf("ready to start ffmpeg\n");

	extern int ffmpeg_main(int argc, char **argv);
	ffmpeg_main(argc, argv);


	host_exit();
}

