#include "hostcalls.h"

//local store for capabilitites, relative address usualy provided via AUX
char local_cap_store[0xabba];

#define MSG "hello second \n"

void outer_c() {
	host_write_out(MSG, sizeof(MSG));

	host_exit();
}

long syscall() {
	return 0;//not used
}