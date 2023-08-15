#include <sys/types.h>
#include "_types.h"
#include <stdarg.h>
#include <stdlib.h>

#include <wctype.h>
#include <wchar.h>

#include <string.h>
#include <stdio.h>
#include <sys/errno.h>
#include <limits.h>
#include "cheri_helpers.h"
#include "hostcalls.h"

#include "stdio_impl.h"

#include <bits/float.h>
#include <float.h>
#include <math.h>

#define UCHAR_MAX 255

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(x) ((x)-ONES & ~(x) & HIGHS)




void *my_calloc(size_t nmemb, size_t size);
void *my_malloc(size_t size);
       void my_free(void *ptr);
       void *my_realloc(void *ptr, size_t size);

void *calloc(size_t nmemb, size_t size) {
	return my_calloc(nmemb, size);
}

void *malloc(size_t size) {
	return my_malloc(size);
}

void free(void *ptr) {
	my_free(ptr);
}

void *realloc(void *ptr, size_t size) {
	return my_realloc(ptr, size);
}

typedef	__intcap_t word;	/* "word" used for optimal copy speed */
#define	wsize	sizeof(word)
#define	wmask	(wsize - 1)
#define __CAP	__capability

void * memcpy(void * __CAP dst0, const void *  __CAP src0, size_t length) {
	char * __CAP dst = dst0;
	const char * __CAP src = src0;
	size_t t;

	if (length == 0 || dst == src)		/* nothing to do */
		goto done;

	/*
	 * Macros: loop-t-times; and loop-t-times, t>0
	 */
#define	TLOOP(s) if (t) TLOOP1(s)
#define	TLOOP1(s) do { s; } while (--t)

	if (dst < src) {
		/*
		 * Copy forward.
		 */
		t = (__cheri_addr size_t)src;	/* only need low bits */
		if ((t | (__cheri_addr size_t)dst) & wmask) {
			/*
			 * Try to align operands.  This cannot be done
			 * unless the low bits match.
			 */
			if ((t ^ (__cheri_addr size_t)dst) & wmask || length < wsize)
				t = length;
			else
				t = wsize - (t & wmask);
			length -= t;
			TLOOP1(*dst++ = *src++);
		}
		/*
		 * Copy whole words, then mop up any trailing bytes.
		 */
		t = length / wsize;
		TLOOP(*(word * __CAP)(void * __CAP)dst =
		    *(const word * __CAP)(const void * __CAP)src;
		    src += wsize; dst += wsize);
		t = length & wmask;
		TLOOP(*dst++ = *src++);
	} else {
		/*
		 * Copy backwards.  Otherwise essentially the same.
		 * Alignment works as before, except that it takes
		 * (t&wmask) bytes to align, not wsize-(t&wmask).
		 */
		src += length;
		dst += length;
		t = (__cheri_addr size_t)src;
		if ((t | (__cheri_addr size_t)dst) & wmask) {
			if ((t ^ (__cheri_addr size_t)dst) & wmask || length <= wsize)
				t = length;
			else
				t &= wmask;
			length -= t;
			TLOOP1(*--dst = *--src);
		}
		t = length / wsize;
		TLOOP(src -= wsize; dst -= wsize;
		    *(word * __CAP)(void * __CAP)dst =
		    *(const word * __CAP)(const void * __CAP)src);
		t = length & wmask;
		TLOOP(*--dst = *--src);
	}
done:
	return (dst0);
}

void * memmove(void * __CAP dst0, const void *  __CAP src0, size_t length) {
	char * __CAP dst = dst0;
	const char * __CAP src = src0;
	size_t t;

	if (length == 0 || dst == src)		/* nothing to do */
		goto done;

	/*
	 * Macros: loop-t-times; and loop-t-times, t>0
	 */
#define	TLOOP(s) if (t) TLOOP1(s)
#define	TLOOP1(s) do { s; } while (--t)

	if (dst < src) {
		/*
		 * Copy forward.
		 */
		t = (__cheri_addr size_t)src;	/* only need low bits */
		if ((t | (__cheri_addr size_t)dst) & wmask) {
			/*
			 * Try to align operands.  This cannot be done
			 * unless the low bits match.
			 */
			if ((t ^ (__cheri_addr size_t)dst) & wmask || length < wsize)
				t = length;
			else
				t = wsize - (t & wmask);
			length -= t;
			TLOOP1(*dst++ = *src++);
		}
		/*
		 * Copy whole words, then mop up any trailing bytes.
		 */
		t = length / wsize;
		TLOOP(*(word * __CAP)(void * __CAP)dst =
		    *(const word * __CAP)(const void * __CAP)src;
		    src += wsize; dst += wsize);
		t = length & wmask;
		TLOOP(*dst++ = *src++);
	} else {
		/*
		 * Copy backwards.  Otherwise essentially the same.
		 * Alignment works as before, except that it takes
		 * (t&wmask) bytes to align, not wsize-(t&wmask).
		 */
		src += length;
		dst += length;
		t = (__cheri_addr size_t)src;
		if ((t | (__cheri_addr size_t)dst) & wmask) {
			if ((t ^ (__cheri_addr size_t)dst) & wmask || length <= wsize)
				t = length;
			else
				t &= wmask;
			length -= t;
			TLOOP1(*--dst = *--src);
		}
		t = length / wsize;
		TLOOP(src -= wsize; dst -= wsize;
		    *(word * __CAP)(void * __CAP)dst =
		    *(const word * __CAP)(const void * __CAP)src);
		t = length & wmask;
		TLOOP(*--dst = *--src);
	}
done:
	return (dst0);
}

