#include "third-party-pointer-lib.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
    size_t length = 10;
    int* array = malloc(sizeof(int) * length);

    zero_array(array, length);

    for(size_t i = 0; i < length; i++)
    {
        if(array[i] != 0) return 1;
    }

    int *array2 = malloc_array(length);

    for(size_t i = 0; i < length; i++)
    {
        array2[i] = 1;
    }

    return 0;
}
