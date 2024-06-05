#define _GNU_SOURCE
#include <sys/mman.h>

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <alloca.h>
#include <stdbool.h>

#include "checkmacros.h"

#define CHECK_ALIGNED(cap, sz) ({ \
	((__builtin_cheri_address_get(cap) & (sz - 1)) == 0); \
})

// These are used in ASSIGN_CAPS
int x, y, z;

#define ASSIGN_CAPS(__dst) ({ \
	(__dst)[3] = &x;                   \
	(__dst)[4] = NULL;                 \
	(__dst)[5] = &p;                   \
	(__dst)[6] = &q;                   \
	(__dst)[7] = &y;                   \
	(__dst)[(mem_size >> 4) - 1] = &z; \
})

enum tests {
	TEST_SHRINK = 0,
	TEST_EXTEND,
	TEST_MOVE_FIXED,
	TEST_MOVE_DONTUNMAP,
	TEST_SHOULD_SEGFAULT,
	NUM_OF_TEST
};

static int test_remap(int test_type)
{
	const size_t mem_size = getpagesize() * 2;

	// These are used in ASSIGN_CAPS
	int p, q;

	void *mem = mmap(NULL, mem_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	// check page alignment
	if (!CHECK_ALIGNED(mem, getpagesize())) {
		printf("mmap returned address which is not page-aligned: %#p\n", mem);
		return 1;
	}

	memset(mem, 0, mem_size);
	ASSIGN_CAPS((int **)mem);

	void *new_mem = NULL, *new_addr = NULL, *ref_mem = NULL;
	size_t new_mem_size = mem_size * 2;
	size_t check;

	switch (test_type)
	{
	case TEST_SHRINK:
		new_mem_size = mem_size / 2;
		new_mem = mremap(mem, mem_size, new_mem_size, MREMAP_MAYMOVE);
		if (new_mem == MAP_FAILED) {
			perror("mremap");
			return 2;
		}
		// If moved, check for range from MIN(old_size, new_size).
		if (new_mem != mem) {
			mem = malloc(new_mem_size);
			memset(mem, 0, new_mem_size);
			ASSIGN_CAPS((int**)mem);
		}
		check = CHECK_MEM_TAGS(new_mem, mem, new_mem_size);
		break;
	case TEST_EXTEND:
		new_mem = mremap(mem, mem_size, new_mem_size, MREMAP_MAYMOVE);
		if (new_mem == MAP_FAILED) {
			perror("mremap");
			return 2;
		}
		// Check if extended memory is untagged.
		for (ptraddr_t  ptr = (uintptr_t )new_mem + mem_size;
		     ptr < (uintptr_t )new_mem + new_mem_size; ptr += 16) {
			if (get_mem_tag(ptr, new_mem)) {
				return 3;
			}
		}
		// If moved, check for range from MIN(old_size, new_size).
		if (new_mem != mem) {
			mem = malloc(mem_size);
			memset(mem, 0, mem_size);
			ASSIGN_CAPS((int**)mem);
		}
		check = CHECK_MEM_TAGS(new_mem, mem, mem_size);
		break;
	case TEST_MOVE_FIXED:
		// 'new_addr' should always be different from 'mem'.
		new_addr = mmap(NULL, new_mem_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
		                -1, 0);
		ASSIGN_CAPS((int**)new_addr + 2);
		new_mem = mremap(mem, mem_size, new_mem_size, MREMAP_MAYMOVE | MREMAP_FIXED, new_addr);
		if (new_mem == MAP_FAILED) {
			perror("mremap");
			return 2;
		}
		if ((new_mem == mem) || (new_mem != new_addr)) {
			perror("Should have moved!");
			return 3;
		}
		ref_mem = malloc(new_mem_size);
		memset(ref_mem, 0, new_mem_size);
		ASSIGN_CAPS((int**)ref_mem);
		check = CHECK_MEM_TAGS(new_mem, ref_mem, new_mem_size);
		break;
	case TEST_MOVE_DONTUNMAP:
		// For MREMAP_DONTUNMAP, 'new_size' should be same as 'old_size'.
		new_mem_size = mem_size;
		new_mem = mremap(mem, mem_size, new_mem_size, MREMAP_MAYMOVE | MREMAP_DONTUNMAP);
		if (errno == EINVAL) {
			perror("mremap (Possible reason - MREMAP_DONTUNMAP not supported for version < 5.7)");
			return 0;
		}
		if (new_mem == MAP_FAILED) {
			perror("mremap");
			return 2;
		}
		// Allocate another region to use as a reference
		ref_mem = malloc(mem_size);
		memset(ref_mem, 0, mem_size);
		// Check that the PTEs for the old region no longer exist - expecting to see all 0s
		if (memcmp(mem, ref_mem, mem_size)) {
			perror("mremap - Old region should read all 0s!");
			return 3;
		}
		// Check that the tags associated with the old region were cleared
		if (CHECK_MEM_TAGS(mem, ref_mem, mem_size)) {
			perror("mremap - Tags associated with old region should be 0!");
			return 4;
		}
		ASSIGN_CAPS((int**)ref_mem);
		// Check that the tags in the remapped memory match those in the reference memory
		check = CHECK_MEM_TAGS(new_mem, ref_mem, new_mem_size);
		break;
	case TEST_SHOULD_SEGFAULT:
		new_addr = mmap(NULL, new_mem_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
		                -1, 0);
		(void)((volatile int*)mem)[0]; // Valid
		new_mem = mremap(mem, mem_size, new_mem_size, MREMAP_MAYMOVE | MREMAP_FIXED, new_addr);
		if (new_mem == MAP_FAILED) {
			perror("mremap");
			return 2;
		}
		if (new_mem == mem) {
			perror("Should have moved!");
			return 3;
		}
		(void)((volatile int*)mem)[0]; // Should SEGFAULT
		puts("Should SEGFAULT!");
		return 4;
		break;
	}

	if (check) {
		printf("%s: mem tags are not equal at offset %zu\n", __func__, check - 1);
		return 4;
	}
	return 0;
}

int main (int argc, char *argv[])
{
	if (atoi(argv[1]) >= NUM_OF_TEST) {
		printf("unknown test %c\n", argv[1][0]);
		return -1;
	}
	return test_remap(atoi(argv[1]));
}
