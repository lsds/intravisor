#include "monitor.h"

int wrap_write(int fd, void *ptr, int size) {
//      __syscall3(64, 1, (long )ptr, size);

//      int ret = write(STDOUT_FILENO, ptr, size);
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
	printf("%s %d not implemented\n", __FILE__, __LINE__);
#if 0
//__linux__
	struct lkl_netdev *nd;
	int fd, vnet_hdr_sz = 0;

	struct ifreq ifr = {
		.ifr_flags = IFF_TAP | IFF_NO_PI,
	};

	strncpy(ifr.ifr_name, "tap0", IFNAMSIZ);

	int ret, tap_arg = 0;
#if 0
	if(offload & BIT(LKL_VIRTIO_NET_F_GUEST_CSUM))
		tap_arg |= TUN_F_CSUM;
	if(offload & (BIT(LKL_VIRTIO_NET_F_GUEST_TSO4) | BIT(LKL_VIRTIO_NET_F_MRG_RXBUF)))
		tap_arg |= TUN_F_TSO4 | TUN_F_CSUM;
	if(offload & (BIT(LKL_VIRTIO_NET_F_GUEST_TSO6)))
		tap_arg |= TUN_F_TSO6 | TUN_F_CSUM;

	if(tap_arg || (offload & (BIT(LKL_VIRTIO_NET_F_CSUM) | BIT(LKL_VIRTIO_NET_F_HOST_TSO4) | BIT(LKL_VIRTIO_NET_F_HOST_TSO6)))) {
		ifr->ifr_flags |= IFF_VNET_HDR;
		vnet_hdr_sz = sizeof(struct lkl_virtio_net_hdr_v1);
	}
#endif

	fd = open("/dev/net/tun", O_RDWR | O_NONBLOCK);
	if(fd < 0) {
		perror("open");
		return NULL;
	}

	ret = ioctl(fd, TUNSETIFF, ifr);
	if(ret < 0) {
		fprintf(stderr, "%s: failed to attach to: %s\n", "/dev/net/tun", strerror(errno));
		close(fd);
		return NULL;
	}

	if(vnet_hdr_sz && ioctl(fd, TUNSETVNETHDRSZ, &vnet_hdr_sz) != 0) {
		fprintf(stderr, "%s: failed to TUNSETVNETHDRSZ to: %s\n", "/dev/net/tun", strerror(errno));
		close(fd);
		return NULL;
	}

	if(ioctl(fd, TUNSETOFFLOAD, tap_arg) != 0) {
		fprintf(stderr, "%s: failed to TUNSETOFFLOAD: %s\n", "/dev/net/tun", strerror(errno));
		close(fd);
		return NULL;
	}

	return fd;
#endif
#endif
}

#ifndef CONFIG_MODE_SIM
void cinv2(long, void *__capability, void *__capability, void *__capability);
void cinv2_sp(long, void *__capability, void *__capability, void *__capability, unsigned long);
#else
void cinv2(long, void *, void *, void *);
void cinv2_sp(long, void *, void *, void *, void *);
#endif

