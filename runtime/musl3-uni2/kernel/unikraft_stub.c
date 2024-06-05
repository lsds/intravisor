#include <stdio.h>
#include <stdlib.h>
#include <uk/alloc.h>

void uk_thread_wake() {
	printf("%s not implemented\n", __func__); while(1);
}

unsigned long ukplat_lcpu_save_irqf() {
//	printf("%s not implemented\n", __func__);
	return 0;
}

void ukplat_lcpu_restore_irqf() {
//	printf("%s not implemented\n", __func__);
}

UKPLAT_PER_LCPU_DEFINE(struct uk_thread *, __uk_sched_thread_current);

void *uk_alloc_get_default() {
	return 0;
}

void *uk_malloc(void *a, __sz size) {
	return(malloc(size));
}

void uk_free(void *a, void *ptr) {
	free(ptr);
}

void uk_thread_block_until() {
	printf("%s not implemented\n", __func__);
}

void ukplat_lcpu_halt_irq_until() {
	printf("%s not implemented\n", __func__);
}

