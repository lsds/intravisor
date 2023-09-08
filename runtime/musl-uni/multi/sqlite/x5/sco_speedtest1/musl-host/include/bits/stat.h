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

