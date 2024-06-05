#include <signal.h>
#include <stdio.h>
#include <sys/signalfd.h>
#include <sys/timex.h>

int main()
{
	printf("struct sigevent = %zu\n", sizeof(struct sigevent));
	printf("siginfo_t = %zu\n", sizeof(siginfo_t));
	printf("struct signalfd_siginfo = %zu\n", sizeof(struct signalfd_siginfo));
	printf("struct timex = %zu\n", sizeof(struct timex));
	return 0;
}
