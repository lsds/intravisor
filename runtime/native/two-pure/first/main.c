//#include "crt.h"
#include "hostcalls.h"

//local store for capabilitites, relative address usualy provided via AUX
char local_cap_store[0xabba];

#define MSG "hello first(syscall-handler) \n"
#define ERR	"unknown t5\n"


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
		default:
			host_write_out(ERR, sizeof(ERR));
			while(1);
	}

	return ret;
}

void outer_c() {
	host_write_out(MSG, sizeof(MSG));

	host_exit();
}

