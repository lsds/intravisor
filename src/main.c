#include "monitor.h"

struct s_box	cvms[MAX_CVMS];


//default config

int timers = 0;
int debug_calls = 0;
//

pthread_mutex_t print_lock;



void *init_thread(void *arg) {
	struct c_thread *me = (struct c_thread *)arg;
	void *sp_read = me->stack + me->stack_size;//getSP();
	char argv1[128];
	char lc1[128];
	char env1[128];
	char env2[128];
	char env3[128];
	char env4[128];
	char env5[128];

	snprintf(argv1, 128, "/ld.so");
	snprintf(lc1, 128, "LC_ALL=C.UTF-8");

	snprintf(env1, 128, "PYTHONHOME=/usr");
	snprintf(env2, 128, "PYTHONPATH=/usr");
	snprintf(env3, 128, "PYTHONUSERBASE=site-packages");
	snprintf(env4, 128, "TMPDIR=/tmp");
	snprintf(env5, 128, "PYTHONDEBUG=3");
//	snprintf(env5, 128, "_PYTHON_SYSCONFIGDATA_NAME=_sysconfigdata");


	me->m_tp = getTP();
	me->c_tp = (void *)(me->stack+4096);

	char *cenv = (char *) (sp_read -  4096*3); //originally, here was *2, but networking corrupts this memory
	volatile unsigned long *sp = (sp_read -  4096*4);//I don't know why, but without volatile sp gets some wrong value after initing CENV in -O2

	printf("target SP = %lx, old TP = %lx sp_read = %p, me->stacl = %p, getSP()=%p, me->c_tp = %p\n", sp, getTP(), sp_read, me->stack,getSP(), me->c_tp);
	int cenv_size = 0;
	sp[0] = me->argc;
	sp[1] = (unsigned long) (mon_to_comp(argv1, me->sbox));
	int i;
	for(i = 1; i < me->argc; i++) {
		printf("[%d] '%s'\n", i, me->argv[i]);

		int tmp_add = snprintf(&cenv[cenv_size], 128, "%s\0", me->argv[i]);
		if(cenv_size + tmp_add > 4096) {
			printf("need more space for args on the stack, die\n"); while(1);
		}
		sp[i+1] = (unsigned long) (mon_to_comp(&cenv[cenv_size], me->sbox));
		printf("sp[i+1] = '%s'\n", (char *) (comp_to_mon(sp[i+1], me->sbox)));
		cenv_size += tmp_add + 1;
	}
	sp[i+1] = 0; //terminator
	int ienv = i + 2;
	printf("&env0 = %p, &env1=%p\n", &sp[ienv], &sp[ienv+1]);
	sp[ienv++] = mon_to_comp(lc1, me->sbox);
	sp[ienv++] = mon_to_comp(env1, me->sbox);
	sp[ienv++] = mon_to_comp(env2, me->sbox);
	sp[ienv++] = mon_to_comp(env3, me->sbox);
	sp[ienv++] = mon_to_comp(env4, me->sbox);
	sp[ienv++] = mon_to_comp(env5, me->sbox);
	sp[ienv++] = 0;

	size_t *auxv = &sp[ienv];
	printf("%d sp = %p\n", __LINE__, sp);

	if(strlen(me->sbox->disk_image)) {
		me->sbox->lkl_disk.fd = open(me->sbox->disk_image, O_RDWR);
		if(me->sbox->lkl_disk.fd < 0) {
			printf("cannot open disk '%s'\n", me->sbox->disk_image); while(1);
		}
	} else 
		me->sbox->lkl_disk.fd = -1;

	me->sbox->lkl_disk.ops = &lkl_dev_blk_ops;

//	printf("LOADER: argv = %lx, envp = %lx(expected %lx), auxv = %lx \n", &sp[1], &sp[4], &sp[1 + 1 + sp[0]],auxv);
//	printf("LOADER: argv = %s, envp = %s, \n", sp[1], sp[4]);
	auxv[0] = AT_BASE;		auxv[1] = (unsigned long) me->sbox->base;
	auxv[2] = AT_ENTRY;		auxv[3] = (unsigned long)  me->func;
	auxv[4] = AT_PHDR;		auxv[5] = mon_to_comp(me->sbox->base, me->sbox) + 0x40;
	auxv[6] = AT_PAGESZ;	auxv[7] = 4096;
	auxv[8] = AT_IGNORE;	auxv[9] = -1;

	int aid = 10;
    auxv[aid++] = AT_CLKTCK;	auxv[aid++] = 100;
    auxv[aid++] = AT_HWCAP;		auxv[aid++] = 0;
    auxv[aid++] = AT_EGID;		auxv[aid++] = 0;
    auxv[aid++] = AT_EUID;		auxv[aid++] = 0;
    auxv[aid++] = AT_GID;		auxv[aid++] = 0;
    auxv[aid++] = AT_SECURE;	auxv[aid++] = 0;
    auxv[aid++] = AT_UID;		auxv[aid++] = -1;
    auxv[aid++] = AT_RANDOM;	auxv[aid++] = 0;
    auxv[aid++] = AT_NULL;		auxv[aid++] = 0;

//    auxv[12]  = AT_EXECFN;	auxv[13]  = (size_t) "";
//    auxv[22] = AT_PLATFORM;	auxv[23] = (size_t) "x86_64";
//    auxv[28] = AT_RANDOM;	auxv[29] = getauxval(AT_RANDOM);
//	auxv[aid++] = AT_HWCAP;		auxv[aid++] = getauxval(AT_HWCAP);


//	if(mprotect(0x2fffd000, 4096, PROT_READ) == -1) {
//		perror("mprotect");while(1);
//	  }


#if SIM
#define CRTJMP(pc,sp) __asm__ __volatile__( \
	"mv sp, %1 ; jr %0" : : "r"(pc), "r"(sp): "memory" )

	printf("SIM: sp = %p, tp = %p\n", sp, me->c_tp);
	printf("-----------------------------------------------\n");
