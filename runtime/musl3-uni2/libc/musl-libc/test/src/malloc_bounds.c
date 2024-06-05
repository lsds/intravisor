#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "alloc_helpers.h"

// Those test don't care about the data corruption,
// they just do a basic validation of the returned capability
int main(int argc, char **argv) {
    unsigned int small_size = 150;
    unsigned int big_size = 16*32768;

    void* p;
    switch (argv[1][0]) {
    case '0': // malloc_bounds_small
        p = malloc(small_size);
        testptr(p, small_size);
        free(p);
        break;
    case '1': // malloc_bounds_large
        p = malloc(big_size);
        testptr(p, big_size);
        free(p);
        break;
    case '2': // aligned_malloc_bounds_small
        p = aligned_alloc(64, small_size);
        testptr_aligned(p, small_size, 64);
        free(p);
        break;
    case '3': // aligned_malloc_bounds_large
        p = aligned_alloc(512, big_size);
        testptr_aligned(p, big_size, 512);
        free(p);
        break;
    case '4': // realloc_bounds_small
        p = malloc(small_size);
        p = realloc(p, small_size+1);
        testptr(p, small_size+1);
        break;
        free(p);
        break;
    case '5': // realloc_bounds_large
        p = malloc(big_size);
        p = realloc(p, big_size+65536+1);
        testptr(p, big_size+65536+1);
        free(p);
        break;
    case '6': // realloc_bounds_change_regime
        p = malloc(big_size);
        p = realloc(p, small_size);
        testptr(p, small_size);
        free(p);
        break;
    default:
        return BAD_TEST_NUMBER;
    }
    return TEST_SUCCESS;
}
