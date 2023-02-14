/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_TIMES_H
#define _LKL_LINUX_TIMES_H

#include <lkl/linux/types.h>

struct lkl_tms {
	__lkl__kernel_clock_t tms_utime;
	__lkl__kernel_clock_t tms_stime;
	__lkl__kernel_clock_t tms_cutime;
	__lkl__kernel_clock_t tms_cstime;
};

#endif
