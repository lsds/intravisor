#include "crt.h"
#include "hostcalls.h"

#define MSG "hello outer layer \n"
#define ERR	"unknown t5\n"

static __inline__ void * getT5(void) {
    register void * t5 asm("t5");
    asm ("" : "=r"(t5));
    return t5;
}


long syscall(long a0, long a1, long a2, long a3, long a4, long a5, long a6, long a7) {
	long t5 = (long) getT5();

	switch(t5) {
		case 1:
			host_write(a0, a1);
			break;
		case 13:
			host_exit();
			break;
		default:
			host_write(ERR, sizeof(ERR));
	}
}

void outer_c() {
	host_write(MSG, sizeof(MSG));

#define RET_TO_INNER_PPC	(16*13)
	host_get_my_inner(local_cap_store + RET_TO_INNER_PPC);

	host_exit();
}

