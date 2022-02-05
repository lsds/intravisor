#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <poll.h>
#include <lkl_host.h>
#include "iomem.h"
#include "jmp_buf.h"
int __clock_gettime(clockid_t, struct timespec *ts);
/* Let's see if the host has semaphore.h */
#include <unistd.h>
#undef _POSIX_SEMAPHORES

#ifdef _POSIX_SEMAPHORES
#include <semaphore.h>
/* TODO(pscollins): We don't support fork() for now, but maybe one day
 * we will? */
#define SHARE_SEM 0
#endif /* _POSIX_SEMAPHORES */

static void print(const char *str, int len)
{
	int ret __attribute__((unused));

	ret = write(STDOUT_FILENO, str, len);
//	printf("|%s|, str = %p, len = %d\n", str, str, len);
}

struct lkl_mutex {
	pthread_mutex_t mutex;
};

struct lkl_sem {
#ifdef _POSIX_SEMAPHORES
	sem_t sem;
#else
	pthread_mutex_t lock;
	int count;
	pthread_cond_t cond;
#endif /* _POSIX_SEMAPHORES */
};

struct lkl_tls_key {
	pthread_key_t key;
};

#define WARN_UNLESS(exp) do {						\
		if (exp < 0)						\
			printf("%s: %s\n", #exp, strerror(errno));	\
	} while (0)

static int _warn_pthread(int ret, char *str_exp)
{
	if (ret > 0) {
		printf("%s: %s\n", str_exp, strerror(ret)); while(1);
	}

	return ret;
}


/* pthread_* functions use the reverse convention */
#define WARN_PTHREAD(exp) _warn_pthread(exp, #exp)

static struct lkl_sem *sem_alloc(int count)
{
	struct lkl_sem *sem;

	sem = malloc(sizeof(*sem));
	if (!sem)
		return NULL;

//	printf("SEM_ALLOC %p, %d\n", sem, count);

#ifdef _POSIX_SEMAPHORES
	if (sem_init(&sem->sem, SHARE_SEM, count) < 0) {
		printf("sem_init: %s\n", strerror(errno));
		free(sem);
		return NULL;
	}
#else
#ifdef __linux__ 
	pthread_mutex_init(&sem->lock, NULL);
	sem->count = count;
	WARN_PTHREAD(pthread_cond_init(&sem->cond, NULL));
//	printf("ALLOC: &sem->lock = %p\n", &sem->lock);
#else
	sem->lock = PTHREAD_MUTEX_INITIALIZER;
	sem->count = count;
	sem->cond = PTHREAD_COND_INITIALIZER;
#endif
#endif /* _POSIX_SEMAPHORES */
	return sem;
}

static void sem_free(struct lkl_sem *sem)
{
#ifdef _POSIX_SEMAPHORES
	WARN_UNLESS(sem_destroy(&sem->sem));
#else
	WARN_PTHREAD(pthread_cond_destroy(&sem->cond));
	WARN_PTHREAD(pthread_mutex_destroy(&sem->lock));
#endif /* _POSIX_SEMAPHORES */
//	printf("SEM FREE %p\n", sem);
	free(sem);
}

static void sem_up(struct lkl_sem *sem)
{
//	printf("SEM UP%p\n", sem);
#ifdef _POSIX_SEMAPHORES
	WARN_UNLESS(sem_post(&sem->sem));
#else
//	printf("UP: &sem->lock = %p, sem->count = %d\n", &sem->lock, sem->count);
	WARN_PTHREAD(pthread_mutex_lock(&sem->lock));
	sem->count++;
	if (sem->count > 0)
		WARN_PTHREAD(pthread_cond_signal(&sem->cond));
	WARN_PTHREAD(pthread_mutex_unlock(&sem->lock));
#endif /* _POSIX_SEMAPHORES */

}

static void sem_down(struct lkl_sem *sem)
{
//	printf("SEM DOWN %p\n", sem);
#ifdef _POSIX_SEMAPHORES
	int err;

	do {
		err = sem_wait(&sem->sem);
	} while (err < 0 && errno == EINTR);
	if (err < 0 && errno != EINTR)
		printf("sem_wait: %s\n", strerror(errno));
#else
//	printf("DOWN: &sem->lock = %p, count=%d\n", &sem->lock, sem->count);
	WARN_PTHREAD(pthread_mutex_lock(&sem->lock));
	while (sem->count <= 0) {
		WARN_PTHREAD(pthread_cond_wait(&sem->cond, &sem->lock));
}
	sem->count--;
	WARN_PTHREAD(pthread_mutex_unlock(&sem->lock));
#endif /* _POSIX_SEMAPHORES */
}

