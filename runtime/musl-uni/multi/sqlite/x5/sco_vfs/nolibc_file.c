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

extern int vfscore_rootfs(void);
extern void fdtable_init(void);
extern void vfscore_init(void);

extern int my_open(const char* pathname, int flags, mode_t mode);
extern ssize_t my_write(int fildes, const void *buf, size_t nbyte);
extern ssize_t my_read(int fildes, void *buf, size_t nbyte);
extern int my_close(int fildes);


void nolibos_init() {
	printf("prepare nolibos init\n");
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
	my_write(fd, "hello world", sizeof("hello world"));
	my_close(fd);
	fd = my_open("/test", 02, 0666);
	fd = my_open("/test", 02, 0666);
	fd = my_open("/test", 02, 0666);
	fd = my_open("/test", 02, 0666);
	printf("fd = %d\n", fd);
	char data[128];
	my_read(fd, data, 128);
	printf("read from file = %s\n", data);
}

