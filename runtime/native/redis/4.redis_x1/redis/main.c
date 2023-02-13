#include "hostcalls.h"
#include <stdio.h>
#include <stdlib.h>

//local store for capabilitites, relative address usualy provided via AUX
char local_cap_store[0xabba];

#define MSG "hello LibOS \n"

#if 0
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
#endif
extern void nolibos_init();


long syscall(void *a0, void *a1, void *a2, long a3, long a4, long a5, long a6, long a7) {
//syscalls dont exist in this configuration
}

#include "root_cpio.h"

#if 1
//./redis-server --daemonize no --save "" --bind 0.0.0.0
char *argv[] = {"redis-server", "--daemonize", "no", "--save", "\"\"", "--bind", "127.0.0.1", "--port", "6379", NULL};
int argc = 9;

#endif


void outer_c() {
	host_write_out(MSG, sizeof(MSG));

	nolibos_init();

	extern void copy_cpio(intptr_t *name);

	copy_cpio((intptr_t *) root_cpio);

	printf("ready to start redis \n");

	extern int redis_main(int argc, char **argv);
	redis_main(argc, argv);


	host_exit();
}

