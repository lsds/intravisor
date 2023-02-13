#include "hostcalls.h"

//local store for capabilitites, relative address usualy provided via AUX
char local_cap_store[0xabba];

#define MSG "hello LibOS \n"
#define ERR	"unknown t5\n"

long tgv = 5;

void *my_memcpy(void *dst, void *src, unsigned long n) {
	int i;
	char *d = dst;
	char *s = src;
	for (i = 0; i < n; i++) {
		d[i] = s[i];
	}

	return dst;
}

long syscall(void *a0, void *a1, void *a2, long a3, long a4, long a5, long a6, long a7) {
	long t5 = (long) getT5();

	int ret;

	char output[256];
	char *t;

	switch(t5) {
		case 1:
			host_write_out(a0, (unsigned long) a1);
			break;
		case 13:
			host_exit();
			break;
		case 702:
			ret = host_get_sc_caps(a0, a1, a2);
			break;
		case 1000:
			t = (char *) a0;
			my_memcpy(a0, a1, (unsigned long) a2);
			t[0]='0' + tgv++;
			break;
		default:
			__asm__ __volatile__ ("brk 0");
			host_write_out(ERR, sizeof(ERR));
			while(1);
	}

	return ret;
}

void outer_c() {
//while this code will print something to console, in fact, it will breake the next LLVM stuff.
//get a pointer MSG, LLVM will create 'variables' that countain 0/0, and use the same later for printf
//	host_write_out(MSG, sizeof(MSG));

	host_exit();
}

