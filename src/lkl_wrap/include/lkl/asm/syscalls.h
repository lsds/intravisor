#ifndef _LKL_ASM_UAPI_LKL_SYSCALLS_H
#define _LKL_ASM_UAPI_LKL_SYSCALLS_H

#include <lkl/autoconf.h>
#include <lkl/linux/types.h>

typedef __lkl__kernel_uid32_t 	lkl_qid_t;
typedef __lkl__kernel_fd_set		lkl_fd_set;
typedef __lkl__kernel_mode_t		lkl_mode_t;
typedef unsigned short		lkl_umode_t;
typedef __lkl__u32			lkl_nlink_t;
typedef __lkl__kernel_off_t		lkl_off_t;
typedef __lkl__kernel_pid_t		lkl_pid_t;
typedef __lkl__kernel_key_t		lkl_key_t;
typedef __lkl__kernel_suseconds_t	lkl_suseconds_t;
typedef __lkl__kernel_timer_t	lkl_timer_t;
typedef __lkl__kernel_clockid_t	lkl_clockid_t;
typedef __lkl__kernel_mqd_t		lkl_mqd_t;
typedef __lkl__kernel_uid32_t	lkl_uid_t;
typedef __lkl__kernel_gid32_t	lkl_gid_t;
typedef __lkl__kernel_uid16_t        lkl_uid16_t;
typedef __lkl__kernel_gid16_t        lkl_gid16_t;
typedef unsigned long		lkl_uintptr_t;
#ifdef CONFIG_UID16
typedef __lkl__kernel_old_uid_t	lkl_old_uid_t;
typedef __lkl__kernel_old_gid_t	lkl_old_gid_t;
#endif
typedef __lkl__kernel_loff_t		lkl_loff_t;
typedef __lkl__kernel_size_t		lkl_size_t;
typedef __lkl__kernel_ssize_t	lkl_ssize_t;
typedef __lkl__kernel_time_t		lkl_time_t;
typedef __lkl__kernel_clock_t	lkl_clock_t;
typedef __lkl__u32			lkl_u32;
typedef __lkl__s32			lkl_s32;
typedef __lkl__u64			lkl_u64;
typedef __lkl__s64			lkl_s64;

#define __lkl__user

#include <lkl/asm/unistd.h>
/* Temporary undefine system calls that don't have data types defined in UAPI
 * headers */
#undef __lkl__NR_kexec_load
#undef __lkl__NR_getcpu
#undef __lkl__NR_sched_getattr
#undef __lkl__NR_sched_setattr
#undef __lkl__NR_sched_setparam
#undef __lkl__NR_sched_getparam
#undef __lkl__NR_sched_setscheduler
#undef __lkl__NR_name_to_handle_at
#undef __lkl__NR_open_by_handle_at

/* deprecated system calls */
#undef __NR_epoll_create
#undef __NR_epoll_wait
#undef __NR_access
#undef __NR_chmod
#undef __NR_chown
#undef __NR_lchown
#undef __NR_open
#undef __NR_creat
#undef __NR_readlink
#undef __NR_pipe
#undef __NR_mknod
#undef __NR_mkdir
#undef __NR_rmdir
#undef __NR_unlink
#undef __NR_symlink
#undef __NR_link
#undef __NR_rename
#undef __NR_getdents
#undef __NR_select
#undef __NR_poll
#undef __NR_dup2
#undef __NR_futimesat
#undef __NR_utimes
#undef __NR_ustat
#undef __NR_eventfd
#undef __NR_bdflush
#undef __NR_send
#undef __NR_recv

#undef __lkl__NR_umount
#define __lkl__NR_umount __lkl__NR_umount2

#ifdef LKL_CONFIG_64BIT
#define __lkl__NR_newfstat __lkl__NR3264_fstat
#define __lkl__NR_newfstatat __lkl__NR3264_fstatat
#endif

#define __lkl__NR_mmap_pgoff __lkl__NR3264_mmap

#include <lkl/linux/time.h>
#include <lkl/linux/times.h>
#include <lkl/linux/timex.h>
#include <lkl/linux/capability.h>
#define __LKL__KERNEL__ /* to pull in S_ definitions */
#include <lkl/linux/stat.h>
#undef __LKL__KERNEL__
#include <lkl/linux/errno.h>
#include <lkl/linux/fcntl.h>
#include <lkl/linux/fs.h>
#include <lkl/asm/statfs.h>
#include <lkl/asm/stat.h>
#include <lkl/linux/bpf.h>
#include <lkl/linux/msg.h>
#include <lkl/linux/resource.h>
#include <lkl/linux/sysinfo.h>
#include <lkl/linux/shm.h>
#include <lkl/linux/aio_abi.h>
#include <lkl/linux/socket.h>
#include <lkl/linux/perf_event.h>
#include <lkl/linux/sem.h>
#include <lkl/linux/futex.h>
#include <lkl/linux/poll.h>
#include <lkl/linux/mqueue.h>
#include <lkl/linux/eventpoll.h>
#include <lkl/linux/uio.h>
#include <lkl/asm/signal.h>
#include <lkl/asm/siginfo.h>
#include <lkl/linux/utime.h>
#include <lkl/asm/socket.h>
#include <lkl/linux/icmp.h>
#include <lkl/linux/ip.h>

