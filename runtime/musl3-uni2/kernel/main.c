#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <fcntl.h>              /* Definition of O_* constants */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/uio.h>
#include "hostcalls.h"
#include "syscall.h.in"
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include <sys/socket.h>
#include <dirent.h>
#include <poll.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <stdint.h>

#include "unikraft/lib/syscall_shim/include/uk/syscall.h"

#define WRAP_HOST_INET	1

int uk_syscall_e_fcntl(int fd, unsigned int cmd, unsigned long arg);
int uk_syscall_e_ioctl(int fd, unsigned int request, void *arg);
int uk_syscall_e_getpeername(int sock, struct sockaddr *restrict addr, socklen_t *restrict addr_len);
int uk_syscall_e_getsockopt(int socket, int level, int option_name, void *option_value, socklen_t *option_len);
long sysconf(int name);

//local store for capabilitites, relative address usualy provided via AUX
char local_cap_store[0xabba];

#define MSG "hello musl2-uni2 \n"
#define ERR	"unknown t5\n"

int wrap_socket_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout) {
	fd_set out_readfds, out_writefds, out_errorfds;
	int ret;

	char *fd_map = malloc(nfds);

	FD_ZERO(&out_readfds);
	FD_ZERO(&out_writefds);
	FD_ZERO(&out_errorfds);

	for(int i = 0; i < nfds; i++) {
		int tmp_fd = -1;
		if (FD_ISSET(i, readfds)) {
			tmp_fd = uk_syscall_e_ioctl(i, 0xcaca, 0);
			FD_SET(i, &out_readfds);
			fd_map[tmp_fd] = i;
		}

		if (FD_ISSET(i, writefds)) {
			tmp_fd = uk_syscall_e_ioctl(i, 0xcaca, 0);
			FD_SET(i, &out_writefds);
			fd_map[tmp_fd] = i;
		}
	}

	ret = host_select(nfds, &out_readfds, &out_writefds, &out_errorfds, timeout);

	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_ZERO(&errorfds);

	for(int i = 0; i < nfds; i++) {
		if (FD_ISSET(i, &out_readfds)) {
			FD_SET(fd_map[i], readfds);
		}

		if (FD_ISSET(i, &out_writefds)) {
			FD_SET(fd_map[i], writefds);
		}

		if (FD_ISSET(i, &out_errorfds)) {
			FD_SET(fd_map[i], errorfds);
		}
	}

	return ret;
}

int wrap_socket_poll(struct pollfd fds[], nfds_t nfds, int timeout) {
	int ret;
	struct pollfd *out_fds = malloc(sizeof(struct pollfd)*nfds);
	if(!out_fds) {
		uk_pr_err("cannot aclloc mem for fds\n");
		return -1;
	}

	for(int i = 0; i < nfds; i++) {
		out_fds[i].fd = uk_syscall_e_ioctl(fds[i].fd, 0xcaca, 0);
		out_fds[i].events = fds[i].events;
	}

	ret = host_poll(out_fds, nfds, timeout);

	for(int i = 0; i < nfds; i++) {
		fds[i].revents = out_fds[i].revents;
	}

	return ret;
}

