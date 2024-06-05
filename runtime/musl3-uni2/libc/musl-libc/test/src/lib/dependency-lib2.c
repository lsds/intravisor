#include "dependency-lib2.h"
#include "dependency-lib1.h"

int add_multiply(int num1, int num2, int num3)
{
    return add(num1, num2) * num3;
}
