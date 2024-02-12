/*-
 * Copyright (c) 2002 Mike Barcroft <mike@FreeBSD.org>
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	From: @(#)ansi.h	8.2 (Berkeley) 1/4/94
 *	From: @(#)types.h	8.3 (Berkeley) 1/5/94
 * $FreeBSD$
 */

#ifndef _MACHINE__TYPES_H_
#define	_MACHINE__TYPES_H_

/*
 * Basic types upon which most other types are built.
 */
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long __int64_t;
typedef unsigned long __uint64_t;

/*
 * Standard type definitions.
 */
typedef __int32_t __clock_t;	/* clock()... */
typedef __int64_t __critical_t;
#ifndef _STANDALONE
typedef double __double_t;
typedef float __float_t;
#endif
#ifdef __CHERI_PURE_CAPABILITY__
typedef __intcap_t __intfptr_t;
typedef __intcap_t __intptr_t;
#else
#if arm_sim
typedef __int64_t __intcap_t;
typedef __uint64_t __uintcap_t;
#define __capability	__attribute__(())
#define __cheri_addr
#endif
typedef __int64_t __intfptr_t;
typedef __int64_t __intptr_t;
#endif
typedef __int64_t __intmax_t;
typedef __int32_t __int_fast8_t;
typedef __int32_t __int_fast16_t;
typedef __int32_t __int_fast32_t;
typedef __int64_t __int_fast64_t;
typedef __int8_t __int_least8_t;
typedef __int16_t __int_least16_t;
typedef __int32_t __int_least32_t;
typedef __int64_t __int_least64_t;
typedef __int64_t __ptrdiff_t;	/* ptr1 - ptr2 */
typedef __int64_t __register_t;
typedef __int64_t __segsz_t;	/* segment size (in pages) */
typedef __uint64_t __size_t;	/* sizeof() */
typedef __int64_t __ssize_t;	/* byte count or error */
typedef __int64_t __time_t;	/* time()... */
#ifdef __CHERI_PURE_CAPABILITY__
typedef __uintcap_t __uintfptr_t;
typedef __uintcap_t __uintptr_t;
typedef __uintcap_t uintptr_t;
#else
typedef __uint64_t __uintfptr_t;
typedef __uint64_t __uintptr_t;
#endif
typedef __uint64_t __uintmax_t;
typedef __uint32_t __uint_fast8_t;
typedef __uint32_t __uint_fast16_t;
typedef __uint32_t __uint_fast32_t;
typedef __uint64_t __uint_fast64_t;
typedef __uint8_t __uint_least8_t;
typedef __uint16_t __uint_least16_t;
typedef __uint32_t __uint_least32_t;
typedef __uint64_t __uint_least64_t;
typedef __uint64_t __u_register_t;
typedef __uint64_t __vm_offset_t;
typedef __uint64_t __vm_paddr_t;
typedef __uint64_t __vm_size_t;
typedef int ___wchar_t;

typedef __size_t size_t;

typedef __uint64_t uint64_t;
typedef __uint32_t uint32_t;

typedef __uintptr_t __ptraddr_t;

#ifndef _INT8_T_DECLARED
typedef __int8_t int8_t;
#define	_INT8_T_DECLARED
#endif

#ifndef _INT16_T_DECLARED
typedef __int16_t int16_t;
#define	_INT16_T_DECLARED
#endif

#ifndef _INT32_T_DECLARED
typedef __int32_t int32_t;
#define	_INT32_T_DECLARED
#endif

#ifndef _INT64_T_DECLARED
typedef __int64_t int64_t;
#define	_INT64_T_DECLARED
#endif

#ifndef _UINT8_T_DECLARED
typedef __uint8_t uint8_t;
#define	_UINT8_T_DECLARED
#endif

#ifndef _UINT16_T_DECLARED
typedef __uint16_t uint16_t;
#define	_UINT16_T_DECLARED
#endif

#ifndef _UINT32_T_DECLARED
typedef __uint32_t uint32_t;
#define	_UINT32_T_DECLARED
#endif

#ifndef _UINT64_T_DECLARED
typedef __uint64_t uint64_t;
#define	_UINT64_T_DECLARED
#endif

#ifndef _INTCAP_T_DECLARED
typedef __intcap_t intcap_t;
#define	_INTCAP_T_DECLARED
#endif
#ifndef _UINTCAP_T_DECLARED
typedef __uintcap_t uintcap_t;
#define	_UINTCAP_T_DECLARED
#endif

#ifndef _INTPTR_T_DECLARED
typedef __intptr_t intptr_t;
#define	_INTPTR_T_DECLARED
#endif

#ifndef _UINTPTR_T_DECLARED
typedef __uintptr_t uintptr_t;
#define	_UINTPTR_T_DECLARED
#endif
#ifndef _INTMAX_T_DECLARED
typedef __intmax_t intmax_t;
#define	_INTMAX_T_DECLARED
#endif
#ifndef _UINTMAX_T_DECLARED
typedef __uintmax_t uintmax_t;
#define	_UINTMAX_T_DECLARED
#endif
#ifndef _KINTCAP_T_DECLARED
#ifdef _KERNEL
typedef __intcap_t kintcap_t;
#else
typedef __intptr_t kintcap_t;
#endif
#define	_KINTCAP_T_DECLARED
#endif
#ifndef _KUINTCAP_T_DECLARED
#ifdef _KERNEL
typedef __uintcap_t kuintcap_t;
#else
typedef __uintptr_t kuintcap_t;
#endif
#define	_KUINTCAP_T_DECLARED
#endif

#ifndef _PTRADDR_T_DECLARED
typedef __ptraddr_t ptraddr_t;
#define	_PTRADDR_T_DECLARED
#endif

#ifndef _VADDR_T_DECLARED
#ifndef __CHERI_PURE_CAPABILITY__
typedef __uintptr_t vaddr_t;
#else
typedef __uint64_t vaddr_t;
#endif
#define _VADDR_T_DECLARED
#endif

typedef void *__capability otype_t;
typedef __register_t register_t;

#if defined(__GNUC__)
#define	__GNUC_PREREQ__(ma, mi)	\
	(__GNUC__ > (ma) || __GNUC__ == (ma) && __GNUC_MINOR__ >= (mi))
#else
#define	__GNUC_PREREQ__(ma, mi)	0
#endif

#if __GNUC_PREREQ__(3, 4)
#define	__fastcall	__attribute__((__fastcall__))
#define	__result_use_check	__attribute__((__warn_unused_result__))
#else
#define	__fastcall
#define	__result_use_check
#endif

#define	__WCHAR_MIN	__INT_MIN	/* min value for a wchar_t */
#define	__WCHAR_MAX	__INT_MAX	/* max value for a wchar_t */

#endif /* !_MACHINE__TYPES_H_ */
