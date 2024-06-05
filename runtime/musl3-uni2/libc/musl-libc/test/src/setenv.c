#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    const char* world = "world";
    const char* universe = "universe";

    //check that the env var used for this test is set appropriately
    char* val1 = getenv("HELLO");
    if (!val1 || strcmp(val1,world)) return 1;

    //check that it does not override when it's not told to do so
    setenv("HELLO", universe, 0);
    char* val2 = getenv("HELLO");
    if (!val2 || strcmp(val2,world)) return 2;

    //check that it *does* override when told to
    setenv("HELLO", universe, 1);
    char* val3 = getenv("HELLO");
    if (!val3 || strcmp(val3,universe)) return 3;

    //check that it can add a new env var
    char* val4 = getenv("THISVARDONTEXIST");
    if (val4 != NULL) return 4;
    setenv("THISVARDONTEXIST", world, 0);
    char* val5 = getenv("THISVARDONTEXIST");
    if (!val5 || strcmp(val5,world)) return 5;

    return 0;
}
