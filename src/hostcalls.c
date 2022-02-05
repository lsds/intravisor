#include "monitor.h"

#define __asm_syscall(...) \
	__asm__ __volatile__ ("ecall\n\t" \
	: "=r"(a0) : __VA_ARGS__ : "memory"); \
	return a0; \

static inline long __syscall3(long n, long a, long b, long c)
{
	register long t0 __asm__("t0") = n;
	register long a0 __asm__("a0") = a;
	register long a1 __asm__("a1") = b;
	register long a2 __asm__("a2") = c;
	__asm_syscall("r"(t0), "0"(a0), "r"(a1), "r"(a2))
}

static __inline__ void * getT5(void) {
    register void * t5 asm("t5");
    asm ("" : "=r"(t5));
    return t5;
}

int wrap_write(int fd, void *ptr, int size) {
//	__syscall3(64, 1, (long )ptr, size);

//	int ret = write(STDOUT_FILENO, ptr, size);
	int ret = write(fd, ptr, size);

	return ret;
}
///////////////////////////
/*
0	const char *virtio_devices;
//1	void (*print)(const char *str, int len);
2	void (*panic)(void);
//3	struct lkl_sem* (*sem_alloc)(int count);
//4	void (*sem_free)(struct lkl_sem *sem);
//5	void (*sem_up)(struct lkl_sem *sem);
//6	void (*sem_down)(struct lkl_sem *sem);
//7	struct lkl_mutex *(*mutex_alloc)(int recursive);
//8	void (*mutex_free)(struct lkl_mutex *mutex);
//9	void (*mutex_lock)(struct lkl_mutex *mutex);
//10	void (*mutex_unlock)(struct lkl_mutex *mutex);
//11	lkl_thread_t (*thread_create)(void (*f)(void *), void *arg);
12	void (*thread_detach)(void);
13	void (*thread_exit)(void);
14	int (*thread_join)(lkl_thread_t tid);
//15	lkl_thread_t (*thread_self)(void);
16	int (*thread_equal)(lkl_thread_t a, lkl_thread_t b);
17	struct lkl_tls_key *(*tls_alloc)(void (*destructor)(void *));
18	void (*tls_free)(struct lkl_tls_key *key);
19	int (*tls_set)(struct lkl_tls_key *key, void *data);
20	void *(*tls_get)(struct lkl_tls_key *key);
21	void* (*mem_alloc)(unsigned long);
22	void (*mem_free)(void *);
23	void* (*mem_executable_alloc)(unsigned long);
24	void (*mem_executable_free)(void *, unsigned long size);
25	unsigned long long (*time)(void);
26	void* (*timer_alloc)(void (*fn)(void *), void *arg);
27	int (*timer_set_oneshot)(void *timer, unsigned long delta);
28	void (*timer_free)(void *timer);
29	void* (*ioremap)(long addr, int size);
30	int (*iomem_access)(const __volatile__ void *addr, void *val, int size,
			    int write);
31	long (*gettid)(void);
32	void (*jmp_buf_set)(struct lkl_jmp_buf *jmpb, void (*f)(void));
33	void (*jmp_buf_longjmp)(struct lkl_jmp_buf *jmpb, int val);
*/
///////////////////////////

int open_tap(char *ifname) {
#if __FreeBSD__
	return open(ifname, O_RDWR | O_NONBLOCK);
#else
//__linux__
	struct lkl_netdev *nd;
	int fd, vnet_hdr_sz = 0;

	struct ifreq ifr = {
		.ifr_flags = IFF_TAP | IFF_NO_PI,
	};

	strncpy(ifr.ifr_name, "tap0", IFNAMSIZ);

	int ret, tap_arg = 0;
#if 0
	if (offload & BIT(LKL_VIRTIO_NET_F_GUEST_CSUM))
		tap_arg |= TUN_F_CSUM;
	if (offload & (BIT(LKL_VIRTIO_NET_F_GUEST_TSO4) |
	    BIT(LKL_VIRTIO_NET_F_MRG_RXBUF)))
		tap_arg |= TUN_F_TSO4 | TUN_F_CSUM;
	if (offload & (BIT(LKL_VIRTIO_NET_F_GUEST_TSO6)))
		tap_arg |= TUN_F_TSO6 | TUN_F_CSUM;

	if (tap_arg || (offload & (BIT(LKL_VIRTIO_NET_F_CSUM) |
				   BIT(LKL_VIRTIO_NET_F_HOST_TSO4) |
				   BIT(LKL_VIRTIO_NET_F_HOST_TSO6)))) {
		ifr->ifr_flags |= IFF_VNET_HDR;
		vnet_hdr_sz = sizeof(struct lkl_virtio_net_hdr_v1);
	}
#endif

	fd = open("/dev/net/tun", O_RDWR|O_NONBLOCK);
	if (fd < 0) {
		perror("open");
		return NULL;
	}

	ret = ioctl(fd, TUNSETIFF, ifr);
	if (ret < 0) {
		fprintf(stderr, "%s: failed to attach to: %s\n",
			"/dev/net/tun", strerror(errno));
		close(fd);
		return NULL;
	}

	if (vnet_hdr_sz && ioctl(fd, TUNSETVNETHDRSZ, &vnet_hdr_sz) != 0) {
		fprintf(stderr, "%s: failed to TUNSETVNETHDRSZ to: %s\n",
			"/dev/net/tun", strerror(errno));
		close(fd);
		return NULL;
	}

	if (ioctl(fd, TUNSETOFFLOAD, tap_arg) != 0) {
		fprintf(stderr, "%s: failed to TUNSETOFFLOAD: %s\n",
			"/dev/net/tun", strerror(errno));
		close(fd);
		return NULL;
	}

	return fd;
#endif
}


