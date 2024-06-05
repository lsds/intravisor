#ifndef _HOSTCALLS___H_
#define	_HOSTCALLS___H_

#include <arch.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdint.h>

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


int host_write_out(char *ptr, long size);
int host_gettimeofday(void *tv, void *tz);
void host_exit();

long host_get_cpio_size(char *ptr);
long host_load_cpio(char *ptr, char *where, long size);

int host_socket(int domain, int type, int protocol);
int host_setsockopt(int socket, int level, int option_name, const void *option_value, unsigned long option_len);
int host_getsockopt(int socket, int level, int option_name, const void *option_value, void *a);
int host_bind(int socket, void *address, unsigned long address_len);
int host_connect(int socket, void *address, unsigned long address_len);
int host_listen(int socket, int backlog);
int host_accept(int socket, void *address, void *restrict address_len);
ssize_t host_send(int socket, const void *buffer, size_t length, int flags);
ssize_t host_recv(int socket, void *buffer, size_t length, int flags);
int host_select(int nfds, __intcap_t * readfds, __intcap_t * writefds, __intcap_t * errorfds, __intcap_t * timeout);
int host_poll(void *fds, long nfds, int timeout);
int host_getpeername(int socket, struct sockaddr *restrict address, __intcap_t *a);
int host_close(int fd);
int host_fcntl(int fd, int cmd, long opt);
int host_futex(uint32_t *, int, uint32_t, void *, uint32_t *, uint32_t);
int host_clone(__intcap_t a0, __intcap_t a1, __intcap_t a2, __intcap_t a3, __intcap_t a4);
int host_gettid();
#endif