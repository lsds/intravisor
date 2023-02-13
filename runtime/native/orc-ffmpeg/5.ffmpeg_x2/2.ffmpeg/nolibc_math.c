#include <sys/types.h>
#include "_types.h"
#include <stdarg.h>

#include <string.h>
#include <stdio.h>

#include <bits/float.h>

#include "cheri_helpers.h"
#include "hostcalls.h"

#include <math.h>


double sqrt(double x)
{
    __asm__ ("fsqrt %d0, %d1" : "=w"(x) : "w"(x));
    return x;
}

long long llrint(double x)
{
    long long n;
    __asm__ (
	"frintx %d1, %d1\n"
	"fcvtzs %x0, %d1\n" : "=r"(n), "+w"(x));
    return n;
}


long long llrintf(float x)
{
    long long n;
    __asm__ (
	"frintx %s1, %s1\n"
	"fcvtzs %x0, %s1\n" : "=r"(n), "+w"(x));
    return n;
}

long lrintf(float x)
{
    long n;
    __asm__ (
	"frintx %s1, %s1\n"
	"fcvtzs %x0, %s1\n" : "=r"(n), "+w"(x));
    return n;
}

long lrint(double x)
{
    long n;
    __asm__ (
	"frintx %d1, %d1\n"
	"fcvtzs %x0, %d1\n" : "=r"(n), "+w"(x));
    return n;
}

