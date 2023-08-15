#include "hostcalls.h"

extern long c_out(void *);

int host_write_out(char __capability *ptr, int size) {
	return (int) c_out_3(1, ptr, (long) size, 0);
}

void host_exit() {
	c_out_3(13, 0, 0, 0);
}

