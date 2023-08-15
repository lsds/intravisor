#include "monitor.h"

static int shm_fd = -1;

int host_get_sc_caps(int me, int they, void *ptr) {
#ifndef SCO
	return 0;
#endif
#if arm_sim
	return 0;
#endif
	printf("GET SCO CAPS: %d %d %p\n", me, they, ptr);
	void *sbuf;
#if 0
	sbuf = malloc(cvms[they].box_size);
	if(!sbuf) {
		printf("cannot alloc memory for shadow SCO of %lx bytes\n", cvms[they].box_size);
		while(1) ;
	}
#else
	sbuf = mmap(0, cvms[they].box_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if(sbuf == MAP_FAILED) {
		perror("mmap");
		while(1) ;
	}
#endif

#warning host_get_sc_caps should be checked for CLEAN_ROOM

	void *__capability dcap = datacap_create(sbuf, sbuf + cvms[they].box_size, 0);

//      TODO: actually we shold copy only data/bss
	memcpy(sbuf, cvms[they].base, cvms[they].box_size);

	int ret1 = munmap(sbuf, cvms[they].end_of_ro);
	int ret2 = munmap(sbuf + cvms[they].box_size - cvms[they].extra_load, cvms[they].extra_load);

	printf("clonned %p--%p to %p--%p, first %lx unmapped = %d , payload %lx unmapped = %d\n", cvms[they].base, cvms[they].base + cvms[they].box_size, sbuf, sbuf + cvms[they].box_size,
	       cvms[they].end_of_ro, ret1, cvms[they].extra_load, ret2);

	st_cap(ptr + 128, dcap);

	long tmp = cvms[they].base;

	memcpy(ptr + 144, &tmp, sizeof(long));
}
