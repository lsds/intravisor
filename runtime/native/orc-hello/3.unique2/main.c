#include "hostcalls.h"

//local store for capabilitites, relative address usualy provided via AUX
char local_cap_store[0xabba];

#define MSG "hello U2\n"
#define MSG2 " :In buffer U2\n"

void outer_c() {
	char dst[32];

	host_write_out(MSG, sizeof(MSG));
	host_get_sc_caps(1, //me -- should be cap provided by Intravisor, not just a variable
			 2, //SCO LIbrary I want to use
			 (long) getTLS() + 2 * 32 ); 

	for(int i = 0; i < 5; i++) {

		host_inv(dst, MSG2, sizeof(MSG2));

		host_write_out(dst, sizeof(dst));

	}

	while(1);
}

