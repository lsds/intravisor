/*****************************************************************************
 *                                                                           *
 * Copyright (c) David L. Mills 1993                                         *
 *                                                                           *
 * Permission to use, copy, modify, and distribute this software and its     *
 * documentation for any purpose and without fee is hereby granted, provided *
 * that the above copyright notice appears in all copies and that both the   *
 * copyright notice and this permission notice appear in supporting          *
 * documentation, and that the name University of Delaware not be used in    *
 * advertising or publicity pertaining to distribution of the software       *
 * without specific, written prior permission.  The University of Delaware   *
 * makes no representations about the suitability this software for any      *
 * purpose.  It is provided "as is" without express or implied warranty.     *
 *                                                                           *
 *****************************************************************************/

/*
 * Modification history timex.h
 *
 * 29 Dec 97	Russell King
 *	Moved CLOCK_TICK_RATE, CLOCK_TICK_FACTOR and FINETUNE to asm/timex.h
 *	for ARM machines
 *
 *  9 Jan 97    Adrian Sun
 *      Shifted LATCH define to allow access to alpha machines.
 *
 * 26 Sep 94	David L. Mills
 *	Added defines for hybrid phase/frequency-lock loop.
 *
 * 19 Mar 94	David L. Mills
 *	Moved defines from kernel routines to header file and added new
 *	defines for PPS phase-lock loop.
 *
 * 20 Feb 94	David L. Mills
 *	Revised status codes and structures for external clock and PPS
 *	signal discipline.
 *
 * 28 Nov 93	David L. Mills
 *	Adjusted parameters to improve stability and increase poll
 *	interval.
 *
 * 17 Sep 93    David L. Mills
 *      Created file $NTP/include/sys/timex.h
 * 07 Oct 93    Torsten Duwe
 *      Derived linux/timex.h
 * 1995-08-13    Torsten Duwe
 *      kernel PLL updated to 1994-12-13 specs (rfc-1589)
 * 1997-08-30    Ulrich Windl
 *      Added new constant NTP_PHASE_LIMIT
 * 2004-08-12    Christoph Lameter
 *      Reworked time interpolation logic
 */
#ifndef _LKL_LINUX_TIMEX_H
#define _LKL_LINUX_TIMEX_H

#include <lkl/linux/time.h>

#define LKL_NTP_API		4	/* NTP API version */

/*
 * syscall interface - used (mainly by NTP daemon)
 * to discipline kernel clock oscillator
 */
struct lkl_timex {
	unsigned int modes;	/* mode selector */
	__lkl__kernel_long_t offset;	/* time offset (usec) */
	__lkl__kernel_long_t freq;	/* frequency offset (scaled ppm) */
	__lkl__kernel_long_t maxerror;/* maximum error (usec) */
	__lkl__kernel_long_t esterror;/* estimated error (usec) */
	int status;		/* clock command/status */
	__lkl__kernel_long_t constant;/* pll time constant */
	__lkl__kernel_long_t precision;/* clock precision (usec) (read only) */
	__lkl__kernel_long_t tolerance;/* clock frequency tolerance (ppm)
				   * (read only)
				   */
	struct lkl_timeval time;	/* (read only, except for LKL_ADJ_SETOFFSET) */
	__lkl__kernel_long_t tick;	/* (modified) usecs between clock ticks */

	__lkl__kernel_long_t ppsfreq;/* pps frequency (scaled ppm) (ro) */
	__lkl__kernel_long_t jitter; /* pps jitter (us) (ro) */
	int shift;              /* interval duration (s) (shift) (ro) */
	__lkl__kernel_long_t stabil;            /* pps stability (scaled ppm) (ro) */
	__lkl__kernel_long_t jitcnt; /* jitter limit exceeded (ro) */
	__lkl__kernel_long_t calcnt; /* calibration intervals (ro) */
	__lkl__kernel_long_t errcnt; /* calibration errors (ro) */
	__lkl__kernel_long_t stbcnt; /* stability limit exceeded (ro) */

	int tai;		/* TAI offset (ro) */

	int  :32; int  :32; int  :32; int  :32;
	int  :32; int  :32; int  :32; int  :32;
	int  :32; int  :32; int  :32;
};

/*
 * Mode codes (timex.mode)
 */
