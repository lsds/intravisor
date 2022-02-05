#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

#include "loader.h"


//	void (*panic)(void);
int wrap_panic() {
	__asm__ __volatile__ ("ebreak");
}
int wrap_print(char *ptr, int size) {
	int tmp = 1;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) ptr;
	register long a1 __asm__("a1") = (long) size;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return a0; 
}


unsigned long wrap_sem_alloc(int count) {
	int tmp = 3;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) count;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return a0; 
}

unsigned long wrap_sem_free(void *sem) {
	int tmp = 4;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) sem;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return a0; 
}

unsigned long wrap_sem_up(void *sem) {
	int tmp = 5;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) sem;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return a0; 
}

unsigned long wrap_sem_down(void *sem) {
	int tmp = 6;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) sem;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return a0; 
}


unsigned long wrap_mutex_alloc(int count) {
	int tmp = 7;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) count;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return a0; 
}

unsigned long wrap_mutex_free(void *mutex) {
	int tmp = 8;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) mutex;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return a0; 
}

unsigned long wrap_mutex_lock(void *mutex) {
	int tmp = 9;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) mutex;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return a0; 
}

unsigned long wrap_mutex_unlock(void *mutex) {
	int tmp = 10;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) mutex;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return a0; 
}


unsigned long wrap_thread_create(void *f, void *arg) {
	int tmp = 11;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) f;
	register long a1 __asm__("a1") = (long) arg;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return a0; 
}

//12	void (*thread_detach)(void);
void wrap_thread_detach() {
	int tmp = 12;
	register long a0 __asm__("a0");
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5) : "memory" );
}

//13	void (*thread_exit)(void);
void wrap_thread_exit() {
	int tmp = 13;
	register long a0 __asm__("a0");
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5) : "memory" );
}

//14	int (*thread_join)(lkl_thread_t tid);
int wrap_thread_join(long tid) {
	int tmp = 14;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) tid;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return (int) a0; 
}



unsigned long wrap_thread_self() {
	int tmp = 15;
	register long a0 __asm__("a0");
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5) : "memory" );
	return a0; 
}

//16	int (*thread_equal)(lkl_thread_t a, lkl_thread_t b);
int wrap_thread_equal(long a, long b) {
	int tmp = 16;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) a;
	register long a1 __asm__("a1") = (long) b;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return (int) a0; 
}


//17	struct lkl_tls_key *(*tls_alloc)(void (*destructor)(void *));
unsigned long wrap_tls_alloc(void *dis) {
	int tmp = 17;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) dis;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return a0; 
}

//18	void (*tls_free)(struct lkl_tls_key *key);
void wrap_tls_free(void *key) {
	int tmp = 18;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) key;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
}

//19	int (*tls_set)(struct lkl_tls_key *key, void *data);
int wrap_tls_set(void *key, void *value) {
	int tmp = 19;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) key;
	register long a1 __asm__("a1") = (long) value;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return (int)a0; 
}

//20	void *(*tls_get)(struct lkl_tls_key *key);
unsigned long wrap_tls_get(void *key) {
	int tmp = 20;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) key;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return a0; 
}


//25	unsigned long long (*time)(void);
long wrap_time() {
	int tmp = 25;
	register long a0 __asm__("a0");
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5) : "memory" );
	return a0; 
}

struct s_timer {
	int id;
	void *f;
	void *arg;
} c_timers[50];

int c_max_timer = 0;

static __inline__ void * getSP(void) {
    register void * sp asm("sp");
    asm ("" : "=r"(sp));
    return sp;
}

one_shot_thread(void *arg) {
	struct s_timer *t = (struct s_timer *) arg;
	int (*f_ptr)(void *);
	f_ptr = (int (*)(void *)) t->f;
//	lkl_printf("one shot timer %d: SP=%p, %p %p\n",  t->id,getSP(), t->f, t->arg);
	(f_ptr)(t->arg);

	wrap_thread_exit();
}

