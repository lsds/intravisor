#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

pthread_key_t global_key;

void cleanup_thread_specific_data(void *data) {
    printf("Cleaning up thread-specific data: %d\n", *((int *)data));
    free(data);
}

int main(int argc, char **argv)
{
    pthread_key_create(&global_key, cleanup_thread_specific_data);

    int in_data = 0xabba;

    pthread_setspecific(global_key, &in_data);

    int *ret_data = pthread_getspecific(global_key);

    printf("in = %x, out = %x[%p]\n", in_data, *ret_data, ret_data);

    pthread_key_delete(global_key);

    exit(0);
}

