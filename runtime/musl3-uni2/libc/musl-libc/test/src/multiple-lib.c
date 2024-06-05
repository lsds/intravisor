#include "multi-lib1.h"
#include "multi-lib2.h"

int main(int argc, char **argv)
{
    if(add(2, 2) != 4) return 1;
    if(multiply(2, 2) != 4) return 2;

    return 0;
}
