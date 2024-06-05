#include "lib/capinit-lib.h"
#include <stdio.h>

volatile int* PTR = &GLOBAL_VARIABLE;

int main(int argc, char **argv)
{
    int x = 5;
    printf("%p %d\n", (void *)PTR, *PTR);
    PTR = &x;
    printf("%p %d\n", (void *)PTR, *PTR);
    return 0;
}
