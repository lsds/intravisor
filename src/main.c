//indent -npro -kr -i8 -ts8 -sob -l200 -ss -cp1 -brf -nsaf -nsai -nsaw -cs

#include "monitor.h"
#include <sys/types.h>
#if defined(arm_sim) || defined(x86_sim)
//actually it is about linux vs freebsd
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/resource.h>
#else
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/vmmeter.h>
#include <sys/limits.h>
#include <vm/vm_param.h>
#include <sys/resource.h>
#endif
struct s_box cvms[MAX_CVMS];

//default config

int timers = 0;
int debug_calls = 0;
//

pthread_mutex_t print_lock;

#define DEBUG 1

void *init_thread(void *arg) {

	struct c_thread *me = (struct c_thread *) arg;
	void *sp_read = me->stack + me->stack_size;	//getSP();
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
//      snprintf(env5, 128, "_PYTHON_SYSCONFIGDATA_NAME=_sysconfigdata");

	me->m_tp = getTP();
	me->c_tp = (__cheri_tocap void *__capability) (me->stack + 4096);

	char *cenv = (char *) (sp_read - 4096 * 3);	//originally, here was *2, but networking corrupts this memory
	volatile unsigned long *sp = (sp_read - 4096 * 4);	//I don't know why, but without volatile sp gets some wrong value after initing CENV in -O2

	printf("target SP = %lx, old TP = %lx sp_read = %p, me->stacl = %p, getSP()=%p, me->c_tp = %p %lx\n", sp, getTP(), sp_read, me->stack, getSP(), me->c_tp, me->c_tp);
	int cenv_size = 0;
	sp[0] = me->argc;
#ifndef MODE_PURE
	sp[1] = (unsigned long) (mon_to_comp(argv1, me->sbox));
#else
	sp[1] = 0xaa;
	sp[2] = (unsigned long) (mon_to_comp(argv1, me->sbox));
	sp[3] = 0xbb;
	int shift = 4;
#endif
	int i;
	for(i = 1; i < me->argc; i++) {
		printf("[%d] '%s'\n", i, me->argv[i]);

		int tmp_add = snprintf(&cenv[cenv_size], 128, "%s\0", me->argv[i]);
		if(cenv_size + tmp_add > 4096) {
			printf("need more space for args on the stack, die\n");
			while(1) ;
		}
#ifndef MODE_PURE
		sp[i + 1] = (unsigned long) (mon_to_comp(&cenv[cenv_size], me->sbox));
		printf("sp[i+1] = '%s'\n", (char *) (comp_to_mon(sp[i + 1], me->sbox)));
#else
		sp[shift + 2 * (i - 1)] = (unsigned long) (mon_to_comp(&cenv[cenv_size], me->sbox));
		sp[shift + 2 * (i - 1) + 1] = 0xcc + i - shift;
#endif
		cenv_size += tmp_add + 1;
	}
#ifndef MODE_PURE
	sp[i + 1] = 0;		//terminator
	int ienv = i + 2;
#if DEBUG
	printf("&env0 = %p, &env1=%p\n", &sp[ienv], &sp[ienv + 1]);
#endif
	sp[ienv++] = mon_to_comp(lc1, me->sbox);
	sp[ienv++] = mon_to_comp(env1, me->sbox);
	sp[ienv++] = mon_to_comp(env2, me->sbox);
	sp[ienv++] = mon_to_comp(env3, me->sbox);
	sp[ienv++] = mon_to_comp(env4, me->sbox);
	sp[ienv++] = mon_to_comp(env5, me->sbox);
	sp[ienv++] = 0;
#else
	sp[shift + i] = 0;	//terminator
	sp[shift + i + 1] = 0;	//terminator
	int ienv = shift + i + 2;
#if DEBUG
	printf("&env0 = %p, &env2=%p\n", &sp[ienv], &sp[ienv + 2]);
#endif
	sp[ienv++] = 0;
	sp[ienv++] = 0;
#endif

	size_t *auxv = &sp[ienv];

#if LKL
	if(strlen(me->sbox->disk_image)) {
		me->sbox->lkl_disk.fd = open(me->sbox->disk_image, O_RDWR);
		if(me->sbox->lkl_disk.fd < 0) {
			printf("cannot open disk '%s'\n", me->sbox->disk_image);
			while(1) ;
		}
	} else
		me->sbox->lkl_disk.fd = -1;

	me->sbox->lkl_disk.ops = &lkl_dev_blk_ops;
#endif

//      printf("LOADER: argv = %lx, envp = %lx(expected %lx), auxv = %lx \n", &sp[1], &sp[4], &sp[1 + 1 + sp[0]],auxv);
//      printf("LOADER: argv = %s, envp = %s, \n", sp[1], sp[4]);
#ifndef MODE_PURE
	auxv[0] = AT_BASE;
	auxv[1] = (unsigned long) me->sbox->base;
	auxv[2] = AT_ENTRY;
	auxv[3] = (unsigned long) me->func;
	auxv[4] = AT_PHDR;
	auxv[5] = mon_to_comp(me->sbox->base, me->sbox) + 0x40;
	auxv[6] = AT_PAGESZ;
	auxv[7] = 4096;
	auxv[8] = AT_IGNORE;
	auxv[9] = -1;
	int aid = 10;
	auxv[aid++] = AT_CLKTCK;
	auxv[aid++] = 100;
	auxv[aid++] = AT_HWCAP;
	auxv[aid++] = 0;
	auxv[aid++] = AT_EGID;
	auxv[aid++] = 0;
	auxv[aid++] = AT_EUID;
	auxv[aid++] = 0;
	auxv[aid++] = AT_GID;
	auxv[aid++] = 0;
	auxv[aid++] = AT_SECURE;
	auxv[aid++] = 0;
//    auxv[aid++] = AT_UID;             auxv[aid++] = -1;
	auxv[aid++] = AT_UID;
	auxv[aid++] = mon_to_comp(me->sbox->top - me->sbox->stack_size + 0x1000, me->sbox);	//so, in ABIv1 we need somehow to pass the location of local_store-vars into cVM
	auxv[aid++] = AT_RANDOM;
	auxv[aid++] = 0;
	auxv[aid++] = AT_NULL;
	auxv[aid++] = 0;
#else
	int aid = 0;
	auxv[aid++] = AT_BASE;
	auxv[aid++] = 0;
	void *__capability bcap = pure_codecap_create((void *) me->sbox->base, me->sbox->base + CVM_MAX_SIZE, me->sbox->clean_room);
	bcap = cheri_setaddress(bcap, me->sbox->base);

//TODO: there is a problem with aligment of auxv, which depends on the number of arguments
	st_cap(&auxv[aid++], bcap);
	aid++;
	auxv[aid++] = AT_PHDR;
	auxv[aid++] = 0;
	auxv[aid++] = mon_to_comp(me->sbox->base, me->sbox) + 0x40;
	auxv[aid++] = 0;
	auxv[aid++] = AT_NULL;
	auxv[aid++] = 0;
	auxv[aid++] = 0;
	auxv[aid++] = 0;

	auxv[aid++] = AT_NULL;
	auxv[aid++] = 0;
	auxv[aid++] = 0;
	auxv[aid++] = 0;

#endif

//    auxv[12]  = AT_EXECFN;    auxv[13]  = (size_t) "";
//    auxv[22] = AT_PLATFORM;   auxv[23] = (size_t) "x86_64";
//    auxv[28] = AT_RANDOM;     auxv[29] = getauxval(AT_RANDOM);
//      auxv[aid++] = AT_HWCAP;         auxv[aid++] = getauxval(AT_HWCAP);

//      if(mprotect(0x20103000, 4096, PROT_READ | PROT_EXEC) == -1) {
//              perror("mprotect");while(1);
//        }

/////////////////////////
	void *__capability sealed_codecap = me->sbox->box_caps.sealed_codecap;
	void *__capability sealed_datacap = me->sbox->box_caps.sealed_datacap;
	void *__capability dcap = me->sbox->box_caps.dcap;
	void *__capability sealed_codecapt = me->sbox->box_caps.sealed_codecapt;
	void *__capability sealed_codecapt2 = me->sbox->box_caps.sealed_codecapt2;
	void *__capability sealed_datacapt = me->sbox->box_caps.sealed_datacapt;
	void *__capability sealed_ret_from_mon = me->sbox->box_caps.sealed_ret_from_mon;
//note: .S has hardcoded offsets for caps, so in the case of sim we should double pointers aritficially
#if arm_sim
#define SHIFT	2
#else
#define SHIFT	1
#endif

	struct cinv_s {
		void *__capability caps[10 * SHIFT];
	} cinv_args;
//
	cinv_args.caps[0 * SHIFT] = sealed_codecap;
#if DEBUG
	printf("ca0: sealed COMP PCC\n");
	CHERI_CAP_PRINT(cinv_args.caps[0]);
#endif
//
	cinv_args.caps[1 * SHIFT] = sealed_datacap;
#if DEBUG
	printf("ca1: sealed COMP DDC\n");
	CHERI_CAP_PRINT(cinv_args.caps[1]);
#endif
//
	cinv_args.caps[2 * SHIFT] = dcap;
#if DEBUG
	printf("ca2: COMP DDC\n");
	CHERI_CAP_PRINT(cinv_args.caps[2]);
#endif
//
	cinv_args.caps[3 * SHIFT] = sealed_codecapt;
#if DEBUG
	printf("ca3: sealed HC PCC\n");
	CHERI_CAP_PRINT(cinv_args.caps[3]);
#endif
//
	cinv_args.caps[4 * SHIFT] = sealed_datacapt;
#if DEBUG
	printf("ca4: sealed HC DDC (mon.DDC)\n");
	CHERI_CAP_PRINT(cinv_args.caps[4]);
#endif
//
	cinv_args.caps[5 * SHIFT] = sealed_codecapt2;
#if DEBUG
	printf("ca5: sealed OCALL PCC \n");
	CHERI_CAP_PRINT(cinv_args.caps[5]);
#endif
//
	cinv_args.caps[6 * SHIFT] = sealed_ret_from_mon;
#if DEBUG
	printf("ca6: sealed ret from mon\n");
	CHERI_CAP_PRINT(cinv_args.caps[6]);
#endif
//

	if(me->sbox->pure) {

//TOD: this is very unreliable. we need to use precise bottom of the stack here
		void *__capability sp_cap = datacap_create((void *) me->stack, (unsigned long) me->stack + (unsigned long) me->stack_size, me->sbox->clean_room);
		sp_cap = cheri_setaddress(sp_cap, sp);

		cinv_args.caps[7] = sp_cap;
#if DEBUG
		printf("ca7: SP cap for purecap cVMs\n");
		CHERI_CAP_PRINT(cinv_args.caps[7]);
#endif
		void *__capability tp_cap = datacap_create((void *) ((unsigned long) me->c_tp), (unsigned long) me->c_tp + 4096, me->sbox->clean_room);
		tp_cap = cheri_setaddress(tp_cap, me->c_tp);

		cinv_args.caps[8] = tp_cap;
#if DEBUG
		printf("ca8: TP cap for purecap cVMs, me->c_tp = %lx\n", me->c_tp);
		CHERI_CAP_PRINT(cinv_args.caps[8]);
#endif
	} else {
#if arm_sim
//perhaps something is wrong here 
		cinv_args.caps[7 * SHIFT] = sp;
#if DEBUG
		printf("ca7: SP for hybrid cVMs\n");
		CHERI_CAP_PRINT(cinv_args.caps[7]);
#endif
#else
		sp = mon_to_comp(sp, me->sbox);
		me->c_tp = mon_to_comp(me->c_tp, me->sbox);
		cinv_args.caps[7 * SHIFT] = (void *__capability) sp;
#endif
	}

	if(me->sbox->use_scl) {

		char *sh_st = malloc(4096 * 20);
		if(!sh_st) {
			printf("cannot allocate memory for shadow store, die\n");
			while(1) ;
		}

		void *__capability sh_st_cap = datacap_create((void *) ((unsigned long) sh_st), (unsigned long) sh_st + 4096 * 10, me->sbox->clean_room);
		sh_st_cap = cheri_setaddress(sh_st_cap, sh_st);

		st_cap((unsigned long) me->c_tp + 128, sh_st_cap);

		struct cap_relocs_s *cr = cvms[2].cr;
		for(int j = 0; j < cvms[2].cap_relocs_size / sizeof(struct cap_relocs_s); j++) {
			void *__capability rel_cap;
			if(cr[j].perms != 0x8000000000000000ull) {
#if DEBUG
				printf("TODO: DST = %p, Base: %p, Length: %ld\n", cr[j].dst, cr[j].addr, cr[j].len);
				printf("COPYING OBJECTS: %lx, %lx, %ld\n", (unsigned long) sh_st + cr[j].addr, cvms[2].base + cr[j].addr, cr[j].len);
#endif
				memcpy((unsigned long) sh_st + cr[j].addr, cvms[2].base + cr[j].addr, cr[j].len);
			}
		}
//
	}

	extern void cinv(void *, void *);
	extern void cinv_sp(void *, void *, unsigned long);
#if DEBUG
	printf("HW: sp = %p, tp = %p, &cinv_args = %p\n", sp, me->c_tp, (void *) &cinv_args);
#endif
#ifndef MODE_PURE
	unsigned long *tp_args = comp_to_mon(me->c_tp, me->sbox);
#else
	unsigned long *tp_args = (__cheri_fromcap unsigned long *) (me->c_tp);
#endif
	tp_args[0] = me->sbox->top - me->sbox->stack_size + 0x1000;
	tp_args[1] = me->sbox->cid;
#if DEBUG
	printf("TP_ARGS: %lx, %lx, %lx\n", tp_args[0], tp_args[1], &tp_args[0]);
#endif
	printf("-----------------------------------------------\n");
//printf doesn't work anymore 

	cmv_ctp(me->c_tp);
	cinv(tp_args[0],	//local_cap_store
	     (void *) &cinv_args);

	printf("something is wrong, die at %d\n", __LINE__);
	while(1) ;
}