#ifndef SIM
void cinv2(long, void *__capability, void *__capability, void *__capability);
#else
void cinv2(long, void *, void *, void *);
#endif

void *c_thread_body(void *carg) {
	struct c_thread *me = (struct c_thread *)carg;
//	void *sp_read = me->stack + me->stack_size;
//	unsigned long *sp = (sp_read -  4096*1);

	long addr = (long) me->arg; //there is no mon_to_cap here because in all cases the args are cap-relative

	me->m_tp = getTP();
	me->c_tp = (void *)(me->stack+4096);

//	printf("me->func = %p, addr=%p, sp = %p\n", me->func, addr, getSP());

#ifdef SIM
//	__asm__ __volatile__ ("mv ra, %0" : : "r"(ra): "memory" );
//	__asm__ __volatile__("mv tp, %0;" :: "r"(me->c_tp) : "memory");
//inline doesnt work like this
	cinv2(addr,
		  me->func,  	//entrance
		  NULL,  	//entrance
		  NULL 			//compartment data cap
		);


#else

//	printf("%p starting thread[%d]: [%lx -- %lx], func = %p, arg = %p\n",me, me->id, (long)me->stack, (long)me->stack+me->stack_size, me->func, me->arg);

	void * __capability sealcap;
	size_t sealcap_size;

	sealcap_size = sizeof(sealcap);
	if (sysctlbyname("security.cheri.sealcap", &sealcap, &sealcap_size, NULL, 0) < 0) {
		printf("sysctlbyname(security.cheri.sealcap)\n");while(1);
	}

	void * __capability ccap = codecap_create((void *) me->sbox->cmp_begin, (void *) me->sbox->cmp_end);
	void * __capability dcap = datacap_create((void *) me->sbox->cmp_begin, (void *) me->sbox->cmp_end);

	ccap = cheri_setaddress(ccap, (unsigned long) me->func);

	void * __capability sealed_datacap = cheri_seal(dcap, sealcap);
	void * __capability sealed_codecap = cheri_seal(ccap, sealcap);

	me->c_tp = mon_to_comp(me->c_tp, me->sbox->cmp_begin);

repeat:

//	__asm__ __volatile__ ("mv ra, %0" : : "r"(ra): "memory" );
	__asm__ __volatile__("mv tp, %0;" :: "r"(me->c_tp) : "memory");
//inline doesnt work like this
	cinv2(addr,
		  sealed_codecap,  	//entrance
		  sealed_datacap,  	//entrance
		  dcap 			//compartment data cap
		);

	__asm__ __volatile__("mv tp, %0;" :: "r"(me->m_tp) : "memory");
	goto repeat;

#endif

	printf("stuck in thread, die\n");
	while(1);
}

void destroy_carrie_thread(struct c_thread *ct) {
	pthread_t tid = pthread_self();
    pthread_mutex_lock(&ct->sbox->ct_lock);
	for(int i = 0; i < MAX_THREADS; i++) {
		if(ct[i].tid == tid) {
			ct[i].id = -1;
//			printf("thread %d exited\n", i);
  			pthread_mutex_unlock(&ct->sbox->ct_lock);
			lkl_host_ops.thread_exit();
		}
	}
    pthread_mutex_unlock(&ct->sbox->ct_lock);
	printf("something is wrong with the tread, check %p\n", tid);
	while(1);
}

struct thread_bootstrap_arg {
	struct thread_info *ti;
	int (*f)(void *);
	void *arg;
};

