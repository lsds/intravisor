#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat"
#include <stdio.h>
#include <stdint.h>
#include <sys/auxv.h>
#include <cheriintrin.h>

int test_csp() {
	void *csp = __builtin_cheri_stack_get();
	int n = printf("%+#p\n", csp);
	if(n < 0) return 1;

	return 0;
}

int test_pcc() {
	void *pcc = cheri_pcc_get();
	int n = printf("%#+p\n", pcc);
	if (n < 0) return 1;

	return 0;
}

int test_local() {
	int x;
	int *p = &x;
	p = cheri_perms_clear(p, CHERI_PERM_GLOBAL);
	int n = printf("%+#p\n", (void *) p); 
	if (n < 0) return 1;

	return 0;
}

int test_sentry() {
	void *sentry = (void *)test_local;
	int m =  printf("%+#lp\n", sentry);
	if(m < 0) return 2;
	void *sentry_invalid = cheri_tag_clear(sentry);
	m =  printf("%+#lp\n", sentry_invalid);
	if(m < 0) return 2;
	void *sentry_invalid_local = cheri_perms_clear(sentry_invalid, CHERI_PERM_GLOBAL);
	m =  printf("%+#lp\n", sentry_invalid_local);
	if(m < 0) return 2;
	return 0;
}

int test_auxv() {
	void *entry = getauxptr(AT_CHERI_SEAL_CAP);
	int m =  printf("%+#lp\n", entry);
	if(m < 0) return 2;
	entry = getauxptr(AT_CHERI_CID_CAP);
	m =  printf("%+#lp\n", entry);
	if(m < 0) return 2;
	return 0;
}

int test_cap_null() {
	int n = printf("%+#p\n", NULL);
	if(n < 0) return 1;

	int m =  printf("%+#lp\n", NULL);
	if(m < 0) return 2;

	return 0;
}

int main (int argc, char **argv) {
	switch (argv[1][0]) {
	case '0':
		return test_csp();
	case '1':
		return test_pcc();
	case '2':
		return test_local();
	case '3':
		return test_sentry();
	case '4':
		return test_auxv();
	case '5':
		return test_cap_null();
	}

	return 1;
}

#pragma clang diagnostic pop
