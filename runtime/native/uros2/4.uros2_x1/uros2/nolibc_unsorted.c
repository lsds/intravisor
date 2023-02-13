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

//ssize_t sendto(int socket, const void *buffer, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len) {
ssize_t sendto(int socket, const void *buffer, size_t length, int flags, void *dest_addr, int dest_len) {
         printf("not implemented %s\n", __func__);
}

//ssize_t recvfrom(int socket, void *restrict buffer, size_t length, int flags, struct sockaddr *restrict address, socklen_t *restrict address_len) {
ssize_t recvfrom(int socket, void *restrict buffer, size_t length, int flags, void *restrict address, void *restrict address_len) {
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

#endif

int sigfillset(sigset_t *set) {
       printf("not implemented %s\n", __func__);
}


//////////////////// REDIS

void
     freeaddrinfo(struct addrinfo *ai)
 {
	printf("not implemented %s\n", __func__);
}

int
     chmod(const char *path, mode_t mode)
 {
	printf("not implemented %s\n", __func__);
}

 int
     pipe(int fildes[2])
 {
	printf("not implemented %s\n", __func__);
}

 long
     random(void)
 {
	printf("not implemented %s\n", __func__);
}

int
     rand(void)
 {
	printf("not implemented %s\n", __func__);
}

int
     flock(int fd, int operation)
 {
	printf("not implemented %s\n", __func__);
}

long
     sysconf(int name)
 {
	printf("not implemented %s\n", __func__);
}

 int
     usleep(useconds_t microseconds)
 {
	printf("not implemented %s\n", __func__);
}

char **environ;

int
     execve(const char *path, char *const argv[], char *const envp[])
 {
	printf("not implemented %s\n", __func__);
}
 int
     getrlimit(int resource, struct rlimit *rlp)
 {
	printf("not implemented %s\n", __func__);
}
int
     sigemptyset(sigset_t *set)
 {
	printf("not implemented %s\n", __func__);
}
int
     sprintf(char * restrict str, const char * restrict format, ...)
 {
	printf("not implemented %s\n", __func__);
}
pid_t
     setsid(void)
 {
	printf("not implemented %s\n", __func__);
}
     int
     dup(int fildes)
 {
	printf("not implemented %s\n", __func__);
}
     int
     dup2(int fildes, int fildes2)
 {
	printf("not implemented %s\n", __func__);
}
int
     fileno(FILE *stream)
 {
	printf("not implemented %s\n", __func__);
}
int
     raise(int sig)
 {
	printf("not implemented %s\n", __func__);
}
char *
     setlocale(int category, const char *locale)
 {
	printf("not implemented %s\n", __func__);
}
void
     tzset(void)
 {
	printf("not implemented %s\n", __func__);
}
void
     srand(unsigned seed)
 {
	printf("not implemented %s\n", __func__);
}
     void
     srandom(unsigned seed) {
	printf("not implemented %s\n", __func__);
}
mode_t
     umask(mode_t cmask)
 {
	printf("not implemented %s\n", __func__);
}

size_t
     fread(void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream)
 {
	printf("not implemented %s\n", __func__);
}
char *
     timezone(int zone, int dst)
 {
	printf("not implemented %s\n", __func__);
}
     int
     strcoll(const char *s1, const char *s2)
 {
	printf("not implemented %s\n", __func__);
}
 int
     kill(pid_t pid, int sig)
 {
	printf("not implemented %s\n", __func__);
}
int
     mkostemp(char *template, int oflags)
 {
	printf("not implemented %s\n", __func__);
}
  int
     chdir(const char *path)
 {
	printf("not implemented %s\n", __func__);
}
     long long
     atoll(const char *str)
 {
	printf("not implemented %s\n", __func__);
}

 int
     fseek(FILE *stream, long offset, int whence) {
	printf("not implemented %s\n", __func__);
}
     off_t
     ftello(FILE *stream)
 {
	printf("not implemented %s\n", __func__);
}
     int
     dladdr(const void* addr, void* info)
 {
	printf("not implemented %s\n", __func__);
}
int
     setitimer(int which, const struct itimerval *restrict value, struct itimerval *restrict ovalue)
 {
	printf("not implemented %s\n", __func__);
}

 int
     sigaddset(sigset_t *set, int signo)
 {
	printf("not implemented %s\n", __func__);
}
 int
     ioctl(int fildes, unsigned long request, ...)
 {
	printf("not implemented %s\n", __func__);
}
 int
     mprotect(void *addr, size_t len, int prot)
 {
	printf("not implemented %s\n", __func__);
}
int
     madvise(void *addr, size_t len, int advice)
 {
	printf("not implemented %s\n", __func__);
}

     char *
     ctime_r(const time_t *clock, char *buf)
 {
	printf("not implemented %s\n", __func__);
}

void*
     dlopen(const char* path, int mode)
      {
	printf("not implemented %s\n", __func__);
}
 void*
     dlsym(void* handle, const char* symbol)
 {
	printf("not implemented %s\n", __func__);
}
const char*
     dlerror(void)
 {
	printf("not implemented %s\n", __func__);
}
     int
     dlclose(void* handle)
      {
	printf("not implemented %s\n", __func__);
}

     void
     longjmp(int env, int val)
 {
	printf("not implemented %s\n", __func__);
}
     void
     longjmperror(void)
 {
	printf("not implemented %s\n", __func__);
}
     int
     setjmp(int env)
 {
	printf("not implemented %s\n", __func__);
}
struct lconv *
     localeconv(void)
 {
	printf("not implemented %s\n", __func__);
}
 int
     ungetc(int c, FILE *stream)
 {
	printf("not implemented %s\n", __func__);
}
     
     
int
     ferror(FILE *stream)
 {
	printf("not implemented %s\n", __func__);
}
long
     ftell(FILE *stream)
 {
	printf("not implemented %s\n", __func__);
}
    
    
void
     clearerr(FILE *stream)
 {
	printf("not implemented %s\n", __func__);
}

 FILE *
     tmpfile(void)
 {
	printf("not implemented %s\n", __func__);
}

double
     difftime(time_t time1, time_t time0)
 {
	printf("not implemented %s\n", __func__);
}

int     system(const char *command)
 {
	printf("not implemented %s\n", __func__);
}
     
int remove(const char *path) {
	printf("not implemented %s\n", __func__);
}

char *tmpnam(char *) {
	printf("not implemented %s\n", __func__);
}

int sched_setaffinity(pid_t tid, size_t size, int *set) {
	printf("not implemented %s\n", __func__);

}

int setenv (const char *, const char *, int) {
	printf("not implemented %s\n", __func__);

}

int sync_file_range(int, off_t, off_t, unsigned) {
	printf("not implemented %s\n", __func__);

}

char *dirname(char *) {
	printf("not implemented %s\n", __func__);
}

char *basename(char *path) {
	printf("not implemented %s\n", __func__);
}

int prctl (int, ...) {
	printf("not implemented %s\n", __func__);
}

int uname (struct utsname *) {
	printf("not implemented %s\n", __func__);
}

void openlog (const char *, int, int) {
	printf("not implemented %s\n", __func__);
}

int fdatasync(int) {
	printf("not implemented %s\n", __func__);

}

void syslog (int, const char *, ...) {
	printf("not implemented %s\n", __func__);

}

int pipe2(int [2], int) {
	printf("not implemented %s\n", __func__);

}

//////// pthread
//#include <pthread.h>

int     pthread_mutex_trylock(pthread_mutex_t *mutex) {
	printf("not implemented %s\n", __func__);

}

int     pthread_cond_signal(pthread_cond_t *cond) {
	printf("not implemented %s\n", __func__);

}

int     pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex) {
	printf("not implemented %s\n", __func__);

}

