#include "crt.h"
#include "hostcalls.h"

//local store for capabilitites, relative address usualy provided via AUX
char local_cap_store[0xabba];

long tgv = 5;

#define MSG "BOOT: SCO Speedtest1 \n"
#define MSG2 "ST1: intercepting message '"
#define ERR	"ST1: unknown t5\n"

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


long syscall(void *a0, void *a1, void *a2, long a3, long a4, long a5, long a6, long a7) {
	long t5 = (long) getT5();
//	__intcap_t *tls = getTLS();

	char output[256];
	char *t;

	switch(t5) {
		case 1:
			host_write_out(a0, (unsigned long) a1);
			break;
		case 13:
			host_exit();
			break;
		case 1000:
			t = (char *) a0;
			my_memcpy(a0, a1, (unsigned long) a2);
			t[0]='0' + tgv++;
			break;
		case 1001:
		default:
			host_write_out(ERR, sizeof(ERR));
	}

	return 0;
}

extern int speedtest_main(int argc, char **argv);
extern void nolibos_init();

extern const char *sqlite3_sourceid(void);

void outer_c() {
	host_write_out(MSG, sizeof(MSG));

	char dummy[16];

	host_get_sc_caps(3, //me -- should be cap provided by Intravisor, not just a variable
			 1, //SCO SQLite
			 (long) getTLS() + 1 * 32);

	host_get_sc_caps(3, //me -- should be cap provided by Intravisor, not just a variable
			 2, //SCO VFS
			 (long) getTLS() + 2 * 32);  //2 * 32 -- ugly and needs to be changed inside Intravisor, but I will leave it as is for compatability with previous versions

	host_get_sc_caps(3, //me -- should be cap provided by Intravisor, not just a variable
			 4, //SCO RAMFS
			 (long) getTLS() + 4 * 32);

	host_get_sc_caps(3, //me -- should be cap provided by Intravisor, not just a variable
			 5, //SCO LibC
			 (long) getTLS() + 5 * 32);

//	host_syscall_handler_prb("libsco_libc.so", &local_cap_store[16*5], &local_cap_store[16*6], dummy);
	host_syscall_handler_prb("libsco_libc.so", 0x30000000 + 0xe001000 + 16*5, 0x30000000 + 0xe001000 + 16*6, dummy);

	ramfs_caps_init();

	vfs_caps_init();

	nolibc_caps_init();

	sqlite_caps_init();

	host_nolibos_init();

	extern int speedtest_main(int argc, char **argv);
	speedtest_main(1, 0);

	host_exit();
}