//26	void* (*timer_alloc)(void (*fn)(void *), void *arg);
unsigned long wrap_timer_alloc(void *f, void *arg) {
	int tid = c_max_timer++;
	c_timers[tid].f = f;
	c_timers[tid].arg = arg;
	c_timers[tid].id = tid;

	lkl_printf("TIMER[%d]: %p %p\n", tid, f, arg);

	if(tid>=50) {
	printf("DOLG\n");while(1);
	}

	int tmp = 26;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) one_shot_thread;
	register long a1 __asm__("a1") = (long) &c_timers[tid];
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return a0;
}


//27	int (*timer_set_oneshot)(void *timer, unsigned long delta);
int wrap_timer_set_oneshot(void *timer, long arg) {
	int tmp = 27;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) timer;
	register long a1 __asm__("a1") = (long) arg;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return (int) a0; 
}

//28	void (*timer_free)(void *timer);
void wrap_timer_free(void *timer) {
#if 0
	int tmp = 28;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) timer;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
#else
	lkl_printf("WRAP_TIMER_FREE NOT IMPLEMENTED\n");
	while(1);
#endif
}

//	void (*jmp_buf_set)(struct lkl_jmp_buf *jmpb, void (*f)(void)); //32
void wrap_jmp_buf_set(void *jmpb, void *f) {
	lkl_printf("JUMP BUF SET NOT IMPLEMENTED, %p %p\n", jmpb, f);
	while(1);
}

//	void (*jmp_buf_longjmp)(struct lkl_jmp_buf *jmpb, int val); //33
void wrap_jmp_buf_longjmp(void *jmpb, int val) {
	lkl_printf("JUMP BUF LONGJMP NOT IMPLEMENTED, %p %x\n", jmpb, val);
	while(1);
}

void *wrap_mem_alloc(int size) {
	return malloc(size);
//	lkl_printf("MEM ALLOC SHOULD NOT BE CALLED\n");
//	while(1);
}

void wrap_mem_free(void *ptr) {
	free(ptr);
//	lkl_printf("MEM FREE SHOULD NOT BE CALLED\n");
//	while(1);
}


///
//static int blk_request(struct lkl_disk disk, struct lkl_blk_req *req)
int wrap_request(void *disk, void *req) {
	int tmp = 100;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) disk;
	register long a1 __asm__("a1") = (long) req;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return (int) a0;
}

//static int fd_get_capacity(struct lkl_disk disk, unsigned long long *res)
int wrap_get_capacity(void *disk, void *res) {
	int tmp = 101;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) disk;
	register long a1 __asm__("a1") = (long) res;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return (int) a0;
}
/// network 

int wrap_tx(struct lkl_netdev *nd, struct iovec *iov, int cnt) {
	int tmp = 200;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) nd;
	register long a1 __asm__("a1") = (long) iov;
	register long a2 __asm__("a2") = (long) cnt;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );
	return (int) a0;
}

int wrap_rx(struct lkl_netdev *nd, struct iovec *iov, int cnt) {
	int tmp = 201;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) nd;
	register long a1 __asm__("a1") = (long) iov;
	register long a2 __asm__("a2") = (long) cnt;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );
	return (int) a0;
}


int wrap_poll(struct lkl_netdev *nd) {
	int tmp = 202;
	register long a0 __asm__("a0") = nd;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return (int) a0; 
}

void wrap_poll_hup(struct lkl_netdev *nd) {
	int tmp = 203;
	register long a0 __asm__("a0") = nd;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return;
}

void wrap_free(struct lkl_netdev *nd) {
	int tmp = 204;
	register long a0 __asm__("a0") = nd;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return; 
}


/// host calls. they must not exist 
//int open(const char *pathname, int flags);
int wrap_host_open(const char *pathname, int flags) {
	int tmp = 300;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) pathname;
	register long a1 __asm__("a1") = (long) flags;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return (int) a0;
}