/* Define data structures used in system calls that are not defined in UAPI
 * headers */
struct lkl_sockaddr {
	unsigned short int sa_family;
	char sa_data[14];
};

#define __LKL__UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO 1
#define __LKL__UAPI_DEF_IF_IFNAMSIZ	1
#define __LKL__UAPI_DEF_IF_NET_DEVICE_FLAGS 1
#define __LKL__UAPI_DEF_IF_IFREQ	1
#define __LKL__UAPI_DEF_IF_IFMAP	1
#include <lkl/linux/if.h>
#define __LKL__UAPI_DEF_IN_IPPROTO	1
#define __LKL__UAPI_DEF_IN_ADDR	1
#define __LKL__UAPI_DEF_IN6_ADDR	1
#define __LKL__UAPI_DEF_IP_MREQ	1
#define __LKL__UAPI_DEF_IN_PKTINFO	1
#define __LKL__UAPI_DEF_SOCKADDR_IN	1
#define __LKL__UAPI_DEF_IN_CLASS	1
#include <lkl/linux/in.h>
#include <lkl/linux/in6.h>
#include <lkl/linux/sockios.h>
#include <lkl/linux/route.h>
#include <lkl/linux/ipv6_route.h>
#include <lkl/linux/ipv6.h>
#include <lkl/linux/netlink.h>
#include <lkl/linux/neighbour.h>
#include <lkl/linux/rtnetlink.h>
#include <lkl/linux/fib_rules.h>

#include <lkl/linux/kdev_t.h>
#include <lkl/asm/irq.h>
#include <lkl/linux/virtio_blk.h>
#include <lkl/linux/virtio_net.h>
#include <lkl/linux/virtio_ring.h>
#include <lkl/linux/pkt_sched.h>

struct lkl_user_msghdr {
	void		*msg_name;	/* ptr to socket address structure */
	int		msg_namelen;		/* size of socket address structure */
	struct lkl_iovec	*msg_iov;	/* scatter/gather array */
	__lkl__kernel_size_t	msg_iovlen;		/* # elements in msg_iov */
	void		*msg_control;	/* ancillary data */
	__lkl__kernel_size_t	msg_controllen;		/* ancillary data buffer length */
	unsigned int	msg_flags;		/* flags on received message */
};

typedef __lkl__u32 lkl_key_serial_t;

struct lkl_mmsghdr {
	struct lkl_user_msghdr  msg_hdr;
	unsigned int        msg_len;
};

struct lkl_linux_dirent64 {
	lkl_u64		d_ino;
	lkl_s64		d_off;
	unsigned short	d_reclen;
	unsigned char	d_type;
	char		d_name[0];
};

struct lkl_linux_dirent {
	unsigned long	d_ino;
	unsigned long	d_off;
	unsigned short	d_reclen;
	char		d_name[1];
};

struct lkl_ustat {
	__lkl__kernel_daddr_t	f_tfree;
	__lkl__kernel_ino_t		f_tinode;
	char			f_fname[6];
	char			f_fpack[6];
};

typedef __lkl__kernel_rwf_t		lkl_rwf_t;

#define LKL_AF_UNSPEC       0
#define LKL_AF_UNIX         1
#define LKL_AF_LOCAL        1
#define LKL_AF_INET         2
#define LKL_AF_AX25         3
#define LKL_AF_IPX          4
#define LKL_AF_APPLETALK    5
#define LKL_AF_NETROM       6
#define LKL_AF_BRIDGE       7
#define LKL_AF_ATMPVC       8
#define LKL_AF_X25          9
#define LKL_AF_INET6        10
#define LKL_AF_ROSE         11
#define lkl_AF_DECnet       12
#define LKL_AF_NETBEUI      13
#define LKL_AF_SECURITY     14
#define LKL_AF_KEY          15
#define LKL_AF_NETLINK      16
#define LKL_AF_ROUTE        LKL_AF_NETLINK
#define LKL_AF_PACKET       17
#define LKL_AF_ASH          18
#define LKL_AF_ECONET       19
#define LKL_AF_ATMSVC       20
#define LKL_AF_RDS          21
#define LKL_AF_SNA          22
#define LKL_AF_IRDA         23
#define LKL_AF_PPPOX        24
#define LKL_AF_WANPIPE      25
#define LKL_AF_LLC          26
#define LKL_AF_IB           27
#define LKL_AF_MPLS         28
#define LKL_AF_CAN          29
#define LKL_AF_TIPC         30
#define LKL_AF_BLUETOOTH    31
#define LKL_AF_IUCV         32
#define LKL_AF_RXRPC        33
#define LKL_AF_ISDN         34
#define LKL_AF_PHONET       35
#define LKL_AF_IEEE802154   36
#define LKL_AF_CAIF         37
#define LKL_AF_ALG          38
#define LKL_AF_NFC          39
#define LKL_AF_VSOCK        40

