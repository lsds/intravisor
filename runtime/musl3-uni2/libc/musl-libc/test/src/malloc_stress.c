#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "alloc_helpers.h"

static int test_large_allocation();
static int test_many_allocations();
static int test_all_sizeclasses();

int main(int argc, char *argv[]) {
	switch (argv[1][0]) {
	case '0': return test_large_allocation();
	case '1': return test_many_allocations();
	case '2': return test_all_sizeclasses();
	default: return BAD_TEST_NUMBER;
	}
}

static int test_large_allocation()
{
	const size_t s = 1024 * 1024 * 10;
	void *p = malloc(s);
	testptr(p, s);
	memset(p, 4, s);
	free(p);

	return TEST_SUCCESS;
}

static int test_many_allocations()
{
	for (int k = 0; k < 10000; k++) {
		void *q = malloc(517);
		testptr(q, 517);

		const size_t s = 1024 * (k % 100 + 1);
		void *p = malloc(s);
		testptr(p, s);
		if ((k % 30) == 0) {
			free(p);
		}
		free(q);
	}

	return TEST_SUCCESS;
}

static int test_all_sizeclasses()
{
	const uint16_t size_classes[] = {
		1, 2, 3, 4, 5, 6, 7, 8,
		9, 10, 12, 15,
		18, 20, 25, 31,
		36, 42, 50, 63,
		72, 84, 102, 127,
		146, 170, 204, 254,
		292, 340, 409, 510,
		584, 682, 818, 1022,
		1169, 1364, 1637, 2046,
		2340, 2730, 3276, 4094,
		4680, 5460, 6552, 8190,
	};

	for (size_t i = 0; i < (sizeof(size_classes) / sizeof(uint16_t)); i++) {
		size_t s = (size_classes[i] * 16) - 8;
		void *p = malloc(s);
		testptr(p, s);
		free(p);
	}

	void *p = NULL;
	for (size_t i = 0; i < (sizeof(size_classes) / sizeof(uint16_t)); i++) {
		size_t s = (size_classes[i] * 16) - 8;
		p = realloc(p, s);
		testptr(p, s);
	}
	free(p);

	return TEST_SUCCESS;
}