extern void __inline__ cinv(void *, void *, void *, void *, void *, void *, void *, void *);
	__asm__ __volatile__("mv sp, %0; mv tp, %1;" :: "r"(sp), "r"(me->c_tp) : "memory");
	cinv(
		  me->func,  	//entrance
		  NULL,  	//entrance
		  NULL, 			//compartment data cap
		  me->hostcall,	//cap for exit
		  NULL,	//cap for example
		  NULL, //default data cap after exit, must be changed
		  me->sbox->ret_from_mon + me->sbox->base,
		  auxv[1] /* AT_BASE */ + 0x0e000000 + 0x1000 //local_cap_store
		);

	printf("%s:%d\tBUG, die\n",__func__, __LINE__); while(1);

#else

/////////////////////////
  void * __capability sealed_codecap	= me->sbox->box_caps.sealed_codecap;
  void * __capability sealed_datacap	= me->sbox->box_caps.sealed_datacap;
  void * __capability dcap				= me->sbox->box_caps.dcap;
  void * __capability sealed_codecapt	= me->sbox->box_caps.sealed_codecapt;
  void * __capability sealed_codecapt2	= me->sbox->box_caps.sealed_codecapt2;
  void * __capability sealed_datacapt	= me->sbox->box_caps.sealed_datacapt;
  void * __capability sealed_ret_from_mon	= me->sbox->box_caps.sealed_ret_from_mon;

	struct cinv_s {
		void *__capability caps[10];
	} cinv_args;
//
	cinv_args.caps[0] = sealed_codecap;
	printf("ca0: sealed COMP PPC\n");
	CHERI_CAP_PRINT(cinv_args.caps[0]);
//
	cinv_args.caps[1] = sealed_datacap;
	printf("ca1: sealed COMP DDC\n");
	CHERI_CAP_PRINT(cinv_args.caps[1]);
//
	cinv_args.caps[2] = dcap;
	printf("ca2: COMP DDC\n");
	CHERI_CAP_PRINT(cinv_args.caps[2]);