int     pthread_cond_broadcast(pthread_cond_t *cond) {
	printf("not implemented %s\n", __func__);

}

int     pthread_sigmask(int how, const sigset_t * restrict set, sigset_t * restrict oset) {
	printf("not implemented %s\n", __func__);

}

int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize) {
	printf("not implemented %s\n", __func__);
}

 int
     pthread_attr_getstacksize(const pthread_attr_t *restrict attr, size_t *restrict stacksize) {
	printf("not implemented %s\n", __func__);
     }

int pthread_attr_init(pthread_attr_t *attr) {
	printf("not implemented %s\n", __func__);

     }


int
     pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr) {
	printf("not implemented %s\n", __func__);
     
     }


int
     pthread_join(pthread_t thread, void **value_ptr) {
	printf("not implemented %s\n", __func__);
     
     }
     
int
     pthread_cancel(pthread_t thread) {
	printf("not implemented %s\n", __func__);
     
     }
int
     pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg) {
	printf("not implemented %s\n", __func__);
     return 0;
     }
 int
     pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr) {
	printf("not implemented %s\n", __func__);
     
     }
     
void
     pthread_setname_np(const char *name) {
	printf("not implemented %s\n", __func__);
     
     }
int
     pthread_mutex_unlock(pthread_mutex_t *mutex) {
//	printf("not implemented %s\n", __func__);
    return 0;     
     }
     
int
     pthread_mutex_lock(pthread_mutex_t *mutex) {
//	printf("not implemented %s\n", __func__);
     return 0;
     }
pthread_t
     pthread_self(void) {
	printf("not implemented %s\n", __func__);
     
     }
     
  int
     pthread_setcanceltype(int type, int *oldtype) {
	printf("not implemented %s\n", __func__);
     
     }
 int
     pthread_setcancelstate(int state, int *oldstate) {
	printf("not implemented %s\n", __func__);
     
     }