long create_carrie_thread(struct c_thread *ct, void *f, void *arg) {
again:
    pthread_mutex_lock(&ct->sbox->ct_lock);
	int j;
	for(j = 0; j < MAX_THREADS; j++) {
		if(ct[j].id == -1)
			break;
	}
	if(j == MAX_THREADS) {
//		printf("need more threads, die\n");
//		exit(1);
		pthread_mutex_unlock(&ct->sbox->ct_lock);
		usleep(100);
		goto again;
	}

	int tmp = j;

	ct[tmp].id = tmp;
    pthread_mutex_unlock(&ct->sbox->ct_lock);

	int ret = pthread_attr_init(&ct[tmp].tattr);
	if(ret != 0) {
		perror("attr init");printf("ret = %d\n", ret); while(1);
	}

	ct[tmp].stack_size = STACK_SIZE;
	ct[tmp].stack = (void *)(ct[tmp].sbox->cmp_end - ct[tmp].stack_size*(ct[tmp].id+1));

    ret = pthread_attr_setstack(&ct[tmp].tattr, ct[tmp].stack, ct[tmp].stack_size);
	if(ret != 0) {
		perror("pthread attr setstack");printf("ret = %d\n", ret);
	}

	ct[tmp].arg = arg;
	ct[tmp].func = comp_to_mon(f, ct[tmp].sbox->cmp_begin);

	struct thread_bootstrap_arg *targ = (struct thread_bootstrap_arg *) (comp_to_mon(arg, ct[tmp].sbox->cmp_begin));
	void *targ_f = NULL;
	void *targ_arg = NULL;
//	printf("arg = %p, targ = %p\n", arg, targ);
	if(arg) {
		targ_f = targ->f;
		targ_arg = targ->arg;
	} 

//	printf("CARRIE_THREAD %d %p, [%lx -- %lx], guessing (%p %p)\n", tmp, ct[tmp].func, ct[tmp].stack, ct[tmp].stack+STACK_SIZE, targ_f, targ_arg);

#ifdef __linux__
	ret  = pthread_attr_setaffinity_np(&ct[tmp].tattr, sizeof(ct[tmp].sbox->cpuset), &ct[tmp].sbox->cpuset);
	if (ret != 0) {
		perror("pthread set affinity");printf("ret = %d\n", ret);
	}
#endif

	ret = pthread_create(&ct[tmp].tid, &ct[tmp].tattr, c_thread_body, &ct[tmp]);
	if(ret != 0) {
		perror("pthread create");printf("ret = %d\n", ret);while(1);
	}

	return (long) ct[tmp].tid;
}

long host_make_call(struct c_thread *ct, void *f, void *arg) {
    pthread_mutex_lock(&ct->sbox->ct_lock);
	int j;
	for(j = 0; j < MAX_THREADS; j++) {
		if(ct[j].id == -1)
			break;
	}
	if(j == MAX_THREADS) {
		printf("need more threads, die\n");
		exit(1);
	}

	int tmp = j;

	ct[tmp].id = tmp;
    pthread_mutex_unlock(&ct->sbox->ct_lock);

	int ret = pthread_attr_init(&ct[tmp].tattr);
	if(ret != 0) {
		perror("attr init");printf("ret = %d\n", ret); while(1);
	}

	ct[tmp].stack_size = STACK_SIZE;
	ct[tmp].stack = (void *)(ct[tmp].sbox->cmp_end - ct[tmp].stack_size*(ct[tmp].id+1));

    ret = pthread_attr_setstack(&ct[tmp].tattr, ct[tmp].stack, ct[tmp].stack_size);
	if(ret != 0) {
		perror("pthread attr setstack");printf("ret = %d\n", ret);
	}

	ct[tmp].arg = arg;
	ct[tmp].func = f;
//printf("HOST_CALL: CARRIE_THREAD %d %p %p\n", tmp, f, getSP());
    ret = pthread_create(&ct[tmp].tid, &ct[tmp].tattr, c_thread_body, &ct[tmp]);
	if(ret != 0) {
		perror("pthread create");printf("ret = %d\n", ret);
	}

	pthread_join(ct[tmp].tid, NULL);

	return 0; //todo: here should be return value
}



//////

struct s_thread {
	void *f;
	void *arg;
};

//this is very wrong, needs rework
void *timer_f = NULL;

void create_timer_thread(void *arg) {
	create_carrie_thread(cvms[0].threads, timer_f, arg);
}

long create_carrie_timer(void *f, void *arg) {
	timer_f = f;

	return (long) lkl_host_ops.timer_alloc(create_timer_thread, arg);
}


struct c_tread *get_cur_thread() {
	int cid = (long) getSP() / 0x10000000;
	if ((cid <= 0 ) || (cid >= MAX_CVMS) ) {
		printf("wrong cvm id %d, sp = %p, die\n", cid, (long) getSP()); while(1);
	}

// would be nice to check something
	struct c_thread *ret = &cvms[cid].threads[ (cvms[cid].cmp_end - (((long) getSP() / STACK_SIZE)*STACK_SIZE))/STACK_SIZE - 1];

	return ret;
}


int host_reg_cap(void *ptr, long size, void *location) {
#ifndef SIM
//todo: internally, datacap_create default cap of monitor. it might be slightly better to use caps of the target isolation layer
	void * __capability dcap = datacap_create(ptr, (void *) ((unsigned long) ptr + size));
//	CHERI_CAP_PRINT(dcap);
#else
	void *dcap = ptr;
#endif
	extern void st_cap(void *loc, void *__capability);
	st_cap(location, dcap);
}