//
	cinv_args.caps[3] = sealed_codecapt;
	printf("ca3: sealed HC PCC\n");
	CHERI_CAP_PRINT(cinv_args.caps[3]);
//
	cinv_args.caps[4] = sealed_datacapt;
	printf("ca4: sealed HC DDC (mon.DDC)\n");
	CHERI_CAP_PRINT(cinv_args.caps[4]);
//
	cinv_args.caps[5] = sealed_codecapt2;
	printf("ca5: sealed OCALL PCC \n");
	CHERI_CAP_PRINT(cinv_args.caps[5]);
//
	cinv_args.caps[6] = sealed_ret_from_mon;
	printf("ca6: sealed ret from mon\n");
	CHERI_CAP_PRINT(cinv_args.caps[6]);
//

	if(me->sbox->pure) {

//TOD: this is very unreliable. we need to use precise bottom of the stack here
		void * __capability sp_cap = datacap_create((void *) ((unsigned long) sp - STACK_SIZE + 4096*4), (void *) sp);
		sp_cap = cheri_setaddress(sp_cap, sp);

//
		cinv_args.caps[7] = sp_cap;
		printf("ca7: SP cap for purecap cVMs\n");
		CHERI_CAP_PRINT(cinv_args.caps[7]);
//
	}

	sp = mon_to_comp(sp, me->sbox);
	me->c_tp = mon_to_comp(me->c_tp, me->sbox);


extern void cinv(void *, void *);
	printf("HW: sp = %p, tp = %p\n", sp, me->c_tp);
	printf("-----------------------------------------------\n");
	__asm__ __volatile__("mv sp, %0;" :: "r"(sp) : "memory");
	__asm__ __volatile__("mv tp, %0;" :: "r"(me->c_tp) : "memory");
	cinv(
#if 0
		  sealed_codecap,  	//ca0:	entrance
		  sealed_datacap,  	//ca1:	entrance
		  dcap, 			//ca2:	compartment data cap
///
		  sealed_codecapt,	//ca3:	cap for hostcalls
		  sealed_datacapt,	//ca4:	cap for hostcall, in fact -- sealed mon.DDC
///
		  sp_cap,
//		  sealed_codecapt2,	//ca5:	cap for ret from CINV2 (OCALL)
///
		  sealed_ret_from_mon, //ca6:	because compartment cannot create CAPS, this cap is created by MON prior calling
		  auxv[1] /* AT_BASE */ + 0x0e000000 + 0x1000 //local_cap_store
#else
		  auxv[1] /* AT_BASE */ + 0x0e000000 + 0x1000, //local_cap_store
		  &cinv_args
#endif
		);


	while(1);
#endif
}

void sig_handler(int j, siginfo_t *si, void *uap) {
	mcontext_t *mctx = &((ucontext_t *)uap)->uc_mcontext;
	printf("trap %d\n", j);
	printf("SI_ADDR: %ld\n", si->si_addr);

#ifdef SIM 
	printf("not implemented, linux has different mcontext\n");
#else
	__register_t ra = mctx->mc_gpregs.gp_ra;
	__register_t sp = mctx->mc_gpregs.gp_sp;
	__register_t gp = mctx->mc_gpregs.gp_sp;
	__register_t tp = mctx->mc_gpregs.gp_tp;
	__register_t *a = &mctx->mc_gpregs.gp_a[0];
	__register_t *t = &mctx->mc_gpregs.gp_t[0];
	__register_t *s = &mctx->mc_gpregs.gp_s[0];
	__register_t gp_sepc = mctx->mc_gpregs.gp_sepc;
	__register_t gp_sstatus = mctx->mc_gpregs.gp_sstatus;

	printf("ra = %lx, sp = %lx, gp = %lx, tp = %lx, gp_sepc = %p, gp_status = %p\n", ra, sp, gp, tp, gp_sepc, gp_sstatus);
	for(int i = 0; i < 7; i++) {
		printf("gp_t[%d]\t%lx\n", i, t[i]);
	}

	for(int i = 0; i < 12; i++) {
		printf("gp_s[%d]\t%lx\n", i, s[i]);
	}

	for(int i = 0; i < 8; i++) {
		printf("gp_a[%d]\t%lx\n", i, a[i]);
	}
#endif
	while(1);
}

