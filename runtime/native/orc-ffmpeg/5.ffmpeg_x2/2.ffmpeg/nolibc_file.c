#include <sys/types.h>
#include "_types.h"
#include <stdarg.h>

#include <string.h>
#include <stdio.h>
#include <fcntl.h>

#include "cheri_helpers.h"
#include "hostcalls.h"
#include <sys/uio.h>

#define UCHAR_MAX 255

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(x) ((x)-ONES & ~(x) & HIGHS)

#define true 1

#define NL	1

int carrie_errno;


size_t strftime(char *restrict s, size_t n, const char *restrict f, const struct tm *restrict tm) {
	__asm__ __volatile__ ("brk 0");
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
	printf("%s %d %d\n", __func__, fd, cmd);
//	int my_ret =  my_fcntl(fd, cmd, ptr);
	int my_ret =  my_fcntl(fd, cmd, 0);
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

uid_t getuid(void) {
	return 0xabba;
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
	printf("%s %s\n", __func__, pathname);
	int my_ret =  my_open(pathname, flags, mode);
	printf("ret = %d\n", my_ret);
	if(my_ret < 0) {
		my_ret = -1;
		carrie_errno = -my_ret;
	}

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
//	return my_ret;
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
	__asm__ __volatile__ ("brk 0");
}

struct tm *gmtime(const time_t *timep) {
	__asm__ __volatile__ ("brk 0");
};

void exit(int status) {
	__asm__ __volatile__ ("brk 0");
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

#include <errno.h>

extern int vfscore_rootfs(void);
extern void fdtable_init(void);
extern void vfscore_init(void);
extern int devfs_register_null(void);
extern int devfs_automount(void);

extern int my_open(const char* pathname, int flags, mode_t mode);
extern ssize_t my_write(int fildes, const void *buf, size_t nbyte);
extern ssize_t my_read(int fildes, void *buf, size_t nbyte);
extern int my_close(int fildes);
extern int devfs_register(void);
extern int _uk_swrand_init(void);

       void *my_malloc(size_t size);
       void my_free(void *ptr);
       void *my_realloc(void *ptr, size_t size);


void nolibos_init() {
	printf("prepare nolibos init\n");
	
	void *ptr = my_malloc(1024);
	printf("ptr = %p, %x\n", ptr, (int)ptr);
	
//	vfscore_rootfs();
//	printf("%d\n", __LINE__);
	fdtable_init();
	printf("%d\n", __LINE__);
	vfscore_init();
	printf("%d\n", __LINE__);
	vfscore_rootfs();
	printf("%d\n", __LINE__);
	devfs_automount();
	printf("%d\n", __LINE__);
	devfs_register_null();
	printf("%d\n", __LINE__);
	devfs_register();
	printf("%d\n", __LINE__);
	_uk_swrand_init();

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
	close(fd);

	printf("....testing /dev/zero\n");
	fd = my_open("/dev/zero", 02, 0666);
	printf("/dev/zero fd = %d\n", fd);
	ret2 = my_read(fd, data, 128);
	printf("read %d bytes from /dev/zero\n", ret2);
	close(fd);
	printf("....testing /dev/random\n");
	fd = my_open("/dev/random", 02, 0666);
	printf("/dev/zero fd = %d\n", fd);
	unsigned long rd;
	ret2 = my_read(fd, &rd, sizeof(rd));
	printf("read %d bytes from /dev/random, rd=%lx\n", ret2, rd);
	close(fd);

}


//------------
#include <dirent.h>
int closedir(DIR *dir)
{
#if 0
    int ret = close(dir->fd);
    free(dir);
    return ret;
#else
    printf("not implemened '%s'\n", __func__);
#endif
}

struct dirent *readdir(DIR *dir) {
    printf("not implemened '%s'\n", __func__);
}

DIR *opendir(const char *name)
{
    printf("not implemened '%s'\n", __func__);
 }
 
 
int fprintf(FILE *__restrict, const char *__restrict fmt, ...) {
    printf("not implemened '%s' '%s'\n", __func__, fmt);
}

int rename(const char *old, const char *new) {
    printf("not implemened '%s'\n", __func__);
}


int getpwnam_r(const char *name, struct passwd *pw, char *buf, size_t size, struct passwd **res) {
    printf("not implemened '%s'\n", __func__);
}

int mkstemp(char *template) {
    printf("not implemened '%s'\n", __func__);
}

#include "stdio_impl.h"

static FILE *ofl_head;
static volatile int ofl_lock[1];
volatile int *const __stdio_ofl_lockptr = ofl_lock;

FILE **__ofl_lock()
{
//    LOCK(ofl_lock);
    return &ofl_head;
}

void __ofl_unlock()
{
//    UNLOCK(ofl_lock);
}


FILE *__ofl_add(FILE *f)
{
    FILE **head = __ofl_lock();
    f->next = *head;
    if (*head) (*head)->prev = f;
    *head = f;
    __ofl_unlock();
    return f;
}

ssize_t readv (int d, const struct iovec *iovcnt, int offset) {
    printf("not implemened '%s'\n", __func__);
}

ssize_t writev (int d, const struct iovec *iovcnt, int offset) {
    printf("not implemened '%s'\n", __func__);
}

off_t __stdio_seek(FILE *f, off_t off, int whence)
{
    return lseek(f->fd, off, whence);
}

int __stdio_close(FILE *f)
{
    return close(f->fd);
}


size_t __stdio_write(FILE *f, const unsigned char *buf, size_t len)
{
    struct iovec iovs[2] = {
	{ .iov_base = f->wbase, .iov_len = f->wpos-f->wbase },
	{ .iov_base = (void *)buf, .iov_len = len }
    };
    struct iovec *iov = iovs;
    size_t rem = iov[0].iov_len + iov[1].iov_len;
    int iovcnt = 2;
    ssize_t cnt;
    for (;;) {
//	cnt = syscall(SYS_writev, f->fd, iov, iovcnt);
	cnt = writev(f->fd, iov, iovcnt);
	if (cnt == rem) {
	    f->wend = f->buf + f->buf_size;
	    f->wpos = f->wbase = f->buf;
	    return len;
	}
	if (cnt < 0) {
	    f->wpos = f->wbase = f->wend = 0;
	    f->flags |= F_ERR;
	    return iovcnt == 2 ? 0 : len-iov[0].iov_len;
	}
	rem -= cnt;
	if (cnt > iov[0].iov_len) {
	    cnt -= iov[0].iov_len;
	    iov++; iovcnt--;
	}
	iov[0].iov_base = (char *)iov[0].iov_base + cnt;
	iov[0].iov_len -= cnt;
    }
}


size_t __stdio_read(FILE *f, unsigned char *buf, size_t len)
{
    struct iovec iov[2] = {
	{ .iov_base = buf, .iov_len = len - !!f->buf_size },
	{ .iov_base = f->buf, .iov_len = f->buf_size }
    };
    ssize_t cnt;

//    cnt = iov[0].iov_len ? syscall(SYS_readv, f->fd, iov, 2)
//	: syscall(SYS_read, f->fd, iov[1].iov_base, iov[1].iov_len);
    cnt = iov[0].iov_len ? readv(f->fd, iov, 2)
	: read( f->fd, iov[1].iov_base, iov[1].iov_len);

    if (cnt <= 0) {
	f->flags |= cnt ? F_ERR : F_EOF;
	return 0;
    }
    if (cnt <= iov[0].iov_len) return cnt;
    cnt -= iov[0].iov_len;
    f->rpos = f->buf;
    f->rend = f->buf + cnt;
    if (f->buf_size) buf[len-1] = *f->rpos++;
    return len;
}


FILE *fdopen(int fd, const char *mode)
{
    FILE *f;


    /* Check for valid initial mode character */
    if (!strchr("rwa", *mode)) {
	errno = EINVAL;
	return 0;
    }

    /* Allocate FILE+buffer or fail */
    if (!(f=my_malloc(sizeof *f + UNGET + BUFSIZ))) return 0;

    /* Zero-fill only the struct, not the buffer */
    memset(f, 0, sizeof *f);

    /* Impose mode restrictions */
    if (!strchr(mode, '+')) f->flags = (*mode == 'r') ? F_NOWR : F_NORD;

#if 0
    /* Apply close-on-exec flag */
    if (strchr(mode, 'e')) __syscall(SYS_fcntl, fd, F_SETFD, FD_CLOEXEC);

    /* Set append mode on fd if opened for append */
    if (*mode == 'a') {
	int flags = __syscall(SYS_fcntl, fd, F_GETFL);
	if (!(flags & O_APPEND))
	    __syscall(SYS_fcntl, fd, F_SETFL, flags | O_APPEND);
	f->flags |= F_APP;
    }
#endif
    f->fd = fd;
    f->buf = (unsigned char *)f + sizeof *f + UNGET;
    f->buf_size = BUFSIZ;

    /* Activate line buffered mode for terminals */
    f->lbf = EOF;
#if 0
    struct winsize wsz;
    if (!(f->flags & F_NOWR) && !__syscall(SYS_ioctl, fd, TIOCGWINSZ, &wsz))
	f->lbf = '\n';
#endif

    /* Initialize op ptrs. No problem if some are unneeded. */
    f->read = __stdio_read;
    f->write = __stdio_write;
    f->seek = __stdio_seek;
    f->close = __stdio_close;

//    printf("f = %x, f->write = %x, %x\n", (int) f, (int)f->write, (int) __stdio_write);

    /* Add new FILE to open file list */
    return __ofl_add(f);
}



int fmodeflags(const char *mode)
{
    int flags;
    if (strchr(mode, '+')) flags = O_RDWR;
    else if (*mode == 'r') flags = O_RDONLY;
    else flags = O_WRONLY;
    if (strchr(mode, 'x')) flags |= O_EXCL;
    if (strchr(mode, 'e')) flags |= O_CLOEXEC;
    if (*mode != 'r') flags |= O_CREAT;
    if (*mode == 'w') flags |= O_TRUNC;
    if (*mode == 'a') flags |= O_APPEND;
    return flags;
}


FILE *fopen(const char *restrict filename, const char *restrict mode)
{
    FILE *f;
    int fd;
    int flags;
printf("%s %s\n", filename, mode);
    /* Check for valid initial mode character */
    if (!strchr("rwa", *mode)) {
	errno = EINVAL;
	printf("fopen failed\n");
	return 0;
    }

    /* Compute the flags to pass to open() */
    flags = fmodeflags(mode);

    fd = my_open(filename, flags, 0666);
    if (fd < 0) return 0;
//    if (flags & O_CLOEXEC)
//	__syscall(SYS_fcntl, fd, F_SETFD, FD_CLOEXEC);

    f = fdopen(fd, mode);
    if (f) return f;

//    __syscall(SYS_close, fd);
    my_close(fd);

    return 0;
}

int fclose(FILE *f)
{
    int r;
    
//    FLOCK(f);
    r = fflush(f);
    r |= f->close(f);
//    FUNLOCK(f);

    /* Past this point, f is closed and any further explict access
     * to it is undefined. However, it still exists as an entry in
     * the open file list and possibly in the thread's locked files
     * list, if it was closed while explicitly locked. Functions
     * which process these lists must tolerate dead FILE objects
     * (which necessarily have inactive buffer pointers) without
     * producing any side effects. */

    if (f->flags & F_PERM) return r;

//    __unlist_locked_file(f);

    FILE **head = __ofl_lock();
    if (f->prev) f->prev->next = f->next;
    if (f->next) f->next->prev = f->prev;
    if (*head == f) *head = f->next;
//    __ofl_unlock();

    my_free(f->getln_buf);
    my_free(f);

    return r;
}


static int __toread(FILE *f)
{
    f->mode |= f->mode-1;
    if (f->wpos != f->wbase) f->write(f, 0, 0);
    f->wpos = f->wbase = f->wend = 0;
    if (f->flags & F_NORD) {
	f->flags |= F_ERR;
	return EOF;
    }
    f->rpos = f->rend = f->buf + f->buf_size;
    return (f->flags & F_EOF) ? EOF : 0;
}


int getc(FILE *f)
{
    unsigned char c;
    if (!__toread(f) && f->read(f, &c, 1)==1) return c;
    return EOF;
}


#define MIN(a,b) ((a)<(b) ? (a) : (b))

char *fgets(char *restrict s, int n, FILE *restrict f)
{
    char *p = s;
    unsigned char *z;
    size_t k;
    int c;

//    FLOCK(f);

    if (n--<=1) {
	f->mode |= f->mode-1;
//	FUNLOCK(f);
	if (n) return 0;
	*s = 0;
	return s;
    }

    while (n) {
	if (f->rpos != f->rend) {
	    z = memchr(f->rpos, '\n', f->rend - f->rpos);
	    k = z ? z - f->rpos + 1 : f->rend - f->rpos;
	    k = MIN(k, n);
	    memcpy(p, f->rpos, k);
	    f->rpos += k;
	    p += k;
	    n -= k;
	    if (z || !n) break;
	}
	if ((c = getc(f)) < 0) {
	    if (p==s || !feof(f)) s = 0;
	    break;
	}
	n--;
	if ((*p++ = c) == '\n') break;
    }
    if (s) *p = 0;

//    FUNLOCK(f);

    return s;
}
