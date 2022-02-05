/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_ASM_GENERIC_IOCTL_H
#define _LKL_ASM_GENERIC_IOCTL_H

/* ioctl command encoding: 32 bits total, command in lower 16 bits,
 * size of the parameter structure in the lower 14 bits of the
 * upper 16 bits.
 * Encoding the size of the parameter structure in the ioctl request
 * is useful for catching programs compiled with old versions
 * and to avoid overwriting user space outside the user buffer area.
 * The highest 2 bits are reserved for indicating the ``access mode''.
 * NOTE: This limits the max parameter size to 16kB -1 !
 */

/*
 * The following is for compatibility across the various Linux
 * platforms.  The generic ioctl numbering scheme doesn't really enforce
 * a type field.  De facto, however, the top 8 bits of the lower 16
 * bits are indeed used as a type field, so we might just as well make
 * this explicit here.  Please be sure to use the decoding macros
 * below from now on.
 */
#define _LKL_IOC_NRBITS	8
#define _LKL_IOC_TYPEBITS	8

/*
 * Let any architecture override either of the following before
 * including this file.
 */

#ifndef _LKL_IOC_SIZEBITS
# define _LKL_IOC_SIZEBITS	14
#endif

#ifndef _LKL_IOC_DIRBITS
# define _LKL_IOC_DIRBITS	2
#endif

#define _LKL_IOC_NRMASK	((1 << _LKL_IOC_NRBITS)-1)
#define _LKL_IOC_TYPEMASK	((1 << _LKL_IOC_TYPEBITS)-1)
#define _LKL_IOC_SIZEMASK	((1 << _LKL_IOC_SIZEBITS)-1)
#define _LKL_IOC_DIRMASK	((1 << _LKL_IOC_DIRBITS)-1)

#define _LKL_IOC_NRSHIFT	0
#define _LKL_IOC_TYPESHIFT	(_LKL_IOC_NRSHIFT+_LKL_IOC_NRBITS)
#define _LKL_IOC_SIZESHIFT	(_LKL_IOC_TYPESHIFT+_LKL_IOC_TYPEBITS)
#define _LKL_IOC_DIRSHIFT	(_LKL_IOC_SIZESHIFT+_LKL_IOC_SIZEBITS)

/*
 * Direction bits, which any architecture can choose to override
 * before including this file.
 *
 * NOTE: _LKL_IOC_WRITE means userland is writing and kernel is
 * reading. _LKL_IOC_READ means userland is reading and kernel is writing.
 */

#ifndef _LKL_IOC_NONE
# define _LKL_IOC_NONE	0U
#endif

#ifndef _LKL_IOC_WRITE
# define _LKL_IOC_WRITE	1U
#endif

#ifndef _LKL_IOC_READ
# define _LKL_IOC_READ	2U
#endif

#define _LKL_IOC(dir,type,nr,size) \
	(((dir)  << _LKL_IOC_DIRSHIFT) | \
	 ((type) << _LKL_IOC_TYPESHIFT) | \
	 ((nr)   << _LKL_IOC_NRSHIFT) | \
	 ((size) << _LKL_IOC_SIZESHIFT))

#define _LKL_IOC_TYPECHECK(t) (sizeof(t))

/*
 * Used to create numbers.
 *
 * NOTE: _LKL_IOW means userland is writing and kernel is reading. _LKL_IOR
 * means userland is reading and kernel is writing.
 */
#define _LKL_IO(type,nr)		_LKL_IOC(_LKL_IOC_NONE,(type),(nr),0)
#define _LKL_IOR(type,nr,size)	_LKL_IOC(_LKL_IOC_READ,(type),(nr),(_LKL_IOC_TYPECHECK(size)))
#define _LKL_IOW(type,nr,size)	_LKL_IOC(_LKL_IOC_WRITE,(type),(nr),(_LKL_IOC_TYPECHECK(size)))
#define _LKL_IOWR(type,nr,size)	_LKL_IOC(_LKL_IOC_READ|_LKL_IOC_WRITE,(type),(nr),(_LKL_IOC_TYPECHECK(size)))
#define _LKL_IOR_BAD(type,nr,size)	_LKL_IOC(_LKL_IOC_READ,(type),(nr),sizeof(size))
#define _LKL_IOW_BAD(type,nr,size)	_LKL_IOC(_LKL_IOC_WRITE,(type),(nr),sizeof(size))
#define _LKL_IOWR_BAD(type,nr,size)	_LKL_IOC(_LKL_IOC_READ|_LKL_IOC_WRITE,(type),(nr),sizeof(size))

/* used to decode ioctl numbers.. */
#define _LKL_IOC_DIR(nr)		(((nr) >> _LKL_IOC_DIRSHIFT) & _LKL_IOC_DIRMASK)
#define _LKL_IOC_TYPE(nr)		(((nr) >> _LKL_IOC_TYPESHIFT) & _LKL_IOC_TYPEMASK)
#define _LKL_IOC_NR(nr)		(((nr) >> _LKL_IOC_NRSHIFT) & _LKL_IOC_NRMASK)
#define _LKL_IOC_SIZE(nr)		(((nr) >> _LKL_IOC_SIZESHIFT) & _LKL_IOC_SIZEMASK)

/* ...and for the drivers/sound files... */

#define LKL_IOC_IN		(_LKL_IOC_WRITE << _LKL_IOC_DIRSHIFT)
#define LKL_IOC_OUT		(_LKL_IOC_READ << _LKL_IOC_DIRSHIFT)
#define LKL_IOC_INOUT	((_LKL_IOC_WRITE|_LKL_IOC_READ) << _LKL_IOC_DIRSHIFT)
#define LKL_IOCSIZE_MASK	(_LKL_IOC_SIZEMASK << _LKL_IOC_SIZESHIFT)
#define LKL_IOCSIZE_SHIFT	(_LKL_IOC_SIZESHIFT)

#endif /* _LKL_ASM_GENERIC_IOCTL_H */
