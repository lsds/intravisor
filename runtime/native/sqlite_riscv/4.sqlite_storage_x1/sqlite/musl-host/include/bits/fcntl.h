#define O_CREAT        0100
#define O_EXCL         0200
#define O_NOCTTY       0400
#define O_TRUNC       01000
#define O_APPEND      02000
#define O_NONBLOCK    04000
#define O_DSYNC      010000
#define O_SYNC     04010000
#define O_RSYNC    04010000
#define O_DIRECTORY 0200000
#define O_NOFOLLOW  0400000
#define O_CLOEXEC  02000000

#define O_ASYNC      020000
#define O_DIRECT     040000
#define O_LARGEFILE 0100000
#define O_NOATIME  01000000
#define O_PATH    010000000
#define O_TMPFILE 020200000
#define O_NDELAY O_NONBLOCK

#if 0
#define F_DUPFD  0
#define F_GETFD  1
#define F_SETFD  2
#define F_GETFL  3
#define F_SETFL  4
#define F_GETLK  5
#define F_SETLK  6
#define F_SETLKW 7
#define F_SETOWN 8
#define F_GETOWN 9
#define F_SETSIG 10
#define F_GETSIG 11
#else

#define	F_DUPFD		0		/* duplicate file descriptor */
#define	F_GETFD		1		/* get file descriptor flags */
#define	F_SETFD		2		/* set file descriptor flags */
#define	F_GETFL		3		/* get file status flags */
#define	F_SETFL		4		/* set file status flags */
#define	F_GETOWN	5		/* get SIGIO/SIGURG proc/pgrp */
#define	F_SETOWN	6		/* set SIGIO/SIGURG proc/pgrp */
#define	F_OGETLK	7		/* get record locking information */
#define	F_OSETLK	8		/* set record locking information */
#define	F_OSETLKW	9		/* F_SETLK; wait if blocked */
#define	F_DUP2FD	10		/* duplicate file descriptor to arg */
#define	F_GETLK		11		/* get record locking information */
#define	F_SETLK		12		/* set record locking information */
#define	F_SETLKW	13		/* F_SETLK; wait if blocked */
#define	F_SETLK_REMOTE	14		/* debugging support for remote locks */
#define	F_READAHEAD	15		/* read ahead */
#define	F_RDAHEAD	16		/* Darwin compatible read ahead */
#define	F_DUPFD_CLOEXEC	17		/* Like F_DUPFD, but FD_CLOEXEC is set */
#define	F_DUP2FD_CLOEXEC 18		/* Like F_DUP2FD, but FD_CLOEXEC is set */
#define	F_ADD_SEALS	19
#define	F_GET_SEALS	20
#define	F_ISUNIONSTACK	21		/* Kludge for libc, don't use it. */
#define	F_KINFO		22		/* Return kinfo_file for this fd */

#endif


#define F_SETOWN_EX 15
#define F_GETOWN_EX 16

#define F_GETOWNER_UIDS 17