//int pipe(int pipefd[2]);
int wrap_host_pipe(int *pipefd) {
	int tmp = 301;
	register long a0 __asm__("a0") = (long) pipefd;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return (int) a0; 

}
//int fcntl(int fd, int cmd, ... /* arg */ );
int wrap_host_fcntl(int fd, int a, int b) {
	int tmp = 302;
	register long a0 __asm__("a0") = (long) fd;
	register long a1 __asm__("a1") = (long) a;
	register long a2 __asm__("a2") = (long) b;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );
	return (int) a0; 
}

///////////
//int fcntl(int fd, int cmd, ... /* arg */ );
int wrap_host_open_portal(int id, long a) {
	int tmp = 400;
	register long a0 __asm__("a0") = (long) id;
	register long a1 __asm__("a1") = (long) a;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return (int) a0; 
}

int wrap_host_get_state(int id, int st) {
	int tmp = 401;
	register long a0 __asm__("a0") = (long) id;
	register long a1 __asm__("a1") = (long) st;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return (int) a0; 
}

int wrap_host_set_state(int id, int st) {
	int tmp = 402;
	register long a0 __asm__("a0") = (long) id;
	register long a1 __asm__("a1") = (long) st;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return (int) a0; 
}

//extern ssize_t wrap_host_make_call(void *, void *);
int wrap_host_make_call(void *f, void *arg) {
	int tmp = 403;
	register long a0 __asm__("a0") = (long) f;
	register long a1 __asm__("a1") = (long) arg;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return (int) a0; 
}

//extern int wrap_host_reg_cap(void *ptr, long size, void *location) {
int wrap_host_reg_cap(void *ptr, long size, void *location) {
	int tmp = 404;
	register long a0 __asm__("a0") = (long) ptr;
	register long a1 __asm__("a1") = (long) size;
	register long a2 __asm__("a2") = (long) location;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );
	return (int) a0; 
}

int wrap_host_cap_adv(void *ptr, long size, char *key) {
	int tmp = 405;
	register long a0 __asm__("a0") = (long) ptr;
	register long a1 __asm__("a1") = (long) size;
	register long a2 __asm__("a2") = (long) key;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );
	return (int) a0; 
}

int wrap_host_cap_prb(char *key, void *location, long *size) {
	int tmp = 406;
	register long a0 __asm__("a0") = (long) key;
	register long a1 __asm__("a1") = (long) location;
	register long a2 __asm__("a2") = (long) size;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );
	return (int) a0; 
}

int wrap_host_cap_wait(int id) {
	int tmp = 407;
	register long a0 __asm__("a0") = (long) id;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return (int) a0; 
}

int wrap_host_cap_wake(int id) {
	int tmp = 408;
	register long a0 __asm__("a0") = (long) id;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return (int) a0; 
}

//extern int wrap_host_cap_stream_adv(void *func, void *device, char *key);
int wrap_host_cap_stream_adv(void *ptr, void *dev, char *key) {
	int tmp = 409;
	register long a0 __asm__("a0") = (long) ptr;
	register long a1 __asm__("a1") = (long) dev;
	register long a2 __asm__("a2") = (long) key;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );
	return (int) a0; 
}

int wrap_host_cap_stream_prb(char *key) {
	int tmp = 410;
	register long a0 __asm__("a0") = (long) key;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return (int) a0; 
}

//extern int wrap_host_make_cap_call(int id, void *buf, int len);
int wrap_host_make_cap_call(int id, void *buf, int len) {
	int tmp = 411;
	register long a0 __asm__("a0") = (long) id;
	register long a1 __asm__("a1") = (long) buf;
	register long a2 __asm__("a2") = (long) len;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );

	return (int) a0; 
}

//extern wrap_host_finish_cap_call(int id, void *buff);
int wrap_host_finish_cap_call(int id, void *buf) {
	int tmp = 412;
	register long a0 __asm__("a0") = (long) id;
	register long a1 __asm__("a1") = (long) buf;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );

	return (int) a0; 
}

