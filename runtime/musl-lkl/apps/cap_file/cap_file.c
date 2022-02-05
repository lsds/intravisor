#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define IOCTL_CF_PRB		0x4004e203

int main(int argc, char **argv)
{
	char key[] = "test1";
	char buf[32];

	int fd = open("/cap/cf1", O_RDWR);
	if(!fd) {
		printf("cannot open /cap/cf1\n"); while(1);
	} else
		printf("fd = %d\n", fd);


	int err = ioctl(fd, IOCTL_CF_PRB, key);
	if (err != 0) {
		printf( "Error: ioctl %d  %s\n", __LINE__, strerror(err));
		while(1);
	}

	int nsize = read(fd, buf, 32);

	printf("read %d bytes ('%s') from cap_file with key '%s'\n", nsize, buf, key);

	char send[] = "cap filler\n";

	printf("let's write '%s' into cap_file and read result back\n", send);

	lseek(fd, 0, SEEK_SET);

	int wrote = write(fd, send, sizeof(send));

	printf("wrote %d bytes\n", wrote);

	lseek(fd, 0, SEEK_SET);

	memset(buf, 0, 32);

	int new_nsize = read(fd, buf, 32);

	printf("read %d bytes ('%s') from cap_file with key '%s'\n", new_nsize, buf, key);

    return 0;
}

