#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "alloc_helpers.h"

#define max_malloc 300 //min 33. Mainly used to size test #3

int main(int argc, char **argv) {
    void* all_ptr[max_malloc];

    switch (argv[1][0]) {
    case '0'://basic test to run malloc and check the capability validity
        // test allocating seveal slot of the same size
        all_ptr[0] = malloc(150);
        all_ptr[1] = malloc(150);
        testptr(all_ptr[0], 150);

        // test the limit of a slot's size
        all_ptr[2] = malloc(511);
        testptr(all_ptr[2], 511);

        // test a dedicated mmap
        all_ptr[3] = malloc(32768);
        testptr(all_ptr[3], 32768);

        break;
    case '1'://basic test for free
        all_ptr[0] = malloc(150);
        testptr(all_ptr[0], 150);
        //printf("malloc return : %p\n",all_ptr[0]);
        free(all_ptr[0]);
        all_ptr[1] = malloc(16*32768);
        testptr(all_ptr[1], 16*32768);
        //printf("malloc return : %p\n",all_ptr[0]);
        free(all_ptr[1]);
        break;

    case '2':// tries to fill a few group, make some space, refill. In case there is some corruption of the metadata on free
        for (int i = 0; i < max_malloc; i++){
            all_ptr[i] = malloc(63);
            testptr(all_ptr[i], 63);
        }
        for (int i = 0; i < max_malloc; i+=2){
            free(all_ptr[i]);
        }
        for (int i = 0; i < max_malloc; i+=2){
            all_ptr[i] = malloc(63);
            testptr(all_ptr[i], 63);
        }
        break;
    case '3':// Check that the data don't overlaps with the metadata or some other data
        // allocate all slots
        for (int i = 0; i < 33; i++){
            all_ptr[i] = malloc(63);
            testptr(all_ptr[i], 63);
        }
        // fill them with two set of data, in case some corruption match one set
        for (int i = 0; i < 33; i++){
            for (int j = 0; j < 63; j++){
                ((char *)all_ptr[i])[j] = j%2 ? j : -j;
            }
        }
        // check there is no overlap
        for (int i = 0; i < 33; i++){
            for (int j = 0; j < 63; j++){
                char val = ((char *)all_ptr[i])[j];
                char expected = (j%2 ? j : -j); //I have to put this value in a variable. Making a direct comparison fails.
                if (val != expected){
                    printf("Some byte seems corrupted. Value : [%hhd, %#02X], j : %d, expected : %d\n", val, val, j, expected);
                    return UNEXPECTED_VALUE;
                }
            }
        }
        for (int i = 0; i < 33; i+=3){
            free(all_ptr[i]);
        }
        // check again the sets, in case free overwrote some neighbour slots
        for (int i = 0; i < 33; i++){
            if (i%3==0)
                continue;
            for (int j = 0; j < 63; j++){
                char val = ((char *)all_ptr[i])[j];
                char expected = (j%2 ? j : -j);
                if (val != expected){
                    printf("Some byte seems corrupted after some free(). Value : [%hhd, %#02X], j : %d, expected : %d\n", val, val, j, expected);
                    return UNEXPECTED_VALUE;
                }
            }
        }
        break;
    case '4'://segfault on use after free
        /**
         * This test has been removed
         */
        return BAD_TEST_NUMBER;
        break;
    case '5'://segfault on double free
        all_ptr[0] = malloc(16*32768);
        testptr(all_ptr[0], 16*32768);
        free(all_ptr[0]);
        free(all_ptr[0]);

        break;
        //TODO needs some tests on the narrow bounds of malloc. Ideally, we want the user to only be able to access the slot they requested,
        //and not be able to mess with the metadata, not with other adjacent slots. Currently this narrow bound mechanism is not implemented
        //because free need the wide capability to work. Some mechanism have to be added to find the wide capability from the narrowed one.
    case '6':// check malloc(SIZE_MAX) fails with ENOMEM
        all_ptr[0] = malloc(SIZE_MAX);
        if (all_ptr[0]) {
            printf("malloc(SIZE_MAX) succeeded unexpectedly\n");
            return UNEXPECTED_VALUE;
        }

        if (errno != ENOMEM) {
            printf("malloc(SIZE_MAX) failed with an unexpected errno: %d\n", errno);
            return UNEXPECTED_VALUE;
        }
        break;
    default:
        return BAD_TEST_NUMBER;
    }
    return TEST_SUCCESS;
}
