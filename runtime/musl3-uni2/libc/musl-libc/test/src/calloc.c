#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "alloc_helpers.h"

int main(int argc, char **argv) {
    size_t size = 10 * sizeof(int);

    int *array = malloc(size);
    memset(array, 1, size);
    free(array);

    array = (int*) calloc(sizeof(int), 10);
    testptr(array, size);

    for(int i = 0; i < 10; i++) {
        if (array[i] != 0) {
            return UNEXPECTED_VALUE;
        }
    }

    return TEST_SUCCESS;
}
