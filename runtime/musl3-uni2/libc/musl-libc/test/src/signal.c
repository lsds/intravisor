#define _GNU_SOURCE

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * This test should pass on a real Morello system
 **/

static void jump_to_c(void) {
	printf("reached jump_to!\n");
	exit(0);
}

#if defined(__aarch64__)
#define UC_MCONTEXT_NREGS 32
#define UC_MCONTEXT_REGS(__ctx) (__ctx.regs)
#define UC_MCONTEXT_PC(__ctx) (__ctx.pc)
#define UC_MCONTEXT_SP(__ctx) (__ctx.sp)
#elif defined(__x86_64__)
#define UC_MCONTEXT_NREGS 23
#define UC_MCONTEXT_REGS(__ctx) (__ctx.gregs)
#define UC_MCONTEXT_PC(__ctx) (UC_MCONTEXT_REGS(__ctx)[REG_RIP])
#define UC_MCONTEXT_SP(__ctx) (UC_MCONTEXT_REGS(__ctx)[REG_RSP])
#else
#error "Please add support for this architecture"
#endif

static void catcher(int sig, siginfo_t *si, void *ctx) {
	printf("inside catcher() function\n");

	ucontext_t *uc = ctx;

	for (int k = 0; k < UC_MCONTEXT_NREGS; k++) {
		printf("r%02d = %016lx\n", k, UC_MCONTEXT_REGS(uc->uc_mcontext)[k]);
	}
	printf("xsp = %016lx\n", UC_MCONTEXT_SP(uc->uc_mcontext));
	printf(" pc = %016lx\n", UC_MCONTEXT_PC(uc->uc_mcontext));

#if defined(__aarch64__)
	unsigned long *data = (unsigned long *)uc->uc_mcontext.__reserved;
	for (int k = 0; k < 256; k+=2) {
		printf("reserved %03d = %016lx %016lx\n", k, data[k + 1], data[k]);
	}

	struct morello_context *morello_ctx = (struct morello_context *) uc->uc_mcontext.__reserved;
	while (morello_ctx->head.magic && morello_ctx->head.size && morello_ctx->head.magic != MORELLO_MAGIC) {
		morello_ctx = (struct morello_context *) (((unsigned char *) morello_ctx) + morello_ctx->head.size);
	}

//	This should work on a real Morello system with Morello kernel
//	if (!morello_ctx->head.magic || !morello_ctx->head.size) {
//		printf("morello context entry (magic number 0x%x) not found\n", MORELLO_MAGIC);
//		exit(1);
//	}
//	if (!__builtin_cheri_tag_get(morello_ctx->pcc)) {
//		printf("PCC tag in morello context not set (pcc=%#p)\n", (void *) morello_ctx->pcc);
//		exit(2);
//	}
#endif

	/* The LSB of the PC should not be set otherwise an instruction abort will occur.
	 * PSTATE.C64 is correct as:
	 * C64 ISA - Remove LSB but PSTATE.C64 would have been set already by signal handler.
	 * A64 ISA - LSB not set and PSTATE.C64 would not have been set by signal handler.
	 */
	UC_MCONTEXT_PC(uc->uc_mcontext) = (unsigned long) __builtin_cheri_address_get(jump_to_c) & ~0x1;
}

int main() {
	struct sigaction sigact;

	printf("jump_to_c addr: %#p\n", (void *) jump_to_c);

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigact.sa_flags = sigact.sa_flags | SA_SIGINFO | SA_RESTART;
	sigact.sa_sigaction = catcher;
	sigaction(SIGUSR1, &sigact, NULL);

	printf("raise SIGUSR1 signal\n");
	kill(getpid(), SIGUSR1);

	return 1;
}
