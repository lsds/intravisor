#include <sys/types.h>
#include "_types.h"
#include <stdarg.h>

#include <string.h>
#include <stdio.h>

#include "morello_helpers.h"
#include "hostcalls.h"



//void * __capability libc_gate;

void *my_malloc(size_t size) {
#if 0
	int tmp = 1100;
	register long t5 __asm__("t5") = tmp;
	register long ca0 __asm__("ca0") = (long) size;
	register long cs0 __asm__("cs0") = libc_gate;

	__asm__ __volatile__("cjr %1" : "=C"(a0) : "C"(cap_jump), "r"(t5), "C"(cs0), "r"(ca0) : "memory" );

	return ca0; 
#else
	return c_out2_3(1100, size, 0, 0);
#endif
}


void my_free(void *ptr) {
	c_out2_3(1101, ptr, 0, 0);
}

void *my_realloc(void *ptr, size_t size) {
	return c_out2_3(1102, ptr, size, 0);
}


int strcmp(const char *l, const char *r) {
	return c_out2_3(1103, l, r, 0);
}

#define __CAP	__capability
void * memcpy(void * __CAP dst0, const void *  __CAP src0, size_t length) {
	return c_out2_3(1104, dst0, src0, length);
}

size_t strlen(const char *str) {
	return c_out2_3(1105, str, 0, 0);
}

_Noreturn void __assert_fail (const char *a0, const char *a1, int a2, const char *a3) {
	c_out2_5(1106, a0, a1, a2, a3, 0);
}

void exit(int status) {
	host_exit();
}


int vfprintf(FILE *stream, const char *format, va_list ap) {
	printf(format, ap);
}

char pbuf2[4096];

int mini_vsnprintf(char *buffer, unsigned int buffer_len, const char *fmt, va_list va) {
	return c_out2_5(1107, buffer, buffer_len, fmt, va, 0);
}

void *memset(void *dest, int c, size_t n) {
	return c_out2_3(1108, dest, c, n);
}

//actually we should direct out output to libc
int printf(const char *fmt, ...)
{
	int ret;

	memset(pbuf2, 0, 4096);
	va_list va;
	va_start(va, fmt);
	ret = mini_vsnprintf(pbuf2, 4096, fmt, va);
	va_end(va);

	host_write_out(pbuf2, ret);

	return ret;
}

int puts(const char *s) {
	return c_out2_3(1109, s, 0, 0);
}

int putchar(int c) {
	return c_out2_3(1110, c, 0, 0);
}


int *__errno_location(void) {
	return c_out2_3(1111, 0, 0, 0);
}

int bcmp (const void *a, const void *b, size_t c) {
	return c_out2_3(1112, a, b, c);
}

void *memmove (void *a, const void *b, size_t c) {
	return c_out2_3(1113, a, b, c);
}

int strncmp (const char *a, const char *b, size_t c) {
	return c_out2_3(1114, a, b, c);
}

size_t strcspn (const char *a, const char *b) {
	return c_out2_3(1115, a, b, 0);
}

int memcmp(const void *a, const void *b, size_t c) {
	return c_out2_3(1116, a, b, c);
}