__intcap_t syscall(__intcap_t a0, __intcap_t a1, __intcap_t a2, __intcap_t a3, __intcap_t a4, __intcap_t a5, __intcap_t a6, __intcap_t a7) {
	long t5 = (long) getT5();

	int ret;

//	printf("LibOS: --> [%d] %d %d %d %d %d\n", t5, __builtin_cheri_tag_get(a0), __builtin_cheri_tag_get(a1), __builtin_cheri_tag_get(a2), __builtin_cheri_tag_get(a3), __builtin_cheri_tag_get(a4));

	switch (t5) {
//17
	case __NR_getcwd:
		ret = uk_syscall_e_getcwd((char*) a0, (size_t) a1);
		break;
//23
	case __NR_dup:
		ret = uk_syscall_e_dup((int) a0);
		break;
//24
	case __NR_dup3:
		ret = uk_syscall_e_dup3((int) a0, (int) a1, (int) a2);
		break;
//25
	case __NR_fcntl:
		ret = uk_syscall_e_ioctl(a0, 0xcaca, 0);
		if( ret < 0 || a1 == F_GETFL) {
			ret = uk_syscall_e_fcntl((int) a0, (int) a1, (int) a2);
			break;
		}
		//a1 is F_SETFL

//#define SOCK_FLAGS (SOCK_NONBLOCK|SOCK_CLOEXEC)
// in fact, these flags do not exist
// should we make a0 fd also non-block? 
		ret = 1;

		if(a2 == 0) {
			ret = uk_syscall_e_setsockopt(a0, SOL_SOCKET, 1, &ret, sizeof(ret));
			break;
		}

//		printf("a2 = %lx\n", a2);
//todo: rewrite this to ioctl
		if(a2 & O_NONBLOCK) {
			ret = uk_syscall_e_setsockopt(a0, SOL_SOCKET, SOCK_NONBLOCK, &ret, sizeof(ret));
			a2 &= ~(O_NONBLOCK);
		}
		if(a2 & FD_CLOEXEC) {
			ret = uk_syscall_e_setsockopt(a0, SOL_SOCKET, SOCK_CLOEXEC, &ret, sizeof(ret));
			a2 &= ~(FD_CLOEXEC);
		}
		
		a2 &= ~O_LARGEFILE;
		a2 &= ~O_RDWR;
		
		if(a2 > 0) {
			uk_pr_err("unknown operationg on socket. %lx\n", a2); 
			while(1);
		}
		break;
//29
	case __NR_ioctl:
//todo: because a2 is not va_arg, we directly jump unto the routine
		ret = uk_syscall_e_ioctl((long) a0, (long) a1, a2);
		break;
//34
	case __NR_mkdirat:
		ret = uk_syscall_e_mkdirat((int) a0, (const char *) a1, (mode_t) a2);
		break;
//35
	case __NR_unlinkat:
		ret = uk_syscall_e_unlinkat((int) a0, (char *)a1, (int) a2);
		break;
//45
	case	__NR_truncate:
		ret = (int) uk_syscall_e_truncate((const char *) a0, (off_t) a1);
		break;
//46
	case	__NR_ftruncate:
		ret = (int) uk_syscall_e_ftruncate((int) a0, (off_t) a1);
		break;
//48
	case __NR_faccessat:
		ret = uk_syscall_e_faccessat((int) a0, (const char *) a1, (int) a2, (int) a3);
		break;
//56
	case __NR_openat:
		ret = uk_syscall_e_openat(a0, a1, a2, a3);
		break;
//57
	case __NR_close:
		ret = uk_syscall_e_close((int) a0);
		break;
//59
	case __NR_pipe2:
		ret = uk_syscall_e_pipe(a0);
		break;
//61
	case	__NR_getdents64:
		ret = uk_syscall_e_getdents64((int) a0, a1, (size_t) a2);
		break;
//62
	case __NR_lseek:
		ret = uk_syscall_e_lseek((int) a0, (off_t) a1, (int) a2);
		break;
//63
	case __NR_read:
		ret = uk_syscall_e_read(a0, a1, a2);
		break;
//64
	case __NR_write:
		ret = uk_syscall_e_write(a0, a1, a2);
		break;
//65
	case __NR_readv:
		ret = uk_syscall_e_readv(a0, a1, a2);
		break;
//66
	case __NR_writev:
		ret = uk_syscall_e_writev(a0, a1, a2);
		break;
//67
	case __NR_pread64:
		ret = uk_syscall_e_pread64((int) a0, (void *)a1, (size_t) a2, (off_t) a3);
		break;
//72
//note: because we mix fd from LibOS and HostOS, we must be super careful
	case __NR_pselect6:
#if WRAP_HOST_INET
		ret = wrap_socket_select((int) a0, a1, a2, a3, a4);
#else
		ret = host_select((int) a0, a1, a2, a3, a4);
#endif
		break;
//73
	case __NR_ppoll:
#if WRAP_HOST_INET
		ret = wrap_socket_poll(a0, a1, a2);
#else
		ret = host_poll(a0, a1, a2);
#endif
		break;
//78
	case __NR_readlinkat:
//we do not have readlinkat, only readlink
		ret = uk_syscall_e_readlink((const char *) a1, (char *) a2, (ssize_t) a3);
		break;
//79
	case __NR_newfstatat:
		ret = uk_syscall_e_newfstatat((int) a0, (char*) a1, (struct stat*) a2, a3);
		break;
//80
	case __NR_fstat:
		ret = uk_syscall_e_fstat((int) a0, (struct stat *) a1);
		break;
//82
	case __NR_fsync:
		ret = uk_syscall_e_fsync((int) a0);
		break;
//93
	case __NR_exit:
//94
	case __NR_exit_group:
//		uk_syscall_e_exit_group(a0); requires posix-process
		host_exit(a0);
		break;

//113
	case __NR_clock_gettime:
		ret = uk_syscall_e_clock_gettime((clockid_t) a0, (struct timespec *) a1);
		break;
//160
	case __NR_uname:
		ret = uk_syscall_e_uname((struct utsname *) a0);
		break;
/************** HOST NETWORKING ************/
//198
	case __NR_socket:
#if WRAP_HOST_INET
		ret = uk_syscall_e_socket((int) a0, (int) a1, (int) a2);
#else
		ret = host_socket((int) a0, (int) a1, (int) a2);
#endif
		break;
//200
	case __NR_bind:
#if WRAP_HOST_INET
		ret = uk_syscall_e_bind((int) a0, a1, (unsigned long) a2);
#else
		ret = host_bind((int) a0, a1, (unsigned long) a2);
#endif
		break;
//201
	case __NR_listen:
#if WRAP_HOST_INET
		ret = uk_syscall_e_listen((int) a0, (int) a1);
#else
		ret = host_listen((int) a0, (int) a1);
#endif
		break;
//202
	case __NR_accept:
#if WRAP_HOST_INET
		ret = uk_syscall_e_accept((int) a0, a1, a2);
#else
		ret = host_accept((int) a0, a1, a2);
#endif
		break;
//203
	case __NR_connect:
#if WRAP_HOST_INET
		ret = uk_syscall_e_connect((int) a0, a1, (unsigned long) a2);
#else
		ret = host_connect((int) a0, a1, (unsigned long) a2);
#endif
		break;
//205
	case __NR_getpeername:
#if WRAP_HOST_INET
		ret = uk_syscall_e_getpeername(a0, a1, a2);
#else
		ret = host_getpeername(a0, a1, a2);
#endif
		break;
//206 //we ignore last two args
	case __NR_sendto:
#if WRAP_HOST_INET
		ret = uk_syscall_e_sendto((int) a0, (void *)a1, (size_t) a2, (int) a3, (struct sockaddr *)a4, (socklen_t) a5);
#else
		ret = host_send(a0, a1, a2, a3);
#endif
		break;
//207 //we ignore last two args
	case __NR_recvfrom:
#if WRAP_HOST_INET
		ret = uk_syscall_e_recvfrom((int) a0, (void *) a1, (size_t) a2, (int) a3, (struct sockaddr *restrict) a4, (socklen_t *restrict) a5);
#else
		ret = host_recv(a0, a1, a2, a3);
#endif
		break;
//208
	case __NR_setsockopt:
#if WRAP_HOST_INET
		ret = uk_syscall_e_setsockopt((int) a0, (int) a1, (int) a2, a3, (unsigned long) a4);
#else
		ret = host_setsockopt((int) a0, (int) a1, (int) a2, a3, (unsigned long) a4);
#endif
		break;
//209
	case __NR_getsockopt:
#if WRAP_HOST_INET
		ret = uk_syscall_e_getsockopt((int) a0, (int) a1, (int) a2, a3, a4);
#else
		ret = host_getsockopt((int) a0, (int) a1, (int) a2, a3, a4);
#endif


		break;
//278
	case __NR_getrandom:
		ret = uk_syscall_e_getrandom((void *) a0, (size_t) a1, (unsigned int) a2);
		break;
/************** host threads ******/
//98
	case __NR_futex:
//		ret = host_futex((uint32_t *)a0, (int) a1, (uint32_t) a2, (struct timespec *)a3, (uint32_t *)a4, (uint32_t) a5);
		ret = uk_syscall_e_futex((uint32_t *)a0, (int) a1, (uint32_t) a2, (struct timespec *)a3, (uint32_t *)a4, (uint32_t) a5);
		break;
//220
	case __NR_clone:
//		printf("%p %p %lx %p %p %p %p\n", a0, a1, a2, a3, a4);
		ret = host_clone(a0, a1, a2, a3, a4);
		break;
/************** stubs *************/
//96
	case __NR_set_tid_address:
		ret = host_gettid();
		printf("tid = %x\n", ret);
		break;
//130
	case __NR_tkill:
		ret = 0;
		break;
//134
	case __NR_rt_sigaction:
//todo: can live without so far
		ret = 0;
		break;
//135
	case __NR_rt_sigprocmask:
//not implemented in uksignal
		ret = 0;
		break;
//172
	case __NR_getpid:
//173
	case __NR_getppid:
//174
	case __NR_getuid:
//175
	case __NR_geteuid:
//176
	case __NR_getgid:
//177
	case __NR_getegid:
//178
	case __NR_gettid:
		ret = host_gettid();
		break;
//179
	case __NR_sysinfo:
		ret = (int) sysinfo(a0);
		break;
//122
	case __NR_sched_setaffinity:
//123
	case __NR_sched_getaffinity:
//210
	case __NR_shutdown:
//261
	case __NR_prlimit64:
		ret = 0;
		break;
//226
	case __NR_mprotect:
		ret = 0;
		break;
//283
	case __NR_membarrier:
		ret = 0;
		break;
	default:
		printf("LibOS/Kernel: unknown t5 %d\n", (int) t5);
		while(1) ;
	}

//	printf("LibOS: <-- [%d]:'%lx'\n", t5, ret);
	return ret;
}

void outer_c() {
	host_write_out(MSG, sizeof(MSG));

	unikraft_init();

	printf("--------- LibOS is ok,  ------- \n\n"); //compiler eats one of \n have no idea how

	extern int app_main();
	int ret = app_main();

	host_exit(ret);
}
