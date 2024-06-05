#include "hostcalls.h"

extern long c_out(void *);

int host_write_out(char *ptr, long size) {
	return (int) c_out_3(1, ptr, (long) size, 0);
}

void host_exit() {
	c_out_3(13, 0, 0, 0);
}

int host_gettimeofday(void *ptr, void *ptr2) {
	return c_out_3(800, (long) ptr, (long) ptr2, 0);
}

long host_get_cpio_size(char *ptr) {
	return c_out_3(900, (long) ptr, 0, 0);
}

long host_load_cpio(char *ptr, char *where, long size) {
	return c_out_3(901, (long) ptr, (long) where, size);
}

/*********/ 

int host_socket(int domain, int type, int protocol) {
	return c_out_3(500, domain, type, protocol);
}

int host_setsockopt(int socket, int level, int option_name, const void *option_value, unsigned long option_len) {
	return c_out_5(501, socket, level, option_name, option_value, option_len);
}

#if 0
int host_getsockopt(int socket, int level, int option_name, const void *option_value, void *a4) {
	return c_out_5(, socket, level, option_name, option_value, a4);
}
#endif


int host_bind(int socket, void *address, unsigned long address_len) {
	return c_out_3(506, socket, address, address_len);
}

int host_connect(int socket, void *address, unsigned long address_len) {
	return c_out_3(532, socket, address, address_len);
}

int host_listen(int socket, int backlog) {
	return c_out_3(504, socket, backlog, 0);
}

int host_accept(int socket, void *address, void *restrict address_len) {
	return c_out_3(505, socket, address, address_len);
}

int host_select(int nfds, __intcap_t * readfds, __intcap_t * writefds, __intcap_t * errorfds, __intcap_t * timeout) {
	return c_out_5(514, nfds, readfds, writefds, errorfds, timeout);
}

ssize_t host_send(int socket, const void *buffer, size_t length, int flags) {
	return c_out_5(509, socket, buffer, length, flags, 0);
}

ssize_t host_recv(int socket, void *buffer, size_t length, int flags) {
	return c_out_5(510, socket, buffer, length, flags, 0);
}

int host_poll(void *fds, long nfds, int timeout) {
	return c_out_3(513, fds, nfds, timeout);
}

int host_getpeername(int socket, struct sockaddr *restrict address, __intcap_t *a) {
	return c_out_3(531, socket, address, a);
}

int host_close(int socket) {
	return c_out_3(511, socket, 0, 0);
}

int host_fcntl(int fd, int cmd, long val) {
	return c_out_3(533, fd, cmd, val);
}

// threading
int host_futex(uint32_t *a0, int a1, uint32_t a2, void *a3, uint32_t *a4, uint32_t a5) {
	return c_out_7(1000, a0, a1, a2, a3, a4, a5, 0);
}

int host_clone(__intcap_t a0, __intcap_t a1, __intcap_t a2, __intcap_t a3, __intcap_t a4) {
	return c_out_5(1001, a0, a1, a2, a3, a4);
}

int host_gettid() {
	return c_out_3(1002, 0, 0, 0);
}