struct tmp_s {
	unsigned long a;
	unsigned long b;
};

int build_cvm(int cid, struct cmp_s *comp, char *libos, char *disk, int argc, char *argv[], char *cb_out, char *cb_in, int clean_room, int libvirt) {
	struct encl_map_info encl_map;
	void *base = comp->base;
//      printf("comp->base = %p\n", comp->base);
	unsigned long size = comp->size;
	unsigned long cmp_begin = comp->begin;
	unsigned long cmp_end = comp->end;

	memset(&encl_map, 0, sizeof(struct encl_map_info));

	load_elf(libos, base, &encl_map);
	if(encl_map.base < 0) {
		printf("Could not load '%s', die\n", libos);
		while(1) ;
	}

	if(encl_map.base != (unsigned long) base) {
		printf("mapped at wrong addres [%p]:[%p], die\n", encl_map.base, base);
		while(1) ;
	}
//todo: CVM_MAX_SIZE Should be passed to elf_loader to stop loading after reaching it, otherwaise big cVM can corrupt others
	if(encl_map.size > CVM_MAX_SIZE) {
		printf("actual cVM is bigger (%lx) than it could be (%lx), die\n", encl_map.size, CVM_MAX_SIZE);
		while(1) ;
	}
#if DEBUG
	printf("ELF BASE = %p, MAP SIZE = %lx, ENTRY = %p\n", encl_map.base, encl_map.size, encl_map.entry_point);
#endif
	int ret = 0;

	if(encl_map.entry_point == 0) {
		printf("entry_point is 0, runtime image is wrong/corrupted\n");
		while(1) ;
	}
#if DEBUG
	else
		printf("encl_map.entry = %p\n", encl_map.entry_point);
#endif
	if(encl_map.ret_point == 0) {
		printf("ret_from_monitor is 0, runtime image is wrong/corrupted\n");
		while(1) ;
	}
#if DEBUG
	else
		printf("encl_map.ret = %p\n", encl_map.ret_point);
#endif

#ifdef CONFIG_OPENSSL
	SHA256_Init(&cvms[cid].context);
	SHA256_Update(&cvms[cid].context, encl_map.base, encl_map.size);
	SHA256_Final(cvms[cid].hash, &cvms[cid].context);
#endif
	cvms[cid].clean_room = clean_room;
	cvms[cid].libvirt = libvirt;

#if riscv
	if(encl_map.cap_relocs) {
#if DEBUG
		printf("we have __cap_relocs, it is a purecap binary\n");
#endif
		cvms[cid].pure = 1;
//              cvms[cid].use_scl = 2; //todo, should be a list of SCL it uses
		cvms[cid].cr = (struct cap_relocs_s *) encl_map.cap_relocs;
		cvms[cid].cap_relocs_size = encl_map.cap_relocs_size;
		cvms[cid].cap_relocs = encl_map.cap_relocs;
		struct cap_relocs_s *cr = (struct cap_relocs_s *) encl_map.cap_relocs;
		for(int j = 0; j < encl_map.cap_relocs_size / sizeof(struct cap_relocs_s); j++) {
#if DEBUG
			printf("create cap: %p Base: %p Length: %ld Perms: %lx Unk = %ld\n", comp->base + cr[j].dst, cr[j].addr, cr[j].len, cr[j].perms, cr[j].unknown);
#endif
			void *__capability rel_cap;
			if(cr[j].perms == 0x8000000000000000ull) {
//                      printf("FUNCTION: \t");
// Function
				rel_cap = pure_codecap_create((void *) comp->base, (void *) comp->base + comp->size, cvms[cid].clean_room);
				rel_cap = cheri_setaddress(rel_cap, comp->base + cr[j].addr);
			} else if(cr[j].perms == 0x0ull) {
//                      printf("OBJECT: \t");
// Object
//TODO: we need something better
				if(cr[j].len == 0xabba) {
					printf("ACHTUNG: RISCV USES OUTDATED ABI\n");
					rel_cap =
					    datacap_create(comp->base + comp->size - (MAX_THREADS + 1) * STACK_SIZE + 0x1000, comp->base + comp->size - (MAX_THREADS + 1) * STACK_SIZE + 0x2000,
							   cvms[cid].clean_room);
				} else
					rel_cap = datacap_create((void *) comp->base + cr[j].addr, (void *) comp->base + cr[j].addr + cr[j].len, cvms[cid].clean_room);
			} else if(cr[j].perms == 0x4000000000000000ull) {
// Constant
//                      printf("CONSTANT: \t");
				rel_cap = datacap_create((void *) comp->base + cr[j].addr, (void *) comp->base + cr[j].addr + cr[j].len, cvms[cid].clean_room);
			} else {
				printf("Wrong Perm! %llx, die\n", cr[j].perms);
				while(1) ;
			}

//                      CHERI_CAP_PRINT(rel_cap);
			st_cap(cr[j].dst + comp->base, rel_cap);
		}
	}
#endif

#if arm
	if(encl_map.rela_dyn) {
#if DEBUG
		printf("we have rela_dyn, it is an ARM (might be purecap) binary\n");
#endif
		cvms[cid].pure = 1;
//              cvms[cid].use_scl = 2; //todo, should be a list of SCL it uses
		cvms[cid].rd = (struct rela_dyn_s *) encl_map.rela_dyn;
		cvms[cid].rela_dyn_size = encl_map.rela_dyn_size;
		cvms[cid].rela_dyn = encl_map.rela_dyn;
		struct rela_dyn_s *cr = (struct rela_dyn_s *) encl_map.rela_dyn;
		for(int j = 0; j < encl_map.rela_dyn_size / sizeof(struct rela_dyn_s); j++) {
/* from https://github.com/CTSRD-CHERI/cheribsd/blob/main/libexec/rtld-elf/aarch64/reloc.c:
 * Fragments consist of a 64-bit address followed by a 56-bit length and an
 * 8-bit permission field.
*/
//                      printf("%d: create cap: %lx %lx %lx\n", j, cr[j].dest,cr[j].addr,cr[j].unknown);
			struct tmp_s *ttt = (struct tmp_s *) (comp->base + (unsigned long) cr[j].dest);
			long len = ttt->b & ((1UL << 56) - 1);
			long perms = ttt->b >> 56;
//                      printf("test2: addr = %p, len - %lx perms = %lx\n", ttt->a, len, perms);
			void *__capability rel_cap;
#ifndef arm_sim
			if(perms == 0)
				continue;
			if(perms == 1) {
#else
			if(perms == 1 || perms == 0) {
#endif
//                              printf("CONSTANT: \t"); //should be RO
				rel_cap = datacap_create((void *) comp->base + ttt->a, (void *) comp->base + ttt->a + len, cvms[cid].clean_room);
			} else if(perms == 2) {
//                              printf("OBJECT: \t");
				rel_cap = datacap_create((void *) comp->base + ttt->a, (void *) comp->base + ttt->a + len, cvms[cid].clean_room);
			} else if(perms == 4) {
//                              printf("FUNCTION\t");
				rel_cap = pure_codecap_create((void *) comp->base, (void *) comp->base + comp->size, cvms[cid].clean_room);
				rel_cap = cheri_setaddress(rel_cap, comp->base + ttt->a + cr[j].unknown);
			}
//                      CHERI_CAP_PRINT(rel_cap);
			st_cap(cr[j].dest + comp->base, rel_cap);

		}
	}
#endif

	cvms[cid].base = encl_map.base;
	cvms[cid].top = (void *) ((unsigned long) base + size);
	cvms[cid].box_size = encl_map.size;
	cvms[cid].entry = encl_map.entry_point;
	cvms[cid].stack_size = (MAX_THREADS + 1) * STACK_SIZE;	// last thread -- store for caps 

	cvms[cid].ret_from_mon = encl_map.ret_point;
	cvms[cid].end_of_ro = encl_map.end_of_ro;
	cvms[cid].extra_load = encl_map.extra_load;
	cvms[cid].cid = cid;

#if arm
	cvms[cid].ret_from_mon |= 1;
#endif
	if(pthread_mutex_init(&cvms[cid].ct_lock, NULL) != 0) {
		printf("\n mutex init failed\n");
		return 1;
	}
//      printf("cvms.base = %p, cvms.box_size = %lx\n", cvms[cid].base, cvms[cid].box_size);

	void *addr = (void *) ((unsigned long) cvms[cid].top - cvms[cid].stack_size);
	void *addr_ret = mmap(addr, cvms[cid].stack_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_FIXED | MAP_ANONYMOUS, -1, 0);
	if(addr_ret == MAP_FAILED) {
		perror("mmap");
		return 1;
	}
#if DEBUG
	else
		printf("[cVM STACKs] = [%p -- %lx]\n", addr_ret, (unsigned long) addr_ret + (cvms[cid].stack_size));
#endif

#if arm_sim
	int r1 = madvise(encl_map.base, ((encl_map.size >> 12) + 0) << 12, MADV_MERGEABLE);
	int r2 = madvise(addr_ret, cvms[cid].stack_size, MADV_MERGEABLE);
//      int r2 = 0;
#if DEBUG
	printf("MADVISE: %d %d, CODE PAGES: %ld, STACK PAGES: %ld\n", r1, r2, ((encl_map.size >> 12) + 1), (cvms[cid].stack_size >> 12));
#endif
#endif

	cvms[cid].stack = addr_ret;

	memset(cvms[cid].stack, 0, cvms[cid].stack_size);

	place_canaries(addr, cvms[cid].stack_size, 0xabbacaca);
	check_canaries(addr, cvms[cid].stack_size, 0xabbacaca);

#ifdef EVAL
	printf("unmap some thread stacks to save space (%ld pages), \n", (MAX_THREADS - 1) * STACK_SIZE / 4096);
	munmap(cvms[cid].stack + STACK_SIZE, (MAX_THREADS - 1) * STACK_SIZE);
#endif

	cvms[cid].cmp_begin = cmp_begin;
	cvms[cid].cmp_end = cmp_end;

#if LIBVIRT
	cvms[cid].fd = create_console(cid);
#else
#if EVAL
	cvms[cid].fd = -1;
#else
	cvms[cid].fd = STDOUT_FILENO;
#endif
#endif
	if(disk)
		strncpy(cvms[cid].disk_image, disk, sizeof(cvms[cid].disk_image));

	unsigned long heap_start = ((((unsigned long) base + encl_map.size) >> 12) + 1) << 12;
	cvms[cid].heap = (void *) heap_start;
	cvms[cid].heap_size = addr_ret - heap_start;

	printf("Convrting free memory into cVM Heap: %lx -- %lx +%lx ( %f MB)\n", cvms[cid].heap, cvms[cid].heap + cvms[cid].heap_size, cvms[cid].heap_size, cvms[cid].heap_size / 1024.0 / 1024);

	void *heap_ret = mmap(cvms[cid].heap, cvms[cid].heap_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_FIXED | MAP_ANONYMOUS, -1, 0);
	if(heap_ret == MAP_FAILED) {
		perror("mmap");
		return 1;
	}

	if((encl_map.cvm_heap_begin != 0) && (encl_map.cvm_heap_size != 0)) {
		printf("cVM has cvm_heap_begin (%lx) and cvm_heap_size (%lx)\n", encl_map.cvm_heap_begin, encl_map.cvm_heap_size);
#if (defined riscv_hyb) || (defined arm_hyb)
		unsigned long to = cvms[cid].base + encl_map.cvm_heap_begin;
		unsigned long from = mon_to_comp(cvms[cid].heap, &cvms[cid]);
		memcpy(to, &from, sizeof(from));
		to = cvms[cid].base + encl_map.cvm_heap_size;
		from = cvms[cid].heap_size;
		memcpy(to, &from, sizeof(from));
#else
#if (defined riscv) || (defined arm)
		void *__capability heap_cap = datacap_create(cvms[cid].heap, cvms[cid].heap + cvms[cid].heap_size, cvms[cid].clean_room);
		st_cap(cvms[cid].base + encl_map.cvm_heap_begin, heap_cap);
		unsigned long to = cvms[cid].base + encl_map.cvm_heap_size;
		unsigned long from = cvms[cid].heap_size;
		memcpy(to, &from, sizeof(from));
#else
#warning this architecture doesnot setup heap inside cVM
#endif
#endif
	} else
		printf("cVM doesn't use heap or has a built-in one\n");

////////////////////
	struct c_thread *ct = cvms[cid].threads;
	for(int i = 0; i < MAX_THREADS; i++) {
		ct[i].id = -1;
		ct[i].sbox = &cvms[cid];
	}
	extern void hostcall_asm();
	ct[0].id = 0;
	ct[0].func = encl_map.entry_point;
	ct[0].cb_in = cb_in;
	ct[0].cb_out = cb_out;
	ct[0].stack_size = STACK_SIZE;
	ct[0].stack = (void *) ((unsigned long) cvms[cid].top - STACK_SIZE);
	ct[0].arg = NULL;
	ct[0].sbox = &cvms[cid];
	ct[0].argc = argc;
	ct[0].argv = argv;
	ret = pthread_attr_init(&ct[0].tattr);
	if(ret != 0) {
		perror("attr init");
		printf("ret = %d\n", ret);
		while(1) ;
	}
	ret = pthread_attr_setstack(&ct[0].tattr, ct[0].stack, STACK_SIZE);
	if(ret != 0) {
		perror("pthread attr setstack");
		printf("ret = %d\n", ret);
		while(1) ;
	}
#ifdef __linux__
//      int from = (cid - 2) * 2;
//      int to  = ((cid - 2) + 1) * 2;
	int from = 0;
	int to = 4;
	CPU_ZERO(&cvms[cid].cpuset);
	for(int j = from; j < to; j++)
		CPU_SET(j, &cvms[cid].cpuset);

	ret = pthread_attr_setaffinity_np(&ct[0].tattr, sizeof(cvms[cid].cpuset), &cvms[cid].cpuset);
	if(ret != 0) {
		perror("pthread set affinity");
		printf("ret = %d\n", ret);
	}
#endif
/*** gen caps ***/

//do we really need to save the sealcap?
	ct[0].sbox->box_caps.sealcap_size = sizeof(ct[0].sbox->box_caps.sealcap);
#if __FreeBSD__
	if(sysctlbyname("security.cheri.sealcap", &ct[0].sbox->box_caps.sealcap, &ct[0].sbox->box_caps.sealcap_size, NULL, 0) < 0) {
		printf("sysctlbyname(security.cheri.sealcap)\n");
		while(1) ;
	}
#else
	printf("sysctlbyname security.cheri.sealcap is not implemented in your OS\n");
#endif
	void *__capability ccap;
	if(cvms[cid].pure)
		ccap = pure_codecap_create((void *) ct[0].sbox->cmp_begin, (void *) ct[0].sbox->cmp_end, cvms[cid].clean_room);
	else
		ccap = codecap_create((void *) ct[0].sbox->cmp_begin, (void *) ct[0].sbox->cmp_end, cvms[cid].clean_room);
	void *__capability dcap = datacap_create((void *) ct[0].sbox->cmp_begin, (void *) ct[0].sbox->cmp_end, cvms[cid].clean_room);
	ct[0].sbox->box_caps.dcap = dcap;
	ccap = cheri_setaddress(ccap, (unsigned long) (ct[0].func) + (unsigned long) (ct[0].sbox->base));
	ct[0].sbox->box_caps.sealed_datacap = cheri_seal(dcap, ct[0].sbox->box_caps.sealcap);
	ct[0].sbox->box_caps.sealed_codecap = cheri_seal(ccap, ct[0].sbox->box_caps.sealcap);
	//probe capabilitites for syscall/hostcall. 
	extern host_syscall_handler_prb(char *name, void *, void *, void *);
	if(cb_out == NULL) {
		printf("callback_out is empty, use default 'monitor'\n");
		cb_out = "monitor";
	}
	host_syscall_handler_prb(cb_out, &ct[0].sbox->box_caps.sealed_codecapt, &ct[0].sbox->box_caps.sealed_datacapt, &ct[0].sbox->box_caps.sealed_codecapt2);

	//generate capabilitites for ret_from_mon. TODO: we should make them public and our syscall/hostcall should fetch them
	//todo: we need something better than comp_to_mon_force
	ccap = cheri_setaddress(ccap, (unsigned long) comp_to_mon_force((unsigned long) ct[0].sbox->ret_from_mon + (unsigned long) ct[0].sbox->base - (unsigned long) ct[0].sbox->cmp_begin, ct[0].sbox));	//here should be base but not cmp_begin. 
	ct[0].sbox->box_caps.sealed_ret_from_mon = cheri_seal(ccap, ct[0].sbox->box_caps.sealcap);
#if DEBUG
	printf("SEALED RET FROM MON %p %p\n", ct[0].sbox->box_caps.sealed_ret_from_mon, ccap);
#endif
	//if we have syscall handler, we should publish it. TODO: let's init thread pubs this handler?
	if(encl_map.syscall_handler != 0) {
#if DEBUG
		printf("ACHTUNG: '%s' has syscall handler 'syscall_handler' at %p\n", libos, encl_map.syscall_handler);
#endif
		void *__capability syscall_pcc_cap = cheri_setaddress(ccap, (unsigned long) comp_to_mon_force(encl_map.syscall_handler + ct[0].sbox->base - ct[0].sbox->cmp_begin, ct[0].sbox));
		void *__capability sealed_syscall_pcc_cap = cheri_seal(syscall_pcc_cap, ct[0].sbox->box_caps.sealcap);

		host_syscall_handler_adv(libos, sealed_syscall_pcc_cap, ct[0].sbox->box_caps.sealed_datacap);
	}

	return 0;
}

pthread_t run_cvm(int cid) {
	struct c_thread *ct = cvms[cid].threads;

	int ret = pthread_create(&ct[0].tid, &ct[0].tattr, init_thread, &ct[0]);
	if(ret != 0) {
		perror("pthread create");
		printf("ret = %d\n", ret);
	}

	return ct[0].tid;
}

int parse_and_spawn_yaml(char *yaml_cfg, char libvirt) {
	struct cmp_s comp;
	struct parser_state *state = run_yaml_scenario(yaml_cfg);
	if(state == 0) {
		printf("yaml is corrupted, die\n");
		exit(1);
	}

	for(struct capfile * f = state->clist; f; f = f->next) {
//                      printf("capfile: name=%s, data='%s', size=0x%lx, addr=0x%lx \n", f->name, f->data, f->size, f->addr);
		if(f->addr) {
			printf("capfiles with pre-defined addresses are not supported\n");
		}

		void *ptr = malloc(f->size);
		if(!ptr) {
			printf("cannot alloc %d bytes for %s key\n", f->size, f->name);
			continue;
		}

		memset(ptr, 0, f->size);

		//we support only text here
		if(f->data) {
			snprintf(ptr, f->size, "%s", f->data);
		}

		host_cap_file_adv(ptr, f->size, f->name);
	}

	for(struct cvm * f = state->flist; f; f = f->next) {
		printf("***************** [%d] Deploy '%s' ***************\n", f->isol.base / CVM_MAX_SIZE, f->name);
		printf
		    ("BUILDING cvm: name=%s, disk=%s, runtime=%s, net=%s, args='%s', base=0x%lx, size=0x%lx, begin=0x%lx, end=0x%lx, cb_in = '%s', cb_out = '%s' wait = %ds clean_room = %d, libvirt = %d\n",
		     f->name, f->disk, f->runtime, f->net, f->args, f->isol.base, f->isol.size, f->isol.begin, f->isol.end, f->cb_in, f->cb_out, f->wait, f->cr, f->lv);

		if(CVM_MAX_SIZE != f->isol.size) {
			printf("CVM_MAX_SIZE = %lx, requested = %lx, die\n", CVM_MAX_SIZE, f->isol.size);
			exit(1);
		} else {
			printf("requested cVM size matches CVM_MAX_SIZE (%lx)\n", CVM_MAX_SIZE);
		}

		enum { kMaxArgs = 16 };
		int c_argc = 0;
		long *c_argv = malloc(kMaxArgs * sizeof(long));

		char *p2 = strtok(f->args, " ");
		while(p2 && c_argc < kMaxArgs - 1) {
			c_argv[c_argc++] = p2;
			p2 = strtok(0, " ");
		}
		c_argv[c_argc] = 0;

		comp.base = f->isol.base;	/* base addr */
		comp.size = f->isol.size;	/* size */
		comp.begin = f->isol.begin;	/* cmp_begin */
		comp.end = f->isol.end;	/* cmp_end  */

//todo: sanitise base addresses, check cvms/sbox max number
		struct timeval start, end;
		gettimeofday(&start, NULL);

		int cid = f->isol.base / CVM_MAX_SIZE;
		build_cvm(cid,	//so far it is the best I can offer. 
			  &comp, f->runtime,	/* libOS+init */
			  f->disk,	/* user disk */
			  c_argc, (char **) c_argv, f->cb_out, f->cb_in, f->cr, f->lv);

		gettimeofday(&end, NULL);
		unsigned long now = (end.tv_sec * 1000ull) + (end.tv_usec / (1000ull));
		unsigned long then = (start.tv_sec * 1000ull) + (start.tv_usec / (1000ull));
		printf("Deploy %d in %f, ", cid, (now - then) / 1000.0);
#ifdef CONFIG_OPENSSL
		printf("SHA-256 Hash: ");
		for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
			printf("%02x", cvms[cid].hash[i]);
		}
		printf("\n");
#else
		printf("\n");
#endif
	}

	printf("***************** Link Inner<-->Outer ***************\n");
	for(struct cvm * f = state->flist; f; f = f->next) {
		if(f->cb_in) {
			for(struct cvm * n = state->flist; n; n = n->next) {
//todo: instead of runtime name we should use name. here in all other relevant places
				if(strcmp(f->cb_in, n->runtime) == 0) {
					cvms[f->isol.base / CVM_MAX_SIZE].inner = &cvms[n->isol.base / CVM_MAX_SIZE];
					printf("%s[%d] is inner for %s[%d]\n", cvms[f->isol.base / CVM_MAX_SIZE].threads[0].cb_in, n->isol.base / CVM_MAX_SIZE,
					       f->runtime, f->isol.base / CVM_MAX_SIZE);
				}
			}
		}
	}

	printf("***************** ALL cVMs loaded ***************\n");
	void *cret;
	pthread_t tid;
	for(struct cvm * f = state->flist; f; f = f->next) {
		tid = run_cvm(f->isol.base / CVM_MAX_SIZE);

		if(f->wait == -1) {
			pthread_join(tid, &cret);
//                              printf("join returned\n");
		} else
			sleep(f->wait);
	}

//in libvirt we don't wait the completion and simply return tid
	if(libvirt) {
		struct c_thread *ct = cvms[0].threads;
		return ct[0].tid;
	}
	//wait completion
	for(int i = 0; i < MAX_CVMS; i++) {
		struct c_thread *ct = cvms[i].threads;
		pthread_join(ct[0].tid, &cret);
	}
}

