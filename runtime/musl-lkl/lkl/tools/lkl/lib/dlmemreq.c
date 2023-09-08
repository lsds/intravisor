#include "dlmemreq.h"

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

//#define DEBUG

void lkl_host_abort(void) {
	lkl_printf("abort has been called\n");while(1);
}

void *__expand_heap(size_t *pn)
{
    lkl_printf("expand_heap is not supported\n");
    while(1);
}

static void *ch_start = NULL;
static long ch_ctr = 0;
#define S_SIZE	(200*1024*1024LL)
static long ch_size = S_SIZE;

static char s_heap[S_SIZE]  __attribute__ ((aligned (16)));

char* get_memory_netdev(unsigned num_bytes) {
#ifdef DEBUG
    lkl_printf("get_mem netdev: %p/%x/%x/%lx\n", ch_start, ch_ctr, ch_size, num_bytes);
#endif
	if(ch_start == NULL) {
		ch_start = s_heap;
		memset(ch_start, 0, ch_size);
		lkl_printf("HEAP: %p -- %p (%x)\n", ch_start, ch_start + ch_size, ch_size);
		ch_ctr = 0;
	}

	if(ch_ctr + num_bytes > ch_size) {
		lkl_printf("OOM, die\n");
		while(1);
	}

	char *ret = (char *) (ch_start + ch_ctr);
	ch_ctr += num_bytes;

	return ret;
}
