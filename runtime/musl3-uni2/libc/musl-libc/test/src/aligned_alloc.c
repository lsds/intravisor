#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "alloc_helpers.h"

int main(int argc, char **argv) {
    for (size_t alignment = 16; alignment <= 4096; alignment *= 2) {
        void *aligned_memory = aligned_alloc(alignment, alignment * 4);
        testptr_aligned(aligned_memory, alignment * 4, alignment);
    }

    return TEST_SUCCESS;
}
