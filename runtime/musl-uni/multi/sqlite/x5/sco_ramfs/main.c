#include "crt.h"
#include "hostcalls.h"

//local store for capabilitites, relative address usualy provided via AUX
char local_cap_store[0xabba];

long tgv = 5;

#define MSG "BOOT: SCO RAMFS \n"
#define MSG2 "Outer: intercepting message '"
#define ERR	"unknown t5\n"

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


void ramfs_caps_init();
#define comp_to_mon(a, b)	a
extern int *__errno_location(void);

extern __intcap_t ramfs_syscalls(long t5, void *a0, void *a1, void *a2, void  *a3, void *a4, void *a5, void *a6);

__intcap_t syscall(void *a0, void *a1, void *a2, void *a3, void *a4, void *a5, void *a6) {
	long t5 = (long) getT5();
//	__intcap_t *tls = getTLS();

	__intcap_t ret;

	char output[256];
	char *t;

//	printf("t5 = %d\n", (int) t5);

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
		case 800:
			ret = host_gettimeofday(a0, a1);
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
			ret = ramfs_syscalls(t5, a0, a1, a2, a3, a4, a5, a6);
			break;
		default:
			printf("RAMFS: unknown t5 %d\n", (int) t5);
			while(1);
//			host_write_out(ERR, sizeof(ERR));
	}

	return ret;
}

extern int speedtest_main(int argc, char **argv);
extern void nolibos_init();

void ramfs_caps_init() {
	char dummy[16];

//	host_syscall_handler_prb("libsco_vfs.so", &local_cap_store[16*5], &local_cap_store[16*6], dummy);
//	host_syscall_handler_prb("libsco_libc.so", &local_cap_store[16*8], &local_cap_store[16*9], dummy);

	host_syscall_handler_prb("libsco_vfs.so", 0x60000000 + 0xe001000 + 16*5, 0x60000000 + 0xe001000 + 16*6, dummy);
	host_syscall_handler_prb("libsco_libc.so", 0x60000000 + 0xe001000 + 16*8, 0x60000000 + 0xe001000 + 16*9, dummy);


}

void outer_c() {
	host_write_out(MSG, sizeof(MSG));

	char dummy[16];

//in riscv, local_cap_store points to _base_ + 0xe001000. when this code is executing in the context of 'init' thread,
//despite the existance of the llvm pass, local_cap_store anyway points to the same address (simply because offset caps from the pass are 0).
//later, asm code, which is completely unaware about the pass use these addresses directly. 
//this is wrong, but it works.
//in arm, we don't change local_cap_store, so this code requires full address, which is also wrong and needs to be changed. 

//	host_syscall_handler_prb("libsco_vfs.so", &local_cap_store[16*5], &local_cap_store[16*6], dummy);
//	host_syscall_handler_prb("libsco_libc.so", &local_cap_store[16*8], &local_cap_store[16*9], dummy);

	host_syscall_handler_prb("libsco_vfs.so", 0x60000000 + 0xe001000 + 16*5, 0x60000000 + 0xe001000 + 16*6, dummy);
	host_syscall_handler_prb("libsco_libc.so", 0x60000000 + 0xe001000 + 16*8, 0x60000000 + 0xe001000 + 16*9, dummy);

	host_exit();
}

