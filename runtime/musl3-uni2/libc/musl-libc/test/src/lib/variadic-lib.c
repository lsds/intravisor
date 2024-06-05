#include "variadic-lib.h"
#include <stdarg.h>
#include <stdio.h>

int variadic(int args, ...)
{
    va_list vargs;
    va_start(vargs, args);

    if(args != 1) return 1;
    if(va_arg(vargs, int) != 2) return 2;
    if(va_arg(vargs, int) != 3) return 3;

    return 0;
}
