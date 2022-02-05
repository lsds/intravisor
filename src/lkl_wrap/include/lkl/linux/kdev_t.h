/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_KDEV_T_H
#define _LKL_LINUX_KDEV_T_H

/*
Some programs want their definitions of LKL_MAJOR and LKL_MINOR and LKL_MKDEV
from the kernel sources. These must be the externally visible ones.
*/
#define LKL_MAJOR(dev)	((dev)>>8)
#define LKL_MINOR(dev)	((dev) & 0xff)
#define LKL_MKDEV(ma,mi)	((ma)<<8 | (mi))
#endif /* _LKL_LINUX_KDEV_T_H */
