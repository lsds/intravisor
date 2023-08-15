#define __capability	__attribute__(())
#define __cheri_tocap	__attribute__(())
#define __cheri_fromcap	__attribute__(())

static __inline__ void * getSP(void) {
    register void * sp asm("sp");
    asm ("" : "=r"(sp));
    return sp;
}

static __inline__ void * __capability getTP(void) {
    register void *tp;
#warning "not implemented"

    return tp;
}


static __inline__ long getT5(void) {
    register long t5 asm("r10");
    asm ("" : "=r"(t5));
    return t5;
}


static __inline__ void mv_sp(unsigned long sp) {
#warning "not implemented"
}

static __inline__ void cmv_ctp(void * tp) {
#warning "not implemented"
}

static __inline__ void cmv_csp(void * sp) {
#warning "not implemented"
}

static __inline__ unsigned long cheri_setaddress(unsigned long a, unsigned long b) {
	return b;
}

static __inline__ unsigned long cheri_seal(unsigned long a, unsigned long b) {
	return a;
}

static __inline__ unsigned long cheri_gettag(unsigned long a) {
	return 0;
}

static __inline__ unsigned long cheri_getsealed(unsigned long a) {
	return 0;
}

static __inline__ unsigned long cheri_getbase(unsigned long a) {
	return a;
}

static __inline__ unsigned long cheri_getlen(unsigned long a) {
	return 0;
}

static __inline__ unsigned long cheri_getoffset(unsigned long a) {
	return 0;
}

static __inline__ unsigned long cheri_getperm(unsigned long a) {
	return 0;
}

static __inline__ unsigned long cheri_gettype(unsigned long a) {
	return 0;
}


static __inline__ unsigned long codecap_create(unsigned long a, unsigned long b, int c)
{
	return a;
}

static __inline__ unsigned long pure_codecap_create(unsigned long a, unsigned long b, int c)
{
	return a;
}


static __inline__ unsigned long datacap_create(unsigned long a, unsigned long b, int c) {
	return a;
}

static __inline__ unsigned long  cheri_getpcc() {
	return 0;
}

static __inline__ unsigned long cheri_getdefault() {
	return 0;
}

