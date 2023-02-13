#include <sys/types.h>
#include "_types.h"
#include <stdarg.h>

#include <string.h>
#include <stdio.h>

#include "cheri_helpers.h"
#include "hostcalls.h"

typedef int (*cmpfun)(const void *, const void *);

int getpwuid_r(uid_t uid, struct passwd *pw, char *buf, size_t size, struct passwd **res) {
    printf("not implemented %s\n", __func__);
}

int fnmatch(const char *pat, const char *str, int flags) {
    printf("not implemented %s\n", __func__);
}

FILE *const stderr;
FILE *const stdout;
FILE *const stdin;

int fputs(const char *restrict s, FILE *restrict f) {
    printf("%s", s);
}

int isatty(int fd) {
    printf("%s %d \n", __func__, fd);
    if(fd < 3)
	return 0;
    else
	return 1;
}



int feof(FILE *stream) {
    printf("not implemented %s\n", __func__);
}

int fscanf(FILE *restrict stream, const char *restrict format, ...) {
    printf("not implemented %s\n", __func__);
}

int unsetenv (const char *e) {
    printf("not implemented %s\n", __func__);
}

int sigaction(int sig, const struct sigaction *restrict act, struct sigaction *restrict oact) {
    printf("not implemented %s\n", __func__);
}

//sig_t signal(int sig, sig_t func) {
int signal(int sig, void * func) {
    printf("not implemented %s\n", __func__);
}

pid_t waitpid(pid_t pid, int *stat_loc, int options) {
    printf("not implemented %s\n", __func__);
}

//int getsockname(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len) {
int getsockname(int socket, void *address, void *address_len) {
    printf("not implemented %s\n", __func__);
}

void perror(const char *s) {
    printf("not implemented %s\n", __func__);
}
char *ctime(const time_t *clock) {
    printf("not implemented %s\n", __func__);
}

pid_t fork(void) {
    printf("not implemented %s\n", __func__);
}

FILE * freopen(const char *path, const char *mode, FILE *stream) {
    printf("not implemented %s\n", __func__);
}

int execvp(const char *file, char *const argv[]) {
    printf("not implemented %s\n", __func__);
}

void _exit(int status) {
    printf("not implemented %s\n", __func__);
}
     
FILE * popen(const char *command, const char *mode) {
    printf("not implemented %s\n", __func__);
}

static once = 0;

int getchar(void) {
    printf("not implemented %s\n", __func__);
    if (once == 0) {
	once = 1;
        return 'y';
    }
    
    return 0;
}

int setrlimit(int resource, const struct rlimit *rlp) {
    printf("not implemented %s\n", __func__);
}
     
struct tm * localtime(const time_t *clock) {
    printf("not implemented %s\n", __func__);
}

//struct hostent * gethostbyaddr(const void *addr, socklen_t len, int type) {
struct hostent * gethostbyaddr(const void *addr, int len, int type) {
    printf("not implemented %s\n", __func__);
}

//int getsockopt(int socket, int level, int option_name, void *restrict option_value, socklen_t *restrict option_len) {
int getsockopt(int socket, int level, int option_name, void *restrict option_value, void * option_len) {
         printf("not implemented %s\n", __func__);
     }

//int connect(int socket, const struct sockaddr *address, socklen_t address_len) {
int connect(int socket, const struct sockaddr *address, int address_len) {
         printf("not implemented %s\n", __func__);
}

//ssize_t sendto(int socket, const void *buffer, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len) {
ssize_t sendto(int socket, const void *buffer, size_t length, int flags, void *dest_addr, int dest_len) {
         printf("not implemented %s\n", __func__);
}

//int getpeername(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len) {
int getpeername(int socket, void *restrict address, void *restrict address_len) {
              printf("not implemented %s\n", __func__);
}

//ssize_t recvfrom(int socket, void *restrict buffer, size_t length, int flags, struct sockaddr *restrict address, socklen_t *restrict address_len) {
ssize_t recvfrom(int socket, void *restrict buffer, size_t length, int flags, void *restrict address, void *restrict address_len) {
                   printf("not implemented %s\n", __func__);
}

int select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, struct timeval *restrict timeout) {
                   printf("not implemented %s\n", __func__);
}

int getrusage(int who, struct rusage *r_usage) {
                   printf("not implemented %s\n", __func__);
}

int setvbuf(FILE *restrict stream, char *restrict buf, int type, size_t size) {
	printf("not implemented %s\n", __func__);
}

int tcgetattr(int fildes, struct termios *termios_p) {
       printf("not implemented %s\n", __func__);
}

int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p) {
       printf("not implemented %s\n", __func__);
}

#if arm_sim
void __getauxval() {
	printf("not implemented %s\n", __func__);
}

void * calloc(size_t count, size_t size) {
	printf("not implemented %s\n", __func__);
}
#endif

int sigfillset(sigset_t *set) {
       printf("not implemented %s\n", __func__);
}