#include "third-party-library.h"
#include "symbol-library.h"

int main(int argc, char **argv)
{
    if(foo != 10) return 1;
    if(multiply(1, foo) != 10) return 2;

    return 0;
}