/////// this function is used to spawn a call thread. it runs once and used for multiple calls. 

void *c_call_thread_body(void *carg) {
	struct c_thread *me = (struct c_thread *)carg;
//	void *sp_read = me->stack + me->stack_size;
//	unsigned long *sp = (sp_read -  4096*1);

	long addr = (long) me->arg; //there is no mon_to_cap here because in all cases the args are cap-relative

	me->m_tp = getTP();
	me->c_tp = (void *)(me->stack+4096);

	printf("me->func = %p, addr=%p, sp = %p\n", me->func, addr, getSP());

#ifdef SIM
//	__asm__ __volatile__ ("mv ra, %0" : : "r"(ra): "memory" );
//	__asm__ __volatile__("mv tp, %0;" :: "r"(me->c_tp) : "memory");
//inline doesnt work like this
	cinv2(addr,
		  me->func,  	//entrance
		  NULL,  	//entrance
		  NULL 			//compartment data cap
		);


#else

//	printf("%p starting thread[%d]: [%lx -- %lx], func = %p, arg = %p\n",me, me->id, (long)me->stack, (long)me->stack+me->stack_size, me->func, me->arg);

	void * __capability sealcap;
	size_t sealcap_size;

	sealcap_size = sizeof(sealcap);
	if (sysctlbyname("security.cheri.sealcap", &sealcap, &sealcap_size, NULL, 0) < 0) {
		printf("sysctlbyname(security.cheri.sealcap)\n");while(1);
	}

	void * __capability ccap = codecap_create((void *) me->sbox->cmp_begin, (void *) me->sbox->cmp_end);
	void * __capability dcap = datacap_create((void *) me->sbox->cmp_begin, (void *) me->sbox->cmp_end);

	ccap = cheri_setaddress(ccap, (unsigned long) me->func);

	void * __capability sealed_datacap = cheri_seal(dcap, sealcap);
	void * __capability sealed_codecap = cheri_seal(ccap, sealcap);

	me->c_tp = mon_to_comp(me->c_tp, me->sbox->cmp_begin);

	struct stream_caps_store *cs = me->cs;

repeat:

	pthread_mutex_lock(&cs->call_lock2.lock);
	cs->call_lock2.predicate = true;
	pthread_cond_signal(&cs->call_lock2.cond); 
	pthread_mutex_unlock(&cs->call_lock2.lock); 

	__asm__ __volatile__("mv tp, %0;" :: "r"(me->c_tp) : "memory");
	cinv2(addr,
		  sealed_codecap,  	//entrance
		  sealed_datacap,  	//entrance
		  dcap 			//compartment data cap
		);

	__asm__ __volatile__("mv tp, %0;" :: "r"(me->m_tp) : "memory");

	pthread_mutex_lock(&cs->call_lock.lock);
	if( ! cs->call_lock.predicate ) pthread_cond_wait(&cs->call_lock.cond, &cs->call_lock.lock); 
	cs->call_lock.predicate = false;
	pthread_mutex_unlock(&cs->call_lock.lock);

	goto repeat;

#endif

	printf("stuck in thread, die\n");
	while(1);
}


long host_spawn_call(struct stream_caps_store *cs, struct c_thread *ct, void *f, void *arg) {
	if(cs->call_lock.armed == 0) {
		pthread_mutex_lock(&ct->sbox->ct_lock);
		int j;
		for(j = 0; j < MAX_THREADS; j++) {
			if(ct[j].id == -1)
				break;
		}
		if(j == MAX_THREADS) {
			printf("need more threads, die\n");
			exit(1);
		}

		int tmp = j;

		ct[tmp].id = tmp;
		pthread_mutex_unlock(&ct->sbox->ct_lock);

		int ret = pthread_attr_init(&ct[tmp].tattr);
		if(ret != 0) {
			perror("attr init");printf("ret = %d\n", ret); while(1);
		}

		ct[tmp].stack_size = STACK_SIZE;
		ct[tmp].stack = (void *)(ct[tmp].sbox->cmp_end - ct[tmp].stack_size*(ct[tmp].id+1));

		ret = pthread_attr_setstack(&ct[tmp].tattr, ct[tmp].stack, ct[tmp].stack_size);
		if(ret != 0) {
			perror("pthread attr setstack");printf("ret = %d\n", ret);
		}

		ct[tmp].arg = arg;
		ct[tmp].func = f;
		ct[tmp].cs = cs;
//printf("HOST_CALL: CARRIE_THREAD %d %p %p\n", tmp, f, getSP());
		ret = pthread_create(&ct[tmp].tid, &ct[tmp].tattr, c_call_thread_body, &ct[tmp]);
		if(ret != 0) {
			perror("pthread create");printf("ret = %d\n", ret);
		}

		cs->call_lock.armed = 1;
	}

	pthread_mutex_lock(&cs->call_lock.lock);
	cs->call_lock.predicate = true;
	pthread_cond_signal(&cs->call_lock.cond); 
	pthread_mutex_unlock(&cs->call_lock.lock); 

	pthread_mutex_lock(&cs->call_lock2.lock);
	if( ! cs->call_lock2.predicate ) pthread_cond_wait(&cs->call_lock2.cond, &cs->call_lock2.lock); 
	cs->call_lock2.predicate = false;
	pthread_mutex_unlock(&cs->call_lock2.lock); 

}



