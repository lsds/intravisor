#include "hostcalls.h"
#include <stdio.h>
#include <stdlib.h>

//local store for capabilitites, relative address usualy provided via AUX
char local_cap_store[0xabba];

#define MSG "hello musl-uni \n"
#define ERR	"unknown t5\n"

extern void nolibos_init();

long syscall(void *a0, void *a1, void *a2, long a3, long a4, long a5, long a6, long a7) {
	int ret;
	long t5 = (long) getT5();

	switch (t5) {
	case 1:
		host_write_out(a0, (unsigned long) a1);
		break;
	case 13:
		host_exit(a0);
		break;
	default:
		printf("unknown t5 %d\n", (int) t5);
		while(1) ;
	}

	return ret;
}

void outer_c() {
	host_write_out(MSG, sizeof(MSG));

	nolibos_init();

	printf("--------- LibOS is ok,  ------- \n");
	printf("\n");

	extern int app_main();
	int ret = app_main();

	host_exit(ret);
}
