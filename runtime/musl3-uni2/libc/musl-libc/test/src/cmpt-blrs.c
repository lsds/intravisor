#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/auxv.h>
#include <sys/mman.h>
#include <errno.h>

extern void trampoline(void);

typedef struct
{
	void* code;
	void* data;
} cap_pair;

static void print_cap(void* cap, const char* name)
{
	char out[256] = {};
	strfcap(out, 256, "%v%B | %-64C | %-4s | %P", cap);
	printf("CAP %-32s: %s\n", name, out);
}

#define READ_PERMS (__CHERI_CAP_PERMISSION_PERMIT_LOAD__ | __CHERI_CAP_PERMISSION_PERMIT_LOAD_CAPABILITY__ | __ARM_CAP_PERMISSION_MUTABLE_LOAD__)
#define WRITE_PERMS (__CHERI_CAP_PERMISSION_PERMIT_STORE__ | __CHERI_CAP_PERMISSION_PERMIT_STORE_CAPABILITY__ | __CHERI_CAP_PERMISSION_PERMIT_STORE_LOCAL__)
#define EXEC_PERMS (__CHERI_CAP_PERMISSION_PERMIT_EXECUTE__ | __ARM_CAP_PERMISSION_EXECUTIVE__ | __CHERI_CAP_PERMISSION_ACCESS_SYSTEM_REGISTERS__)
#define BSP_PERM (__ARM_CAP_PERMISSION_BRANCH_SEALED_PAIR__)

#define PROTECTED_DATA_VALUE 53

static void unsealed_function(void* protected_capability)
{
	//Ensure the "root" capability is usable here
	//Do something with the capability
	if(__builtin_cheri_sealed_get(protected_capability))
	{
		printf("Failure: protected capability sealed in unsealed function\n");
		exit(1);
	}
	else 	printf("Success: protected capability unsealed in unsealed function\n");
	int protected_data = *(int*)protected_capability;
	printf("Protected Data Dereference: %d\n", protected_data);
	if(protected_data != PROTECTED_DATA_VALUE) exit(-1);
}

#define LABEL(name) \
".global " name " \n" \
".hidden " name "\n" \
".size " name ",16\n" \
".type " name ",%function\n" \
name ":\n"

__attribute__ ((naked))
static void transition(void* func, void* cap, void* target)
{
	__asm__ volatile
	(
		"sub csp, csp, #(64)\n"
		"stp c29, c30, [csp, #(0)]\n"
		"blrs c29, c0, c1\n"
		LABEL("trampoline")
		"mov c0, c29\n"
		"blr c2\n"
		"ldp c29, c30, [csp, #(0)]\n"
		"add csp, csp, #(64)\n"
		"ret\n"
	);
}

//Ideal API functions for using sealed capability pairs
// - create_sealed_capability_pair (create)
// - branch_to_sealed_capability_pair (use)

static void branch_to_sealed_capability_pair(const cap_pair* pair)
{
	transition(pair->code, pair->data, (void*)unsealed_function);
}

static cap_pair create_sealed_capability_pair(void* code, char* data, size_t data_size)
{
	const int page_size = getpagesize();

	cap_pair pair = {};
	const size_t seal_otype = 42;

	void* root_seal_cap = __builtin_cheri_offset_set(getauxptr(AT_CHERI_SEAL_CAP), seal_otype);
	void* root_rx_cap = getauxptr(AT_CHERI_EXEC_RX_CAP);

	print_cap(root_seal_cap, "Root Seal");
	print_cap(root_rx_cap, "Root RX");

	pair.code = __builtin_cheri_cap_from_pointer(root_rx_cap, __builtin_cheri_address_get(trampoline));
	pair.code = __builtin_cheri_address_set(pair.code, __builtin_cheri_base_get(trampoline));
	pair.code = __builtin_cheri_bounds_set_exact(pair.code, __builtin_cheri_length_get(trampoline));
	pair.code = __builtin_cheri_offset_set(pair.code, __builtin_cheri_offset_get(trampoline));
	pair.code = __builtin_cheri_seal(pair.code, root_seal_cap);

	//Note: perms_and below a temporary workaround while the Morello board's mmap implementation isn't
	//fully PCuABI compliant (returned capability has more permissions than it should, e.g. xE)
	pair.data = __builtin_cheri_perms_and(mmap(NULL, page_size, PROT_READ | PROT_WRITE | PROT_CAP_INVOKE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0), READ_PERMS | WRITE_PERMS | BSP_PERM);
	memcpy(pair.data, data, data_size);
	pair.data = __builtin_cheri_seal(pair.data, root_seal_cap);

	return pair;
}

int main(int argc, char** argv)
{
	int protection_candidate_data = PROTECTED_DATA_VALUE;
	char* protection_candidate = (char*)&protection_candidate_data;
	print_cap(protection_candidate, "Init Protection Candidate");

	cap_pair pair = create_sealed_capability_pair((void*)trampoline, protection_candidate, sizeof(protection_candidate_data));
	void* sealed_blrs_trampoline = pair.code;
	void* sealed_protection_candidate = pair.data;

	print_cap(pair.data, "Pair Protection Candidate");
	print_cap(pair.code, "Pair Trampoline");

	//Check cmpt_entry and cmpt_data permissions
	size_t trampoline_perms = __builtin_cheri_perms_get(sealed_blrs_trampoline);
	size_t trampoline_sealed = __builtin_cheri_sealed_get(sealed_blrs_trampoline);
	size_t trampoline_executable = trampoline_perms & __CHERI_CAP_PERMISSION_PERMIT_EXECUTE__;
	bool trampoline_valid = __builtin_cheri_tag_get(sealed_blrs_trampoline);

	size_t protection_candidate_perms = __builtin_cheri_perms_get(sealed_protection_candidate);
	size_t protection_candidate_sealed = __builtin_cheri_sealed_get(sealed_protection_candidate);
	size_t protection_candidate_readable = protection_candidate_perms & __CHERI_CAP_PERMISSION_PERMIT_LOAD__;
	size_t protection_candidate_writeable = protection_candidate_perms & __CHERI_CAP_PERMISSION_PERMIT_STORE__;
	bool protection_candidate_valid = __builtin_cheri_tag_get(sealed_blrs_trampoline);

	if(!(	trampoline_sealed 		&&
		trampoline_executable 		&&
		trampoline_valid		&&
		protection_candidate_sealed 	&&
		protection_candidate_readable 	&&
		protection_candidate_writeable	&&
		protection_candidate_valid
	)) return 2;

	branch_to_sealed_capability_pair(&pair);

	if(!(	trampoline_sealed 		&&
		trampoline_executable 		&&
		trampoline_valid		&&
		protection_candidate_sealed 	&&
		protection_candidate_readable 	&&
		protection_candidate_writeable	&&
		protection_candidate_valid
	)) return 2;

	printf("CMPT BLRS COMPLETE\n");

	return 0;
}
