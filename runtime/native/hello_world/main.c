#include "hostcalls.h"

#define MSG "hello world, let's read cap 'test1' \n"

void out_c() {
	char buf[32];
	char cap[16]; //place to store the capability
	long size;

	host_write_out(MSG, sizeof(MSG));

	host_cap_prb("test1", cap, &size);

	copy_from_cap(buf, cap, 32);

	host_write_out(buf, 32);

	host_exit();
}

