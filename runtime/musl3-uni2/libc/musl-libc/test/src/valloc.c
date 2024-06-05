#include <stdlib.h>
#include <stdio.h>

#include "alloc_helpers.h"

int main(int argc, char **argv) {
    size_t size = 64;

    void *aligned_memory = valloc(size);
    testptr_aligned(aligned_memory, size, 4096);

    return TEST_SUCCESS;
}