#define LKL_SOCK_STREAM		1
#define LKL_SOCK_DGRAM		2
#define LKL_SOCK_RAW		3
#define LKL_SOCK_RDM		4
#define LKL_SOCK_SEQPACKET		5
#define LKL_SOCK_DCCP		6
#define LKL_SOCK_PACKET		10

#define LKL_MSG_TRUNC 0x20
#define LKL_MSG_DONTWAIT 0x40

/* avoid colision with system headers defines */
#define lkl_sa_handler lkl_sa_handler
#define lkl_st_atime lkl_st_atime
#define lkl_st_mtime lkl_st_mtime
#define lkl_st_ctime lkl_st_ctime
#define lkl_s_addr lkl_s_addr

long lkl_syscall(long no, long *params);
long lkl_sys_halt(void);

#define __LKL__MAP0(m,...)
#define __LKL__MAP1(m,t,a) m(t,a)
#define __LKL__MAP2(m,t,a,...) m(t,a), __LKL__MAP1(m,__VA_ARGS__)
#define __LKL__MAP3(m,t,a,...) m(t,a), __LKL__MAP2(m,__VA_ARGS__)
#define __LKL__MAP4(m,t,a,...) m(t,a), __LKL__MAP3(m,__VA_ARGS__)
#define __LKL__MAP5(m,t,a,...) m(t,a), __LKL__MAP4(m,__VA_ARGS__)
#define __LKL__MAP6(m,t,a,...) m(t,a), __LKL__MAP5(m,__VA_ARGS__)
#define __LKL__MAP(n,...) __LKL__MAP##n(__VA_ARGS__)

#define __LKL__SC_LONG(t, a) (long)a
#define __LKL__SC_TABLE(t, a) {sizeof(t), (long long)(a)}
#define __LKL__SC_DECL(t, a) t a

#define LKL_SYSCALL0(name)					       \
	static __inline__ long lkl_sys##name(void)			       \
	{							       \
		long params[6];					       \
		return lkl_syscall(__lkl__NR##name, params);	       \
	}

#if __LKL__BITS_PER_LONG == 32
#define LKL_SYSCALLx(x, name, ...)				       \
	static __inline__						       \
	long lkl_sys##name(__LKL__MAP(x, __LKL__SC_DECL, __VA_ARGS__))	       \
	{							       \
		struct {					       \
			unsigned int size;				       \
			long long value;			       \
		} lkl_params[x] = { __LKL__MAP(x, __LKL__SC_TABLE, __VA_ARGS__) }; \
		long params[6], i, k;				       \
		for (i = k = 0;i < x && k < 6;i++, k++) {	       \
			if (lkl_params[i].size > sizeof(long) &&       \
			    k + 1 < 6) {     	   		       \
				params[k] =			       \
					(long)(lkl_params[i].value & (-1UL));	   \
				k++;				       \
				params[k] =			       \
					(long)(lkl_params[i].value >> __LKL__BITS_PER_LONG); \
			} else {				       \
				params[k] = (long)(lkl_params[i].value); \
			}					       \
		}						       \
		return lkl_syscall(__lkl__NR##name, params);	       \
	}
#else
#define LKL_SYSCALLx(x, name, ...)				       \
       	static __inline__						       \
	long lkl_sys##name(__LKL__MAP(x, __LKL__SC_DECL, __VA_ARGS__))	       \
	{							       \
		long params[6] = { __LKL__MAP(x, __LKL__SC_LONG, __VA_ARGS__) }; \
		return lkl_syscall(__lkl__NR##name, params);	       \
	}
#endif

#define LKL_SYSCALL_DEFINE0(name, ...) LKL_SYSCALL0(name)
#define LKL_SYSCALL_DEFINE1(name, ...) LKL_SYSCALLx(1, name, __VA_ARGS__)
#define LKL_SYSCALL_DEFINE2(name, ...) LKL_SYSCALLx(2, name, __VA_ARGS__)
#define LKL_SYSCALL_DEFINE3(name, ...) LKL_SYSCALLx(3, name, __VA_ARGS__)
#define LKL_SYSCALL_DEFINE4(name, ...) LKL_SYSCALLx(4, name, __VA_ARGS__)
#define LKL_SYSCALL_DEFINE5(name, ...) LKL_SYSCALLx(5, name, __VA_ARGS__)
#define LKL_SYSCALL_DEFINE6(name, ...) LKL_SYSCALLx(6, name, __VA_ARGS__)

#if __LKL__BITS_PER_LONG == 32
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#endif

#include <lkl/asm/syscall_defs.h>

#if __LKL__BITS_PER_LONG == 32
#pragma GCC diagnostic pop
#endif

#endif
