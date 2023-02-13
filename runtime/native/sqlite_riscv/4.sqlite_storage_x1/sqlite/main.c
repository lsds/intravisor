#include "hostcalls.h"

//local store for capabilitites, relative address usualy provided via AUX
char local_cap_store[0xabba];

#define MSG "hello LibOS \n"
#define MSG2 "LibOS: intercepting message '"
#define ERR	"unknown t5\n"

static __inline__ void * getT5(void) {
    register void * t5 asm("ct5");
    asm ("" : "=r"(t5));
    return t5;
}

static __inline__ __intcap_t * getTLS(void) {
    register __intcap_t * t5 asm("ctp");
    asm ("" : "=C"(t5));
    return t5;
}


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

extern int speedtest_main(int argc, char **argv);
extern void nolibos_init();


#define comp_to_mon(a, b)	a
			extern int *__errno_location(void);

long syscall(void *a0, void *a1, void *a2, long a3, long a4, long a5, long a6, long a7) {
	long t5 = (long) getT5();
//	__intcap_t *tls = getTLS();

	int ret;

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
////		
		case 702:
			ret = host_get_sc_caps(a0, a1, a2);
			break;
////
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
		default:
			printf("unknown t5 %d\n", (int) t5);
			while(1);
//			host_write_out(ERR, sizeof(ERR));
	}

	return ret;
}


void outer_c() {
	host_write_out(MSG, sizeof(MSG));

	nolibos_init();

//	extern int dlmalloc_test(int argc, char **argv);
//	dlmalloc_test(1, 0);

	extern int speedtest_main(int argc, char **argv);
	speedtest_main(1, 0);


	host_exit();
}

