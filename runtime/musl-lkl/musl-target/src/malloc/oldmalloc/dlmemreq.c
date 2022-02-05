#include <unistd.h>
#include <string.h>


void nginx_abort(void) {
	lkl_printf("abort has been called\n");while(1);
}

void *__expand_heap(size_t *pn)
{
    lkl_printf("expand_heap is not supported\n");
    while(1);
}

static void *ch_start = 0x10000000;
static long ch_ctr = 0;
static long ch_size = (50*1024*1024LL);

char* get_memory_nginx(unsigned num_bytes) {
//#ifdef DEBUG
    lkl_printf("get_mem nginx: %p/%x/%x/%lx\n", ch_start, ch_ctr, ch_size, num_bytes);
//#endif
//	if(ch_start == NULL) {
	if(ch_ctr == 0) {
		memset(ch_start, 0, ch_size);
		lkl_printf("NGINX HEAP: %p -- %p (%x)\n", ch_start, ch_start + ch_size, ch_size);
	}

	if(ch_ctr + num_bytes > ch_size) {
		lkl_printf("OOM, die\n");
		while(1);
	}

	char *ret = (char *) (ch_start + ch_ctr);
	ch_ctr += num_bytes;

	return ret;
}
