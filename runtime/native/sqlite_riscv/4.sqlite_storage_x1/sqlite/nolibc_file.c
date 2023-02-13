#include <sys/types.h>
#include "_types.h"
#include <stdarg.h>

#include <string.h>
#include <stdio.h>

#include "morello_helpers.h"
#include "hostcalls.h"

#define UCHAR_MAX 255

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(x) ((x)-ONES & ~(x) & HIGHS)

#define true 1

#define NL	1

int carrie_errno;

size_t strftime(char *restrict s, size_t n, const char *restrict f, const struct tm *restrict tm) {
	__asm__ __volatile__ ("ebreak");
}


int fflush(FILE *stream) {
//	printf("FFLUSH\n");
	return 0; //
}

int close(int fd) {
//	printf("%s %d\n", __func__, fd);
#if NL
	return my_close(fd);

//	if(my_ret != host_ret)
//		printf("%s my:%d, host=%d\n", __func__, my_ret, host_ret);
//	return host_ret;

#else
	return host_close(fd);
#endif
}

int access(const char *pathname, int mode) {
	printf("%s\n", __func__);
#if NL
	int my_ret = my_access(pathname, mode);
//	int host_ret = host_access(pathname, mode);
//	if(my_ret != host_ret)
//		printf("%s my:%d, host=%d\n", __func__, my_ret, host_ret);
//	return host_ret;
	return my_ret;
#else
	return host_access(pathname, mode);
#endif
}

#define MYPATH	"/e"

char *getcwd(char *buf, size_t size) {
#if NL
	printf("getcwd\n");

	char *my_ret = my_getcwd(buf, size);
	printf("getcwd '%s'\n", my_ret);

//	return host_getcwd(buf, size);

	if(buf) {
		memcpy(buf, MYPATH, sizeof(MYPATH));
		return buf;
	} else
		return MYPATH;
#endif
}

int stat(const char *pathname, struct stat *statbuf) {
#if NL
//	printf("%s\n", __func__);
	int my_ret = my_stat(pathname, statbuf);
//	int host_ret = host_stat(pathname, statbuf);
//	if(my_ret != host_ret)
//		printf("%s my:%d, host=%d\n", __func__,  my_ret, host_ret);
//	return host_ret;

	return my_ret;
#else
	int ret = host_stat(pathname, statbuf);
	return ret;
#endif
}

int fstat(int fd, struct stat *statbuf) {
#if NL
//	printf("%s\n", __func__);
	int my_ret = my_fstat(fd, statbuf);
//	int host_ret = host_fstat(fd, statbuf);
//	if(my_ret != host_ret)
//		printf("%s my:%d, host=%d\n", __func__, my_ret, host_ret);
//	return host_ret;
	return my_ret;
#else
	return host_fstat(fd, statbuf);
#endif
}

int truncate(const char *path, off_t length) {
#if NL
	printf("%s\n", __func__);
	int my_ret =  my_truncate(path, length);
#if 0
	int host_ret = host_truncate(path, length);
	if(my_ret != host_ret)
		printf("%s my:%d, host=%d\n", __func__, my_ret, host_ret);
	return host_ret;
#else
	return my_ret;
#endif
#else
	return host_truncate(path, length);
#endif
}

//int fcntl(int fd, int cmd, ... /* arg */ ) {
int fcntl(int fd, int cmd, long *ptr ) {
#if NL
//	printf("%s %d %d\n", __func__, fd, cmd);
	int my_ret =  my_fcntl(fd, cmd, ptr);
#if 0
	int host_ret = host_fcntl(fd, cmd, ptr);
	if(my_ret != host_ret)
		printf("%s my:%d, host=%d\n", __func__, my_ret, host_ret);
//	return host_ret;
#endif
	return 0;
#else
	int ret = host_fcntl(fd, cmd, ptr);
//	printf("fcntl ret = %d\n", ret);
	return 0;
#endif
}

ssize_t read(int fd, void *buf, size_t count) {
#if NL
//	printf("%s\n", __func__);

	int my_ret = my_read(fd, buf, count);

	return my_ret;

#else
	return host_read(fd, buf, count);
#endif
}