//todo: instead of addresses, here should be capabiltites
//however, they should be sealed, but, for now, the sealing cap for caps appear much later than I pub these addresses.
struct sc_cb_store_s {
	char name[20];
	void * __capability pcc;
	void * __capability ddc;
	void * __capability pcc2;
}	sc_cbs[10];

struct caps_store caps[10];
struct stream_caps_store stream_caps[MAX_STREAM_CAPS];

void init_cap_store() {
	for(int i = 0; i < 10; i++) {
		caps[i].ptr = NULL;
		caps[i].size = 0;
		pthread_mutex_init(&caps[i].hlock.lock, NULL);
		pthread_cond_init(&caps[i].hlock.cond, NULL);
	}

	for(int i =0; i < 10; i++) {
		memset(sc_cbs[i].name, 0, 20);
	}
}

int host_cap_adv(void *ptr, long size, char *key) {
//	printf("advertise: %p, %ld, %s\n", ptr, size, key);
	int i = 0;
	for(i = 0; i < 10; i++) {
		if(caps[i].ptr == 0)
			break;
	}
	
	if(i == 10) {
		printf("need more cap streams/files, die\n");
		while(1);
	}



	caps[i].ptr = ptr;
	caps[i].size = size;
//todo: init locks/mutex
//	memcpy(caps[i].name, key, 10); //yeah, snprintf or so
	snprintf(caps[i].name, 10, "%s", key);

	printf("MON: CAP[%d] %p %s %d\n", i, caps[i].ptr, caps[i].name, caps[i].size);

	return i;
}

int host_cap_prb(char *key, void *location, long *size) {
	printf("MON: probe for key %s, store at %p\n", key, location);
	int i;
	for(i = 0; i < 10; i++) {
		if(strncmp(caps[i].name, key, 10) == NULL)
			break;
	}
	
	if(i == 10) {
		printf("wrong cap key %s ", key); while(1);
		
	}

	host_reg_cap(caps[i].ptr, caps[i].size, location);
	if(size) 
		*size = caps[i].size;

	return i;
}

// NB: we don't translate *dev because it is not used outside of the compartment. 
int host_cap_stream_adv(struct c_thread *ct, void *func, void *dev, char *key) {
//	printf("cap_stream avertise: %p, %p, %s\n", func, dev, key);
	int i = 0;
	for(i = 0; i < MAX_STREAM_CAPS; i++) {
		if(stream_caps[i].func == 0)
			break;
	}
	
	if(i == MAX_STREAM_CAPS) {
		printf("need more cap streams/files, die\n");
		while(1);
	}



	stream_caps[i].func = func;
	stream_caps[i].dev = dev;
	stream_caps[i].ct = ct;
//todo: init locks/mutex
	snprintf(stream_caps[i].name, 10, "%s", key);

	printf("MON: STREAM_CAP[%d] %p %s %p\n", i, stream_caps[i].func, stream_caps[i].name, stream_caps[i].dev);

//this is super insecure and wrong. we should return capability, or store this index into per-cVM OS-'cap' store
	return i;
}

int host_cap_stream_prb(char *key) {
//	printf("probe cap_stream for key %s\n", key);
	int i;
	for(i = 0; i < MAX_STREAM_CAPS; i++) {
		if(strncmp(stream_caps[i].name, key, 10) == NULL)
			break;
	}
	
	if(i == MAX_STREAM_CAPS) {
		printf("wrong cap key %s ", key); while(1);
		
	}

	return i;
}


int host_syscall_handler_adv(char *libos, void * __capability pcc, void * __capability ddc, void * __capability pcc2) {
//	printf("MON: SYSCALL avertise: %s, %p, %p\n", libos, pcc, ddc);
	int i = 0;
	for(i = 0; i < 10; i++) {
		if(sc_cbs[i].name[0] == 0)
			break;
	}
	
	if(i == 10) {
		printf("need more sc_cbs, die\n");
		while(1);
	}

	snprintf(sc_cbs[i].name, 20, "%s", libos);
	sc_cbs[i].pcc = pcc;
	sc_cbs[i].pcc2 = pcc2;
	sc_cbs[i].ddc = ddc;

	printf("MON: sc_cbs[%d]: %s, %p, %p, %p\n", i, sc_cbs[i].name, sc_cbs[i].pcc, sc_cbs[i].ddc);
	return 0;
}