#define LKL_ADJ_OFFSET		0x0001	/* time offset */
#define LKL_ADJ_FREQUENCY		0x0002	/* frequency offset */
#define LKL_ADJ_MAXERROR		0x0004	/* maximum time error */
#define LKL_ADJ_ESTERROR		0x0008	/* estimated time error */
#define LKL_ADJ_STATUS		0x0010	/* clock status */
#define LKL_ADJ_TIMECONST		0x0020	/* pll time constant */
#define LKL_ADJ_TAI			0x0080	/* set TAI offset */
#define LKL_ADJ_SETOFFSET		0x0100  /* add 'time' to current time */
#define LKL_ADJ_MICRO		0x1000	/* select microsecond resolution */
#define LKL_ADJ_NANO		0x2000	/* select nanosecond resolution */
#define LKL_ADJ_TICK		0x4000	/* tick value */

#define LKL_ADJ_OFFSET_SINGLESHOT	0x8001	/* old-fashioned adjtime */
#define LKL_ADJ_OFFSET_SS_READ	0xa001	/* read-only adjtime */

/* NTP userland likes the MOD_ prefix better */
#define LKL_MOD_OFFSET	LKL_ADJ_OFFSET
#define LKL_MOD_FREQUENCY	LKL_ADJ_FREQUENCY
#define LKL_MOD_MAXERROR	LKL_ADJ_MAXERROR
#define LKL_MOD_ESTERROR	LKL_ADJ_ESTERROR
#define LKL_MOD_STATUS	LKL_ADJ_STATUS
#define LKL_MOD_TIMECONST	LKL_ADJ_TIMECONST
#define LKL_MOD_TAI	LKL_ADJ_TAI
#define LKL_MOD_MICRO	LKL_ADJ_MICRO
#define LKL_MOD_NANO	LKL_ADJ_NANO


/*
 * Status codes (timex.status)
 */
#define LKL_STA_PLL		0x0001	/* enable PLL updates (rw) */
#define LKL_STA_PPSFREQ	0x0002	/* enable PPS freq discipline (rw) */
#define LKL_STA_PPSTIME	0x0004	/* enable PPS time discipline (rw) */
#define LKL_STA_FLL		0x0008	/* select frequency-lock mode (rw) */

#define LKL_STA_INS		0x0010	/* insert leap (rw) */
#define LKL_STA_DEL		0x0020	/* delete leap (rw) */
#define LKL_STA_UNSYNC	0x0040	/* clock unsynchronized (rw) */
#define LKL_STA_FREQHOLD	0x0080	/* hold frequency (rw) */

#define LKL_STA_PPSSIGNAL	0x0100	/* PPS signal present (ro) */
#define LKL_STA_PPSJITTER	0x0200	/* PPS signal jitter exceeded (ro) */
#define LKL_STA_PPSWANDER	0x0400	/* PPS signal wander exceeded (ro) */
#define LKL_STA_PPSERROR	0x0800	/* PPS signal calibration error (ro) */

#define LKL_STA_CLOCKERR	0x1000	/* clock hardware fault (ro) */
#define LKL_STA_NANO	0x2000	/* resolution (0 = us, 1 = ns) (ro) */
#define LKL_STA_MODE	0x4000	/* mode (0 = PLL, 1 = FLL) (ro) */
#define LKL_STA_CLK		0x8000	/* clock source (0 = A, 1 = B) (ro) */

/* read-only bits */
#define LKL_STA_RONLY (LKL_STA_PPSSIGNAL | LKL_STA_PPSJITTER | LKL_STA_PPSWANDER | \
	LKL_STA_PPSERROR | LKL_STA_CLOCKERR | LKL_STA_NANO | LKL_STA_MODE | LKL_STA_CLK)

/*
 * Clock states (time_state)
 */
#define LKL_TIME_OK		0	/* clock synchronized, no leap second */
#define LKL_TIME_INS	1	/* insert leap second */
#define LKL_TIME_DEL	2	/* delete leap second */
#define LKL_TIME_OOP	3	/* leap second in progress */
#define LKL_TIME_WAIT	4	/* leap second has occurred */
#define LKL_TIME_ERROR	5	/* clock not synchronized */
#define LKL_TIME_BAD	LKL_TIME_ERROR /* bw compat */


#endif /* _LKL_LINUX_TIMEX_H */