//extern wrap_host_fetch_cap_call(int id, void *cap, void *size);
int wrap_host_fetch_cap_call(int id, void *cap, void *size) {
	int tmp = 413;

	register long a0 __asm__("a0") = (long) id;
	register long a1 __asm__("a1") = (long) cap;
	register long a2 __asm__("a2") = (long) size;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );

	return (int) a0; 
}

/* if you change anything inside this function, you should check what happend with $sp:
000000000046c7d4 <wrap_ocall_exit>:
  46c7d4: 79 71         addi    sp, sp, -48
  46c7d6: 06 f4         sd      ra, 40(sp)
  46c7d8: 22 f0         sd      s0, 32(sp)
  46c7da: 00 18         addi    s0, sp, 48

48 should be manually add inside o_call handler in Monitor 
*/
void wrap_ocall_exit(long ret) {
	int tmp = 414;
	register long a0 __asm__("a0") = (long) ret;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal o_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
}



#define USE_HOST_NET

#ifdef USE_HOST_NET
int wrap_socket(int domain, int type, int protocol) {
	int tmp = 500;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) domain;
	register long a1 __asm__("a1") = (long) type;
	register long a2 __asm__("a2") = (long) protocol;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );
	return (int) a0;
}

int wrap_setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen) {
	int tmp = 501;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) fd;
	register long a1 __asm__("a1") = (long) level;
	register long a2 __asm__("a2") = (long) optname;
	register long a3 __asm__("a3") = (long) optval;
	register long a4 __asm__("a4") = (long) optlen;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4): "memory" );
	return (int) a0;
}

int wrap_ioctl(int fd, unsigned long request, unsigned long cont) {
	int tmp = 502;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) fd;
	register long a1 __asm__("a1") = (long) request;
	register long a2 __asm__("a2") = (long) cont;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );
	return (int) a0;
}

int wrap_accept4(int fd, struct sockaddr *restrict addr, socklen_t *restrict len, int flg) {
	int tmp = 503;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) fd;
	register long a1 __asm__("a1") = (long) addr;
	register long a2 __asm__("a2") = (long) len;
	register long a3 __asm__("a3") = (long) flg;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2), "r"(a3): "memory" );
	return (int) a0;
}

//int listen(int fd, int backlog)
int wrap_listen(int fd, int backlog) {
	int tmp = 504;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) fd;
	register long a1 __asm__("a1") = (long) backlog;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return (int) a0;
}

//int accept(int fd, struct sockaddr *restrict addr, socklen_t *restrict len)
int wrap_accept(int fd, struct sockaddr *restrict addr, socklen_t *restrict len) {
	int tmp = 505;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) fd;
	register long a1 __asm__("a1") = (long) addr;
	register long a2 __asm__("a2") = (long) len;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );
	return (int) a0;
}

//int bind(int fd, const struct sockaddr *addr, socklen_t len)
int wrap_bind(int fd, const struct sockaddr *addr, socklen_t len) {
	int tmp = 506;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) fd;
	register long a1 __asm__("a1") = (long) addr;
	register long a2 __asm__("a2") = (long) len;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );
	return (int) a0;
}

//ssize_t write(int fd, const void *buf, size_t count)
ssize_t wrap_write(int fd, const void *buf, size_t count) {
	int tmp = 507;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) fd;
	register long a1 __asm__("a1") = (long) buf;
	register long a2 __asm__("a2") = (long) count;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );
	return (ssize_t) a0;
}

//ssize_t read(int fd, const void *buf, size_t count)
ssize_t wrap_read(int fd, const void *buf, size_t count) {
	int tmp = 508;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) fd;
	register long a1 __asm__("a1") = (long) buf;
	register long a2 __asm__("a2") = (long) count;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );
	return (ssize_t) a0;
}

