#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>


#define HW_FILE "/app/helloworld.txt"

pthread_key_t global_key;

static __inline__ void * getSP(void) {
    register void * sp asm("sp");
    asm ("" : "=r"(sp));
    return sp;
}

void cleanup_thread_specific_data(void *data) {
    printf("Cleaning up thread-specific data: %d\n", *((int *)data));
    free(data);
}


void *thread_function(void *arg) {

    int in_data = 0xdead;

    int *ret_data = pthread_getspecific(global_key);

    printf("Trying pre-existing key: %x[%p]\n", *ret_data, ret_data);

    pthread_setspecific(global_key, &in_data);

    int *ret_data2 = pthread_getspecific(global_key);

    printf("in = %x, out = %x[%p]\n", in_data, *ret_data2, ret_data2);

//    return 0x5a;
    pthread_exit(0x5b);
}

int main(int argc, char **argv)
{
    char buf[100];
    FILE *f = fopen(HW_FILE, "r");
    if (!f) {
        fprintf(stderr, "Could not open file %s: %s\n", HW_FILE, strerror(errno));
        exit(1);
    }

    printf("getSP = %p\n", getSP);

    // Prints first line of file /app/helloworld.txt (max 100 characters)
    if (fgets(buf, sizeof(buf), f) == buf) {
        printf("%s", buf);
    } else {
        fprintf(stderr, "Could not read first line of file %s: %s\n", HW_FILE, strerror(errno));
        exit(1);
    }

    pthread_key_create(&global_key, cleanup_thread_specific_data);

    int in_data = 0xabba;

    pthread_setspecific(global_key, &in_data);

    int *ret_data = pthread_getspecific(global_key);

    printf("in = %x, out = %x[%p]\n", in_data, *ret_data, ret_data);

    pthread_t thread1;

    // Create two threads
    if (pthread_create(&thread1, NULL, thread_function, NULL) != 0) {
        perror("pthread_create for thread1");
        return 1;
    }

    unsigned long ret;

    pthread_join(thread1, &ret);

    printf("thread ret = %lx\n", ret);

    int *ret_data2 = pthread_getspecific(global_key);

    printf("key after ret: in = %x, out = %x[%p]\n", in_data, *ret_data, ret_data);

    pthread_key_delete(global_key);

    return 0;
}

