#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	char buffer[64] = {};
	int fd = memfd_create("temp",0);
	dprintf(fd, "hello %s %d %p", "morello", argc, (void *)argv);
	lseek(fd, 0, SEEK_SET);
	read(fd, buffer, 64);
	return strncmp(buffer, "hello morello 1 0x", 18);
}
