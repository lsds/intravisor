#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MMAP_THRESHOLD 131036

int main(int argc, char **argv)
{
    for(size_t n = 1; n < 2 * MMAP_THRESHOLD; n++)
    {
        void *p = malloc(n);
        if(p == NULL)
        {
            fprintf(stderr, "Failed to allocate memory of size: %zu", n);
            return 1;
        }
        memset(p, 0, n);
        free(p);
    }
    return 0;
}