//ssize_t send(int fd, const void *buf, size_t len, int flags)
ssize_t wrap_send(int fd, const void *buf, size_t len, int flags) {
	int tmp = 509;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) fd;
	register long a1 __asm__("a1") = (long) buf;
	register long a2 __asm__("a2") = (long) len;
	register long a3 __asm__("a3") = (long) flags;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2), "r"(a3): "memory" );
	return (ssize_t) a0;
}

//ssize_t recv(int fd, void *buf, size_t len, int flags)
ssize_t wrap_recv(int fd, void *buf, size_t len, int flags) {
	int tmp = 510;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) fd;
	register long a1 __asm__("a1") = (long) buf;
	register long a2 __asm__("a2") = (long) len;
	register long a3 __asm__("a3") = (long) flags;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2), "r"(a3): "memory" );
	return (ssize_t) a0;
}

//int close(int fd)
int wrap_close(int fd) {
	int tmp = 511;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) fd;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return (int) a0;
}

//int socketpair(int domain, int type, int protocol, int fd[2])
int wrap_socketpair(int domain, int type, int protocol, int fd[2]) {
	int tmp = 512;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) domain;
	register long a1 __asm__("a1") = (long) type;
	register long a2 __asm__("a2") = (long) protocol;
	register long a3 __asm__("a3") = (long) fd;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2), "r"(a3): "memory" );
	return (int) a0;
}


//int epoll_create(int size)
int wrap_epoll_create(int size) {
	int tmp = 513;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) size;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return (int) a0;
}

//int epoll_create1(int flags)
int wrap_epoll_create1(int flags) {
	int tmp = 514;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) flags;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return (int) a0;
}


//int eventfd(unsigned int count, int flags)
int wrap_eventfd(unsigned int count, int flags) {
	int tmp = 515;
	register long a0 __asm__("a0") = (long) count;
	register long a1 __asm__("a1") = (long) flags;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return (int) a0; 
}

//int epoll_ctl(int fd, int op, int fd2, struct epoll_event *ev)
int wrap_epoll_ctl(int fd, int op, int fd2, struct epoll_event *ev) {
	int tmp = 516;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) fd;
	register long a1 __asm__("a1") = (long) op;
	register long a2 __asm__("a2") = (long) fd2;
	register long a3 __asm__("a3") = (long) ev;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2), "r"(a3): "memory" );
	return (int) a0;
}

//int epoll_wait(int fd, struct epoll_event *ev, int cnt, int to)
int wrap_epoll_wait(int fd, struct epoll_event *ev, int cnt, int to) {
	int tmp = 517;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) fd;
	register long a1 __asm__("a1") = (long) ev;
	register long a2 __asm__("a2") = (long) cnt;
	register long a3 __asm__("a3") = (long) to;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2), "r"(a3): "memory" );
	return (int) a0;
}

//int epoll_pwait(int fd, struct epoll_event *ev, int cnt, int to, const sigset_t *sigs)
int wrap_epoll_pwait(int fd, struct epoll_event *ev, int cnt, int to, const sigset_t *sigs) {
	int tmp = 518;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) fd;
	register long a1 __asm__("a1") = (long) ev;
	register long a2 __asm__("a2") = (long) cnt;
	register long a3 __asm__("a3") = (long) to;
	register long a4 __asm__("a4") = (long) sigs;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4): "memory" );
	return (int) a0;
}

//ssize_t recvfrom(int fd, void *restrict buf, size_t len, int flags, struct sockaddr *restrict addr, socklen_t *restrict alen)
ssize_t wrap_recvfrom(int fd, void *restrict buf, size_t len, int flags, struct sockaddr *restrict addr, socklen_t *restrict alen) {
	int tmp = 519;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) fd;
	register long a1 __asm__("a1") = (long) buf;
	register long a2 __asm__("a2") = (long) len;
	register long a3 __asm__("a3") = (long) flags;
	register long a4 __asm__("a4") = (long) addr;
	register long a5 __asm__("a5") = (long) alen;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r" (a5): "memory" );
	return (ssize_t) a0;
}