ssize_t write(int fd, const void *buf, size_t count) {
#if NL
//	printf("%s\n", __func__);
	int my_ret = my_write(fd, buf, count);
//	printf("%s %d %x %d\n", __func__, fd, (int) buf, (int) count);
#if 0
	int host_ret = host_write(fd, buf, count);
	if(my_ret != host_ret)
		printf("%s my:%d, host=%d\n", __func__, my_ret, host_ret);
	return host_ret;
#else
	return my_ret;
#endif
#else
	return host_write(fd, buf, count);
#endif
}

int fchmod(int fd, mode_t mode) {
//	printf("%s\n", __func__);
	return 0; //
}

int unlink(const char *pathname) {
#if NL
//	printf("%s %s\n", __func__, pathname);
	int ret_my = my_unlink(pathname);
#if 0
	int ret_host = host_unlink(pathname);
	printf("%s: %d %d\n", __func__, ret_host, ret_my);
	return ret_host;
#else
	return ret_my;
#endif
#else
	return host_unlink(pathname);
#endif
}

int mkdir(const char *pathname, mode_t mode) {
//	printf("%s\n", __func__);
	return 0; //
}

int rmdir(const char *pathname) {
//	printf("%s\n", __func__);
	return 0; //
}

int fchown(int fd, uid_t owner, gid_t group) {
//	printf("%s\n", __func__);
	return 0; //
}

uid_t geteuid(void) {
//	printf("%s\n", __func__);
	return 1000;
}



//ld: error: undefined symbol: __assert_fail
//ld: error: undefined symbol: __errno_location

pid_t getpid(void) {
//	printf("%s\n", __func__);
	return 2000;
}
unsigned int sleep(unsigned int seconds) {
//	printf("%s\n", __func__);
	return 0; //
}


int gettimeofday(struct timeval *tv, struct timezone *tz){
	if (!tv) return 0;

//	printf("%s\n", __func__);
	return host_gettimeofday(tv, tz);
}

int open(const char *pathname, int flags, mode_t mode){
#if NL
//	printf("%s %s\n", __func__, pathname);
	int my_ret =  my_open(pathname, flags, mode);
#if 0
	int host_ret = host_open(pathname, flags, mode);
	if(my_ret != host_ret)
		printf("%s my:%d, host=%d\n", __func__, my_ret, host_ret);
	return host_ret;
#else
	return my_ret;
#endif

#else
	int ret = host_open(pathname, flags, mode);
//	printf("open %s --> %d\n", pathname, ret);
	return ret;
#endif
}

int getpagesize(void){
//	printf("%s\n", __func__);
	return 4096;
}

off_t lseek(int fd, off_t offset, int whence){
#if NL
//	printf("%s\n", __func__);
	int my_ret = my_lseek(fd, offset, whence);
#if 0
	int host_ret = host_lseek(fd, offset, whence);
	if(my_ret != host_ret)
		printf("%s my:%d, host=%d\n", __func__, my_ret, host_ret);

	return host_ret;
#else
	return my_ret;
#endif
#else
	return host_lseek(fd, offset, whence);
#endif
}

int fsync(int fd){
//	printf("%s\n", __func__);
	return 0; //
}


int utimes(const char *filename, const struct timeval times[2]){
//	printf("%s\n", __func__);
	return 0; //
}

int ftruncate(int fd, off_t length){
//	printf("%s\n", __func__);
	return 0; //
}

int munmap(void *addr, size_t length){
//	printf("%s\n", __func__);
	return 0; //
}

void *mremap(void *old_address, size_t old_size,  size_t new_size, int flags, ... /* void *new_address */){
//	printf("%s\n", __func__);
	return 0; //
}


int lstat(const char *pathname, struct stat *statbuf){
#if NL
	printf("%s %s\n", __func__, pathname);
	int my_ret = my_lstat(pathname, statbuf);
#if 0
	int host_ret = host_lstat(pathname, statbuf);
	printf("%s: my_ret = %d, host_ret = %d\n", __func__, my_ret, host_ret);
	return host_ret;
#else
//	carrie_errno = -my_ret;
	return 0;
#endif
#else
	return host_lstat(pathname, statbuf);
#endif
}



