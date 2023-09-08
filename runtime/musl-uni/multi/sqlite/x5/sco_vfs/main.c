#include "crt.h"
#include "hostcalls.h"

//local store for capabilitites, relative address usualy provided via AUX
char local_cap_store[0xabba];

long tgv = 5;

#define MSG "BOOT: SCO VFS \n"
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

#define comp_to_mon(a, b)	a
extern int *__errno_location(void);
extern __intcap_t syscalls_vfs(int, void *, void *, void*);
void vfs_caps_init();
extern void nolibos_init();

__intcap_t syscall(void *a0, void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7) {
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
		case 801:
			ret = my_lstat(comp_to_mon(a0, ct->sbox), comp_to_mon(a1, ct->sbox));
			ret = 0;
			break;
		case 806:
			ret = my_stat(comp_to_mon(a0, ct->sbox), comp_to_mon(a1, ct->sbox));
			break;
		case 807:
			ret = my_fstat(a0, comp_to_mon(a1, ct->sbox));
//			printf("fstat: st_dev = %x, st_ino = %x\n", statbuf.st_dev, statbuf.st_ino);
			break;
		case 802:
			ret = my_unlink(a0);
			break;
		case 803:
			ret = my_close(a0);
			break;
		case 804:
			ret = my_access(comp_to_mon(a0, ct->sbox), a1);
			break;
		case 808:
			ret = my_truncate(comp_to_mon(a0, ct->sbox), a1);
			break;
		case 809:
//			printf("read = %d, %p, %d\n", a0, comp_to_mon(a1, ct->sbox), a2);
			ret = my_read(a0, comp_to_mon(a1, ct->sbox), a2);
//			printf("read ret = %d\n", ret);
			break;
		case 810:
			ret = my_write(a0, comp_to_mon(a1, ct->sbox), a2);
			break;
		case 811:
			ret = my_open(comp_to_mon(a0, ct->sbox), a1, a2);
//			ret = open(comp_to_mon(a0, ct->sbox), O_RDWR | O_CREAT, 0666);
			break;
		case 812:
//			printf("lseek set %d %d %d\n", a0, a1, a2);
			ret = my_lseek(a0, a1, a2);
//			printf("lseek ret = %d\n", ret);
			break;

		case 813:

			ret = (*__errno_location());
			break;

		case 814:
			ret = my_fcntl(a0, a1, comp_to_mon(a3, ct->sbox));
			break;
		case 815:
			nolibos_init();
			break;
		case 1000:
		case 1001:
		case 1002:
		case 1003:
		case 1004:
			ret = syscalls_vfs(t5, a0, a1, a2);
			break;
		case 1005:
			vfs_caps_init();
			break;
		default:
			printf("VFS: unknown t5 %d\n", (int) t5);
			while(1);
//			host_write_out(ERR, sizeof(ERR));
	}

	return ret;
}

extern int speedtest_main(int argc, char **argv);


void vfs_caps_init() {
	char dummy[16];

//	host_syscall_handler_prb("libsco_libc.so", &local_cap_store[16*5], &local_cap_store[16*6], dummy);
	host_syscall_handler_prb("libsco_libc.so", 0x20000000 + 0xe001000 + 16*5, 0x20000000 + 0xe001000 + 16*6, dummy);
}

void outer_c() {
	host_write_out(MSG, sizeof(MSG));

#if 1
	char dummy[16];
//	host_syscall_handler_prb("libsco_libc.so", &local_cap_store[16*5], &local_cap_store[16*6], dummy);
	host_syscall_handler_prb("libsco_libc.so", 0x20000000 + 0xe001000 + 16*5, 0x20000000 + 0xe001000 + 16*6, dummy);

#endif

	host_exit();
}

