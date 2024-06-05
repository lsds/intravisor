#include <syscall.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

int test_write()
{
	char input_buf[32] = {};
	syscall(SYS_write, 0, input_buf, 8);
	if (!__builtin_cheri_tag_get(input_buf)) return 1;
	write(0, input_buf, 8); // This tests syscall_cp call
	if (!__builtin_cheri_tag_get(input_buf)) return 4;
	return 0;
}

int test_getcpu()
{
	unsigned int cpu;
	unsigned int node;
	syscall(SYS_getcpu, &cpu, &node);
	return 0;
}

int test_mmap()
{
	intptr_t point = syscall(SYS_mmap, NULL, 100, PROT_NONE, MAP_PRIVATE|MAP_ANON, -1, 0);
	if (!__builtin_cheri_tag_get(point)) return 5;
	if (0 != syscall(SYS_munmap, point, 100)) return 6;
	return 0;
}

int main(int argc, char *argv[])
{
	switch (argv[1][0]) {
	case '0': return test_write();
	case '1': return test_getcpu();
	case '2': return test_mmap();
	default: return 9;
	}
}
