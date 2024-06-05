#include "dependency-lib2.h"

int main(int argc, char **argv)
{
    if(add_multiply(2, 2, 2) != 8) return 1;

    return 0;
}
