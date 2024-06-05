#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "alloc_helpers.h"

int main(int argc, char **argv) {

    size_t size = 10 * sizeof(int);
    int *array = (int*) calloc(sizeof(int), 10);

    // first make sure calloc worked properly
    testptr((void*)array, size);
    for(int i = 0; i < 10; i++) {
        if (array[i] != 0) {
            return UNEXPECTED_VALUE;
        }
        array[i] = i;
    }

    array = reallocarray(array, sizeof(int), 30);

    testptr((void*)array, size*3);
    for(int i = 0; i < 10; i++) {
        if (array[i] != i) {
            return UNEXPECTED_VALUE;
        }
    }
    return TEST_SUCCESS;
}
