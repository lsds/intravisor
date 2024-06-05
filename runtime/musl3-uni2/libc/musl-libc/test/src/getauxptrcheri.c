#include <sys/auxv.h>
#include <stdio.h>

#include "cheri_test_helpers.h"

#define RW_PERMS    (READ_CAP_PERMS | WRITE_CAP_PERMS | ROOT_CAP_PERMS)
#define RX_PERMS    (READ_CAP_PERMS | EXEC_CAP_PERMS | ROOT_CAP_PERMS)
#if defined(__CHERI_CAP_PERMISSION_GLOBAL__) && defined(__ARM_CAP_PERMISSION_COMPARTMENT_ID__)
#define CMPT_ID_PERMS    (__CHERI_CAP_PERMISSION_GLOBAL__ | __ARM_CAP_PERMISSION_COMPARTMENT_ID__)
#endif

static int check(void *cap, uint64_t req_perms, const char name[]);

int main (void) {

	uint64_t items[] = {
		AT_CHERI_EXEC_RW_CAP,
		AT_CHERI_EXEC_RX_CAP,
#ifdef DYNAMIC
		AT_CHERI_INTERP_RW_CAP,
		AT_CHERI_INTERP_RX_CAP,
#endif
		AT_CHERI_STACK_CAP,
		AT_CHERI_SEAL_CAP,
#ifdef CMPT_ID_PERMS
		AT_CHERI_CID_CAP
#endif
	};

	uint64_t req_perms[] = {
#ifdef __ARM_CAP_PERMISSION_BRANCH_SEALED_PAIR__
		__ARM_CAP_PERMISSION_BRANCH_SEALED_PAIR__ |
#endif
		RW_PERMS,
#ifdef __ARM_CAP_PERMISSION_BRANCH_SEALED_PAIR__
		__ARM_CAP_PERMISSION_BRANCH_SEALED_PAIR__ |
#endif
		RX_PERMS,
#ifdef DYNAMIC
#ifdef __ARM_CAP_PERMISSION_BRANCH_SEALED_PAIR__
		__ARM_CAP_PERMISSION_BRANCH_SEALED_PAIR__ |
#endif
		RW_PERMS,
#ifdef __ARM_CAP_PERMISSION_BRANCH_SEALED_PAIR__
		__ARM_CAP_PERMISSION_BRANCH_SEALED_PAIR__ |
#endif
		RX_PERMS,
#endif
		RW_PERMS,
		SEAL_CAP_PERMS,
#ifdef CMPT_ID_PERMS
		CMPT_ID_PERMS
#endif
	};

	const char* names[] = {
		"AT_CHERI_EXEC_RW_CAP",
		"AT_CHERI_EXEC_RX_CAP",
#ifdef DYNAMIC
		"AT_CHERI_INTERP_RW_CAP",
		"AT_CHERI_INTERP_RX_CAP",
#endif
		"AT_CHERI_STACK_CAP",
		"AT_CHERI_SEAL_CAP",
#ifdef CMPT_ID_PERMS
		"AT_CHERI_CID_CAP"
#endif
	};

	int n = sizeof(items) / sizeof(uint64_t);

	int success = 1;
	for (int k = 0; k < n; k++) {
		void *cap = getauxptr(items[k]);
		if (check(cap, req_perms[k], names[k])) {
			printf("root cap %s is not correct\n", names[k]);
			success = 0;
		}
	}

	return success ? 0 : 1;
}

static int check(void *cap, uint64_t req_perms, const char name[])
{
	if (!__builtin_cheri_tag_get(cap)) {
		printf("tag is not set for %s: %#p\n", name, cap);
		return 1;
	}
	uint64_t actual = __builtin_cheri_perms_get(cap);
	if (actual != req_perms) {
		char __perms_buffer1[19];
		char __perms_buffer2[19];
		printf("%s perms: actual: %s required: %s\n",
			name,
			__print_perms(actual, __perms_buffer1),
			__print_perms(req_perms, __perms_buffer2));
		return 2;
	}
	if (__builtin_cheri_sealed_get(cap)) {
		printf("sealed capability %s: %#p\n", name, cap);
		return 3;
	}
	return 0;
}
