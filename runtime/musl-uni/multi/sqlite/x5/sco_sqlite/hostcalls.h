#ifndef _HOSTCALLS___H_
#define	_HOSTCALLS___H_

#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>

#include <sys/types.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include <arch.h>

#include "_types.h"

void *my_memcpy(void *dst, void *src, unsigned long n);
void *my_memset(void *dst, char c, unsigned long n);

__intcap_t c_out2_5(int, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t);
__intcap_t c_out2_3(int, __intcap_t, __intcap_t, __intcap_t);


// hostcalls
__intcap_t c_out_7(int, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t);
__intcap_t c_out_6(int, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t);
__intcap_t c_out_5(int, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t);
__intcap_t c_out_4(int, __intcap_t, __intcap_t, __intcap_t, __intcap_t);
__intcap_t c_out_3(int, __intcap_t, __intcap_t, __intcap_t);
__intcap_t c_out_2(int, __intcap_t, __intcap_t);
__intcap_t c_out_1(int, __intcap_t);
__intcap_t c_out_0(int);


int host_get_my_inner(void *ptr);
int host_syscall_handler_prb(char *name, void *, void *, void *);
int host_get_sc_caps(int, int, void *ptr);
int host_write_out(char *ptr, int size);

void host_exit();

////////////////
int host_gettimeofday(void *tv, void *tz);
void host_nolibos_init(void);
//////
void ramfs_caps_init();
void vfs_caps_init();
void nolibc_caps_init();
/////
#include <sys/stat.h>

int host_lstat(const char *pathname, struct stat *statbuf);
int host_unlink(const char __capability *pathname);				//my
int host_close(int fd);						//my
int host_access(const char *pathname, int mode);		//my
//char *host_getcwd(char *buf, size_t size);			//my
int host_stat(const char *pathname, struct stat *statbuf);
int host_fstat(int fd, struct stat *statbuf);
int host_truncate(const char *path, size_t length);		//my
__ssize_t host_read(int fd, void *buf, size_t count);		//my
__ssize_t host_write(int fd, const void *buf, size_t count);	//my
int host_open(const char *pathname, int flags, mode_t mode);	//my
off_t host_lseek(int fd, off_t offset, int whence);		//my
int host_get_errno(void);
int host_fcntl(int fd, int cmd, long *ptr );			//my

int my_lstat(const char *pathname, struct stat *statbuf);
int my_unlink(const char *pathname);				//my
int my_close(int fd);						//my
int my_access(const char *pathname, int mode);		//my
char *my_getcwd(char *buf, size_t size);			//my
int my_stat(const char *pathname, struct stat *statbuf);
int my_fstat(int fd, struct stat *statbuf);
int my_truncate(const char *path, size_t length);		//my
__ssize_t my_read(int fd, void *buf, size_t count);		//my
__ssize_t my_write(int fd, const void *buf, size_t count);	//my
int my_open(const char *pathname, int flags, mode_t mode);	//my
off_t my_lseek(int fd, off_t offset, int whence);		//my
int my_fcntl(int fd, int cmd, long *ptr );			//my


#endif