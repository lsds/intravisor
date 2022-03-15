#include "monitor.h"

#define MAX_STREAM_CAPS	10
struct stream_caps_store {
	void *func;
	void *dev;
	void *u_buff;
	void *u_size;
	char name[10];


	struct cs_lock hlock;
	struct c_thread *ct;
//
	struct cs_lock call_lock;
	struct cs_lock call_lock2;
};

static struct stream_caps_store stream_caps[MAX_STREAM_CAPS];

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