void setup_sig() {
	stack_t sigstack;
	struct sigaction sa;
#if 1
	int stsize = SIGSTKSZ*100;

	sigstack.ss_sp = malloc(stsize);
	if(sigstack.ss_sp == NULL) {
		perror("malloc");
	}

	sigstack.ss_size = stsize;
	sigstack.ss_flags = 0;
	if(sigaltstack(&sigstack, NULL) == -1) {
		perror("sigstack");
		exit(1);
	}
#endif
#ifdef DEBUG
	printf("%d Alternate stack is at %10p-%p\n", stsize, sigstack.ss_sp,sigstack.ss_sp+stsize);
#endif

//	sa.sa_handler = sig_handler;
	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_ONSTACK | SA_SIGINFO;

	if(sigaction(SIGSEGV, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}
}


int build_cvm(int cid, struct cmp_s *comp, char *libos, char *disk, int argc, char *argv[], char *cb_out, char *cb_in) {
	struct encl_map_info encl_map;
	void *base = comp->base;
	unsigned long size = comp->size;
	unsigned long cmp_begin = comp->begin;
	unsigned long cmp_end = comp->end;


	memset(&encl_map, 0, sizeof(struct encl_map_info));

	load_elf(libos, base, &encl_map);
	if (encl_map.base < 0) {
		printf("Could not load '%s', die\n", libos); while(1);
	}

	if(encl_map.base != (unsigned long) base) {
		printf("mapped at wrong addres [%p]:[%p], die\n", encl_map.base, base); while(1);
	}

	printf("ELF BASE = %p, MAP SIZE = %lx, ENTRY = %p\n", encl_map.base, encl_map.size, encl_map.entry_point);

	int ret = 0;

	if(encl_map.entry_point == 0) {
		printf("entry_point is 0, runtime image is wrong/corrupted\n"); while(1);
	} else printf("encl_map.entry = %p\n",encl_map.entry_point);

	if(encl_map.ret_point == 0) {
		printf("ret_from_monitor is 0, runtime image is wrong/corrupted\n"); while(1);
	}else printf("encl_map.ret = %p\n",encl_map.ret_point);


	if(encl_map.cap_relocs) {
		printf("we have __cap_relocs, it is a purecap binary\n");
		cvms[cid].pure = 1;
		struct cap_relocs_s *cr = (struct cap_relocs_s *) encl_map.cap_relocs;
		for(int j = 0; j < encl_map.cap_relocs_size / sizeof(struct cap_relocs_s); j++) {
			printf("TODO: create cap: %p Base: %p Length: %ld Perms: %lx Unk = %ld\n", comp->base + cr[j].dst, cr[j].addr, cr[j].len, cr[j].perms, cr[j].unknown);
			void * __capability rel_cap;
			if(cr[j].perms == 0x8000000000000000ll) {
#if 0
//there is a problem when I call an asm function. the caller cap doesn't have a proper size.
//so I just make all call caps PCC-size (see the else)
				rel_cap = pure_codecap_create((void *) comp->base,(void *)  comp->base + cr[j].addr + cr[j].len);
				rel_cap = cheri_setaddress(rel_cap, comp->base + cr[j].addr);
#else
				rel_cap = pure_codecap_create((void *) comp->base,(void *)  comp->base + comp->size);
				rel_cap = cheri_setaddress(rel_cap, comp->base + cr[j].addr);
#endif
			} else {
//TODO: we need something better
				if (cr[j].len == 0xabba) {
					printf("replace cap for caps\n");
					rel_cap = datacap_create((void *) comp->base + 0xe001000, comp->base + 0xe002000);
				} else
					rel_cap = datacap_create((void *) comp->base + cr[j].addr,(void *)  comp->base + cr[j].addr + cr[j].len);
			}
			printf("store REL_CAP\n");
			CHERI_CAP_PRINT(rel_cap);
			st_cap(cr[j].dst + comp->base, rel_cap);
			}
	}

	cvms[cid].base = encl_map.base;
	cvms[cid].top = (void *) ((unsigned long) base + size);
	cvms[cid].box_size = encl_map.size;
	cvms[cid].entry = encl_map.entry_point;
	cvms[cid].stack_size = (MAX_THREADS + 1) * STACK_SIZE; // last thread -- store for caps 

	cvms[cid].ret_from_mon = encl_map.ret_point;

	if (pthread_mutex_init(&cvms[cid].ct_lock, NULL) != 0) {
		printf("\n mutex init failed\n");
		return 1;
	}

//	printf("cvms.base = %p, cvms.box_size = %lx\n", cvms[cid].base, cvms[cid].box_size);

	void *addr = (void *)((unsigned long) cvms[cid].top - cvms[cid].stack_size);
	void *addr_ret = mmap(addr, cvms[cid].stack_size, PROT_READ | PROT_WRITE , MAP_PRIVATE | MAP_FIXED | MAP_ANONYMOUS, -1, 0);
	if (addr_ret == MAP_FAILED){
		perror("mmap");
		return 1;
	} else
		printf("[cVM STACKs] = [%p -- %lx]\n", addr_ret, (unsigned long) addr_ret + (cvms[cid].stack_size));

	cvms[cid].stack = addr_ret;

	memset(cvms[cid].stack, 0, cvms[cid].stack_size);

	place_canaries(addr, cvms[cid].stack_size, 0xabbacaca);
	check_canaries(addr, cvms[cid].stack_size, 0xabbacaca);

	cvms[cid].cmp_begin = cmp_begin;
	cvms[cid].cmp_end = cmp_end;

#if 0
	cvms[cid].fd = create_console(cid);
#else
	cvms[cid].fd = STDOUT_FILENO;
#endif
	if(disk)
		strncpy(cvms[cid].disk_image, disk, sizeof(cvms[cid].disk_image));

	struct c_thread *ct = cvms[cid].threads;
////////////////////
	for(int i = 0; i < MAX_THREADS; i++) {
		ct[i].id = -1;
		ct[i].sbox = &cvms[cid];
	}

	extern void tp_write();

	ct[0].id = 0;
	ct[0].func = encl_map.entry_point;
	ct[0].cb_in = cb_in;
	ct[0].cb_out = cb_out;
	ct[0].stack_size = STACK_SIZE;
	ct[0].stack = (void *)((unsigned long)cvms[cid].top - STACK_SIZE);
	ct[0].arg = NULL;
	ct[0].sbox = &cvms[cid];

	ct[0].argc = argc;
	ct[0].argv = argv;

	ret = pthread_attr_init(&ct[0].tattr);
	if(ret != 0) {
		perror("attr init");printf("ret = %d\n", ret); while(1);
	}

	ret = pthread_attr_setstack(&ct[0].tattr, ct[0].stack, STACK_SIZE);
	if(ret != 0) {
		perror("pthread attr setstack");printf("ret = %d\n", ret); while(1);
	}

#ifdef __linux__
//	int from = (cid - 2) * 2;
//	int to  = ((cid - 2) + 1) * 2;
	int from = 0; int to = 4;
	CPU_ZERO(&cvms[cid].cpuset);
	for (int j = from; j < to; j++)
               CPU_SET(j, &cvms[cid].cpuset);

	ret  = pthread_attr_setaffinity_np(&ct[0].tattr, sizeof(cvms[cid].cpuset), &cvms[cid].cpuset);
	if (ret != 0) {
		perror("pthread set affinity");printf("ret = %d\n", ret);
	}

#endif
/*** gen caps ***/

//do we really need to save the sealcap?

	ct[0].sbox->box_caps.sealcap_size = sizeof(ct[0].sbox->box_caps.sealcap);
	if (sysctlbyname("security.cheri.sealcap", &ct[0].sbox->box_caps.sealcap, &ct[0].sbox->box_caps.sealcap_size, NULL, 0) < 0) {
		printf("sysctlbyname(security.cheri.sealcap)\n");while(1);
	}

	void * __capability ccap;
	if(cvms[cid].pure) 
		ccap = pure_codecap_create((void *) ct[0].sbox->cmp_begin, (void *) ct[0].sbox->cmp_end);
	else
		ccap = codecap_create((void *) ct[0].sbox->cmp_begin, (void *) ct[0].sbox->cmp_end);

	void * __capability dcap = datacap_create((void *) ct[0].sbox->cmp_begin, (void *) ct[0].sbox->cmp_end);
	ct[0].sbox->box_caps.dcap = dcap;

	ccap = cheri_setaddress(ccap, (unsigned long) (ct[0].func) + (unsigned long)(ct[0].sbox->base));

	ct[0].sbox->box_caps.sealed_datacap = cheri_seal(dcap, ct[0].sbox->box_caps.sealcap);
	ct[0].sbox->box_caps.sealed_codecap = cheri_seal(ccap, ct[0].sbox->box_caps.sealcap);

	//probe capabilitites for syscall/hostcall. 
	extern 	host_syscall_handler_prb(char *name, void *, void *, void *);
	if(cb_out == NULL) {
		printf("callback_out is empty, use default 'monitor'\n");
		cb_out = "monitor";
	}
	host_syscall_handler_prb(cb_out, &ct[0].sbox->box_caps.sealed_codecapt, &ct[0].sbox->box_caps.sealed_datacapt, &ct[0].sbox->box_caps.sealed_codecapt2);

	//generate capabilitites for ret_from_mon. TODO: we should make them public and our syscall/hostcall should fetch them
	//todo: we need something better than comp_to_mon_force
	ccap = cheri_setaddress(ccap, comp_to_mon_force(ct[0].sbox->ret_from_mon + ct[0].sbox->base - ct[0].sbox->cmp_begin, (unsigned long) ct[0].sbox) ); //here should be base but not cmp_begin. 
	ct[0].sbox->box_caps.sealed_ret_from_mon = cheri_seal(ccap, ct[0].sbox->box_caps.sealcap);

	//if we have syscall handler, we should publish it. TODO: let's init thread pubs this handler?
	if(encl_map.syscall_handler != 0) {
		printf("ACHTUNG: '%s' has syscall handler 'syscall_handler' at %p\n", libos, encl_map.syscall_handler);
		void * __capability syscall_pcc_cap = cheri_setaddress(ccap, (unsigned long) comp_to_mon_force(encl_map.syscall_handler + ct[0].sbox->base - ct[0].sbox->cmp_begin, (unsigned long) ct[0].sbox));
		void * __capability sealed_syscall_pcc_cap = cheri_seal(syscall_pcc_cap, ct[0].sbox->box_caps.sealcap);

		host_syscall_handler_adv(libos, sealed_syscall_pcc_cap, ct[0].sbox->box_caps.sealed_datacap);
	}

	return 0;
}

pthread_t run_cvm(int cid) {
	struct c_thread *ct = cvms[cid].threads;

	int ret = pthread_create(&ct[0].tid, &ct[0].tattr, init_thread, &ct[0]);
	if(ret != 0) {
		perror("pthread create");printf("ret = %d\n", ret);
	}

	return ct[0].tid;
}

int main(int argc, char *argv[]) {
//	printf("hello world %d %s\n", argc, argv[1]);

	char *disk_img = "./disk.img";
	char *yaml_cfg = 0;
	char *runtime_so = "libcarrie.so";

	int skip_argc = 1;
	for (++argv; *argv; ++argv)
	{
		if (strcmp("-h", *argv) == 0 || strcmp("--help", *argv) == 0)
		{
			printf("CARRIE -- a virtualisation platform for CHERI\n\t <monitor> [-hdt] --args /path/to/app [app args] \n");
			printf("\t-h --help\tshow this help and exit\n");
			printf("\t-d --disk\tpath to disk image. Default is %s\n", disk_img);
			printf("\t-r --runtime\tpath to runtime so. Default is %s\n", runtime_so);
			printf("\t-y --yaml\tpath to yaml config. Default is %s\n", yaml_cfg);
			printf("\t-c --debug_calls\t trace hostcalls at the host side, default is %d\n", debug_calls);
			printf("\t-t --timer\tenable oneshot timer threads, default: %d\n", timers);
			exit(0);
		}
		else if (strcmp("-y", *argv) == 0 || strcmp("--yaml", *argv) == 0)
		{
			yaml_cfg = *++argv;
			printf("Using yaml.cfg = %s\n", yaml_cfg);
			break;
		}
		else if (strcmp("-d", *argv) == 0 || strcmp("--disk", *argv) == 0)
		{
		  skip_argc+=2;
			disk_img = *++argv;
		}
		else if (strcmp("-t", *argv) == 0 || strcmp("--timer", *argv) == 0)
		{
		  skip_argc+=2;
			timers = atoi(*++argv);
		}
		else if (strcmp("-c", *argv) == 0 || strcmp("--debug_calls", *argv) == 0)
		{
		  skip_argc+=2;
			debug_calls = atoi(*++argv);
		}
		else if (strcmp("-a", *argv) == 0 || strcmp("--args", *argv) == 0)
		{

			  break; //argv now points to the beginning of args
		}
	}

	if (pthread_mutex_init(&print_lock, NULL) != 0) {
		printf("\n mutex init failed\n");
		return 1;
	}


	setup_sig();

/////////////////
	memset(cvms, 0, sizeof(cvms));
	init_cap_files_store();
	init_cbs();
/*** 		we generate and seal intravisor caps. cVMs use them later as hostcall/syscall handler ***/
	extern void tp_write();
	extern void ret_from_cinv2();

	void *__capability ddc_cap = cheri_getdefault();
	void *__capability pcc_cap = cheri_getpcc();
	void *__capability pcc_cap2 = cheri_getpcc();
	pcc_cap = cheri_setaddress(pcc_cap, (unsigned long) tp_write);

//	printf("ret_from_cinv2 = %ld\n", ret_from_cinv2);
	pcc_cap2 = cheri_setaddress(pcc_cap2, (unsigned long) ret_from_cinv2);

	void * __capability sealcap;
	size_t sealcap_size;

	sealcap_size = sizeof(sealcap);
	if (sysctlbyname("security.cheri.sealcap", &sealcap, &sealcap_size, NULL, 0) < 0) {
		printf("sysctlbyname(security.cheri.sealcap)\n");while(1);
	}

	void * __capability sealed_pcc = cheri_seal(pcc_cap, sealcap);
	void * __capability sealed_pcc2 = cheri_seal(pcc_cap2, sealcap);
	void * __capability sealed_ddc = cheri_seal(ddc_cap, sealcap);

	extern host_syscall_handler_adv(char *, void * __capability pcc, void * __capability ddc, void * __capability pcc2);
	host_syscall_handler_adv("monitor", sealed_pcc, sealed_ddc, sealed_pcc2);


//at this stage, cvmss have fixe size and should begin at from X*0x10000000. This is used
//for identification of box ID and threads ID. In the future, this should be replaced 
// by something more smart. So far compartment ID are not implemented in HW, so, maybe hashtable

	struct cmp_s comp;

	if(yaml_cfg) {
		struct parser_state *state = run_yaml_scenario(yaml_cfg);
		if(state == 0) {
			printf("yaml is corrupted, die\n"); exit(1);
		}

		for (struct capfile *f = state->clist; f; f = f->next) {
//			printf("capfile: name=%s, data='%s', size=0x%lx, addr=0x%lx \n", f->name, f->data, f->size, f->addr);
			if(f->addr) {
				printf("capfiles with pre-defined addresses are not supported\n");
			}

			void *ptr = malloc (f->size);
			if(!ptr) {
				printf("cannot alloc %d bytes for %s key\n", f->size, f->name); continue;
			}

			memset(ptr, 0, f->size);

			//we support only text here
			if(f->data) {
				snprintf(ptr, f->size, "%s", f->data);
			}

			host_cap_file_adv(ptr, f->size, f->name);
		}

		for (struct cvm *f = state->flist; f; f = f->next) {
		printf("***************** Deploy '%s' ***************\n", f->name);
			printf("BUILDING cvm: name=%s, disk=%s, runtime=%s, net=%s, args='%s', base=0x%lx, size=0x%lx, begin=0x%lx, end=0x%lx, cb_in = '%s', cb_out = '%s' wait = %ds\n", f->name, f->disk, f->runtime, f->net, f->args, f->isol.base, f->isol.size, f->isol.begin, f->isol.end, f->cb_in, f->cb_out, f->wait);

			enum { kMaxArgs = 16 };
			int c_argc = 0;
			long *c_argv = malloc(kMaxArgs*sizeof(long));

			char *p2 = strtok(f->args, " ");
			while (p2 && c_argc < kMaxArgs-1) {
				c_argv[c_argc++] = p2;
				p2 = strtok(0, " ");
			}
			c_argv[c_argc] = 0;

			comp.base = f->isol.base;		/* base addr */
			comp.size = f->isol.size;		/* size */
			comp.begin = f->isol.begin;		/* cmp_begin */
			comp.end = f->isol.end;			/* cmp_end  */

//todo: sanitise base addresses, check cvms/sbox max number
			build_cvm(f->isol.base / 0x10000000, //so far it is the best I can offer. 
					&comp,
				    f->runtime, 	/* libOS+init */
				    f->disk,		/* user disk */
				    c_argc,
				    c_argv,
					f->cb_out,
					f->cb_in
				);
		}

		printf("***************** Link Inner<-->Outer ***************\n");
		for (struct cvm *f = state->flist; f; f = f->next) {
			if(f->cb_in) {
				for (struct cvm *n = state->flist; n; n = n->next) {
//todo: instead of runtime name we should use name. here in all other relevant places
					if (strcmp(f->cb_in, n->runtime) == 0) {
						cvms[f->isol.base / 0x10000000].inner=&cvms[n->isol.base / 0x10000000];
						printf("%s[%d] is inner for %s[%d]\n",  cvms[f->isol.base / 0x10000000].threads[0].cb_in, n->isol.base / 0x10000000, 
																f->runtime, f->isol.base / 0x10000000);
					}
				}
			}
		}

		printf("***************** ALL cVMs loaded ***************\n");
			void *cret;
			pthread_t tid;
		for (struct cvm *f = state->flist; f; f = f->next) {
			tid = run_cvm(f->isol.base / 0x10000000);

			if(f->wait == -1) {
				pthread_join(tid, &cret);
//				printf("join returned\n");
			}
			else
				sleep(f->wait);
		}

		//wait completion
		for (int i = 0; i < MAX_CVMS; i++) {
			struct c_thread *ct = cvms[i].threads;
			pthread_join(ct[0].tid, &cret);
		}

	} else {

#if 1
			comp.base = 0x20000000;		/* base addr */
			comp.size = 0x10000000;		/* size */
#ifdef SIM
			comp.begin = 0x0;		/* cmp_begin */
#else
			comp.begin = 0x10000000;		/* cmp_begin */
#endif
			comp.end = 0x30000000;		/* cmp_end  */


			build_cvm( 2,			/* box id */
					&comp,
				    runtime_so, 	/* libOS+init */
				    disk_img,		/* user disk */
				    argc - skip_argc,
				    argv,
					"monitor",		/* CB_out */
					0 				/* CB_IN */
				);

		pthread_t tid = run_cvm(2);

		void *cret;
		pthread_join(tid, &cret);

#endif
	}
}
