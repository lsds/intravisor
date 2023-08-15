#ifndef __UK_STAT_H__
#define __UK_STAT_H__


#include <time.h>

//#define __BYTE_ORDER 1234
//struct timespec { time_t tv_sec; int :8*(sizeof(time_t)-sizeof(long))*(__BYTE_ORDER==4321); long tv_nsec; int :8*(sizeof(time_t)-sizeof(long))*(__BYTE_ORDER!=4321); };

#if 0
struct stat {
        unsigned long st_dev;
        unsigned long st_ino;
        unsigned long st_nlink;

        unsigned int st_mode;
        unsigned int st_uid;
        unsigned int st_gid;
        unsigned int    __pad0;

        unsigned long st_rdev;
        unsigned long st_size;
        long st_blksize;
        long st_blocks;

	struct timespec st_atim;
	struct timespec st_mtim;
	struct timespec st_ctim;
	unsigned __unused[2];

};

#else

typedef unsigned long dev_t;
typedef unsigned long ino_t;

typedef unsigned long __uint64_t;

typedef int blksize_t;

typedef long off_t;
typedef long blkcnt_t;

typedef unsigned int nlink_t;

typedef unsigned mode_t;

typedef unsigned gid_t;
typedef unsigned uid_t;

typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned u_int32_t;
typedef char *caddr_t;
typedef unsigned char u_char;
typedef unsigned short u_short, ushort;
typedef unsigned u_int, uint;
typedef unsigned long u_long, ulong;
typedef long long quad_t;
typedef unsigned long long u_quad_t;


typedef	u_int32_t	__fflags_t;	/* file flags */

struct stat {
	dev_t     st_dev;		/* inode's device */
	ino_t	  st_ino;		/* inode's number */
	nlink_t	  st_nlink;		/* number of hard links */

	mode_t	  st_mode;		/* inode protection mode */
	u_int16_t st_padding0;
	uid_t	  st_uid;		/* user ID of the file's owner */
	gid_t	  st_gid;		/* group ID of the file's group */
	u_int32_t st_padding1;

	dev_t     st_rdev;		/* device type */
	struct	timespec st_atim;	/* time of last access */
	struct	timespec st_mtim;	/* time of last data modification */
	struct	timespec st_ctim;	/* time of last file status change */

	struct	timespec st_birthtim;	/* time of file creation */
	off_t	  st_size;		/* file size, in bytes */
	blkcnt_t st_blocks;		/* blocks allocated for file */
	blksize_t st_blksize;		/* optimal blocksize for I/O */
	__fflags_t  st_flags;		/* user defined flags for file */
	__uint64_t st_gen;		/* file generation number */
	__uint64_t st_spare[10];

};

#endif

#define S_IFMT  0170000

#define S_IFDIR 0040000
#define S_IFCHR 0020000
#define S_IFBLK 0060000
#define S_IFREG 0100000
#define S_IFIFO 0010000
#define S_IFLNK 0120000
#define S_IFSOCK 0140000

#define S_ISDIR(mode)  (((mode) & S_IFMT) == S_IFDIR)
#define S_ISCHR(mode)  (((mode) & S_IFMT) == S_IFCHR)
#define S_ISBLK(mode)  (((mode) & S_IFMT) == S_IFBLK)
#define S_ISREG(mode)  (((mode) & S_IFMT) == S_IFREG)
#define S_ISFIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#define S_ISLNK(mode)  (((mode) & S_IFMT) == S_IFLNK)
#define S_ISSOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)


#define UTIME_NOW  0x3fffffff
#define UTIME_OMIT 0x3ffffffe


#endif