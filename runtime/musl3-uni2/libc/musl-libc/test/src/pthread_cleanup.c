#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static void cleanup(void *arg) {
    printf("inside cleanup... arg=%d\n", *(int *)arg);
    *(int *)arg *= 2;
}

void *run_thread(void *arg) {
    printf("inside thread...\n");

    pthread_cleanup_push(cleanup, arg);

    sleep(1);
    pthread_exit(0);

    pthread_cleanup_pop(0);

    return NULL;
}

int main() {
    int cleanuparg = 16;

    pthread_t thread;
    pthread_create(&thread, NULL, run_thread, (void *) &cleanuparg);
    pthread_join(thread, NULL);

    printf("arg inbetween=%d\n", cleanuparg);

    pthread_t thread2;
    pthread_create(&thread2, NULL, run_thread, (void *) &cleanuparg);
    pthread_cancel(thread2);
    pthread_join(thread2, NULL);

    printf("arg afterwards=%d\n", cleanuparg);
    return cleanuparg != 64;
}
