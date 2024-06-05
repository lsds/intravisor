#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

pthread_mutex_t mutex;
int shared_data = 0;

void *thread_function(void *thread_id) {

    long tid;
    tid = (long)thread_id;

    // Demonstrating thread-specific data
    int *thread_specific_data = (int *)malloc(sizeof(int));
    *thread_specific_data = tid;

    // Increment shared_data while ensuring thread safety
    pthread_mutex_lock(&mutex);
    shared_data++;
    printf("Thread #%ld incremented shared_data to %d\n", tid, shared_data);
    pthread_mutex_unlock(&mutex);

    // Free thread-specific data
    printf("Thread #%ld's specific data: %d\n", tid, *thread_specific_data);
    free(thread_specific_data);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (t = 0; t < NUM_THREADS; t++) {
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, thread_function, (void *)t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            perror("create");
            exit(-1);
        }
    }

    printf("next pthread_join\n");

    // Join threads
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    printf("All threads have completed their tasks.\n");
    pthread_exit(NULL);
    return 0;
}