int host_syscall_handler_prb(char *key,  void *ppc, void *ddc, void *ppc2) {
	printf("MON: probe syscall handler for key %s\n", key);
	int i;
	for(i = 0; i < 10; i++) {
		if(strncmp(sc_cbs[i].name, key, 20) == NULL)
			break;
	}
	
	if(i == 10) {
		printf("wrong SC key %s\n", key); while(1);
	}

	st_cap(ppc, sc_cbs[i].pcc);
	st_cap(ppc2, sc_cbs[i].pcc2);
	st_cap(ddc, sc_cbs[i].ddc);

	return i;

}

void host_cap_wait(int id) {
	if(id < 0 || id > MAX_STREAM_CAPS) {
		printf("%d: wrong stream_caps id = %d, die\n", __LINE__, id);
	}

	struct cs_lock *cs = &stream_caps[id].hlock;

	pthread_mutex_lock(&cs->lock);
	if( ! cs->predicate ) pthread_cond_wait(&cs->cond, &cs->lock); 
	cs->predicate = false;
	pthread_mutex_unlock(&cs->lock); 
}

void host_cap_wake(int id) {
	if(id < 0 || id > MAX_STREAM_CAPS) {
		printf("%d: wrong stream_caps id = %d, die\n", __LINE__, id);
	}

	struct cs_lock *cs = &stream_caps[id].hlock;

	pthread_mutex_lock(&cs->lock);
	cs->predicate = true;
	pthread_cond_signal(&cs->cond); 
	pthread_mutex_unlock(&cs->lock); 
}

int host_get_my_inner(struct c_thread *ct, long location) {
//#define RET_TO_INNER_PPC	(16*13)
//#define RET_TO_INNER_DDC	(16*14)
//#define INNER_DDC			(16*15)
//	st_cap(location, ct->sbox->inner->box_caps.sealed_ret_from_mon);
//	st_cap(location + 16, ct->sbox->inner->box_caps.sealed_datacap);
//	st_cap(location + 32, ct->sbox->inner->box_caps.dcap);

	st_cap(location, 	  cvms[1].box_caps.sealed_ret_from_mon);
	st_cap(location + 16, cvms[1].box_caps.sealed_datacap);
	st_cap(location + 32, cvms[1].box_caps.dcap);

}

int host_make_cap_call(struct c_thread *ct, int id, void *buffer, int size) {
	if(id < 0 || id > MAX_STREAM_CAPS) {
		printf("%d: wrong stream_caps id = %d, die\n", __LINE__, id);
	}

//	printf("%s buffer = %p, size = %d\n", __func__, buffer, size);
	stream_caps[id].u_buff = buffer;
	stream_caps[id].u_size = size;

//	printf("%d %p %d %p\n", __LINE__, ct, id, stream_caps[id].func);

#if 1
//spawn a thread, make call, keep thread working
	return host_spawn_call(&stream_caps[id], stream_caps[id].ct, stream_caps[id].func, id);
#else
//spawn a thread, make call, destroy the thread.
	return host_make_call(stream_caps[id].ct, stream_caps[id].func, id);
#endif
}

int host_finish_cap_call(int id, long *buff) {
	if(id < 0 || id > MAX_STREAM_CAPS) {
		printf("%d: wrong stream_caps id = %d, die\n", __LINE__, id);
	}

	*buff = stream_caps[id].dev;
	return 0;
}
int host_fetch_cap_call(int id, void *cap, long *size) {
	if(id < 0 || id > MAX_STREAM_CAPS) {
		printf("%d: wrong stream_caps id = %d, die\n", __LINE__, id);
	}

//	printf("%s: %p, %d\n", stream_caps[id].u_buff, stream_caps[id].u_size);
	host_reg_cap(stream_caps[id].u_buff, stream_caps[id].u_size, cap);
	if(size)
		*size = stream_caps[id].u_size;
	return 0;
}


/************************ HOSTCALLs **************/