static struct lkl_mutex *mutex_alloc(int recursive)
{
	struct lkl_mutex *_mutex = malloc(sizeof(struct lkl_mutex));
	pthread_mutex_t *mutex = NULL;
	pthread_mutexattr_t attr;

	if (!_mutex)
		return NULL;

	mutex = &_mutex->mutex;
	WARN_PTHREAD(pthread_mutexattr_init(&attr));

	/* PTHREAD_MUTEX_ERRORCHECK is *very* useful for debugging,
	 * but has some overhead, so we provide an option to turn it
	 * off. */
#ifdef DEBUG
	if (!recursive)
		WARN_PTHREAD(pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK));
#endif /* DEBUG */

	if (recursive)
		WARN_PTHREAD(pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE));

	WARN_PTHREAD(pthread_mutex_init(mutex, &attr));

	return _mutex;
}

static void mutex_lock(struct lkl_mutex *mutex)
{
	WARN_PTHREAD(pthread_mutex_lock(&mutex->mutex));
}

static void mutex_unlock(struct lkl_mutex *_mutex)
{
	pthread_mutex_t *mutex = &_mutex->mutex;
	WARN_PTHREAD(pthread_mutex_unlock(mutex));
}

static void mutex_free(struct lkl_mutex *_mutex)
{
	pthread_mutex_t *mutex = &_mutex->mutex;
	WARN_PTHREAD(pthread_mutex_destroy(mutex));
	free(_mutex);
}

static lkl_thread_t thread_create(void (*fn)(void *), void *arg)
{
	pthread_t thread;
	if (WARN_PTHREAD(pthread_create(&thread, NULL, (void* (*)(void *))fn, arg)))
		return 0;
	else
		return (lkl_thread_t) thread;
}

static void thread_detach(void)
{
	WARN_PTHREAD(pthread_detach(pthread_self()));
}

static void thread_exit(void)
{
	pthread_exit(NULL);
}

static int thread_join(lkl_thread_t tid)
{
	if (WARN_PTHREAD(pthread_join((pthread_t)tid, NULL)))
		return -1;
	else
		return 0;
}

static lkl_thread_t thread_self(void)
{
	lkl_thread_t ret = (lkl_thread_t)pthread_self();
//	printf("%s: %p\n", __func__, ret);
	return ret;
}

static int thread_equal(lkl_thread_t a, lkl_thread_t b)
{
//	printf("%s %p %p\n",__func__, a, b); 
	return pthread_equal((pthread_t)a, (pthread_t)b);
}

static struct lkl_tls_key *tls_alloc(void (*destructor)(void *))
{
	struct lkl_tls_key *ret = malloc(sizeof(struct lkl_tls_key));

	if(destructor) {
		printf("ignore destructor in %s\n", __func__);
		destructor = 0;
	}

	if (WARN_PTHREAD(pthread_key_create(&ret->key, destructor))) {
		free(ret);
		return NULL;
	}
	return ret;
}

static void tls_free(struct lkl_tls_key *key)
{
	WARN_PTHREAD(pthread_key_delete(key->key));
	free(key);
}

static __inline__ void * getSP(void) {
    register void * sp asm("sp");
    asm ("" : "=r"(sp));
    return sp;
}



static int tls_set(struct lkl_tls_key *key, void *data)
{
//#define STACK_SIZE (0x100000) //1M
//	int tid = (0x30000000-(((long) getSP() / STACK_SIZE)*STACK_SIZE))/STACK_SIZE - 1;
//printf("key = %p, key->key=%p, data = %p, tid %d\n", key, key->key, data, tid);
	if (WARN_PTHREAD(pthread_setspecific(key->key, data)))
		return -1;

	return 0;
}

static void *tls_get(struct lkl_tls_key *key)
{
	void *reg = pthread_getspecific(key->key);
	return reg;
}

static unsigned long long time_ns(void)
{
	struct timespec ts;

#ifdef __linux__ 
	clock_gettime(CLOCK_MONOTONIC, &ts);
#else
	__sys_clock_gettime(CLOCK_REALTIME, &ts);
#endif

	return 1e9*ts.tv_sec + ts.tv_nsec;
}

static void *timer_alloc(void (*fn)(void *), void *arg)
{
	int err;
	timer_t timer;
	struct sigevent se =  {
		.sigev_notify = SIGEV_THREAD,
		.sigev_value = {
			.sival_ptr = arg,
		},
		.sigev_notify_function = (void (*)(union sigval))fn,
	};

	err = timer_create(CLOCK_REALTIME, &se, &timer);
	if (err)
		return NULL;

	return (void *)(long)timer;
}

