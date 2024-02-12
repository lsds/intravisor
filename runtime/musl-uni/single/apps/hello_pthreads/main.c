
//pthreads a very broken in many ways. they require very deep redevelopment

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#define _GNU_SOURCE
#include <unistd.h>

#define EXP_STAT 0xbc

void *thread_function(void *arg) {
	printf("thread function\n");
	pthread_exit(EXP_STAT);
}

int app_main(int argc, char **argv) {

	pthread_t thread1;

	// Create two threads
	if(pthread_create(&thread1, NULL, thread_function, NULL) != 0) {
		perror("pthread_create for thread1");
		return 1;
	}

	void *ret;

	int jret = pthread_join(thread1, &ret);

	printf("thread ret = %lx, jret = %d\n", (long) ret, jret);

	if(ret != EXP_STAT) {
		printf("pthreads are broken, wrong return value, die\n");
		printf("%s", *(long *) 0);
	} else
		printf("pthread_join works\n");

	return 0;
}