void *c_thread_body(void *carg) {
	struct c_thread *me = (struct c_thread *) carg;

	long addr = (long) me->arg;	//there is no mon_to_cap here because in all cases the args are cap-relative

	me->m_tp = getTP();
	me->c_tp = (void *) (me->stack + 4096);

//      printf("%p starting thread[%d]: [%lx -- %lx], func = %p, arg = %p\n",me, me->id, (long)me->stack, (long)me->stack+me->stack_size, me->func, me->arg);

	void *__capability sealcap;
	size_t sealcap_size;

	sealcap_size = sizeof(sealcap);

#if __FreeBSD__
	if(sysctlbyname("security.cheri.sealcap", &sealcap, &sealcap_size, NULL, 0) < 0) {
		printf("sysctlbyname(security.cheri.sealcap)\n");
		while(1) ;
	}
#else
	printf("sysctlbyname security.cheri.sealcap is not implemented in your OS\n");
#endif

	void *__capability ccap;
	if(me->sbox->pure)
		ccap = pure_codecap_create((void *) me->sbox->cmp_begin, (void *) me->sbox->cmp_end, me->sbox->clean_room);
	else
		ccap = codecap_create((void *) me->sbox->cmp_begin, (void *) me->sbox->cmp_end, me->sbox->clean_room);

	void *__capability dcap = datacap_create((void *) me->sbox->cmp_begin, (void *) me->sbox->cmp_end, me->sbox->clean_room);

	ccap = cheri_setaddress(ccap, (unsigned long) me->func);

	void *__capability sealed_datacap = cheri_seal(dcap, sealcap);
	void *__capability sealed_codecap = cheri_seal(ccap, sealcap);

	void *sp_read = me->stack + me->stack_size;	//getSP();
	volatile unsigned long *sp = (sp_read - 4096 * 4);	//I don't know why, but without volatile sp gets some wrong value after initing CENV in -O2

	void *__capability sp_cap;

	if(me->sbox->pure) {

//TOD: this is very unreliable. we need to use precise bottom of the stack here
		sp_cap = datacap_create((void *) me->stack, (unsigned long) me->stack + (unsigned long) me->stack_size, me->sbox->clean_room);
		sp_cap = cheri_setaddress(sp_cap, sp);

		printf("ca7: SP cap for purecap cVMs\n");
		CHERI_CAP_PRINT(sp_cap);

		void *__capability tp_cap = datacap_create((void *) ((unsigned long) me->c_tp), (unsigned long) me->c_tp + 4096, me->sbox->clean_room);
		tp_cap = cheri_setaddress(tp_cap, me->c_tp);

		printf("ca8: TP cap for purecap cVMs\n");
		CHERI_CAP_PRINT(tp_cap);

		me->c_tp = tp_cap;

	} else {
		sp = mon_to_comp(sp, me->sbox);
		me->c_tp = mon_to_comp(me->c_tp, me->sbox);
	}

	cmv_ctp(me->c_tp);
	cinv2_sp(addr, sealed_codecap,	//entrance
		 sealed_datacap,	//entrance
		 dcap,		//compartment data cap
		 sp);

	printf("stuck in thread, die\n");
	while(1) ;
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
		perror("attr init");
		printf("ret = %d\n", ret);
		while(1) ;
	}

	ct[tmp].stack_size = STACK_SIZE;
	ct[tmp].stack = (void *) (ct[tmp].sbox->cmp_end - ct[tmp].stack_size * (ct[tmp].id + 1));

	ret = pthread_attr_setstack(&ct[tmp].tattr, ct[tmp].stack, ct[tmp].stack_size);
	if(ret != 0) {
		perror("pthread attr setstack");
		printf("ret = %d\n", ret);
	}

	ct[tmp].arg = arg;
	ct[tmp].func = f;
//printf("HOST_CALL: CARRIE_THREAD %d %p %p\n", tmp, f, getSP());
	ret = pthread_create(&ct[tmp].tid, &ct[tmp].tattr, c_thread_body, &ct[tmp]);
	if(ret != 0) {
		perror("pthread create");
		printf("ret = %d\n", ret);
	}

	pthread_join(ct[tmp].tid, NULL);

	return 0;		//todo: here should be return value
}

void destroy_carrie_thread(struct c_thread *ct) {
	pthread_t tid = pthread_self();
	pthread_mutex_lock(&ct->sbox->ct_lock);
	for(int i = 0; i < MAX_THREADS; i++) {
		if(ct[i].tid == tid) {
			ct[i].id = -1;	//id?
//for some reason, code related to clearing previous allocations in main (for eval) doesn't work when tid -1. I don't have time to investigate
//                      ct[i].tid = -1;
			pthread_mutex_unlock(&ct->sbox->ct_lock);
//                      printf("thread %d %d exited\n", i, tid);
#if LKL
			lkl_host_ops.thread_exit();
#else
			pthread_exit(NULL);
#endif
		}
	}
	pthread_mutex_unlock(&ct->sbox->ct_lock);
	printf("something is wrong with the tread, check %p\n", tid);
	while(1) ;
}

