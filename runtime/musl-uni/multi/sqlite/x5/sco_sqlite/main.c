#include "crt.h"
#include "hostcalls.h"

//local store for capabilitites, relative address usualy provided via AUX
char local_cap_store[0xabba];

long tgv = 5;

#define MSG "BOOT: SQLite \n"
#define MSG2 "SQLite: intercepting message '"
#define ERR	"SQLite: unknown t5\n"

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

void sqlite_caps_init();

extern __intcap_t sqlite_syscalls(long t5, void *a0, void *a1, void *a2, void  *a3, void *a4, void *a5, void *a6);

__intcap_t syscall(void *a0, void *a1, void *a2, void  *a3, void *a4, void *a5, void *a6, void *a7) {
	long t5 = (long) getT5();
//	__intcap_t *tls = getTLS();

	char output[256];
	char *t;

	__intcap_t ret = 0;
//	printf("SQLite: incomming syscall %d\n", (int) t5);
	switch(t5) {
		case 1:
			host_write_out(a0, (unsigned long) a1);
			break;
		case 13:
			host_exit();
			break;
		case 701:
			ret = host_syscall_handler_prb(a0, a1, a2, a3);
			break;
		case 702:
			ret = host_get_sc_caps(a0, a1, a2);
			break;
		case 750:
			ramfs_caps_init();
			break;
		case 752:
			nolibc_caps_init();
			break;
		case 802:
			ret = host_unlink(a0);
			break;
		case 815:
			host_nolibos_init();
			break;
		case 900:
		case 901:
		case 902:
		case 903:
		case 904:
		case 905:
		case 906:
		case 907:
		case 908:
		case 909:
		case 910:
		case 911:
		case 912:
		case 913:
		case 914:
		case 915:
		case 916:
		case 917:
		case 918:
		case 919:
		case 920:
		case 921:
		case 922:
		case 923:
		case 924:
		case 925:
		case 926:
		case 927:
		case 928:
		case 929:
		case 930:
		case 931:
		case 932:
		case 933:
		case 934:
			ret = sqlite_syscalls(t5, a0, a1, a2, a3, a4, a5, a6);
			break;
		case 935:
			sqlite_caps_init();
			break;
		case 1005:
			vfs_caps_init();
			break;
		default:
			printf("SQLite: unknown syscall %d\n", (int) t5); while(1);
	}

	return ret;
}

extern int speedtest_main(int argc, char **argv);

void sqlite_caps_init() {
	char dummy[16];

//	host_syscall_handler_prb("libsco_libc.so", &local_cap_store[16*5], &local_cap_store[16*6], dummy);
	host_syscall_handler_prb("libsco_libc.so", 0x10000000 + 0xe001000 + 16*5, 0x10000000 + 0xe001000 + 16*6, dummy);
}


void outer_c() {
	host_write_out(MSG, sizeof(MSG));

#if 1
	char dummy[16];
//	host_syscall_handler_prb("libsco_libc.so", &local_cap_store[16*5], &local_cap_store[16*6], dummy);
	host_syscall_handler_prb("libsco_libc.so", 0x10000000 + 0xe001000 + 16*5, 0x10000000 + 0xe001000 + 16*6, dummy);

#endif

	host_exit();
}

