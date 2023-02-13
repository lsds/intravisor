/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2005-2007, Kohsuke Ohtani
 * Copyright (C) 2013 Cloudius Systems, Ltd.
 * Copyright (c) 2019, NEC Europe Ltd., NEC Corporation.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the names of any co-contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#define _GNU_SOURCE

//#include <sys/statvfs.h>
//#include <sys/stat.h>

#include <sys/uk_stat.h>

#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <vfscore/prex.h>
#include <vfscore/vnode.h>
#include "vfs.h"
#include <sys/file.h>
#include <stdarg.h>
#include <utime.h>
#include <vfscore/file.h>
#include <vfscore/mount.h>
#include <vfscore/fs.h>
#include <uk/print.h>
#include <uk/errptr.h>
#include <uk/ctors.h>
#include <uk/trace.h>
#include <uk/syscall.h>
#include <uk/essentials.h>

#ifdef DEBUG_VFS
int	vfs_debug = VFSDB_FLAGS;
#endif

/* This macro is for defining an alias of the 64bit version of a
 * syscall to the regular one. We only do this when libc-style
 * syscall wrappers are requested to be created.
 * NOTE: When using LFS64(), remember to undefine possible rename
 *       macros created by included libc headers (e.g., <fcntl.h>):
 *       ```
 *       #ifdef openat64
 *       #undef openat64
 *       #endif
 *
 *       LFS64(openat)
 *       ```
 */
