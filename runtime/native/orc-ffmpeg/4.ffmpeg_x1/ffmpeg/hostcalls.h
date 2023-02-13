#ifndef _HOSTCALLS___H_
#define	_HOSTCALLS___H_

#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>

#include <sys/types.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "_types.h"

#include <arch.h>

void *my_memcpy(void *dst, void *src, unsigned long n);
void *my_memset(void *dst, char c, unsigned long n);


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
int host_get_sc_caps(int me, int they, void *ptr);

int host_write_out(char *ptr, int size);

void host_exit();

////////////////
int host_nanosleep(const struct timespec *rqtp, struct timespec *rmtp);
int host_gettimeofday(void *tv, void *tz);
int host_socket(int domain, int type, int protocol);
int host_setsockopt(int socket, int level, int option_name, const void *option_value, unsigned long option_len);
int host_bind(int socket, void *address, unsigned long address_len);
int host_listen(int socket, int backlog);
int host_poll(void *fds, long nfds, int timeout);
int host_accept(int socket, void *address, void *restrict address_len);
ssize_t host_send(int socket, const void *buffer, size_t length, int flags);
ssize_t host_recv(int socket, void *buffer, size_t length, int flags);

//////

#include <sys/stat.h>

int host_lstat(const char *pathname, struct stat *statbuf);
int host_unlink(const char *pathname);				//my
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