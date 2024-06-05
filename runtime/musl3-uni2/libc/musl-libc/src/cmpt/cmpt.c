#ifdef __CHERI_PURE_CAPABILITY__
#include <sys/auxv.h>
#include <sys/mman.h>
#include <cap_perms.h>
#include <errno.h>
#include <string.h>
#include "libc.h"
#include "cmpt.h"

#define LABEL(name) \
".global " name " \n" \
".hidden " name "\n" \
".size " name ",16\n" \
".type " name ",%function\n" \
name ":\n"

typedef struct
{
	void* code;
	void* data;
	cmpt_target_t* target;
	void* map;
	size_t map_size;
	//NOTE: Change this size calculation if cmpt_data_t definition changes
	char __padding[sizeof(cmpt_t) - 4*sizeof(void*) - sizeof(size_t)];
} cmpt_data_t;

void trampoline_start(void);
void trampoline_end(void);

__attribute__ ((naked))
void call_to_cmpt(const cmpt_t* cmpt, void* target_arg)
{
	__asm__ volatile
	(
		"ldp c2, c3, [c0, #(0)]\n" //Load cmpt code and data into c2, c3
		"ldr c4, [c0, #(32)]\n" //Load target func ptr to c4
		"stp c29, c30, [csp, #-32]!\n"
		"blrs c29, c2, c3\n" //Call to map'd + cpy'd trampoline_code
	);
}

//NOTE: This code is not used in the memory defined here, it is copied to an executable map and ran from there
__attribute__ ((naked))
void trampoline_code()
{
	//Assume blrs just used
	//c29 contains unsealed data
	//c4 contains target ptr
	//c1 contains arg ptr for target
	__asm__ volatile
	(
		LABEL("trampoline_start")
		"mov c0, c29\n" //Move unsealed data cap to c0
		"blr c4\n" //Branch to target func
		"ldp c29, c30, [csp], #32\n"
		"ret\n"
		LABEL("trampoline_end")
	);
}

