#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <alloca.h>
#include <stdio.h>

#include "checkmacros.h"

int x = 42;
int y = 9;
int z = 0;

/* We need this wrapper to force compiler use memcpy */
__attribute__ ((naked,noinline))
static void *copy_bytes(register void * c0, register void *c1, register size_t x2)
{
#if defined(__aarch64__)
	__asm__ volatile ("b memcpy\n");
#elif defined(__x86_64__)
	__asm__ volatile ("jmp memcpy\n");
#else
#error "Not implemented"
#endif
}

#define CHECK(res, dst, src, num) ({                          \
	int u = 0;                                                \
	if (res != dst) {                                         \
		printf("%s: result != destination: %#p != %#p\n",     \
			__func__, (void *)res, (void *)dst);              \
		u = 1;                                                \
	}                                                         \
	size_t f;                                                 \
	if(u == 0 && (f = COMPARE_BYTES(res, src, num))) {        \
	printf("%s: bytes are not equal at offset %zu\n",         \
		__func__, f - 1);                                     \
		u = 2;                                                \
	}                                                         \
	if(u == 0 && (f = CHECK_MEM_TAGS(res, src, num))) {       \
		printf("%s: mem tags are not equal at offset %zu\n",  \
			__func__, f - 1);                                 \
		u = 3;                                                \
	}                                                         \
	u;                                                        \
})

/* Test 16-byte aligned memory regions */
static int test_aligned(int n)
{
	int a, b;
	int **p = (int **)alloca(n);
	memset(p, 0, n);
	if (n >= 16) p[0] = &x;
	if (n >= 32) p[1] = &y;
	if (n >= 48) p[2] = &z;
	if (n >= 64) p[3] = NULL;
	if (n >= 80) p[4] = &a;
	if (n >= 96) p[5] = &b;
	void *q = alloca(n);
	memset(q, 0, n);
	void *r = copy_bytes(q, p, n);
	return CHECK(r, q, p, n);
}

static int test_aligned_offset(int n, int b, int a)
{
	char *p = (char *)alloca(n);
	memset(p, 0, n);
	int **t = (int **)p;
	if (n >= 32) {
		t[1] = &x;
	}
	if (n >= 64) {
		t[3] = &y;
	}
	if (n >= 96) {
		t[5] = &z;
	}
	char *q = (char *)alloca(n);
	memset(q, 0, n);
	p = p + b;
	q = q + b;
	void *r = copy_bytes(q, p, n - (b + a));
	return CHECK(r, q, p, n - (b + a));
}

static int test_misaligned(int n, int d)
{
	char *p = (char *)alloca(n);
	memset(p, 0, n);
	int **t = (int **)p;
	if (n >= 32) {
		t[1] = &x;
	}
	if (n >= 64) {
		t[3] = &y;
	}
	if (n >= 96) {
		t[5] = &z;
	}
	char *q = (char *)alloca(n + d);
	memset(q, 0, n + d);
	q = q + d;
	void *r = copy_bytes(q, p, n);
	return CHECK(r, q, p, n);
}

int main (int argc, char *argv[])
{
	                                                    /** # and . means 16-byte-aligned address **/
	                                                    /** #=== means bytes being copied **/
	                                                    /** .... means bytes not copied **/
	switch (argv[1][0]) {
	case '0': return test_aligned(1);                   /* #... .... .... .... */
	case '1': return test_aligned(7);                   /* #=== ===. .... .... */
	case '2': return test_aligned(16);                  /* #=== ==== ==== ==== */
	case '3': return test_aligned(20);                  /* #=== ==== ==== ==== #=== .... .... .... */
	case '4': return test_aligned(96);                  /* #=== ==== ==== ==== <------ 4x16 -----> #=== ==== ==== ==== */ /* 12 bytes */
	case '5': return test_aligned_offset(15, 3, 2);     /* ...= ==== ==== ==.. */ /* 10 bytes */
	case '6': return test_aligned_offset(38, 2, 3);     /* ..== ==== ==== ==== #=== ==== ==== ==== #==. .... .... .... */ /* 33 bytes */
	case '7': return test_aligned_offset(95, 1, 3);     /* .=== ==== ==== ==== <------ 4x16 -----> #=== ==== ==== .... */ /* 91 bytes */
	case '8': return test_aligned_offset(18, 0, 0);     /* #=== ==== ==== ==== #=... .... .... .... */ /* 18 bytes */
	case '9': return test_aligned_offset(15, 0, 3);     /* #=== ==== ==== =... */ /* 12 bytes */
	case 'a': return test_aligned_offset(121, 0, 0);    /* #=== ==== ==== ==== <------ 6x16 -----> #=== ==== =... .... */ /* 121 bytes */
	case 'b': return test_aligned_offset(121, 9, 0);    /* .... .... .=== ==== <------ 6x16 -----> #=== ==== =... .... */ /* 112 bytes */
	case 'c': return test_aligned_offset(121, 0, 7);    /* #=== ==== ==== ==== <------ 6x16 -----> #=.. .... .... .... */ /* 114 bytes */
	case 'd': return test_misaligned(5, 0);             /* #=== =... .... ....        >>>   #=== =... .... .... */ /* 5 bytes */
	case 'e': return test_misaligned(5, 1);             /* #=== =... .... ....        >>>   .=== ==.. .... .... */ /* 5 bytes */
	case 'f': return test_misaligned(96, 5);            /* #=== ==== <-- 88 bytes --> >>>   .... .=== ==== ==== <-- 85 bytes --> */ /* 96 bytes */
	}
	printf("unknown test %c\n", argv[1][0]);
	return -1;
}