int prepare_parse_run_yaml(struct s_box *sbox, void *loc, int size) {
	printf("request for ppr yaml from %d\n", sbox->libvirt);
	if(!sbox->libvirt)
		return -1;

	time_t current_time;
	struct tm *time_info;
	char filename[30];
	FILE *file;

	// Get the current timestamp
	time(&current_time);
	time_info = localtime(&current_time);

	// Format the timestamp as a string
	strftime(filename, sizeof(filename), "/tmp/%Y%m%d%H%M%S.yaml", time_info);

//    snprintf(filename, sizeof(filename), "/1.yaml");

	// Create and open the file
	file = fopen(filename, "w");
	if(file == NULL) {
		printf("cannot create temp yaml file\n");
		while(1) ;
	}

	fwrite(loc, 1, size, file);
	fclose(file);

	return parse_and_spawn_yaml(filename, 1);
}

queue q, ready;
int once = 1;			//SCO

struct timeval start, end;

int main(int argc, char *argv[]) {
//      printf("hello world %d %s\n", argc, argv[1]);
#ifdef UNDERVISOR
	extern void *__capability under_tp;
	under_tp = getTP();
#endif

	gettimeofday(&start, NULL);

	char *disk_img = "./disk.img";
	char *yaml_cfg = 0;
	char *runtime_so = "libcarrie.so";

	char **argv_orig = argv;
	int argc_orig = argc;

	int skip_argc = 1;
	for(++argv; *argv; ++argv) {
		if(strcmp("-h", *argv) == 0 || strcmp("--help", *argv) == 0) {
			printf("Intravisor -- a virtualisation platform for CHERI\n\t <intravisor> [-hdt] --args /path/to/app [app args] \n");
			printf("\t-h --help\tshow this help and exit\n");
			printf("\t-d --disk\tpath to disk image. Default is %s\n", disk_img);
			printf("\t-r --runtime\tpath to runtime so. Default is %s\n", runtime_so);
			printf("\t-y --yaml\tpath to yaml config. Default is %s. Only this argument works!\n", yaml_cfg);
			printf("\t-c --debug_calls\t trace hostcalls at the host side, default is %d\n", debug_calls);
			printf("\t-t --timer\tenable oneshot timer threads, default: %d\n", timers);
			exit(0);
		} else if(strcmp("-y", *argv) == 0 || strcmp("--yaml", *argv) == 0) {
			yaml_cfg = *++argv;
			printf("Using yaml.cfg = %s\n", yaml_cfg);
			break;
		} else if(strcmp("-d", *argv) == 0 || strcmp("--disk", *argv) == 0) {
			skip_argc += 2;
			disk_img = *++argv;
		} else if(strcmp("-t", *argv) == 0 || strcmp("--timer", *argv) == 0) {
			skip_argc += 2;
			timers = atoi(*++argv);
		} else if(strcmp("-c", *argv) == 0 || strcmp("--debug_calls", *argv) == 0) {
			skip_argc += 2;
			debug_calls = atoi(*++argv);
		} else if(strcmp("-a", *argv) == 0 || strcmp("--args", *argv) == 0) {

			break;	//argv now points to the beginning of args
		}
	}

	if(pthread_mutex_init(&print_lock, NULL) != 0) {
		printf("\n mutex init failed\n");
		return 1;
	}
/////////////////
	memset(cvms, 0, sizeof(cvms));
	init_cap_files_store();
	init_cbs();
/*** 		we generate and seal intravisor caps. cVMs use them later as hostcall/syscall handler ***/
	extern void hostcall_asm();
	extern void ret_from_cinv2();

	void *__capability ddc_cap = cheri_getdefault();
	void *__capability pcc_cap = cheri_getpcc();
	void *__capability pcc_cap2 = cheri_getpcc();
	pcc_cap = cheri_setaddress(pcc_cap, (unsigned long) hostcall_asm);

//      printf("ret_from_cinv2 = %ld\n", ret_from_cinv2);
	pcc_cap2 = cheri_setaddress(pcc_cap2, (unsigned long) ret_from_cinv2);

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

	void *__capability sealed_pcc = cheri_seal(pcc_cap, sealcap);
	void *__capability sealed_pcc2 = cheri_seal(pcc_cap2, sealcap);
	void *__capability sealed_ddc = cheri_seal(ddc_cap, sealcap);

	extern host_syscall_handler_adv(char *, void *__capability pcc, void *__capability ddc, void *__capability pcc2);
	host_syscall_handler_adv("monitor", sealed_pcc, sealed_ddc, sealed_pcc2);

	if(yaml_cfg) {
		parse_and_spawn_yaml(yaml_cfg, 0);
	} else {
#if LIBVIRT
		extern int libvirt_main(int argc, char *argv[]);
		return libvirt_main(argc_orig, argv_orig);
#else
		printf("yaml config is required, config-less deployment is depricated, die\n");
		exit(1);
#endif
	}
}
