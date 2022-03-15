#include "crt.h"
#include "hostcalls.h"

//local store for capabilitites, relative address usualy provided via AUX
char local_cap_store[0xabba];

#define MSG "hello outer layer \n"
#define MSG2 "Outer: intercepting message '"
#define ERR	"unknown t5\n"

static __inline__ void * getT5(void) {
    register void * t5 asm("ct5");
    asm ("" : "=r"(t5));
    return t5;
}

void *memcpy(void *dst, void *src, int n) {
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
	char output[256];

	switch(t5) {
		case 1:
			memcpy(output, MSG2, sizeof(MSG2));
			memcpy(&output[sizeof(MSG2)], a0, a1);
			host_write(output, sizeof(MSG2) + a1);
			break;
		case 13:
			host_exit();
			break;
		default:
			host_write(ERR, sizeof(ERR));
	}

	return 0;
}

void outer_c() {
	host_write(MSG, sizeof(MSG));

#define RET_TO_INNER_PPC	(16*13)
	host_get_my_inner(local_cap_store + RET_TO_INNER_PPC);

	host_exit();
}