#if UK_LIBC_SYSCALLS
#define LFS64(x)				\
	__alias(x, x##64)
#else
#define LFS64(x)
#endif /* !UK_LIBC_SYSCALLS */

static mode_t global_umask = S_IWGRP | S_IWOTH;

static inline int libc_error(int err)
{
    errno = err;
    return -1;
}

// In BSD's internal implementation of read() and write() code, for example
// sosend_generic(), a partial read or write returns both an EWOULDBLOCK error
// *and* a non-zero number of written bytes. In that case, we need to zero the
// error, so the system call appear a successful partial read/write.
// In FreeBSD, dofilewrite() and dofileread() (sys_generic.c) do this too.
static inline int has_error(int error, int bytes)
{
	/* TODO: OSv checks also for ERESTART */
	return error && (
		(bytes == 0) ||
		(error != EWOULDBLOCK && error != EINTR));
}

struct task *main_task;	/* we only have a single process */

int my_open(const char* pathname, int flags, mode_t mode)
{
	struct task *t = main_task;
	char path[PATH_MAX];
	struct vfscore_file *fp;
	int fd, error;
	int acc;

	acc = 0;
	switch (flags & O_ACCMODE) {
	case O_RDONLY:
		acc = VREAD;
		break;
	case O_WRONLY:
		acc = VWRITE;
		break;
	case O_RDWR:
		acc = VREAD | VWRITE;
		break;
	}

	error = task_conv(t, pathname, acc, path);
	if (error)
		goto out_error;

	error = sys_open(path, flags, mode, &fp);
	if (error)
		goto out_error;

	error = fdalloc(fp, &fd);
	if (error)
		goto out_fput;
	fdrop(fp);

	return fd;

	out_fput:
	fdrop(fp);
	out_error:

	return -error;
}

/**
 * Return:
 * = 0, Success and the nr of bytes read is returned in bytes parameter.
 * < 0, error code.
 */
static ssize_t do_preadv(struct vfscore_file *fp, const struct iovec *iov,
			 int iovcnt, off_t offset, ssize_t *bytes)
{
	size_t cnt;
	int error;

	UK_ASSERT(fp && iov);

	/* Otherwise, try to read the file. */
	error = sys_read(fp, iov, iovcnt, offset, &cnt);

	if (has_error(error, cnt))
		goto out_error;

	*bytes = cnt;
	return 0;

out_error:
	return -error;
}

#if 0
UK_SYSCALL_R_DEFINE(ssize_t, preadv, int, fd, const struct iovec*, iov,
	int, iovcnt, off_t, offset)
#else
ssize_t my_preadv(int fd, const struct iovec *iov, int iovcnt, off_t offset)
#endif
{
	struct vfscore_file *fp;
	ssize_t bytes;
	int error;

//	trace_vfs_preadv(fd, iov, iovcnt, offset);
	error = fget(fd, &fp);
	if (error) {
		error = -error;
		goto out_error;
	}

	/* Check if the file is indeed seekable. */
	if (fp->f_vfs_flags & UK_VFSCORE_NOPOS) {
		error = -ESPIPE;
		goto out_error_fdrop;
	}
	/* Check if the file has not already been read and that
	 * is not a character device.
	 */
	else if (fp->f_offset < 0 &&
		(fp->f_dentry == NULL ||
		 fp->f_dentry->d_vnode->v_type != VCHR)) {
		error = -EINVAL;
		goto out_error_fdrop;
	}

	/* Otherwise, try to read the file. */
	error = do_preadv(fp, iov, iovcnt, offset, &bytes);

out_error_fdrop:
	fdrop(fp);

	if (error < 0)
		goto out_error;

//	trace_vfs_preadv_ret(bytes);
	return bytes;

out_error:
//	trace_vfs_preadv_err(error);
	return error;
}

#ifdef my_preadv64
#undef my_preadv64
#endif

LFS64(my_preadv);

/*
 * Some libc's define some macros that remove the 64 suffix
 * from some system call function names (e.g., <unistd.h>, <fcntl.h>).
 * We need to undefine them here so that our system call
 * registration does not fail in such a case.
 */
#ifdef pread64
#undef pread64
#endif

#if 0
UK_LLSYSCALL_R_DEFINE(ssize_t, pread64, int, fd,
		      void *, buf, size_t, count, off_t, offset)
#else
ssize_t my_pread64(int fd, void *buf, size_t count, off_t offset)
#endif
{
//	trace_vfs_pread(fd, buf, count, offset);
	struct iovec iov = {
			.iov_base	= buf,
			.iov_len	= count,
	};
	ssize_t bytes;

	bytes = my_preadv((long) fd, &iov, 1, (long) offset);
//	if (bytes < 0)
//		trace_vfs_pread_err(bytes);
//	else
//		trace_vfs_pread_ret(bytes);
	return bytes;
}

#if 0
UK_SYSCALL_R_DEFINE(ssize_t, readv,
		  int, fd, const struct iovec *, iov, int, iovcnt)
#else
ssize_t my_readv(int fd, const struct iovec *iov, int iovcnt)
#endif
{
	struct vfscore_file *fp;
	ssize_t bytes;
	int error;

//	trace_vfs_readv(fd, iov, iovcnt);
	error = fget(fd, &fp);
	if (error) {
		error = -error;
		goto out_error;
	}

	/* Check if the file has not already been read and that is
	 * not a character device.
	 */
	if (fp->f_offset < 0 &&
	   (fp->f_dentry == NULL ||
	    fp->f_dentry->d_vnode->v_type != VCHR)) {
		error = -EINVAL;
		goto out_error_fdrop;
	}

	/* Otherwise, try to read the file. */
	error = do_preadv(fp, iov, iovcnt, -1, &bytes);

out_error_fdrop:
	fdrop(fp);

	if (error < 0)
		goto out_error;

//	trace_vfs_readv_ret(bytes);
	return bytes;

out_error:
//	trace_vfs_readv_err(error);
	return error;
}

#if 0
UK_SYSCALL_R_DEFINE(ssize_t, read, int, fd, void *, buf, size_t, count)
#else
ssize_t my_read(int fd, void *buf, size_t count)
#endif
{
	ssize_t bytes;

	UK_ASSERT(buf);

	struct iovec iov = {
			.iov_base	= buf,
			.iov_len	= count,
	};

//	trace_vfs_read(fd, buf, count);

	bytes = my_readv((long) fd,  &iov, 1);
//	if (bytes < 0)
//		trace_vfs_read_err(bytes);
//	else
//		trace_vfs_read_ret(bytes);
	return bytes;
}


static int do_pwritev(struct vfscore_file *fp, const struct iovec *iov,
		      int iovcnt, off_t offset, ssize_t *bytes)
{
	int error;
	size_t cnt;

	UK_ASSERT(bytes);

	/* Otherwise, try to read the file. */
	error = sys_write(fp, iov, iovcnt, offset, &cnt);

	if (has_error(error, cnt))
		goto out_error;

	*bytes = cnt;
	return 0;

out_error:
	return -error;
}


#if 0
UK_SYSCALL_R_DEFINE(ssize_t, writev,
		  int, fd, const struct iovec *, vec, int, vlen)
#else
ssize_t my_writev(int fd, const struct iovec *vec, int vlen)
#endif
{
	struct vfscore_file *fp;
	ssize_t bytes;
	int error;

//	trace_vfs_writev(fd, vec, vlen);
	error = fget(fd, &fp);
	if (error) {
		error = -error;
		goto out_error;
	}

	/* Check if the file has not already been written to and
	 * that it is not a character device.
	 */
	if (fp->f_offset < 0 &&
	   (fp->f_dentry == NULL ||
	    fp->f_dentry->d_vnode->v_type != VCHR)) {
		error = -EINVAL;
		goto out_error_fdrop;
	}

	/* Otherwise, try to read the file. */
	error = do_pwritev(fp, vec, vlen, -1, &bytes);

out_error_fdrop:
	fdrop(fp);

	if (error < 0)
		goto out_error;

//	trace_vfs_pwritev_ret(bytes);
	return bytes;

out_error:
//	trace_vfs_pwritev_err(error);
	return error;
}


#if 0
UK_SYSCALL_R_DEFINE(ssize_t, write, int, fd, const void *, buf, size_t, count)
#else
ssize_t my_write(int fd, const void *buf, size_t count)
#endif
{
	ssize_t bytes;

	UK_ASSERT(buf);

	struct iovec iov = {
			.iov_base	= (void *)buf,
			.iov_len	= count,
	};

//	trace_vfs_write(fd, buf, count);

	bytes = my_writev((long) fd, &iov, 1);

//	if (bytes < 0)
//		trace_vfs_write_err(errno);
//	else
//		trace_vfs_write_ret(bytes);
	return bytes;
}


static struct task _main_task_impl;
void vfscore_init(void)
{
	memset(&_main_task_impl, 0, sizeof(_main_task_impl));
	strcpy(_main_task_impl.t_cwd, "/");
	main_task = &_main_task_impl;

	vnode_init();
	lookup_init();
}

int fdclose(int fd)
{
	struct vfscore_file *fp;
	int error;

	fp = vfscore_get_file(fd);
	if (!fp)
		return EBADF;

	error = vfscore_put_fd(fd);
	if (!error)
		fdrop(fp);

	return error;
}


#if 0
UK_SYSCALL_R_DEFINE(int, close, int, fd)
#else
int my_close(int fd)
#endif
{
	return 0;
	int error;

//	trace_vfs_close(fd);
	error = fdclose(fd);
	if (error)
		goto out_error;

//	trace_vfs_close_ret();
	return 0;

	out_error:
//	trace_vfs_close_err(error);
	return -error;
}

#if 0
UK_SYSCALL_R_DEFINE(int, unlink, const char*, pathname)
#else
int my_unlink(const char* pathname)
#endif
{
	struct task *t = main_task;
	char path[PATH_MAX];
	int error;

	error = ENOENT;
	if (pathname == NULL)
		goto out_errno;
	if ((error = task_conv(t, pathname, VWRITE, path)) != 0)
		goto out_errno;

	error = sys_unlink(path);
	if (error)
		goto out_errno;

	return 0;
out_errno:
	return -error;
}

#if 0
UK_SYSCALL_R_DEFINE(char*, getcwd, char*, path, size_t, size)
#else
char *my_getcwd(char *path, size_t size)
#endif
{
	struct task *t = main_task;
	size_t len = strlen(t->t_cwd) + 1;
	int error;

	if (size < len) {
		error = ERANGE;
		goto out_error;
	}

	if (!path) {
		if (!size)
			size = len;
		path = (char*)my_malloc(size);
		if (!path) {
			error = ENOMEM;
			goto out_error;
		}
	} else {
		if (!size) {
			error = EINVAL;
			goto out_error;
		}
	}

	memcpy(path, t->t_cwd, len);

	return path;

out_error:

	return ERR2PTR(-error);
}

/*
 * Check permission for file access
 */
#if 0
UK_SYSCALL_R_DEFINE(int, access, const char*, pathname, int, mode)
#else
int my_access(const char *pathname, int mode)
#endif
{
	struct task *t = main_task;
	char path[PATH_MAX];
	int acc, error = 0;

	acc = 0;
	if (mode & R_OK)
		acc |= VREAD;
	if (mode & W_OK)
		acc |= VWRITE;

	if ((error = task_conv(t, pathname, acc, path)) != 0)
		goto out_error;

	error = sys_access(path, mode);
	if (error)
		goto out_error;

	return 0;

	out_error:

	return -error;
}

#if 0
UK_SYSCALL_R_DEFINE(int, truncate, const char*, pathname, off_t, length)
#else
int my_truncate(const char *pathname, off_t length)
#endif
{
	struct task *t = main_task;
	char path[PATH_MAX];
	int error;

	error = ENOENT;
	if (pathname == NULL)
		goto out_error;

	if ((error = task_conv(t, pathname, VWRITE, path)) != 0)
		goto out_error;

	error = sys_truncate(path, length);
	if (error)
		goto out_error;

	return 0;

	out_error:

	return -error;
}

#ifdef my_truncate64
#undef my_truncate64
#endif

LFS64(my_truncate);

#if 0
UK_SYSCALL_R_DEFINE(off_t, lseek, int, fd, off_t, offset, int, whence)
#else
off_t my_lseek(int fd, off_t offset, int whence)
#endif
{
	struct vfscore_file *fp;
	off_t org;
	int error;

	error = fget(fd, &fp);
	if (error)
		goto out_error;

	error = sys_lseek(fp, offset, whence, &org);
	fdrop(fp);

	if (error)
		goto out_error;

	return org;

	out_error:

	return -error;
}

#ifdef my_lseek64
#undef my_lseek64
#endif

LFS64(my_lseek);


/*
 * The file control system call.
 */
#define SETFL (O_APPEND | O_ASYNC | O_DIRECT | O_NOATIME | O_NONBLOCK)

#if 0
UK_LLSYSCALL_R_DEFINE(int, fcntl, int, fd, unsigned int, cmd, int, arg)
#else
int my_fcntl(int fd, unsigned int cmd, int arg)
#endif
{
	struct vfscore_file *fp;
	int ret = 0, error;
#if defined(FIONBIO) && defined(FIOASYNC)
	int tmp;
#endif

	error = fget(fd, &fp);
	if (error)
		goto out_errno;

	// An important note about our handling of FD_CLOEXEC / O_CLOEXEC:
	// close-on-exec shouldn't have been a file flag (fp->f_flags) - it is a
	// file descriptor flag, meaning that that two dup()ed file descriptors
	// could have different values for FD_CLOEXEC. Our current implementation
	// *wrongly* makes close-on-exec an f_flag (using the bit O_CLOEXEC).
	// There is little practical difference, though, because this flag is
	// ignored in OSv anyway, as it doesn't support exec().
	switch (cmd) {
	case F_DUPFD:
		error = fdalloc(fp, &ret);
		if (error)
			goto out_errno;
		break;
	case F_GETFD:
		ret = (fp->f_flags & O_CLOEXEC) ? FD_CLOEXEC : 0;
		break;
	case F_SETFD:
		FD_LOCK(fp);
		fp->f_flags = (fp->f_flags & ~O_CLOEXEC) |
				((arg & FD_CLOEXEC) ? O_CLOEXEC : 0);
		FD_UNLOCK(fp);
		break;
	case F_GETFL:
		// As explained above, the O_CLOEXEC should have been in f_flags,
		// and shouldn't be returned. Linux always returns 0100000 ("the
		// flag formerly known as O_LARGEFILE) so let's do it too.
		ret = (vfscore_oflags(fp->f_flags) & ~O_CLOEXEC) | 0100000;
		break;
	case F_SETFL:
		FD_LOCK(fp);
		fp->f_flags = vfscore_fflags((vfscore_oflags(fp->f_flags) & ~SETFL) |
				(arg & SETFL));
		FD_UNLOCK(fp);

#if defined(FIONBIO) && defined(FIOASYNC)
		/* Sync nonblocking/async state with file flags */
		tmp = fp->f_flags & FNONBLOCK;
		vfs_ioctl(fp, FIONBIO, &tmp);
		tmp = fp->f_flags & FASYNC;
		vfs_ioctl(fp, FIOASYNC, &tmp);
#endif
		break;
	case F_DUPFD_CLOEXEC:
		error = fdalloc(fp, &ret);
		if (error)
			goto out_errno;
		fp->f_flags |= O_CLOEXEC;
		break;
	case F_SETLK:
		uk_pr_warn_once("fcntl(F_SETLK) stubbed\n");
		break;
	case F_GETLK:
		uk_pr_warn_once("fcntl(F_GETLK) stubbed\n");
		break;
	case F_SETLKW:
		uk_pr_warn_once("fcntl(F_SETLKW) stubbed\n");
		break;
	case F_SETOWN:
		uk_pr_warn_once("fcntl(F_SETOWN) stubbed\n");
		break;
	default:
		uk_pr_err("unsupported fcntl cmd 0x%x\n", cmd);
		error = EINVAL;
	}

	fdrop(fp);
	if (error)
		goto out_errno;

	return ret;

out_errno:
	return -error;
}


int __fxstat(int ver __unused, int fd, struct stat *st)
{
	struct vfscore_file *fp;
	int error;

	error = fget(fd, &fp);
	if (error)
		goto out_errno;

	error = sys_fstat(fp, st);
	fdrop(fp);

	if (error)
		goto out_errno;

	return 0;

	out_errno:

	errno = error;
	return -1;
}

#ifdef __fxstat64
#undef __fxstat64
#endif

LFS64(__fxstat);

#if 0
UK_SYSCALL_DEFINE(int, fstat, int, fd, struct stat *, st)
#else
int my_fstat(int fd, struct stat *st)
#endif
{
	return __fxstat(1, fd, st);
}

int __xstat(int ver __unused, const char *pathname, struct stat *st)
{
	struct task *t = main_task;
	char path[PATH_MAX];
	int error;

	error = task_conv(t, pathname, 0, path);
	if (error)
		goto out_errno;

	error = sys_stat(path, st);
	if (error)
		goto out_errno;

	return 0;

	out_errno:

	return -error;
}

#ifdef __xstat64
#undef __xstat64
#endif

LFS64(__xstat);

#if 0
UK_SYSCALL_R_DEFINE(int, stat, const char*, pathname, struct stat*, st)
#else
int my_stat(const char *pathname, struct stat *st)
#endif
{
	if (!pathname) {
		return -EINVAL;
	}
	return __xstat(1, pathname, st);
}

#ifdef stat64
#undef stat64
#endif

LFS64(my_stat);

int __lxstat(int ver __unused, const char *pathname, struct stat *st)
{
	struct task *t = main_task;
	char path[PATH_MAX];
	int error;

	error = task_conv(t, pathname, 0, path);
	if (error) {
		goto out_error;
	}

	error = sys_lstat(path, st);
	if (error) {
		goto out_error;
	}

	return 0;

	out_error:

	return -error;
}

#ifdef __lxstat64
#undef __lxstat64
#endif

LFS64(__lxstat);

#if 0
UK_SYSCALL_R_DEFINE(int, lstat, const char*, pathname, struct stat*, st)
#else
int my_lstat(const char *pathname, struct stat *st)
#endif
{
	return __lxstat(1, pathname, st);
}

#ifdef lstat64
#undef lstat64
#endif

LFS64(my_lstat);