#if LKL

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
//              printf("need more threads, die\n");
//              exit(1);
		pthread_mutex_unlock(&ct->sbox->ct_lock);
		usleep(100);
		goto again;
	}

	int tmp = j;

	ct[tmp].id = tmp;
	pthread_mutex_unlock(&ct->sbox->ct_lock);

	int ret = pthread_attr_init(&ct[tmp].tattr);
	if(ret != 0) {
		perror("attr init");
		printf("ret = %d\n", ret);
		while(1) ;
	}

	ct[tmp].stack_size = STACK_SIZE;
	ct[tmp].stack = (void *) (ct[tmp].sbox->cmp_end - ct[tmp].stack_size * (ct[tmp].id + 1));

	ret = pthread_attr_setstack(&ct[tmp].tattr, ct[tmp].stack, ct[tmp].stack_size);
	if(ret != 0) {
		perror("pthread attr setstack");
		printf("ret = %d\n", ret);
	}

	ct[tmp].arg = arg;
	ct[tmp].func = comp_to_mon(f, ct[tmp].sbox);

	struct thread_bootstrap_arg *targ = (struct thread_bootstrap_arg *) (comp_to_mon(arg, ct[tmp].sbox));
	void *targ_f = NULL;
	void *targ_arg = NULL;
//      printf("arg = %p, targ = %p\n", arg, targ);
	if(arg) {
		targ_f = targ->f;
		targ_arg = targ->arg;
	}
//      printf("CARRIE_THREAD %d %p, [%lx -- %lx], guessing (%p %p)\n", tmp, ct[tmp].func, ct[tmp].stack, ct[tmp].stack+STACK_SIZE, targ_f, targ_arg);

#ifdef __linux__
	ret = pthread_attr_setaffinity_np(&ct[tmp].tattr, sizeof(ct[tmp].sbox->cpuset), &ct[tmp].sbox->cpuset);
	if(ret != 0) {
		perror("pthread set affinity");
		printf("ret = %d\n", ret);
	}
#endif

	ret = pthread_create(&ct[tmp].tid, &ct[tmp].tattr, c_thread_body, &ct[tmp]);
	if(ret != 0) {
		perror("pthread create");
		printf("ret = %d\n", ret);
		while(1) ;
	}

	return (long) ct[tmp].tid;
}

struct s_thread {
	void *f;
	void *arg;
};

//this is very wrong, needs rework
void *timer_f = NULL;
struct s_box *timer_sbox;

void create_timer_thread(void *arg) {
	create_carrie_thread(timer_sbox->threads, timer_f, arg);
}

long create_carrie_timer(struct s_box *sbox, void *f, void *arg) {
	timer_f = f;
	timer_sbox = sbox;
	return (long) lkl_host_ops.timer_alloc(create_timer_thread, arg);
}

#endif
/************************ HOSTCALLs **************/

//the most of the calls are related to MUSL-LKL. They should be separated from basic calls. Ideally, moved into the runtime/musllkl directory and loaded as shared library.

