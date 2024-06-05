#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sodium.h>


int main() {
	extern int libsodium_main(void);
	libsodium_main();
	exit(0);
}