int *__errno_location(void)
{
//	printf("%s\n", __func__);

//	carrie_errno = host_get_errno();

//	printf("current errno = %d\n", carrie_errno);

	return &carrie_errno; //should be thread-local
}

_Noreturn void __assert_fail (const char *, const char *, int, const char *){
	__asm__ __volatile__ ("ebreak");
}

struct tm *gmtime(const time_t *timep) {
	__asm__ __volatile__ ("ebreak");
};

void exit(int status) {
	__asm__ __volatile__ ("ebreak");
}


int atexit(void (*function)(void)) {
	return 0;
}

#if 1
//cheribsd printf uses malloc, malloc uses  these:

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
//	printf("%s\n", __func__);
	return 0; //
}

ssize_t readlink(const char *pathname, char *buf, size_t bufsiz) {
//	printf("%s\n", __func__);
	return 0; //
}

char *getenv(const char *name){
//	printf("%s\n", __func__);
	return 0; //
}
#endif

// from Unikraft

#include <errno.h>

/* GNU-specific version of strerror_r */
int strerror_r(int errnum, char *buf, size_t buflen)
{
    const char *strerr;

    switch (errnum) {
    case EPERM:
	strerr = "Operation not permitted";
	break;
    case ENOENT:
	strerr = "No such file or directory";
	break;
    case ESRCH:
	strerr = "No such process";
	break;
    case EINTR:
	strerr = "Interrupted system call";
	break;
    case EIO:
	strerr = "Input/output error";
	break;
    case ENXIO:
	strerr = "Device not configured";
	break;
    case E2BIG:
	strerr = "Argument list too long";
	break;
    case ENOEXEC:
	strerr = "Exec format error";
	break;
    case EBADF:
	strerr = "Bad file descriptor";
	break;
    case ECHILD:
	strerr = "No child processes";
	break;
    case EDEADLK:
	strerr = "Resource deadlock avoided";
	break;
    case ENOMEM:
	strerr = "Cannot allocate memory";
	break;
    case EACCES:
	strerr = "Permission denied";
	break;
    case EFAULT:
	strerr = "Bad address";
	break;
    case ENOTBLK:
	strerr = "Block device required";
	break;
    case EBUSY:
	strerr = "Device busy";
	break;
    case EEXIST:
	strerr = "File exists";
	break;
    case EXDEV:
	strerr = "Cross-device link";
	break;
    case ENODEV:
	strerr = "Operation not supported by device";
	break;
    case ENOTDIR:
	strerr = "Not a directory";
	break;
    case EISDIR:
	strerr = "Is a directory";
	break;
    case EINVAL:
	strerr = "Invalid argument";
	break;
    case ENFILE:
	strerr = "Too many open files in system";
	break;
    case EMFILE:
	strerr = "Too many open files";
	break;
    case ENOTTY:
	strerr = "Inappropriate ioctl for device";
	break;
    case ETXTBSY:
	strerr = "Text file busy";
	break;
    case EFBIG:
	strerr = "File too large";
	break;
    case ENOSPC:
	strerr = "No space left on device";
	break;
    case ESPIPE:
	strerr = "Illegal seek";
	break;
    case EROFS:
	strerr = "Read-only file system";
	break;
    case EMLINK:
	strerr = "Too many links";
	break;
    case EPIPE:
	strerr = "Broken pipe";
	break;
    case EDOM:
	strerr = "Numerical argument out of domain";
	break;
    case ERANGE:
	strerr = "Result too large";
	break;
    case EAGAIN:
	strerr = "Resource temporarily unavailable";
	break;
    case EINPROGRESS:
	strerr = "Operation now in progress";
	break;
    case EALREADY:
	strerr = "Operation already in progress";
	break;
    case ENOTSOCK:
	strerr = "Socket operation on non-socket";
	break;
    case EDESTADDRREQ:
	strerr = "Destination address required";
	break;
    case EMSGSIZE:
	strerr = "Message too long";
	break;
    case EPROTOTYPE:
	strerr = "Protocol wrong type for socket";
	break;
    case ENOPROTOOPT:
	strerr = "Protocol not available";
	break;
    case EPROTONOSUPPORT:
	strerr = "Protocol not supported";
	break;
    case ESOCKTNOSUPPORT:
	strerr = "Socket type not supported";
	break;
    case EOPNOTSUPP:
	strerr = "Operation not supported on socket";
	break;
    case EPFNOSUPPORT:
	strerr = "Protocol family not supported";
	break;
    case EAFNOSUPPORT:
	strerr = "Address family not supported by protocol family";
	break;
    case EADDRINUSE:
	strerr = "Address already in use";
	break;
    case EADDRNOTAVAIL:
	strerr = "Can't assign requested address";
	break;
    case ENETDOWN:
	strerr = "Network is down";
	break;
    case ENETUNREACH:
	strerr = "Network is unreachable";
	break;
    case ENETRESET:
	strerr = "Network dropped connection on reset";
	break;
    case ECONNABORTED:
	strerr = "Software caused connection abort";
	break;
    case ECONNRESET:
	strerr = "Connection reset by peer";
	break;
    case ENOBUFS:
	strerr = "No buffer space available";
	break;
    case EISCONN:
	strerr = "Socket is already connected";
	break;
    case ENOTCONN:
	strerr = "Socket is not connected";
	break;
    case ESHUTDOWN:
	strerr = "Can't send after socket shutdown";
	break;
    case ETIMEDOUT:
	strerr = "Operation timed out";
	break;
    case ECONNREFUSED:
	strerr = "Connection refused";
	break;
    case ELOOP:
	strerr = "Too many levels of symbolic links";
	break;
    case ENAMETOOLONG:
	strerr = "File name too long";
	break;
    case EHOSTDOWN:
	strerr = "Host is down";
	break;
    case EHOSTUNREACH:
	strerr = "No route to host";
	break;
    case ENOTEMPTY:
	strerr = "Directory not empty";
	break;
    default:
	strerr = NULL;
	errno = EINVAL; /* Unknown errnum requires errno to be set */
	break;
    }

    if (!buflen)
	return buf;

    /*
     * NOTE: If target buffer is too small, we are supposed to set
     *       errno to ERANGE. We ignore this case for simplification.
     */
    if (strerr)
	memcpy(buf, strerr, strlen(strerr)+1);
    else
	printf("unknown error %d\n", errnum);

    return 0;
}