static int timer_set_oneshot(void *_timer, unsigned long ns)
{
	timer_t timer = (timer_t)(long)_timer;
	struct itimerspec ts = {
		.it_value = {
			.tv_sec = ns / 1000000000,
			.tv_nsec = ns % 1000000000,
		},
	};

	return timer_settime(timer, 0, &ts, NULL);
}

static void timer_free(void *_timer)
{
	timer_t timer = (timer_t)(long)_timer;

	timer_delete(timer);
}

static void panic(void)
{
	assert(0);
}

static long _gettid(void)
{
#ifdef	__FreeBSD__
	return (long)pthread_self();
#else
	return syscall(SYS_gettid);
#endif
}

char lkl_virtio_devs[4096];

struct lkl_host_operations lkl_host_ops = {
	.virtio_devices = lkl_virtio_devs,
	.print = print,
	.panic = panic,
	.sem_alloc = sem_alloc,
	.sem_free = sem_free,
	.sem_up = sem_up,
	.sem_down = sem_down,
	.thread_create = thread_create,
	.thread_detach = thread_detach,
	.thread_exit = thread_exit,
	.thread_join = thread_join,
	.thread_self = thread_self,
	.thread_equal = thread_equal,
	.mutex_alloc = mutex_alloc,
	.mutex_free = mutex_free,
	.mutex_lock = mutex_lock,
	.mutex_unlock = mutex_unlock,
	.tls_alloc = tls_alloc,
	.tls_free = tls_free,
	.tls_set = tls_set,
	.tls_get = tls_get,
	.time = time_ns,
	.timer_alloc = timer_alloc,
	.timer_set_oneshot = timer_set_oneshot,
	.timer_free = timer_free,

	.mem_alloc = malloc,
	.mem_free = free,
	.ioremap = lkl_ioremap,
	.iomem_access = lkl_iomem_access,

	.gettid = _gettid,
	.jmp_buf_set = jmp_buf_set,
	.jmp_buf_longjmp = jmp_buf_longjmp,
};

static int fd_get_capacity(unsigned long cof2mon, struct lkl_disk disk, unsigned long long *res)
{
	off_t off;

	res = (unsigned long long) ((unsigned long) res + cof2mon);

	off = lseek(disk.fd, 0, SEEK_END);
	if (off < 0)
		return -1;

	*res = off;
	return 0;
}

static int do_rw(unsigned long cof2mon, ssize_t (*fn)(), struct lkl_disk disk, struct lkl_blk_req *req)
{
	off_t off = req->sector * 512;
	void *addr;
	int len;
	int i;
	int ret = 0;

//	printf("%p, req->count = %d, sec = %d\n", req, req->count, req->sector);

	for (i = 0; i < req->count; i++) {
//		printf("req->buf = %lx\n", req->buf);
		struct iovec *tbuf = (struct iovec *) ((unsigned long) &req->buf[i] + cof2mon);
//		addr = req->buf[i].iov_base;
		addr = tbuf->iov_base + cof2mon;
//		printf("addr = %lx\n", addr);
//		len = req->buf[i].iov_len;
		len = tbuf->iov_len;
//printf("RoW %p, %x %x %d\n", addr, len, off, req->count);
		do {
			ret = fn(disk.fd, addr, len, off);
			if (ret <= 0) {
				ret = -1;
				goto out;
			}

			addr += ret;
			len -= ret;
			off += ret;

		} while (len);
	}

out:
	return ret;
}

static int blk_request(unsigned long cof2mon, struct lkl_disk disk, struct lkl_blk_req *req)
{
	int err = 0;

	req = (struct lkl_blk_req *) ((unsigned long) req + cof2mon);

	switch (req->type) {
	case LKL_DEV_BLK_TYPE_READ:
//printf("READ: ");
		err = do_rw(cof2mon, pread, disk, req);
		break;
	case LKL_DEV_BLK_TYPE_WRITE:
//printf("WRITE: ");
		err = do_rw(cof2mon, pwrite, disk, req);
		break;
	case LKL_DEV_BLK_TYPE_FLUSH:
	case LKL_DEV_BLK_TYPE_FLUSH_OUT:
#ifdef __linux__
		err = fdatasync(disk.fd);
#else
		err = fsync(disk.fd);
#endif
		break;
	default:
		return LKL_DEV_BLK_STATUS_UNSUP;
	}

	if (err < 0)
		return LKL_DEV_BLK_STATUS_IOERR;

	return LKL_DEV_BLK_STATUS_OK;
}

struct lkl_dev_blk_ops lkl_dev_blk_ops = {
	.get_capacity = fd_get_capacity,
	.request = blk_request,
};

