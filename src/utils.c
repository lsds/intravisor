#include "monitor.h"


unsigned long mon_to_comp(unsigned long addr, struct s_box *sbox)  {
	return (addr - (!sbox->pure)*sbox->cmp_begin);
}

unsigned long comp_to_mon(unsigned long addr, struct s_box *sbox) {
	return (addr + (!sbox->pure)*sbox->cmp_begin);
}

unsigned long comp_to_mon_force(unsigned long addr, struct s_box *sbox) {
	return (addr + sbox->cmp_begin);
}


#ifndef SIM
void * __capability codecap_create(void *sandbox_base, void *sandbox_end)
{
  void * __capability codecap;
  codecap = cheri_codeptrperm(sandbox_base, ((size_t)sandbox_end - (size_t)sandbox_base),
	  CHERI_PERM_GLOBAL | CHERI_PERM_LOAD | CHERI_PERM_STORE | CHERI_PERM_EXECUTE | CHERI_PERM_CCALL);

  return (codecap);
}

void * __capability pure_codecap_create(void *sandbox_base, void *sandbox_end)
{
  void * __capability codecap;
  codecap = cheri_codeptrperm(sandbox_base, ((size_t)sandbox_end - (size_t)sandbox_base),
	  CHERI_PERM_GLOBAL | CHERI_PERM_LOAD | CHERI_PERM_LOAD_CAP | CHERI_PERM_STORE | CHERI_PERM_EXECUTE | CHERI_PERM_CCALL);

  codecap = cheri_capmode(codecap);

  return (codecap);
}


void * __capability datacap_create(void *sandbox_base, void *sandbox_end)
{
  void * __capability datacap;

  datacap = cheri_ptrperm(sandbox_base,
      (size_t)sandbox_end - (size_t)sandbox_base,
      CHERI_PERM_GLOBAL | CHERI_PERM_LOAD | CHERI_PERM_STORE |
      CHERI_PERM_LOAD_CAP | 
// we remove these two permisions to avoid using of revoked caps
	  CHERI_PERM_STORE_CAP |
      CHERI_PERM_STORE_LOCAL_CAP | 
	  CHERI_PERM_CCALL);

  return (datacap);
}

#endif

void place_canaries(unsigned long *begin, long size, long magic) {
	for(int i = 0; i < size/STACK_SIZE; i++) {
		begin[i * STACK_SIZE / 8] = magic;
		if(i > 0) {
#ifndef NC
//			printf("mprotecting %p\n", &begin[i * STACK_SIZE / 8]);
#else
//			NCPRINT("mprotecting %p\n", &begin[i * STACK_SIZE / 8]);
#endif
			if(mprotect(&begin[i * STACK_SIZE / 8], 4096, PROT_READ) == -1) {
				perror("mprotect");while(1);
			  }
		}
	}
}

static char fbuf[1024];

void check_canaries(unsigned long *begin, long size, long magic) {
	for(int i = 0; i < size/STACK_SIZE; i++) {
		if(begin[i * STACK_SIZE / 8] != magic) {
//			printf("CORRUPTED CANARY %d, %lx %lx\n", i, begin[i * STACK_SIZE / 8], magic);
			snprintf(fbuf, 1024, "CORRUPTED CANARY thread %d, addr %p, read %lx, expected %lx\n", i, &begin[i * STACK_SIZE / 8], begin[i * STACK_SIZE / 8],magic);
			write(2, fbuf, 1024);
			while(1);
		}
	}

}


int create_console(int cid) {
	int fd;
	char *fifo[20];
	snprintf(fifo, 20, "/tmp/cf%d", cid);

	mkfifo(fifo, 0666);

	fd = open(fifo, O_WRONLY | O_NONBLOCK);

	printf("use #cat %s\n", fifo);

	return fd;
}

int host_reg_cap(void *ptr, long size, void *location) {
#ifndef SIM
//todo: internally, datacap_create default cap of monitor. it might be slightly better to use caps of the target isolation layer
	void * __capability dcap = datacap_create(ptr, (void *) ((unsigned long) ptr + size));
//	CHERI_CAP_PRINT(dcap);
#else
	void *dcap = ptr;
#endif

	st_cap(location, dcap);
}

int host_purge_cap(void *location) {
	memset(location, 0, 16);
}
