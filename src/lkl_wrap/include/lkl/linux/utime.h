/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_UTIME_H
#define _LKL_LINUX_UTIME_H

#include <lkl/linux/types.h>

struct lkl_utimbuf {
	__lkl__kernel_time_t actime;
	__lkl__kernel_time_t modtime;
};

#endif
