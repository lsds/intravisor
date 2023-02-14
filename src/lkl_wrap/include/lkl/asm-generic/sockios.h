/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__ASM_GENERIC_SOCKIOS_H
#define __LKL__ASM_GENERIC_SOCKIOS_H

/* Socket-level I/O control calls. */
#define LKL_FIOSETOWN	0x8901
#define LKL_SIOCSPGRP	0x8902
#define LKL_FIOGETOWN	0x8903
#define LKL_SIOCGPGRP	0x8904
#define LKL_SIOCATMARK	0x8905
#define LKL_SIOCGSTAMP	0x8906		/* Get stamp (timeval) */
#define LKL_SIOCGSTAMPNS	0x8907		/* Get stamp (timespec) */

#endif /* __LKL__ASM_GENERIC_SOCKIOS_H */
