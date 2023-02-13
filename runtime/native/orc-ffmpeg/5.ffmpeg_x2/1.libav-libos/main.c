#include "crt.h"
#include "hostcalls.h"
#include <stdio.h>
#include <stdlib.h>

//local store for capabilitites, relative address usualy provided via AUX
char local_cap_store[0xabba];

#define MSG "hello LibOS \n"
#define ERR	"unknown t5\n"


void *my_memcpy(void *dst, void *src, unsigned long n) {
	int i;
	char *d = dst;
	char *s = src;
	for (i = 0; i < n; i++) {
		d[i] = s[i];
	}

	return dst;
}

void *my_memset(void *dst, char c, unsigned long n) {
	int i;
	char *d = dst;
	for (i = 0; i < n; i++) {
		d[i] = c;
	}

	return dst;
}

extern void nolibos_init();
extern int ffmpeg_main(int argc, char **argv);

#define comp_to_mon(a, b)	a
			extern int *__errno_location(void);

long syscall(void *a0, void *a1, void *a2, long a3, long a4, long a5, long a6, long a7) {
	long t5 = (long) getT5();

	int ret;

	char output[256];
	char *t;

//	printf("t5 = %d\n", (int) t5);

	switch(t5) {
		case 1:
			host_write_out(a0, (unsigned long) a1);
			break;
		case 13:
			host_exit();
			break;
////		
		case 702:
			ret = host_get_sc_caps(a0, a1, a2);
			break;
////
		case 800:
			ret = host_gettimeofday(a0, a1);
			break;
		case 801:
			ret = my_lstat(comp_to_mon(a0, ct->sbox), comp_to_mon(a1, ct->sbox));
			ret = 0;
			break;
		case 806:
			ret = my_stat(comp_to_mon(a0, ct->sbox), comp_to_mon(a1, ct->sbox));
			break;
		case 807:
			ret = my_fstat(a0, comp_to_mon(a1, ct->sbox));
//			printf("fstat: st_dev = %x, st_ino = %x\n", statbuf.st_dev, statbuf.st_ino);
			break;
		case 802:
			ret = my_unlink(a0);
			break;
		case 803:
			ret = my_close(a0);
			break;
		case 804:
			ret = my_access(comp_to_mon(a0, ct->sbox), a1);
			break;
		case 808:
			ret = my_truncate(comp_to_mon(a0, ct->sbox), a1);
			break;
		case 809:
//			printf("read = %d, %p, %d\n", a0, comp_to_mon(a1, ct->sbox), a2);
			ret = my_read(a0, comp_to_mon(a1, ct->sbox), a2);
//			printf("read ret = %d\n", ret);
			break;
		case 810:
			ret = my_write(a0, comp_to_mon(a1, ct->sbox), a2);
			break;
		case 811:
			ret = my_open(comp_to_mon(a0, ct->sbox), a1, a2);
//			ret = open(comp_to_mon(a0, ct->sbox), O_RDWR | O_CREAT, 0666);
			break;
		case 812:
//			printf("lseek set %d %d %d\n", a0, a1, a2);
			ret = my_lseek(a0, a1, a2);
//			printf("lseek ret = %d\n", ret);
			break;

		case 813:

			ret = (*__errno_location());
			break;

		case 814:
			ret = my_fcntl(a0, a1, comp_to_mon(a3, ct->sbox));
			break;
		case 815:
			nolibos_init();
			break;
		case 816:

			ret = ffmpeg_main(a0, a1);
			break;
		default:
			printf("unknown t5 %d\n", (int) t5);
			while(1);
//			host_write_out(ERR, sizeof(ERR));
	}

	return ret;
}

#include "root_cpio.h"


void outer_c() {
//while this code will print something to console, in fact, it will breake the next LLVM stuff.
//get a pointer MSG, LLVM will create 'variables' that countain 0/0, and use the same later for printf
//	host_write_out(MSG, sizeof(MSG));

	host_exit();
}

