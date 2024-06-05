#include "third-party-pointer-lib.h"
#include <stdlib.h>

void zero_array(int *array, size_t length)
{
    for(size_t i = 0; i < length; i++)
    {
        array[i] = 0;
    }
}

int* malloc_array(size_t length)
{
    return malloc(sizeof(int) * length);
}
