#include <stdlib.h>
#include <stdio.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// To check for corruption, we fill the start and end of alloc-ed chunk with some data.
// This define how many byte at maximum we fill on each end. This is so big malloc don't
// take tens of seconds to run during the test. If there is enough space to put two
// capabilities, then fill will add them regardless if it is more than this maximum
#define FILL_THICKNESS 128

#include "alloc_helpers.h"

void fill(char* ptr, size_t size)
{
    // fill with "random" data
    int effective_thickness = MIN(size/2,FILL_THICKNESS);
    for(int i = 0; i < effective_thickness; i++){
        ptr[i] = (char)(i ? i : -i) & 255;
    }
    for(int i = size-1; i >= size-1-effective_thickness; i--){
        ptr[i] = (char)(i ? i : -i) & 255;
    }

    // add a capability at the start and at the end
    if(size >= 48){
        size_t offset = ((__uintcap_t) ptr % 16) ? 16 - ((__uintcap_t) ptr % 16): 0;
        void** first_slot = (void**) (ptr + offset);
        void** last_slot = (void**) (ptr + ((size - 16) & ~15));

        // be aware that with a realloc, those capability might be pointing to the old memory.
        // The only thing we can reliably check is the validity tag. Accessing them can segfault
        *first_slot = first_slot;
        *last_slot = last_slot;
    }
}

void check_fill(char* ptr, size_t size)
{
    void** first_slot;
    void** last_slot;
    int effective_thickness = MIN(size/2,FILL_THICKNESS);

    // check the capability at the start and at the end
    if(size >= 48){
        size_t offset = ((__uintcap_t) ptr % 16) ? 16 - ((__uintcap_t) ptr % 16): 0;
        first_slot = (void**) (ptr + offset);
        last_slot = (void**) (ptr + ((size - 16) & ~15));

        // be aware that with a realloc, those capability might be pointing to the old memory.
        // The only thing we can reliably check is the validity tag. Accessing them can segfault
        if(!__builtin_cheri_tag_get(*first_slot) || !__builtin_cheri_tag_get(*last_slot)){
            printf("tag first slot : %d\ntag last slot : %d\n",__builtin_cheri_tag_get(*first_slot),__builtin_cheri_tag_get(*last_slot));
            exit(CAPABILITY_TAG_CLEARED);
        }
    }

    // check the "random" data
    for(int i = 0; i < effective_thickness; i++){
        if (ptr[i] != (char)((i ? i : -i) & 255)){
            // the two capability are legit missmatch, don't report them
            if ( size>=48 && (ptr+i) >= (char*)first_slot && (ptr+i) < ((char*)first_slot+16) )
                continue;
            exit(UNEXPECTED_VALUE);
        }
    }
    for(int i = size-1; i >= size-1-effective_thickness; i--){
        if (ptr[i] != (char)((i ? i : -i) & 255)){
            // the two capability are legit missmatch, don't report them
            if ( size>=48 && (ptr+i) >= (char*)last_slot && (ptr+i) < ((char*)last_slot+16) )
                continue;
            exit(UNEXPECTED_VALUE);
        }
    }
}

void* basic_test(size_t size1, size_t size2)
{
    size_t smaller_size = size1 < size2 ? size1 : size2;
    void* ptr = malloc(size1);
    fill(ptr,smaller_size);
    ptr = realloc(ptr,size2);
    testptr(ptr,size2);
    check_fill(ptr,smaller_size);
    return ptr;
}

void test_fit_in_slot()
{
    void* all_ptr[2];
    all_ptr[0] = basic_test(175*16, 180*16);
    all_ptr[1] = basic_test(16384*16+1, 16384*16+500);

    free(all_ptr[0]);
    free(all_ptr[1]);
}

void test_increase_size()
{
    void* all_ptr[2];
    all_ptr[0] = basic_test(175*16, 300*16);

    all_ptr[1] = basic_test(16384*16+1, 16384*16*2);

    free(all_ptr[0]);
    free(all_ptr[1]);
}

void test_reduce_size()
{
    void* all_ptr[3];
    // just one size class
    all_ptr[0] = basic_test(175*16, 150*16);

    // several size classes
    all_ptr[1] = basic_test(175*16, 40*16);

    all_ptr[2] = basic_test(16384*16+1, 16384*16+500);

    free(all_ptr[0]);
    free(all_ptr[1]);
    free(all_ptr[2]);
}

void test_change_regime()
{
    void* all_ptr[2];
    all_ptr[0] = basic_test(175*16, 16384*16+1);

    all_ptr[1] = basic_test(16384*16+1, 175*16);

    free(all_ptr[0]);
    free(all_ptr[1]);
}

void test_alignment_increase() {
    // Morello alignment requirement increases when resizing to the larger size
    void *ptr = basic_test(32768 - 32, 32768);
    free(ptr);
}

void test_high_count_bounds() {
    // Increase ctx.mmap_counter to increase offset
    for (int i = 0; i < 1000; i++) {
        malloc(i);
    }
    // malloc and realloc to smaller size, testing if data is within
    // slot, and if the offset is appropriate for slack
    for (int i = 1; i < 1000; i++) {
        void* large_alloc = malloc(2328+i);
        large_alloc = realloc(large_alloc, 2328);
    }
}

void test_half_page_alloc() {
    for (int i = 1620; i < 2032; i++) {
	void* ptr = malloc(i);
	free(ptr);
    }
}

int main(int argc, char **argv)
{
    switch (argv[1][0]) {
    case '0': //realloc, but actually fits within the already allocated slot
        test_fit_in_slot();
        break;
    case '1': // realloc, but bigger
        test_increase_size();
        break;
    case '2': // realloc, but smaller
        test_reduce_size();
        break;
    case '3': // realloc, but change of regime (sizeclass <-> big alloc)
        test_change_regime();
        break;
    case '4':
        test_alignment_increase();
        break;
    case '5': // realloc, with one page/slot groups and high mmap_count
        test_high_count_bounds();
        break;
    case '6': // realloc, checking offset valid with half page slots
        test_half_page_alloc();
        break;
    default:
        return BAD_TEST_NUMBER;
    }
    return TEST_SUCCESS;
}
