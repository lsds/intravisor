#ifndef AUX_HELPER_H
#define AUX_HELPER_H

#include <sys/auxv.h>

/*
 * https://git.morello-project.org/morello/kernel/linux/-/wikis/Morello-pure-capability-kernel-user-Linux-ABI-specification#auxiliary-vector-auxv
 * Elements of the auxiliary vector are either capabilities or values.
 * If a vector element is a pointer, it can appear in both.
 *
 * This list is not a perfect enforcement as it currently supports
 * both the transtional PCuABI and Beta PCuABI, which have different
 * capability entries.
 */

#define AUX_PTR_CASES \
	case AT_ENTRY:\
	case AT_PHDR:\
	case AT_BASE:\
	case AT_SYSINFO_EHDR:\
	case AT_EXECFN:\
	case AT_RANDOM:\
	case AT_PLATFORM:\
	case AT_ARGV:\
	case AT_ENVP:\
	case AT_CHERI_EXEC_RW_CAP:\
	case AT_CHERI_EXEC_RX_CAP:\
	case AT_CHERI_INTERP_RW_CAP:\
	case AT_CHERI_INTERP_RX_CAP:\
	case AT_CHERI_STACK_CAP:\
	case AT_CHERI_SEAL_CAP:\
	case AT_CHERI_CID_CAP:\

#define AUX_NONVAL_CASES \
	case AT_ENTRY:\
	case AT_PHDR:\
	case AT_SYSINFO_EHDR:\
	case AT_EXECFN:\
	case AT_RANDOM:\
	case AT_PLATFORM:\
	case AT_ARGV:\
	case AT_ENVP:\
	case AT_CHERI_EXEC_RW_CAP:\
	case AT_CHERI_EXEC_RX_CAP:\
	case AT_CHERI_INTERP_RW_CAP:\
	case AT_CHERI_INTERP_RX_CAP:\
	case AT_CHERI_STACK_CAP:\
	case AT_CHERI_SEAL_CAP:\
	case AT_CHERI_CID_CAP:\

#endif