char seb[64];

/* NOTE: strerror() is not thread-safe, nor reentrant-safe */
char *strerror(int errnum)
{
    /* NOTE: Our longest message is currently 48 characters. With
     *       64 characters we should have room for minor changes
     *       in the future.
     */
    strerror_r(errnum, seb, sizeof(seb));
    return seb;
}

extern int vfscore_rootfs(void);
extern void fdtable_init(void);
extern void vfscore_init(void);

extern int my_open(const char* pathname, int flags, mode_t mode);
extern ssize_t my_write(int fildes, const void *buf, size_t nbyte);
extern ssize_t my_read(int fildes, void *buf, size_t nbyte);
extern int my_close(int fildes);

void *my_malloc(size_t size);


void nolibos_init() {
	printf("prepare nolibos init\n");
	
	void *ptr = my_malloc(1024);
	printf("ptr = %x%x\n", (int) ((int)ptr >> 32), (int) ptr);
	
//	vfscore_rootfs();
//	printf("%d\n", __LINE__);
	fdtable_init();
	printf("%d\n", __LINE__);
	vfscore_init();
	printf("%d\n", __LINE__);
	vfscore_rootfs();

	int fd = -5; 
	fd = my_open("/test", 02 | 0100, 0666);
	printf("fd = %d\n", fd);
	int ret1 = my_write(fd, "hello world", sizeof("hello world"));
	my_close(fd);
	printf("wrote %d \n", ret1);

	fd = my_open("/test", 02, 0666);
	fd = my_open("/test", 02, 0666);
	fd = my_open("/test", 02, 0666);
	fd = my_open("/test", 02, 0666);
	printf("fd = %d\n", fd);
	char data[128];
	int ret2 = my_read(fd, data, 128);
	printf("read %d from file = %s\n", ret2, data);
}