long hostcall(long a0, long a1, long a2, long a3, long a4, long a5, long a6, long a7) {
	long t5 = (long) getT5();

	struct c_thread *ct = get_cur_thread();
	ct->c_tp = getTP();
	__asm__ __volatile__("mv tp, %0;" :: "r"(ct->m_tp) : "memory");

#if 0
	if ( (ct->id !=1) && debug_calls)
		printf("IN: [%d]:%d %p\n", ct->id, t5, getSP());
#endif
	long ret = 0;
//	struct lkl_disk *disk;
	switch(t5) {
		case 1:
			wrap_write(ct->sbox->fd, (void *)comp_to_mon(a0, ct->sbox->cmp_begin), a1);
			break;
//NB: we don't translate sem/mutex-related addresses because they are not used inside compartments
		case 3:
			ret = (long) lkl_host_ops.sem_alloc(a0);
			break;
		case 4:
			lkl_host_ops.sem_free(a0);
			break;
		case 5:
			lkl_host_ops.sem_up(a0);
			break;
		case 6:
			lkl_host_ops.sem_down(a0);
			break;
		case 7:
			ret = (long) lkl_host_ops.mutex_alloc(a0);
			break;
		case 8:
			lkl_host_ops.mutex_free(a0);
			break;
		case 9:
			lkl_host_ops.mutex_lock(a0);
			break;
		case 10:
			lkl_host_ops.mutex_unlock(a0);
			break;
		case 11:
			ret = (long) create_carrie_thread(ct->sbox->threads, a0, a1);
			break;
		case 12:
			lkl_host_ops.thread_detach();
			break;
		case 13:
			destroy_carrie_thread(ct->sbox->threads);
			break;
		case 14:
			ret = (long) lkl_host_ops.thread_join(a0);
			break;
		case 15:
			ret = (long) lkl_host_ops.thread_self();
			break;
		case 16:
			ret = (long) lkl_host_ops.thread_equal(a0, a1);
			break;
		case 17:
			ret = (long) lkl_host_ops.tls_alloc(a0);
			break;
		case 18:
			lkl_host_ops.tls_free(a0);
			break;
		case 19:
			ret = (long) lkl_host_ops.tls_set(a0, a1);
			break;
		case 20:
			ret = (long) lkl_host_ops.tls_get(a0);
			break;
		case 21:
printf("MEM_ALLOC, who called?\n"); while(1);
			ret = (long) lkl_host_ops.mem_alloc(a0);
			break;
		case 22:
printf("MEM_FREE %p, who called?\n", a0); while(1);
			lkl_host_ops.mem_free(a0);
			break;
		case 23:
printf("EXEC ALLOC %p, who called?\n", a0); while(1);
			ret = (long) lkl_host_ops.mem_executable_alloc(a0);
			break;
		case 24:
printf("EXEC FREE %p, who called?\n", a0); while(1);
			lkl_host_ops.mem_executable_free(a0, a1);
			break;
		case 25:
			ret = (long) lkl_host_ops.time();
			break;
		case 26:
			printf("TODO: CREATE_CARRIE_TIMER\n");
			ret = (long) create_carrie_timer(a0, a1);
			break;
		case 27:
			if(timers) {
				printf("TODO: SET_ONE_SHOT\n");
				ret = (long) lkl_host_ops.timer_set_oneshot(a0, a1);
			}
			break;
		case 28:
			printf("TODO: TIMER_FREE\n");
			lkl_host_ops.timer_free(a0);
			break;
/////
//disk I/O
/////
		case 100:
			ret = (long) lkl_dev_blk_ops.request(ct->sbox->cmp_begin, ct->sbox->lkl_disk, a1);
			break;
		case 101:
			ret = (long) lkl_dev_blk_ops.get_capacity(ct->sbox->cmp_begin, ct->sbox->lkl_disk, a1);
			break;
////
//NETWORK
////
		case 200:
			ret = (long) fd_net_ops.tx(comp_to_mon(a0, ct->sbox->cmp_begin), comp_to_mon(a1, ct->sbox->cmp_begin), a2);
			break;
		case 201:
			ret = (long) fd_net_ops.rx(comp_to_mon(a0, ct->sbox->cmp_begin), comp_to_mon(a1, ct->sbox->cmp_begin), a2);
			break;
		case 202:
			ret = (long) fd_net_ops.poll(comp_to_mon(a0, ct->sbox->cmp_begin));
			break;
		case 203:
			printf("TODO: %d\n", __LINE__);
			fd_net_ops.poll_hup(a0);
			break;
		case 204:
			printf("TODO: %d\n", __LINE__);
			fd_net_ops.free(a0);
			break;
////
//HOST CALLS
//// these 3 calls are used for networking. 
		case 300:
//			ret = open(a0, a1); //FreeBSD and musl have different Flags
			ret = (long) open_tap(comp_to_mon(a0, ct->sbox->cmp_begin));
			break;
		case 301:
			ret = (long) pipe(comp_to_mon(a0, ct->sbox->cmp_begin));
			break;
		case 302:
			ret = (long) fcntl(a0, F_SETFL, O_NONBLOCK); //see the comment above
			break;
////
		case 400:
		case 401:
		case 402:
			printf("deprecated %d\n", t5); while(1);
		case 403:
			printf("TODO: %d\n", __LINE__);
			ret = (long) host_make_call(ct->sbox->threads, comp_to_mon(a0, ct->sbox->cmp_begin), a1);
			break;
		case 404:
			printf("TODO: %d\n", __LINE__);
			ret = (long) host_reg_cap(comp_to_mon(a0, ct->sbox->cmp_begin), a1, comp_to_mon(a2, ct->sbox->cmp_begin));
			break;
		case 405:
			printf("TODO: %d\n", __LINE__);
			ret = (long) host_cap_adv(comp_to_mon(a0, ct->sbox->cmp_begin), a1, comp_to_mon(a2, ct->sbox->cmp_begin));
			break;
		case 406:
			ret = (long) host_cap_prb(comp_to_mon(a0, ct->sbox->cmp_begin), comp_to_mon(a1, ct->sbox->cmp_begin), comp_to_mon(a2, ct->sbox->cmp_begin));
			break;
		case 407:
			host_cap_wait((int)a0);
			break;
		case 408:
			host_cap_wake((int)a0);
			break;
		case 409:
			ret = (long) host_cap_stream_adv(ct->sbox->threads, comp_to_mon(a0, ct->sbox->cmp_begin), a1, comp_to_mon(a2, ct->sbox->cmp_begin));
			break;
		case 410:
			ret = (long) host_cap_stream_prb(comp_to_mon(a0, ct->sbox->cmp_begin));
			break;
		case 411:
			ret = (long) host_make_cap_call(ct->sbox->threads, a0, comp_to_mon(a1, ct->sbox->cmp_begin), a2);
			break;
		case 412:
			ret = (long) host_finish_cap_call(a0, comp_to_mon(a1, ct->sbox->cmp_begin));
			break;
		case 413:
			ret = (long) host_fetch_cap_call(a0, comp_to_mon(a1, ct->sbox->cmp_begin), comp_to_mon(a2, ct->sbox->cmp_begin));
			break;


//#define USE_HOST_NET
#ifdef USE_HOST_NET
		case 500:
			ret = (int) socket(a0, a1, a2);
//			printf("ret = %d, a0 = %d a1 = %d a2 = %d\n", ret, a0, a1, a2);perror("socket");
			break;
		case 501:
			ret = (int) setsockopt(a0, a1, a2, a3, a4);
//			printf("ret = %d, a0 = %d a1 = %d a2 = %d %d %d \n", ret, a0, a1, a2, a3, a4);perror("setcodk");
			break;
		case 502:
			ret = (int) ioctl(a0, a1, a2);
//			printf("ret = %d %d %d %ld %ld\n", ret, a0, a1, a2, FIONBIO);
//			perror("ioctl");
			break;
		case 503:
			ret = (int) accept4((int) a0, (struct sockaddr *) a1, (socklen_t *)a2, (int) a3);
			break;
		case 504:
			ret = (int) listen(a0, a1);
			break;
		case 505:
			ret = (int) accept((int) a0, (struct sockaddr *) a1, (socklen_t *) a2);
			break;
		case 506:
			ret = (int) bind(a0, (const struct sockaddr *)a1, a2);
			break;
		case 507:
			ret =  write( (int) a0, (void *) a1, (size_t) a2);
			break;
		case 508:
			ret = read((int) a0, (void *)a1, (size_t) a2);
			break;
		case 509:
			ret = send((int) a0, (void *)a1, (size_t) a2, (int) a3);
			break;
		case 510:
			ret = recv((int) a0, (void *)a1, (size_t) a2, (int) a3);
			break;
		case 511:
			ret = (int) close((int) a0);
			break;
		case 512:
			ret = (int) socketpair((int) a0, (int) a1, (int) a2, a3);
			break;
#ifdef __linux__
		case 513:
			ret = epoll_create((int) a0);
			break;
		case 514:
			ret = epoll_create1((int) a0);
			break;
		case 515:
			ret = eventfd((unsigned int) a0, (int) a1);
			break;
		case 516:
			ret = epoll_ctl((int) a0, (int) a1, (int) a2, (struct epoll_event *)a3);
			break;
		case 517:
			ret = epoll_wait((int) a0, (struct epoll_event *)a1, (int) a2, (int) a3);
			break;
		case 518:
			ret = epoll_pwait((int) a0, (struct epoll_event *) a1, (int) a2, (int) a3, (sigset_t *) a4);
			break;
#endif
		case 519:
			ret = recvfrom((int) a0, (void *restrict ) a1, (size_t) a2, (int) a3, (struct sockaddr *restrict) a4, (socklen_t *restrict) a5);
			break;
		case 520:
			ret = writev((int) a0, (const struct iovec *) a1, (int) a2);
			break;
#endif

		case 700:
			ret = host_get_my_inner(ct->sbox, comp_to_mon(a0, ct->sbox->cmp_begin));
			break;

		default:
			printf("unknown t5 %d\n", t5);
			while(1);
	}

#if 0
//	if(t5 != 1 && debug_calls)
	if (( tid == 2 && t5 !=1) && debug_calls)
		printf("OUT: %p: %lx %lx %lx %lx %lx %lx %lx %lx, %d \n", getSP(), a0, a1, a2, a3, a4, a5, a6, a7, t5);
#endif

	if(getTP() != ct->m_tp) {
		printf("TP has changed %p %p\n", getTP(), ct->m_tp);
	}

	__asm__ __volatile__("mv tp, %0;" :: "r"(ct->c_tp) : "memory");

	return ret;
}


