#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[])
{
	if (!__builtin_cheri_tag_get(argv)) {
		printf("argv tag is not set: %#p\n", (void *)argv);
		return 5;
	}

	const size_t argv_representable_length =
		__builtin_cheri_round_representable_length((argc + 1) * sizeof(char *));
	const size_t argv_representable_mask =
		__builtin_cheri_representable_alignment_mask(argv_representable_length);
	if (argv_representable_length != __builtin_cheri_length_get(argv)) {
		printf("argv has unexpected length:\nargv: %#p\nrepresentable length: 0x%lx\n",
		       (void *)argv, argv_representable_length);
		return 7;
	}
	if ((uintptr_t)argv != ((uintptr_t)argv & argv_representable_mask)) {
		printf("argv has unexpected alignment:\nargv: %#p\nrepresentable mask: 0x%lx\n",
		       (void *)argv, argv_representable_mask);
		return 8;
	}

	void *cap = NULL;
	size_t tag = 0;
	size_t sz = 0;
	for (int k = 0; k < argc; k++) {
		cap = argv[k];
		if (!(tag = __builtin_cheri_tag_get(cap))) {
			printf("argv[%d] has tag %zu\n", k, tag);
			return 1;
		}
		size_t xsz = (strlen(cap) + 1);
		sz = __builtin_cheri_length_get(cap);
		printf("argv[%d]=`%s` has length %zu (%zu)\n", k, argv[k], sz, xsz);
		if (sz != xsz) {
			return 2;
		}
	}
	cap = argv[argc];
	if ((tag = __builtin_cheri_tag_get(cap))) {
		printf("argv[argc] has tag %zu\n", tag);
		return 3;
	}
	if ((sz = __builtin_cheri_length_get(cap)) != 0xfffffffffffffffful) {
		printf("argv[argc] has length %zu\n", sz);
		return 4;
	}
	return 0;
}
