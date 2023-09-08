#include "crt.h"
#include "hostcalls.h"

//local store for capabilitites, relative address usualy provided via AUX
char local_cap_store[0xabba];

long tgv = 5;

#define MSG "BOOT: SCO LIBC \n"
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

extern int mini_vsnprintf(char *buffer, unsigned int buffer_len, const char *fmt, va_list va);
extern _Noreturn void __assert_fail (const char *, const char *, int, const char *);
extern void *my_malloc(size_t size);
extern void my_free(void *ptr);
extern void *my_realloc(void *ptr, size_t size);
extern void *my_calloc(size_t count, size_t size);

void nolibc_caps_init();

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
		case 752:
			nolibc_caps_init();
			break;
		case 800:
			ret = host_gettimeofday(a0, a1);
			break;

		case 1100:
			ret = my_malloc(a0);
			break;
		case 1101:
			my_free(a0);
			break;
		case 1102:
			ret = my_realloc(a0, a1);
			break;
		case 1103:
			ret = strcmp(a0, a1);
			break;
		case 1104:
			ret = memcpy(a0, a1, a2);
			break;
		case 1105:
			ret = strlen(a0);
			break;
		case 1106:
			__assert_fail (a0, a1, a2, a3);
			break;
		case 1107:
			ret = mini_vsnprintf(a0, a1, a2, a3);
			break;
		case 1108:
			ret = memset(a0, a1, a2);
			break;
		case 1109:
			ret = puts(a0);
			break;
		case 1110:
			ret = putchar(a0);
			break;
		case 1111:
			ret = __errno_location();
			break;
		case 1112:
			ret = bcmp(a0, a1, a2);
			break;
		case 1113:
			ret = memmove(a0, a1, a2);
			break;
		case 1114:
			ret = strncmp(a0, a1, a2);
			break;
		case 1115:
			ret = strcspn(a0, a1);
			break;
		case 1116:
			ret = memcmp(a0, a1, a2);
			break;
		case 1117:
			ret = my_calloc(a0, a1);
			break;
		case 1118:
			ret = strdup(a0);
			break;
		case 1119:
			ret = strlcat(a0, a1, a2);
			break;
		case 1120:
			ret = strlcpy(a0, a1, a2);
			break;
		case 1121:
			ret = strrchr(a0, a1);
			break;
		case 1123:
			ret = strndup(a0, a1);
			break;
		default:
			printf("LIBC: unknown t5 %d\n", (int) t5);
			while(1);
	}

	return ret;
}

extern int speedtest_main(int argc, char **argv);
extern void nolibos_init();

int done = 0;

//remove?
void nolibc_caps_init() {
//libc doesn't call functions, so it doesn't need to retrive caps
}

void outer_c() {
	host_write_out(MSG, sizeof(MSG));

	host_exit();
}

