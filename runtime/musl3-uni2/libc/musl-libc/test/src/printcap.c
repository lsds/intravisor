#include <stdio.h>
#include <stdint.h>

static int test_cap_null()
{
	int n = printf("%#p\n", NULL);
	if(n < 0) return 1;

	int m =  printf("%#lp\n", NULL);
	if(m < 0) return 2;
	
	return 0;
}

static int test_cap_null_derived()
{
	void *cap = __builtin_cheri_offset_set(NULL, 42);
	int n = printf("%#p\n", cap);
	if(n < 0) return 1;

	int m = printf("%#lp\n", cap);
	if(m < 0) return 2;

	return 0;
}

static int test_csp()
{
	void *csp = __builtin_cheri_stack_get();
	int n = printf("%#p\n", csp);
	if(n < 0) return 1;

	int m = printf("%#lp\n", csp);
	if(m < 0) return 2;

	return 0;
}

static int test_cap_max()
{
	/* We make _almost_ cap max because we can't forge tag for it */
	uint64_t hi = 0xffffc00000010005ul;
	void *max = __builtin_cheri_copy_to_high(NULL, hi);
	int n = printf("%#p\n", max);
	if(n < 0) return 1;

	int m = printf("%#lp\n", max);
	if(m < 0) return 2;

	return 0;
}

static int test_cap_sealed()
{
	void *fun;
#if defined(__CHERI_PURE_CAPABILITY__)
	__asm__ volatile ("adrp    %0, test_cap_sealed" : "+C"(fun));
	__asm__ volatile ("add     %0, %0, :lo12:test_cap_sealed" : "+C"(fun));
	__asm__ volatile ("seal %0, %0, LPB" : "+C"(fun));
#else
	// This is not LPB but RB.
	fun = (void*)__builtin_cheri_seal_entry(fun);
#endif
	int n = printf("%#p\n", fun);
	if(n < 0) return 1;

	int m = printf("%#lp\n", fun);
	if(m < 0) return 2;

	return 0;
}

static int test_cap_sentry()
{
	int n = printf("%#p\n", (void *)test_cap_sentry);
	if(n < 0) return 1;

	int m = printf("%#lp\n", (void *)test_cap_sentry);
	if(m < 0) return 2;
	
	return 0;
}

static int test_cap_sealed_invalid()
{
	void *fun = (void *)test_cap_sealed;
	fun = __builtin_cheri_tag_clear(fun);
#if defined(__CHERI_PURE_CAPABILITY__)
	__asm__ volatile ("seal %0, %0, LPB" : "+C"(fun));
#else
	// This is not LPB but RB.
	fun = (void*)__builtin_cheri_seal_entry(fun);
#endif
	int n = printf("%#p\n", fun);
	if(n < 0) return 1;

	int m = printf("%#lp\n", fun);
	if(m < 0) return 2;

	return 0;	
}

int main (int argc, char *argv[])
{
	switch (argv[1][0]) {
	case '0': return test_cap_null();
	case '1': return test_csp();
	case '2': return test_cap_max();
	case '3': return test_cap_sealed();
	case '4': return test_cap_sentry();
	case '5': return test_cap_sealed_invalid();
	case '6': return test_cap_null_derived();
	}
	return 1;
}