//ssize_t writev(int fd, const struct iovec *iov, int count)
ssize_t wrap_writev(int fd, const struct iovec *iov, int count) {
	int tmp = 520;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) fd;
	register long a1 __asm__("a1") = (long) iov;
	register long a2 __asm__("a2") = (long) count;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );

	return (size_t) a0;
}

#endif
////////

/* 

lkl_start_kernel receives lkl_host_operations table as an argument. howoever, internally, some code directly calls
functions from its own lkl_host_ops. some callbacks in these tables should be the same, in general, there should be only one table. 

*/
extern struct lkl_host_operations lkl_host_ops;
extern struct lkl_dev_blk_ops lkl_dev_blk_ops;

struct lkl_host_operations lkl_io_in;
struct lkl_disk disk_io_in;


void init_internal_lkl() {
	struct lkl_host_operations *tmp = (struct lkl_host_operations *) &lkl_io_in;
	struct lkl_disk *tmp_disk = (struct lkl_disk *) &disk_io_in;
	tmp_disk->ops = &lkl_dev_blk_ops;

	tmp->panic = lkl_host_ops.panic;
//////////////// 

	lkl_host_ops.print = wrap_print; //1
	tmp->print = wrap_print; //1

//	void (*panic)(void);
	lkl_host_ops.panic = wrap_panic; //1
	tmp->panic = wrap_panic; //1

//	lkl_host_ops.sem_alloc = wrap_sem_alloc; //3
	tmp->sem_alloc = wrap_sem_alloc;
//	void (*sem_free)(struct lkl_sem *sem); //4
	tmp->sem_free = wrap_sem_free;
//	void (*sem_up)(struct lkl_sem *sem); //5
	tmp->sem_up = wrap_sem_up;
//	void (*sem_down)(struct lkl_sem *sem); //6
	tmp->sem_down = wrap_sem_down;
//	struct lkl_mutex *(*mutex_alloc)(int recursive); //7
	tmp->mutex_alloc = wrap_mutex_alloc;
//	void (*mutex_free)(struct lkl_mutex *mutex); //8
	tmp->mutex_free = wrap_mutex_free;
//	void (*mutex_lock)(struct lkl_mutex *mutex); //9
	tmp->mutex_lock = wrap_mutex_lock;
//	void (*mutex_unlock)(struct lkl_mutex *mutex); //10
	tmp->mutex_unlock = wrap_mutex_unlock;


//	lkl_thread_t (*thread_create)(void (*f)(void *), void *arg); 
	lkl_host_ops.thread_create = wrap_thread_create; //11
	tmp->thread_create = wrap_thread_create; //11

//	void (*thread_detach)(void);
	tmp->thread_detach = wrap_thread_detach; //12

//	void (*thread_exit)(void);
	tmp->thread_exit = wrap_thread_exit; //13

//	int (*thread_join)(lkl_thread_t tid);
	tmp->thread_join = wrap_thread_join; //14

//	lkl_thread_t (*thread_self)(void); //15
	tmp->thread_self = wrap_thread_self;

//	int (*thread_equal)(lkl_thread_t a, lkl_thread_t b);
	tmp->thread_equal = wrap_thread_equal; //16

//	struct lkl_tls_key *(*tls_alloc)(void (*destructor)(void *));
	tmp->tls_alloc = wrap_tls_alloc; //17
//	void (*tls_free)(struct lkl_tls_key *key);
	tmp->tls_free = wrap_tls_free; //18

//	int (*tls_set)(struct lkl_tls_key *key, void *data);
	tmp->tls_set = wrap_tls_set; //19
//	void *(*tls_get)(struct lkl_tls_key *key);
	tmp->tls_get = wrap_tls_get; //20

//	unsigned long long (*time)(void); //25
	tmp->time = wrap_time;
//	void* (*timer_alloc)(void (*fn)(void *), void *arg);
	tmp->timer_alloc = wrap_timer_alloc; //26
//	int (*timer_set_oneshot)(void *timer, unsigned long delta);
	tmp->timer_set_oneshot = wrap_timer_set_oneshot; //27
//	void (*timer_free)(void *timer);
	tmp->timer_free = wrap_timer_free; //28

//	void (*jmp_buf_set)(struct lkl_jmp_buf *jmpb, void (*f)(void)); //32
	tmp->jmp_buf_set = lkl_host_ops.jmp_buf_set;
//	void (*jmp_buf_longjmp)(struct lkl_jmp_buf *jmpb, int val); //33
	tmp->jmp_buf_longjmp = lkl_host_ops.jmp_buf_longjmp;
///////////////
	lkl_dev_blk_ops.get_capacity = wrap_get_capacity;
	lkl_dev_blk_ops.request = wrap_request;
///////////////

	tmp->mem_alloc = lkl_host_ops.mem_alloc;
	tmp->mem_free = lkl_host_ops.mem_free;
//
	tmp->ioremap = lkl_host_ops.ioremap;
	tmp->iomem_access = lkl_host_ops.iomem_access;
	tmp->virtio_devices = lkl_host_ops.virtio_devices;
	tmp->gettid = lkl_host_ops.gettid;

	lkl_printf("STARTING LKL, lkl_io_in = %p, disk_io = %p\n", &lkl_io_in, &disk_io_in);
	lkl_start_kernel((struct lkl_host_operations *)&lkl_io_in, "mem=30M");
	lkl_printf("------ LKL INIT DONE, starting mount  ------- \n");

	struct s_mount m_args;
	m_args.disk_io = &disk_io_in;

extern void *mount_thread(void *arg);
#if 0
	pthread_t mount;
	int ret = pthread_create(&mount, NULL, mount_thread, &m_args);

	if(ret != 0) {
		printf("Cannot create moun thread, die. ret = %d %s\n", ret, strerror(ret));
		while(1);
	}


	pthread_join(mount);
#else
	mount_thread(&m_args);
#endif
	lkl_printf("MOUNT DONE\n");

}



