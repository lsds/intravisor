#define _GNU_SOURCE
#include <dlfcn.h>
#include <sched.h>

#ifndef SIM
#if !__has_feature(capabilities)
#error "This code requires a CHERI-aware compiler"
#endif

#include <cheri/cheri.h>
#include <cheri/cheric.h>
#include <sys/sysctl.h>

#endif

#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <string.h>
#include <sys/uio.h>

#include <signal.h>
#include <stdio.h>
#include <load_elf.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <sys/auxv.h>

#include <sys/ioctl.h>
#include <net/if.h>

#ifdef __linux__
#include <linux/if.h>
#include <linux/if_tun.h>
#else
#include <sys/cpuset.h>
#endif



#include <errno.h>
#include <lkl/asm/host_ops.h>
#include "lkl_wrap/lkl_host.h"

#include <stdbool.h>

#include "intravisor.h"

#define AT_NULL		0
#define AT_IGNORE	1
#define AT_EXECFD	2
#define AT_PHDR		3
#define AT_PHENT	4
#define AT_PHNUM	5
#define AT_PAGESZ	6
#define AT_BASE		7
#define AT_FLAGS	8
#define AT_ENTRY	9
#define AT_NOTELF	10
#define AT_UID		11
#define AT_EUID		12
#define AT_GID		13
#define AT_EGID		14
#define AT_CLKTCK	17
#define AT_PLATFORM	15
#define AT_HWCAP	16
#define AT_FPUCW	18
#define AT_DCACHEBSIZE	19
#define AT_ICACHEBSIZE	20
#define AT_UCACHEBSIZE	21
#define AT_IGNOREPPC	22
#define	AT_SECURE	23
#define AT_BASE_PLATFORM 24
#define AT_RANDOM	25
#define AT_HWCAP2	26
#define AT_EXECFN	31


#define LKL_DEV_BLK_STATUS_OK		0
#define LKL_DEV_BLK_STATUS_IOERR	1
#define LKL_DEV_BLK_STATUS_UNSUP	2


//////////////////
#define	CHERI_CAP_PRINT(cap) do {					\
  printf("tag %ju s %ju perms %08jx type %016jx\n",		\
      (uintmax_t)cheri_gettag(cap),				\
      (uintmax_t)cheri_getsealed(cap),				\
      (uintmax_t)cheri_getperm(cap),				\
      (uintmax_t)cheri_gettype(cap));				\
  printf("\tbase %016jx length %016jx ofset %016jx\n",				\
      (uintmax_t)cheri_getbase(cap),				\
      (uintmax_t)cheri_getlen(cap),				\
      (uintmax_t)cheri_getoffset(cap));				\
} while (0)


//#include <xxhash.h>

//////////////////
#if 1
struct lkl_disk {
	void *dev;
	union {
		int fd;
		void *handle;
	};
	struct lkl_dev_blk_ops *ops;
};


/**
 * struct lkl_dev_blk_ops - block device host operations
 */
struct lkl_dev_blk_ops {
	/**
	 * @get_capacity: returns the disk capacity in bytes
	 *
	 * @disk - the disk for which the capacity is requested;
	 * @res - pointer to receive the capacity, in bytes;
	 * @returns - 0 in case of success, negative value in case of error
	 */
	int (*get_capacity)(unsigned long cof2mon, struct lkl_disk disk, unsigned long long *res);
	/**
	 * @request: issue a block request
	 *
	 * @disk - the disk the request is issued to;
	 * @req - a request described by &struct lkl_blk_req
	 */
	int (*request)(unsigned long cof2mon, struct lkl_disk disk, struct lkl_blk_req *req);
};

#endif

#define AUX_CNT 32
#define DYN_CNT 32




#define MAX_CVMS	10
#if 0
#define MAX_THREADS	23
#define STACK_SIZE (0x200000) //2M
#else
#if 0
#define MAX_THREADS	31
#define STACK_SIZE (0x100000) //1M
#else
#define MAX_THREADS	63
#define STACK_SIZE (0x80000) //512K
#endif
#endif


struct c_thread {
	void *func;
//why is it a part of c_thread but not s_box?
	char *cb_in;
	char *cb_out;
	void *stack;
	void *arg;
	unsigned long stack_size;
	int id;

	void *c_tp;
	void *m_tp;

	int argc;
	char **argv;

	pthread_t tid;
	pthread_attr_t tattr;

	struct s_box *sbox;

	struct stream_caps_store *cs;

};

struct cs_lock {
	char predicate;
	pthread_cond_t cond;
	pthread_mutex_t lock;
	char armed;
};


struct box_caps_s {
	size_t sealcap_size;
	void * __capability sealcap;

	void * __capability sealed_codecap;
	void * __capability sealed_datacap;
	void * __capability dcap;
	void * __capability sealed_codecapt;
	void * __capability sealed_codecapt2;
	void * __capability sealed_datacapt;
	void * __capability sealed_ret_from_mon;
};


struct s_box {
//
	void *base;			//we map binary here
	void *top;			//end of binary
	unsigned long box_size;		//base + box_size + stack = top
	void *stack;			//beginning of stacks
	unsigned long stack_size;	//stack size
// threads
	struct c_thread threads[MAX_THREADS];
	pthread_mutex_t ct_lock;
#ifdef __linux__
	cpu_set_t cpuset;
#else
	cpuset_t cpuset;
#endif
	struct box_caps_s box_caps;

// compartment borders, they might be not the same as borders above
	unsigned long cmp_begin;
	unsigned long cmp_end;
// 
	void *entry;
	unsigned long ret_from_mon;
//  I/O
	struct lkl_disk lkl_disk;
	char disk_image[100];		//path to the disk
// OUTPUT
	int fd;
//	
	char pure;
//
	struct s_box *inner;
	struct s_box *outer;
};


struct cmp_s {
	void *base;				/* base addr */
	unsigned long size;		/* size */
	unsigned long begin;	/* cmp_begin */
	unsigned long end;		/* cmp_end  */
};

extern struct s_box	cvms[MAX_CVMS];

extern struct lkl_host_operations lkl_host_ops;
extern struct lkl_dev_blk_ops lkl_dev_blk_ops;
extern struct lkl_dev_net_ops fd_net_ops;


//default config
extern int timers;
extern int debug_calls;
//

void *my_memcpy(void  *dest, void *src, size_t n);
#ifndef SIM
void *capcpy(void *dest, void *__capability src, size_t n);
#else
void *capcpy(void *dest, void *src, size_t n);
#endif

///////////////////////////

extern pthread_mutex_t print_lock;

///// UTILS 

unsigned long mon_to_comp(unsigned long addr, struct s_box *sbox);
unsigned long comp_to_mon(unsigned long addr, struct s_box *sbox);
unsigned long comp_to_mon_old(unsigned long addr, struct s_box *sbox);
void st_cap(void *loc, void *__capability);

int create_console(int);

#ifndef SIM
void * __capability codecap_create(void *sandbox_base, void *sandbox_end);
void * __capability pure_codecap_create(void *sandbox_base, void *sandbox_end);
void * __capability datacap_create(void *sandbox_base, void *sandbox_end);
#endif

static __inline__ void * getSP(void) {
    register void * sp asm("sp");
    asm ("" : "=r"(sp));
    return sp;
}

static __inline__ void * getTP(void) {
    register void * tp asm("tp");
    asm ("" : "=r"(tp));
    return tp;
}

struct cap_relocs_s {
	unsigned long dst;
	unsigned long addr;
	unsigned long unknown;
	unsigned long len;
	unsigned long perms;
};


