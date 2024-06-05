#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>


#define MALLOC_ATTEMPTS 10
#define MEM_SIZE 8191
/**
 * For a donated memory size of 8191B, musl will see that the the group size of
 * (510*16)+32 = 8192 is insufficient, and then allocate
 * (254*16)+32 = 4096 (leaving 4095), then allocate
 * (127*16)+32 = 2064 (leaving 2031), then allocate
 * (63*16)+32 = 1040 (leaving 991), then allocate
 * (31*16)+32 = 528 (leaving 463), then allocate
 * (15*16)+32 = 272 (leaving 191), then allocate
 * (8*16)+32 = 160 (leaving 31), then stop
 */
#ifndef DYNAMIC
static char memory[MEM_SIZE];
int blockSizes[] = {4096, 2064, 1040, 528, 272}; // we dont test the smallest block

#define NUM_SIZES sizeof(blockSizes)/sizeof(int)

void __malloc_donate(char *start, char *end);
#endif


int main() {

#ifdef DYNAMIC
    printf("Cannot test with dynamic linking\n");
    return 0;
#else

    char *pointers[MALLOC_ATTEMPTS][NUM_SIZES];
    char *lowerBound = memory, *upperBound = memory+MEM_SIZE;
    printf("Lower bound: %#p\n", (void *) lowerBound);
    printf("Upper bound: %#p\n", (void *) upperBound);

    int allInDonatedMem = 1;

    __malloc_donate(lowerBound, upperBound);

    for (int idx=0; idx<NUM_SIZES; ++idx) {
        // Making the malloc size smaller than the block size to account for group header
        // and slot metadata. Not trying to be exact but to check if donated memory is used
        // and allow the test to pass
        int mallocSize = blockSizes[idx] - 100;
        int inDonatedMemory = 0;
        printf("\n");
        for (int attempt=0; attempt<MALLOC_ATTEMPTS; ++attempt) {
            char *p = malloc(mallocSize);
            printf("%#p\n", (void*) p);
            inDonatedMemory |= (p>lowerBound && p<upperBound);
            pointers[attempt][idx] = p;
        }

        allInDonatedMem &= inDonatedMemory;
    }

    for (int idx=0; idx<NUM_SIZES; ++idx)
        for (int attempt=0; attempt<MALLOC_ATTEMPTS; ++attempt)
            free(pointers[attempt][idx]);

    if (allInDonatedMem)
        return 0;
    else
        return 1;

#endif // define DYNAMIC
}
