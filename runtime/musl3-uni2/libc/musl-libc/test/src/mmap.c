#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include "temp_file_helpers.h"

#define MEM_PROT    PROT_READ | PROT_WRITE
#define MEM_FLAGS   MAP_PRIVATE | MAP_ANONYMOUS

int test_mmap();
int test_mmap_offset();
int test_mmap_tags(bool do_munmap);

int main(int argc, char **argv) {
	if (argc < 2) return -1;

	switch(argv[1][0]) {
		case '0':
			return test_mmap();
		case '1':
			return test_mmap_offset();
		case '2':
			return test_mmap_tags(/* do_munmap */true);
		case '3':
			return test_mmap_tags(/* do_munmap */false);
	}

	return -1;
}

int test_mmap() {
	size_t len = 128;
	int *p = mmap(NULL, len, MEM_PROT, MEM_FLAGS, 0, 0);
	if (p == MAP_FAILED) {
		perror("mmap");
		return 1;
	}
	if (__builtin_cheri_tag_get(p) != 1ul) {
		return 2;
	}
	size_t expected_size = len + (-len & (getpagesize() - 1));
	if (__builtin_cheri_length_get(p) != expected_size) {
		return 3;
	}
	p[0] = 0;
	int z = p[0];
	munmap(p, len);
	return z;
}

int test_mmap_offset() {
	char directory_buffer[PATH_MAX];
	char filename_buffer[PATH_MAX];

	if(create_temp_directory("morello-musl-tests-mmap/", &directory_buffer[0]) != 0)
		return -1;

	char *filename = create_temp_file(&directory_buffer[0], "mmap_offset_XXXXXX", &filename_buffer[0]);

	int fd = open(filename, O_CREAT | O_RDWR | O_EXCL, 600);
	if (fd < 0) return -1;
	off_t offset = getpagesize();
	size_t len = 128;
	if (posix_fallocate(fd, offset, len)) return -2;
	int *p = mmap(NULL, len, MEM_PROT, MAP_PRIVATE, fd, offset);
	if (p == MAP_FAILED) {
		perror("mmap");
		return 1;
	}
	if (__builtin_cheri_tag_get(p) != 1ul) {
		return 2;
	}
	size_t expected_size = len + (-len & (getpagesize() - 1));
	if (__builtin_cheri_length_get(p) != expected_size) {
		return 3;
	}
	p[0] = 0;
	int z = p[0];
	munmap(p, len);
	if (close(fd)) return -3;
	return z;
}

int test_mmap_tags(bool do_munmap) {
	size_t len = getpagesize();
	void *mem = mmap(NULL, len, MEM_PROT, MEM_FLAGS, -1, 0);
	if (mem == MAP_FAILED) {
		perror("first mmap");
		return 1;
	}
	// Here '4' corresponds to the granularity of capability in memory.
	size_t cap_count = len >> 4;
	int **ptr = mem;
	int var;
	for(int idx = 0; idx < cap_count; ++idx) {
		// Sets first, middle and last tags for test.
		if ((idx == 0) || (idx == (cap_count/2)) || (idx == (cap_count - 1))) {
			ptr[idx] = &var;
			if (__builtin_cheri_tag_get(ptr[idx]) != 1ul)
				return 2;
		} else {
			if (__builtin_cheri_tag_get(ptr[idx]) != 0ul)
				return 3;
		}
	}
	if (do_munmap) {
		if (munmap(mem, len) == -1) {
			perror("munmap");
			return 4;
		}
	}
	mem = mmap(mem, len, MEM_PROT, MAP_FIXED | MEM_FLAGS, -1, 0);
	if (mem == MAP_FAILED) {
		perror("second mmap");
		return 5;
	}
	// Check if all tags are cleared.
	for(int idx = 0; idx < cap_count; ++idx) {
		if (__builtin_cheri_tag_get(ptr[idx]) != 0ul) {
			printf("Failed at %d\n.", idx);
			return 6;
		}
	}
	return 0;
}