long hostcall(long a0, long a1, long a2, long a3, long a4, long a5, long a6, long a7) {
	long t5 = (long) getT5();
	struct c_thread *ct = get_cur_thread();
	ct->c_tp = getTP();

	char *xx;

	cmv_ctp(ct->m_tp);

#if 0
//      if ( (ct->id !=1) && debug_calls)
	printf("IN: [%d]:%d %p, %p, [%lx %lx %lx %lx] \n", ct->id, t5, getSP(), getTP(), a0, a1, a2, a3);
#endif
	long ret = 0;
//      struct lkl_disk *disk;

	switch (t5) {
	case 1:
		wrap_write(ct->sbox->fd, (void *) comp_to_mon(a0, ct->sbox), a1);
//                      wrap_write(ct->sbox->fd, a0, a1);
		break;
//NB: we don't translate sem/mutex-related addresses because they are not used inside compartments
#if LKL
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
		printf("MEM_ALLOC, who called?\n");
		while(1) ;
		ret = (long) lkl_host_ops.mem_alloc(a0);
		break;
	case 22:
		printf("MEM_FREE %p, who called?\n", a0);
		while(1) ;
		lkl_host_ops.mem_free(a0);
		break;
	case 23:
		printf("EXEC ALLOC %p, who called?\n", a0);
		while(1) ;
//		ret = (long) lkl_host_ops.mem_executable_alloc(a0); renamed
		break;
	case 24:
		printf("EXEC FREE %p, who called?\n", a0);
		while(1) ;
//		lkl_host_ops.mem_executable_free(a0, a1); renamed
		break;
	case 25:
		ret = (long) lkl_host_ops.time();
		break;
	case 26:
		printf("TODO: CREATE_CARRIE_TIMER\n");
		ret = (long) create_carrie_timer(ct->sbox, a0, a1);
		break;
	case 27:
		if(timers) {
//			timers--;
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
#if 0
	case 200:
		ret = (long) fd_net_ops.tx(comp_to_mon(a0, ct->sbox), comp_to_mon(a1, ct->sbox), a2);
		break;
	case 201:
		ret = (long) fd_net_ops.rx(comp_to_mon(a0, ct->sbox), comp_to_mon(a1, ct->sbox), a2);
		break;
	case 202:
		ret = (long) fd_net_ops.poll(comp_to_mon(a0, ct->sbox));
		break;
	case 203:
		printf("TODO: %d\n", __LINE__);
		fd_net_ops.poll_hup(a0);
		break;
	case 204:
		printf("TODO: %d\n", __LINE__);
		fd_net_ops.free(a0);
		break;
#endif
#else
	case 13:
		destroy_carrie_thread(ct->sbox->threads);
		break;
	case 200:
		ret = nanosleep(comp_to_mon(a0, ct->sbox), comp_to_mon(a1, ct->sbox));
		break;
#endif
////
//HOST CALLS
//// these 3 calls are used for networking. 
	case 300:
//                      ret = open(a0, a1); //FreeBSD and musl have different Flags
		ret = (long) open_tap(comp_to_mon(a0, ct->sbox));
		break;
	case 301:
		ret = (long) pipe(comp_to_mon(a0, ct->sbox));
		break;
	case 302:
		ret = (long) fcntl(a0, F_SETFL, O_NONBLOCK);	//see the comment above
		break;
////
	case 400:
	case 401:
	case 402:
		printf("deprecated %d\n", t5);
		while(1) ;
	case 403:
		printf("TODO: %d\n", __LINE__);
		ret = (long) host_make_call(ct->sbox->threads, comp_to_mon(a0, ct->sbox), a1);
		break;
	case 404:
		printf("deprecated %d\n", t5);
		while(1) ;
		break;
	case 405:
		printf("TODO: %d\n", __LINE__);
		ret = (long) host_cap_file_adv(comp_to_mon(a0, ct->sbox), a1, comp_to_mon(a2, ct->sbox));
		break;
	case 406:
		ret = (long) host_cap_file_prb(comp_to_mon(a0, ct->sbox), comp_to_mon(a1, ct->sbox), comp_to_mon(a2, ct->sbox));
		break;
	case 407:
		host_cap_wait((int) a0);
		break;
	case 408:
		host_cap_wake((int) a0);
		break;
	case 409:
		ret = (long) host_cap_stream_adv(ct->sbox->threads, comp_to_mon(a0, ct->sbox), a1, comp_to_mon(a2, ct->sbox));
		break;
	case 410:
		ret = (long) host_cap_stream_prb(comp_to_mon(a0, ct->sbox));
		break;
	case 411:
		ret = (long) host_make_cap_call(ct->sbox->threads, a0, comp_to_mon(a1, ct->sbox), a2);
		break;
	case 412:
		ret = (long) host_finish_cap_call(a0, comp_to_mon(a1, ct->sbox));
		break;
	case 413:
		ret = (long) host_fetch_cap_call(a0, comp_to_mon(a1, ct->sbox), comp_to_mon(a2, ct->sbox));
		break;

#define USE_HOST_NET
#ifdef USE_HOST_NET
	case 500:
		ret = (int) socket(a0, a1, a2);
//                      printf("ret = %d, a0 = %d a1 = %d a2 = %d\n", ret, a0, a1, a2);perror("socket");
		break;
	case 501:
		ret = (int) setsockopt(a0, a1, a2, comp_to_mon(a3, ct->sbox), a4);
//                      printf("ret = %d, a0 = %d a1 = %d a2 = %d %d %d \n", ret, a0, a1, a2, a3, a4);perror("setcodk");
		break;
	case 502:
		ret = (int) ioctl(a0, a1, a2);
//                      printf("ret = %d %d %d %ld %ld\n", ret, a0, a1, a2, FIONBIO);
//                      perror("ioctl");
		break;
	case 503:
		ret = (int) accept4((int) a0, (struct sockaddr *) comp_to_mon(a1, ct->sbox), comp_to_mon(a2, ct->sbox), (int) a3);
		break;
	case 504:
		ret = (int) listen(a0, a1);
		break;
	case 505:
		ret = (int) accept((int) a0, (struct sockaddr *) comp_to_mon(a1, ct->sbox), comp_to_mon(a2, ct->sbox));
		break;
	case 506:
		ret = (int) bind(a0, (struct sockaddr *) comp_to_mon(a1, ct->sbox), a2);
		break;
	case 507:
		ret = write((int) a0, (void *) a1, (size_t) a2);
		break;
	case 508:
		ret = read((int) a0, (void *) a1, (size_t) a2);
		break;
	case 509:
		ret = send((int) a0, comp_to_mon(a1, ct->sbox), (size_t) a2, (int) a3);
		break;
	case 510:
		ret = recv((int) a0, comp_to_mon(a1, ct->sbox), (size_t) a2, (int) a3);
		break;
	case 511:
		ret = (int) close((int) a0);
		break;
	case 512:
		ret = (int) socketpair((int) a0, (int) a1, (int) a2, a3);
		break;
#if 0
//#ifdef __linux__
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
		ret = epoll_ctl((int) a0, (int) a1, (int) a2, (struct epoll_event *) a3);
		break;
	case 517:
		ret = epoll_wait((int) a0, (struct epoll_event *) a1, (int) a2, (int) a3);
		break;
	case 518:
		ret = epoll_pwait((int) a0, (struct epoll_event *) a1, (int) a2, (int) a3, (sigset_t *) a4);
		break;
#else
	case 513:
		ret = poll(comp_to_mon(a0, ct->sbox), a1, a2);
		break;
	case 514:
		ret = select(a0, comp_to_mon(a1, ct->sbox), comp_to_mon(a2, ct->sbox), comp_to_mon(a3, ct->sbox), comp_to_mon(a4, ct->sbox));
		break;
#endif
	case 519:
		ret = recvfrom((int) a0, (void *restrict) a1, (size_t) a2, (int) a3, (struct sockaddr * restrict) a4, (socklen_t * restrict) a5);
		break;
	case 520:
		ret = writev((int) a0, (const struct iovec *) a1, (int) a2);
		break;
#endif
	case 530:
		ret = getaddrinfo(comp_to_mon(a0, ct->sbox), comp_to_mon(a1, ct->sbox), comp_to_mon(a2, ct->sbox), comp_to_mon(a3, ct->sbox));
//                      ret = getaddrinfo(a1, a2, a3, a4);
		break;
	case 531:
#ifndef x86_sim
		ret = getpeername(a0, comp_to_mon(a1, ct->sbox), comp_to_mon(a2, ct->sbox));
#endif
		break;
	case 532:
#ifndef x86_sim
		ret = connect(a0, comp_to_mon(a1, ct->sbox), a2);
#endif
		break;
	case 700:
		ret = host_get_my_inner(ct->sbox, comp_to_mon(a0, ct->sbox));
		break;
	case 701:
		ret = host_syscall_handler_prb(comp_to_mon(a0, ct->sbox), comp_to_mon(a1, ct->sbox), comp_to_mon(a2, ct->sbox), comp_to_mon(a3, ct->sbox));
		break;
	case 702:
		ret = host_get_sc_caps(a0, a1, a2);
		break;
////////////////////////////////

	case 800:
		ret = gettimeofday(comp_to_mon(a0, ct->sbox), comp_to_mon(a1, ct->sbox));
		break;
	case 801:
		ret = lstat(comp_to_mon(a0, ct->sbox), comp_to_mon(a1, ct->sbox));
		break;
	case 806:
		ret = stat(comp_to_mon(a0, ct->sbox), comp_to_mon(a1, ct->sbox));
		break;
	case 807:
		ret = fstat(a0, comp_to_mon(a1, ct->sbox));
//                      printf("fstat: st_dev = %x, st_ino = %x\n", statbuf.st_dev, statbuf.st_ino);
		break;
	case 802:
		ret = unlink(comp_to_mon(a0, ct->sbox));
		break;
	case 803:
		ret = close(a0);
		break;
	case 804:
		ret = access(comp_to_mon(a0, ct->sbox), a1);
		break;
	case 808:
		ret = truncate(comp_to_mon(a0, ct->sbox), a1);
		break;
	case 809:
//                      printf("read = %d, %p, %d\n", a0, comp_to_mon(a1, ct->sbox), a2);
		ret = read(a0, comp_to_mon(a1, ct->sbox), a2);
//                      printf("read ret = %d\n", ret);
		break;
	case 810:
		ret = write(a0, comp_to_mon(a1, ct->sbox), a2);
		break;
	case 811:
//                      ret = open(comp_to_mon(a0, ct->sbox), a1, a2);
		ret = open(comp_to_mon(a0, ct->sbox), O_RDWR | O_CREAT, 0666);
		break;
	case 812:
//                      printf("lseek set %d %d %d\n", a0, a1, a2);
		ret = lseek(a0, a1, a2);
//                      printf("lseek ret = %d\n", ret);
		break;

	case 813:
		ret = errno;
//                      perror("syscall:");
		break;

	case 814:
		ret = fcntl(a0, a1, comp_to_mon(a3, ct->sbox));
		break;

/// GD
//these two calls should not exist, but so far I don't have a better design. the problem is that I cannot put CPIO binary into a pure-cap library using objcopy/ld, so need anyway to pass it into cVM.
//another option would be add to yaml another rule, or develope a unified interface for LKL-musl and baremetal cVMs
	case 900:
		ret = get_file_size(comp_to_mon(a0, ct->sbox));
		break;
	case 901:
		ret = copy_file_into_cvm(comp_to_mon(a0, ct->sbox), comp_to_mon(a1, ct->sbox), a2);
		break;
/// GD
	default:
		printf("Introvisor: unknown t5 %d\n", (int) t5);
		while(1) ;
	}
#if 0
//      if(t5 != 1 && debug_calls)
	if((tid == 2 && t5 != 1) && debug_calls)
		printf("OUT: %p: %lx %lx %lx %lx %lx %lx %lx %lx, %d \n", getSP(), a0, a1, a2, a3, a4, a5, a6, a7, t5);
#endif

	if(getTP() != ct->m_tp) {
		printf("TP has changed %p %p\n", getTP(), ct->m_tp);
	}

	cmv_ctp(ct->c_tp);

	return ret;
}