extern struct lkl_dev_net_ops fd_net_ops;


struct lkl_netdev *carrie_register_netdev_fd(unsigned long base, int fd_rx, int fd_tx)
{
	fd_net_ops.tx = wrap_tx;
	fd_net_ops.rx = wrap_rx;
	fd_net_ops.poll = wrap_poll;
	fd_net_ops.poll_hup = wrap_poll_hup;
	fd_net_ops.free = wrap_free;

	struct lkl_netdev_fd *nd;

	nd = malloc(sizeof(*nd));
	if (!nd) {
		fprintf(stderr, "fdnet: failed to allocate memory\n");
		/* TODO: propagate the error state, maybe use errno for that? */
		return NULL;
	}

	memset(nd, 0, sizeof(*nd));

	nd->cmp_to_mon = base;

#if 0
	nd->fd_rx = fd_rx;
	nd->fd_tx = fd_tx;
#else
	nd->fd_rx = nd->fd_tx = wrap_host_open("/dev/tap0", O_RDWR|O_NONBLOCK);
#endif
	if (wrap_host_pipe(nd->pipe) < 0) {
		lkl_printf("wrap_host_pipe failed\n");
		while(1);
	}

	if (wrap_host_fcntl(nd->pipe[0], F_SETFL, O_NONBLOCK) < 0) {
		lkl_printf("wrap_host_fnctl failed");
		while(1);
	}

	nd->dev.ops = &fd_net_ops;
	return &nd->dev;
}


