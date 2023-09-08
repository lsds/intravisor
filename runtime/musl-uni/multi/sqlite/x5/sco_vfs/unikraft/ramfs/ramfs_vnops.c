/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2006-2007, Kohsuke Ohtani
 * Copyright (C) 2014 Cloudius Systems, Ltd.
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

/*
 * rmafs_vnops.c - vnode operations for RAM file system.
 */
#define _GNU_SOURCE

#include <uk/essentials.h>

//#include <sys/stat.h>
#include <dirent.h>
#include <sys/param.h>

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include <uk/page.h>
#include <vfscore/vnode.h>
#include <vfscore/mount.h>
#include <vfscore/uio.h>
#include <vfscore/file.h>

#include "ramfs.h"
#include <dirent.h>
#include <fcntl.h>
#include <vfscore/fs.h>


extern __intcap_t c_out_7(int, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t);
extern __intcap_t c_out_5(int, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t);
extern __intcap_t c_out_3(int, __intcap_t, __intcap_t, __intcap_t);


int ramfs_open(struct vfscore_file *f) {
	return c_out_3(900, f, 0, 0);
}

int ramfs_close(struct vnode *v, struct vfscore_file *f) {
	return c_out_3(901, v, f, 0);
}

int ramfs_read(struct vnode *v, struct vfscore_file *f, struct uio *u, int a) {
	return c_out_5(902, v, f, u, a, 0);
}

//////
int ramfs_write(struct vnode *v, struct uio *u, int a) {
	return c_out_3(903, v, u, a);
}

int ramfs_seek(struct vnode *v, struct vfscore_file *f, off_t o1, off_t o2) {
	return c_out_5(904, v, f, o1, o2, 0);
}

int ramfs_ioctl(struct vnode *v, struct vfscore_file *f, unsigned long a, void *b) {
	return c_out_5(905, v, f, a, b, 0);
}

int ramfs_fsync(struct vnode *v, struct vfscore_file *f) {
	return c_out_3(906, v, f, 0);
}

int ramfs_readdir(struct vnode *v, struct vfscore_file *f, struct dirent *d) {
	return c_out_3(907, v, f, d);
}

int ramfs_lookup(struct vnode *v, char *a, struct vnode **b) {
	return c_out_3(908, v, a, b);
}

int ramfs_create(struct vnode *v, char *a, mode_t b) {
	return c_out_3(909, v, a, b);
}

int ramfs_remove(struct vnode *v1, struct vnode *v2, char *a) {
	return c_out_3(910, v1, v2, a);
}

int ramfs_rename(struct vnode *v1, struct vnode *v2, char *a, struct vnode *v3, struct vnode *v4, char *b) {
	return c_out_7(911, v1, v2, a, v3, v4, b, 0);
}

int ramfs_mkdir(struct vnode *v, char *a, mode_t b) {
	return c_out_3(912, v, a, b);
}

int ramfs_rmdir(struct vnode *v1, struct vnode *v2, char *a) {
	return c_out_3(913, v1, v2, a);
}

int ramfs_getattr(struct vnode *v1, struct vattr *v2) {
	return c_out_3(914, v1, v2, 0);
}

int ramfs_setattr(struct vnode *v1, struct vattr *v2) {
	return c_out_3(915, v1, v2, 0);
}

int ramfs_inactive(struct vnode *v) {
	return c_out_3(916, v, 0, 0);
}

int ramfs_truncate(struct vnode *v, off_t o) {
	return c_out_3(917, v, o, 0);
}

int ramfs_link(struct vnode *v1, struct vnode *v2, char *a) {
	return c_out_3(918, v1, v2, a);
}

int ramfs_cache(struct vnode *v, struct vfscore_file *f, struct uio *u) {
	return c_out_3(919, v, f, u);
}

int ramfs_fallocate(struct vnode *v, int a, off_t b, off_t c) {
	return c_out_5(920, v, a, b, c, 0);
}

int ramfs_readlink(struct vnode *v, struct uio *u) {
	return c_out_3(921, v, u, 0);
}

int ramfs_symlink(struct vnode *v, char *a, char *b) {
	return c_out_3(922, v, a, b);
}

struct ramfs_node *ramfs_allocate_node(const char *name, int type) {
	return c_out_3(923, name, type, 0);
}

////

__intcap_t syscalls_vfs(int t5, void *a0, void *a1, void *a2) {
	switch(t5) {
		case 1000:
			return vfscore_uiomove(a0, a1, a2);
		case 1001:
			return vfscore_vget(a0, a1, a2);
		case 1002:
			return vfscore_vop_nullop();
		case 1003:
			return vfscore_vop_einval();
		case 1004:
			return vfscore_vop_eperm();
		default:
			printf("VFS RAMFS wrong t5 %d\n", (int) t5);
	}
}



#define ramfs_open      ((vnop_open_t)vfscore_vop_nullop)
#define ramfs_close     ((vnop_close_t)vfscore_vop_nullop)
#define ramfs_seek      ((vnop_seek_t)vfscore_vop_nullop)
#define ramfs_ioctl     ((vnop_ioctl_t)vfscore_vop_einval)
#define ramfs_fsync     ((vnop_fsync_t)vfscore_vop_nullop)
#define ramfs_inactive  ((vnop_inactive_t)vfscore_vop_nullop)
#define ramfs_link      ((vnop_link_t)vfscore_vop_eperm)
#define ramfs_fallocate ((vnop_fallocate_t)vfscore_vop_nullop)

/*
 * vnode operations
 */
struct vnops ramfs_vnops = {
		ramfs_open,             /* open */
		ramfs_close,            /* close */
		ramfs_read,             /* read */
		ramfs_write,            /* write */
		ramfs_seek,             /* seek */
		ramfs_ioctl,            /* ioctl */
		ramfs_fsync,            /* fsync */
		ramfs_readdir,          /* readdir */
		ramfs_lookup,           /* lookup */
		ramfs_create,           /* create */
		ramfs_remove,           /* remove */
		ramfs_rename,           /* remame */
		ramfs_mkdir,            /* mkdir */
		ramfs_rmdir,            /* rmdir */
		ramfs_getattr,          /* getattr */
		ramfs_setattr,          /* setattr */
		ramfs_inactive,         /* inactive */
		ramfs_truncate,         /* truncate */
		ramfs_link,             /* link */
		(vnop_cache_t) NULL,    /* arc */
		ramfs_fallocate,        /* fallocate */
		ramfs_readlink,         /* read link */
		ramfs_symlink,          /* symbolic link */
};

