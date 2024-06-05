#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define COMPARE_BYTES(_q, _p, n) ({ \
	char *pb = (char *)_p;          \
	char *qb = (char *)_q;          \
	int u = 0;                      \
	for(size_t k = 0; k < n; k++) { \
		if (pb[k] != qb[k]) {       \
			u = k + 1; break;       \
		}                           \
	}                               \
	u;                              \
})

/* Get memory tag for aligned address */
static inline bool get_mem_tag(ptraddr_t address, void *wide_cap)
{
	void **cap = __builtin_cheri_address_set(wide_cap, address);
	return __builtin_cheri_tag_get(*cap);
}

#define CHECK_MEM_TAGS(_q, _p, n) ({                            \
	int u = 0;                                                  \
	for(size_t k = 0; k < n && n >= 16 && (n - k) >= 16; k++) { \
		ptraddr_t  x = (uintptr_t )_p + k;                      \
		ptraddr_t  y = (uintptr_t )_q + k;                      \
		if ((x & 0xf) == 0 && (y & 0xf) == 0) {                 \
			uint64_t tx = get_mem_tag(x, _p);                   \
			uint64_t ty = get_mem_tag(y, _q);                   \
			if (tx != ty) {                                     \
				printf("tag: %016lx %016lx - %lu %lu\n",        \
					y, x, ty, tx);                              \
				u = k + 1; break;                               \
			} else {                                            \
				printf("tag: %016lx %016lx - %lu %lu\n",        \
					y, x, ty, tx);                              \
			}                                                   \
		}                                                       \
	}                                                           \
	u;                                                          \
})