int lkl_prestart_net(unsigned long base) {
    struct lkl_netdev *netdev = carrie_register_netdev_fd(base, 0, 0);
    if (netdev == NULL) {
        lkl_printf("Error: unable to register netdev\n");
		while(1);
    }
    char mac[6] = { 0xCA, 0xFE, 0x00, 0x00, 0x00, 0x01 };
    struct lkl_netdev_args netdev_args = {
        .mac = mac,
        .offload= 0,
    };

#define BIT(x) (1 << (x))
#if 0
        netdev->has_vnet_hdr = 1;
        // Host and guest can handle partial checksums
        netdev_args.offload = BIT(LKL_VIRTIO_NET_F_CSUM) | BIT(LKL_VIRTIO_NET_F_GUEST_CSUM);
        // Host and guest can handle TSOv4
        netdev_args.offload |= BIT(LKL_VIRTIO_NET_F_HOST_TSO4) | BIT(LKL_VIRTIO_NET_F_GUEST_TSO4);
        // Host and guest can handle TSOv6
        netdev_args.offload |= BIT(LKL_VIRTIO_NET_F_HOST_TSO6) | BIT(LKL_VIRTIO_NET_F_GUEST_TSO6);
        // Host can merge receive buffers
        netdev_args.offload |= BIT(LKL_VIRTIO_NET_F_MRG_RXBUF);
#endif

    int net_dev_id = lkl_netdev_add(netdev, &netdev_args);
    if (net_dev_id < 0) {
        lkl_printf("Error: unable to register netdev, %s\n",
            lkl_strerror(net_dev_id));
		while(1);
    }

    return net_dev_id;
}

void lkl_poststart_net(int net_dev_id) {
    int res = 0;
	lkl_printf("setting eth0\n");

	char *ip4str = "10.11.11.2";
	char *gw4str = "10.11.11.1";

    struct in_addr ip4 = { 0 };
    if (inet_pton(AF_INET, ip4str, &ip4) != 1) {
        lkl_printf("Invalid IPv4 address %s\n", ip4str);
		while(1);
	}

    struct in_addr gw4 = { 0 };
    if (gw4str != NULL && strlen(gw4str) > 0 &&
            inet_pton(AF_INET, gw4str, &gw4) != 1) {
        lkl_printf("Invalid IPv4 gateway %s\n", gw4str); while(1);
    }

	int mask4 = 24;

    if (net_dev_id >= 0) {
        int ifidx = lkl_netdev_get_ifindex(net_dev_id);
        res = lkl_if_set_ipv4(ifidx, ip4.s_addr, mask4);
        if (res < 0) {
            lkl_printf("Error: lkl_if_set_ipv4(): %s\n",
                lkl_strerror(res));
			while(1);
        }

        res = lkl_if_up(ifidx);

        if (res < 0) {
            lkl_printf("Error: lkl_if_up(eth0): %s\n",
                lkl_strerror(res));
			while(1);
        }

        if (gw4.s_addr > 0) {
            res = lkl_set_ipv4_gateway(gw4.s_addr);
            if (res < 0) {
                lkl_printf("Error: lkl_set_ipv4_gateway(): %s\n",
                    lkl_strerror(res));
					while(1);
            }
        }
    }
	lkl_printf("...done\n");

}

void lkl_poststart_lo(void) {
    int res = 0;
	lkl_printf("setting LO\n");
    res = lkl_if_up(1);
    if (res < 0) {
        lkl_printf("Error: lkl_if_up(1=lo): %s\n",
            lkl_strerror(res));
		while(1);
    }
	lkl_printf("...done\n");
}

void init_network(unsigned long base) {
#if 0
	lkl_printf("NO NETWORK \n");
#else
	lkl_printf("PRESTART NETWORK BEFORE LKL \n");
	int nid = lkl_prestart_net(base);
	lkl_printf("------ NETWORK ----- \n");
	lkl_poststart_lo();
	lkl_poststart_net(nid);
	printf("post start done\n");
    sethostname("carrie1", strlen("carrie1"));
#endif

}

