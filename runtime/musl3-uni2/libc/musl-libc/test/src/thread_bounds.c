#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

void *tsd_test(void *args)
{
    int err = 0;
    pthread_key_t key = 0;
    int value = 10;
    int *valp;
    int *ret = malloc(sizeof(int));

    printf("Thread Running\n");

    err = pthread_key_create(&key, NULL);
    if(err != 0)
    {
        perror("Failed to create key. Error:");
        *ret = 1;
        return ret;
    }

    err = pthread_setspecific(key, &value);
    if(err != 0)
    {
        perror("Failed to set key value. Error:");
        *ret = 2;
        return ret;
    }

    valp = pthread_getspecific(key);
    if(valp != &value)
    {
        perror("Failed to get key value. Error:");
        *ret = 3;
        return ret;
    }

    err = pthread_key_delete(key);
    if(err != 0)
    {
        perror("Failed to delete key. Error:");
        *ret = 4;
        return ret;
    }

    *ret = 0;
    return ret;
}

void *csp_test(void *args)
{
    pthread_attr_t attr;
    size_t stack_size, length;
    void *csp;
    int *ret = malloc(sizeof(int));

    char *mem = alloca(15);
    strncpy(mem, "Thread Running", 15);
    printf("%s\n", mem);

    pthread_getattr_np(pthread_self(), &attr);
    pthread_attr_getstacksize(&attr, &stack_size);

    csp = __builtin_cheri_stack_get();
    length = __builtin_cheri_length_get(csp);

    if(stack_size != length)
    {
        *ret = 1;
        return ret;
    }

    *ret = 0;
    return ret;
}

int main(int argc, char **argv)
{
    pthread_t thread;
    int status = 0;
    int *ret = 0;
    pthread_attr_t attrp;

    switch (argv[1][0])
    {
    case '0':
        pthread_create(&thread, NULL, tsd_test, NULL);
        pthread_join(thread, (void *) &ret);
        break;
    case '1':
        pthread_attr_init(&attrp);
        /* This test works if allocated a stack of 8096 on other architectures
         * due to tsd being included in stack allocation and rounding up to the next page size.
         * Morello does not include tsd in stack allocation so it will have to be manually rounded
         * up to next page size.
         */
        pthread_attr_setstacksize(&attrp, 12288);
        pthread_create(&thread, &attrp, csp_test, NULL);
        pthread_join(thread, (void *) &ret);
        break;
    }

    status = *ret;
    free(ret);

    return status;
}
