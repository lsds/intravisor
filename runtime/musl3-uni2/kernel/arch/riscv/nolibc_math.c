#include <sys/types.h>
#include "_types.h"
#include <stdarg.h>

#include <string.h>
#include <stdio.h>

#include <bits/float.h>

#include "cheri_helpers.h"
#include "hostcalls.h"

#include <float.h>
#include <math.h>
#include <stdint.h>


double sqrt(double x)
{
	__asm__ ("fsqrt.d %0, %1" : "=f"(x) : "f"(x));
	return x;
}

#if FLT_EVAL_METHOD==0 || FLT_EVAL_METHOD==1
#define EPS DBL_EPSILON
#elif FLT_EVAL_METHOD==2
#define EPS LDBL_EPSILON
#endif
static const double_t toint = 1/EPS;

double rint(double x)
{
	union {double f; uint64_t i;} u = {x};
	int e = u.i>>52 & 0x7ff;
	int s = u.i>>63;
	double_t y;

	if (e >= 0x3ff+52)
		return x;
	if (s)
		y = x - toint + toint;
	else
		y = x + toint - toint;
	if (y == 0)
		return s ? -0.0 : 0;
	return y;
}


long long llrint(double x)
{
	return rint(x);
}

#if FLT_EVAL_METHOD==0
#define EPS FLT_EPSILON
#elif FLT_EVAL_METHOD==1
#define EPS DBL_EPSILON
#elif FLT_EVAL_METHOD==2
#define EPS LDBL_EPSILON
#endif
static const float_t toint_f = 1/EPS;

float rintf(float x)
{
	union {float f; uint32_t i;} u = {x};
	int e = u.i>>23 & 0xff;
	int s = u.i>>31;
	float_t y;

	if (e >= 0x7f+23)
		return x;
	if (s)
		y = x - toint_f + toint_f;
	else
		y = x + toint_f - toint_f;
	if (y == 0)
		return s ? -0.0f : 0.0f;
	return y;
}


long long llrintf(float x)
{
	return rintf(x);
}


long lrintf(float x)
{
	return rintf(x);
}

long lrint(double x)
{
	return rint(x);
}

