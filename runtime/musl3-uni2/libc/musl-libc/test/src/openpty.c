#include <errno.h>
#include <pty.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

int main (int argc, char * argv[]) {
	int m = 0, s = 0;
	char name[20];
	char* name_s;

	if(openpty(&m, &s, name, NULL, NULL) == -1)
	{
		fprintf(stderr, "Failed to open psuedoterminal.\n");
		return 1;
	}

	// Check fd are valid
	if (m == 0 || s == 0)
	{
		fprintf(stderr, "Psuedoterminal did not return valid file descriptors.\n");
		return 2;
	}

	if (!(ttyname(m) && (name_s = ttyname(s))))
	{
		fprintf(stderr, "Failed to fetch psuedoterminal name.\n");
		return 3;
	}

	if (strncmp(name_s, name, 20))
	{
		fprintf(stderr, "Psuedoterminal names do not match.\n");
		return 4;
	}

	write(m, "abcd\n", 5);
	read(s, name, 4);
	if (strncmp(name, "abcd", 4))
	{
		fprintf(stderr, "Failed to write string to psuedoterminal.\n");
		return 5;
	}

	return 0;
}
