// TODO: musl: Likely these will need to be adjusted from unsigned
// long long to something 128 bits wide (probably uintptr_t), however
// this is not expected to be problematic for getting a MVP
struct user_regs_struct {
	unsigned long long regs[31];
	unsigned long long sp;
	unsigned long long pc;
	unsigned long long pstate;
};

struct user_fpsimd_struct {
	__uint128_t vregs[32];
	unsigned int fpsr;
	unsigned int fpcr;
};

#define ELF_NREG 34
typedef unsigned long elf_greg_t, elf_gregset_t[ELF_NREG];
typedef struct user_fpsimd_struct elf_fpregset_t;
