#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAGIC 0xb0bacafe

static void *test(void *args);
int test_pthread();
int test_pthread_setstack();

int main(int argc, char **argv) {
    if (argc < 2) return -1;

    switch(argv[1][0]) {
        case '0':
            return test_pthread();
        case '1':
            return test_pthread_setstack();
    }

    return -1;
}

int test_pthread() {
    int ret;

    pthread_attr_t attr;
    printf("pthread_attr_init(%p)...\n", (void *) &attr);
    if ((ret = pthread_attr_init(&attr))) return 1;
    printf("pthread_attr_init() returned %d\n", ret);

    pthread_t thread;
    char *arg_str = "hello world from args!";
    printf("pthread_create(%p, %p, %p, %p)...\n", (void *) &thread, (void *) &attr, (void *) test, (void *) arg_str);
    if ((ret = pthread_create(&thread, &attr, test, arg_str))) return 2;
    printf("pthread_create() returned %d\n", ret);

    void *thread_ret;
    printf("pthread_join(%p, %p)...\n", (void *) thread, (void *) &thread_ret);
    if ((ret = pthread_join(thread, &thread_ret))) return 3;
    printf("pthread_join() returned %d\n", ret);

    printf("thread_ret == %p\n", thread_ret);
    if ((uintptr_t) thread_ret != MAGIC) return 4;

    printf("main thread returning 0\n");
    return 0;
}

int test_pthread_setstack() {
    int ret;

    pthread_attr_t attr;
    printf("pthread_attr_init(%p)...\n", (void *) &attr);
    if ((ret = pthread_attr_init(&attr))) return 1;
    printf("pthread_attr_init() returned %d\n", ret);

    size_t size = 10 * getpagesize();
    void *stack;
    if ((ret = posix_memalign(&stack, getpagesize(), size))) return 2;

    printf("pthread_attr_setstack(%p, %p, %zx)...\n", (void *) &attr, (void *) stack, size);
    pthread_attr_setstack(&attr, stack, size);
    if ((ret = pthread_attr_setstack(&attr, stack, size))) return 3;
    printf("pthread_attr_setstack() returned %d\n", ret);

    pthread_t thread;
    char *arg_str = "hello world from args!";
    printf("pthread_create(%p, %p, %p, %p)...\n", (void *) &thread, (void *) &attr, (void *) test, (void *) arg_str);
    if ((ret = pthread_create(&thread, &attr, test, arg_str))) return 4;
    printf("pthread_create() returned %d\n", ret);

    void *thread_ret;
    printf("pthread_join(%p, %p)...\n", (void *) thread, (void *) &thread_ret);
    if ((ret = pthread_join(thread, &thread_ret))) return 5;
    printf("pthread_join() returned %d\n", ret);

    printf("thread_ret == %p\n", thread_ret);
    if ((uintptr_t) thread_ret != MAGIC) return 6;

    printf("main thread returning 0\n");
    return 0;
}

static void *test(void *args) {
    char *str = (char *) args;
    printf("[thread] str == %s\n", str);

    if (strcmp(str, "hello world from args!")) {
        printf("[thread] returning %p\n", (void *) NULL);
        return (void *) NULL;
    }

    printf("[thread] returning %p\n", (void *) MAGIC);
    return (void *) MAGIC;
}
