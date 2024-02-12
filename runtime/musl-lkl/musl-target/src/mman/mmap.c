#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdint.h>
#include <limits.h>
#include "syscall.h"

#include <sys/sysinfo.h>

static void dummy(void) { }
weak_alias(dummy, __vm_wait);

#define UNIT SYSCALL_MMAP2_UNIT
#define OFF_MASK ((-0x2000ULL << (8*sizeof(syscall_arg_t)-1)) | (UNIT-1))

void *__mmap(void *start, size_t len, int prot, int flags, int fd, off_t off)
{
	long ret;
	if (off & OFF_MASK) {
		errno = EINVAL;
		return MAP_FAILED;
	}
	if (len >= PTRDIFF_MAX) {
		errno = ENOMEM;
		return MAP_FAILED;
	}
	if (flags & MAP_FIXED) {
		__vm_wait();
	}

#if 0
	lkl_printf("pre mmap: %p %lx %x %x %d %x \n", start, len, prot, flags, fd, off);

	    long page_size = sysconf(_SC_PAGE_SIZE);
    long num_processors = sysconf(_SC_NPROCESSORS_ONLN);
    long max_files = sysconf(_SC_OPEN_MAX);
    long max_path = pathconf("/", _PC_PATH_MAX);

    // Additional sysconf queries
    long clock_ticks = sysconf(_SC_CLK_TCK);
    long child_max = sysconf(_SC_CHILD_MAX);
    long arg_max = sysconf(_SC_ARG_MAX);
    long max_hostname = sysconf(_SC_HOST_NAME_MAX);


    lkl_printf("Page size: %ld bytes\n", page_size);
    lkl_printf("Number of processors: %ld\n", num_processors);
    lkl_printf("Maximum number of files that can be opened: %ld\n", max_files);
    lkl_printf("Maximum path length: %ld\n", max_path);
    
    lkl_printf("Clock ticks per second: %ld\n", clock_ticks);
    lkl_printf("Maximum number of simultaneous processes per user ID: %ld\n", child_max);
    lkl_printf("Maximum length of command-line arguments: %ld bytes\n", arg_max);
    lkl_printf("Maximum length of a hostname: %ld bytes\n", max_hostname);


struct sysinfo sys_info;

    if (sysinfo(&sys_info) != 0) {
        perror("sysinfo");
        return 1;
    }


    lkl_printf("Uptime: %ld seconds\n", sys_info.uptime);
    lkl_printf("Total RAM: %lu bytes\n", sys_info.totalram);
    lkl_printf("Free RAM: %lu bytes\n", sys_info.freeram);
    lkl_printf("Shared RAM: %lu bytes\n", sys_info.sharedram);
    lkl_printf("Total Swap: %lu bytes\n", sys_info.totalswap);
    lkl_printf("Free Swap: %lu bytes\n", sys_info.freeswap);
#endif

#ifdef SYS_mmap2
	ret = __syscall(SYS_mmap2, start, len, prot, flags, fd, off/UNIT);
#else
	ret = __syscall(SYS_mmap, start, len, prot, flags, fd, off);
#endif
//	lkl_printf("ret from mmap = %p\n", ret);
	/* Fixup incorrect EPERM from kernel. */
	if (ret == -EPERM && !start && (flags&MAP_ANON) && !(flags&MAP_FIXED))
		ret = -ENOMEM;
	return (void *)__syscall_ret(ret);
}

weak_alias(__mmap, mmap);

weak_alias(mmap, mmap64);