int create_cmpt(cmpt_t* cmpt_handle, const char* data, const size_t data_size, cmpt_target_t* target)
{
	//Max otype is 2^15-1 so keep lowest 14 bits to ensure otype never greater, +4 to prevent otype of 1, 2 or 3 and explicitly prevent 15-bit overflow
	cmpt_data_t *cmpt = (cmpt_data_t*)cmpt_handle;
	size_t seal_otype = ((((size_t)target) & 0x3fffLU) + 4LU) & 0x7fffLU;
	void* root_seal_cap =   __builtin_cheri_offset_set(getauxptr(AT_CHERI_SEAL_CAP), seal_otype);
	void* root_unseal_cap = __builtin_cheri_offset_set(getauxptr(AT_CHERI_SEAL_CAP), 1);

	//STEP: Set target func
	cmpt->target = target;

	//STEP: Create map
	size_t page_size = getpagesize();
	size_t data_pages = (data_size / page_size) + 1; //Round up data size to next page multiple
	cmpt->map_size = page_size*(1 + data_pages); //Assume code will never need > 1 page
	cmpt->map = mmap(NULL, cmpt->map_size, PROT_READ | PROT_WRITE | PROT_EXEC | PROT_CAP_INVOKE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if(cmpt->map == MAP_FAILED)
	{
		return -1;
	}

	//STEP: Load code into code page
	cmpt->code = cmpt->map + 4; //TODO: Remove hardcoded code offset
	void* tramp_code_ptr = (void*)trampoline_start;
	if(__builtin_cheri_sealed_get(tramp_code_ptr))
	{
		//If check necessary since &(trampoline_start) not a sentry in dynamic test
		tramp_code_ptr = __builtin_cheri_unseal(tramp_code_ptr, root_unseal_cap);
	}
	size_t aligned_tramp_code_ptr = __builtin_cheri_address_get(tramp_code_ptr) & (~(0x3LU));
	size_t tramp_code_size = (&(trampoline_end) - &(trampoline_start) + 1);
	tramp_code_ptr = __builtin_cheri_address_set(tramp_code_ptr, aligned_tramp_code_ptr);
	memcpy(cmpt->code, tramp_code_ptr, tramp_code_size);

	//STEP: Load data into data page(s)
	cmpt->data = cmpt->map + page_size;
	memcpy(cmpt->data, data, data_size);

	//STEP: Set permissions and seal
	mprotect(cmpt->map, page_size, PROT_READ | PROT_EXEC | PROT_CAP_INVOKE); //mprotect code
	mprotect(cmpt->data, data_size, PROT_READ | PROT_WRITE | PROT_CAP_INVOKE); //mprotect data
	cmpt->map = __builtin_cheri_perms_and(cmpt->map, ROOT_CAP_PERMS);
	cmpt->map = __builtin_cheri_seal(cmpt->map, root_seal_cap);

	cmpt->code = __builtin_cheri_perms_and(cmpt->code, READ_CAP_PERMS | EXEC_CAP_PERMS | __ARM_CAP_PERMISSION_BRANCH_SEALED_PAIR__);
	cmpt->code = __builtin_cheri_offset_increment(cmpt->code, 1); //Inc to prevent switch to A64
	cmpt->code = __builtin_cheri_seal(cmpt->code, root_seal_cap);

	//fully PCuABI compliant, perms setting necessary because map'd buffer has executable permission on Morello board
	cmpt->data = __builtin_cheri_perms_and(cmpt->data, READ_CAP_PERMS | WRITE_CAP_PERMS | __ARM_CAP_PERMISSION_BRANCH_SEALED_PAIR__);
	cmpt->data = __builtin_cheri_seal(cmpt->data, root_seal_cap);

	return 0;
}

int destroy_cmpt(cmpt_t* cmpt_handle)
{
	cmpt_data_t* cmpt = (cmpt_data_t*)cmpt_handle;
	void* map = cmpt->map;
	size_t map_otype = (size_t)__builtin_cheri_type_get(map);
	void* root_unseal_cap = __builtin_cheri_offset_set(getauxptr(AT_CHERI_SEAL_CAP), map_otype);
	map = __builtin_cheri_unseal(map, root_unseal_cap);
	int failure = munmap(map, cmpt->map_size);

	memset(cmpt_handle, 0, sizeof(cmpt_t));

	return failure;
}

bool is_cmpt_valid(const cmpt_t* cmpt_handle)
{
	cmpt_data_t* cmpt = (cmpt_data_t*)cmpt_handle;
	bool code_tag = __builtin_cheri_tag_get(cmpt->code);
	bool data_tag = __builtin_cheri_tag_get(cmpt->data);
	size_t code_otype = (size_t)__builtin_cheri_type_get(cmpt->code);
	size_t data_otype = (size_t)__builtin_cheri_type_get(cmpt->data);
	size_t code_perms = __builtin_cheri_perms_get(cmpt->code);
	size_t data_perms = __builtin_cheri_perms_get(cmpt->data);

	const size_t max_fixed_seal_type = 0x3LU;

	return
	(
	 	//blrs instruction requirements (from pseudocode) for successful cmpt
		(code_tag && data_tag) && //Valid
		(code_otype > max_fixed_seal_type) && //Sealed with a correct otype
		(code_otype == data_otype) && //Matching otypes
		(code_perms & __ARM_CAP_PERMISSION_BRANCH_SEALED_PAIR__) && //Code bsp perm
		(data_perms & __ARM_CAP_PERMISSION_BRANCH_SEALED_PAIR__) && //Data bsp perm
		(code_perms & EXEC_CAP_PERMS) && //Code can be executed
		!(data_perms & __CHERI_CAP_PERMISSION_PERMIT_EXECUTE__) && //Data cannot be executed

		//Intended use requirements for successful cmpt
		(code_perms & READ_CAP_PERMS) && //Code can be read from
		!(code_perms & __CHERI_CAP_PERMISSION_PERMIT_STORE__) && //Code cannot be written to
		(data_perms & READ_CAP_PERMS) && //Data can be read from
		(data_perms & WRITE_CAP_PERMS) //Data can be written to
	);
}
#endif
