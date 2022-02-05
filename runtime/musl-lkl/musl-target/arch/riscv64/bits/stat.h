#if 1
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
struct stat {
        unsigned long st_dev;
        unsigned long st_ino;
        unsigned int st_mode;
        unsigned int st_nlink;

        unsigned int st_uid;
        unsigned int st_gid;
        unsigned long st_rdev;

        unsigned long    __pad0;
        unsigned long st_size;
        int st_blksize;
        unsigned int    __pad1;
        long st_blocks;

	struct timespec st_atim;
	struct timespec st_mtim;
	struct timespec st_ctim;
	unsigned __unused[2];
};
#endif
