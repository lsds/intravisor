#include <sys/types.h>
#include "_types.h"
#include <stdarg.h>

#include <string.h>
#include <stdio.h>

#include <bits/float.h>

#include "cheri_helpers.h"
#include "hostcalls.h"

#include <math.h>

#if 0

int __netf2 (long double a, long double b) {
    printf("not implemened '%s'\n", __func__);
}

long double __extenddftf2 (double a) {
     printf("not implemened '%s'\n", __func__);
}

long double __addtf3 (long double a, long double b) {
    printf("not implemened '%s'\n", __func__);
}

int __eqtf2 (long double a, long double b) {
    printf("not implemened '%s'\n", __func__);
}

long double __multf3 (long double a, long double b) {
    printf("not implemened '%s'\n", __func__);
}

int __unordtf2 (long double a, long double b) {
    printf("not implemened '%s'\n", __func__);
}

long double __subtf3 (long double a, long double b) {
    printf("not implemened '%s'\n", __func__);
}

unsigned int __fixunstfsi (long double a) {
    printf("not implemened '%s'\n", __func__);
}

long double __floatunsitf (unsigned int i) {
    printf("not implemened '%s'\n", __func__);
}

int __fixtfsi (long double a) {
    printf("not implemened '%s'\n", __func__);
}

long double __floatsitf (int i) {
    printf("not implemened '%s'\n", __func__);
}



int __getf2 (long double a, long double b) {
     printf("not implemened '%s'\n", __func__);
}
long double __extendsftf2 (float a) {
     printf("not implemened '%s'\n", __func__);
}
long double __divtf3 (long double a, long double b) {
     printf("not implemened '%s'\n", __func__);
}
float __trunctfsf2 (long double a) {
     printf("not implemened '%s'\n", __func__);
}
double __trunctfdf2 (long double a) {
     printf("not implemened '%s'\n", __func__);
}

 int __letf2 (long double a, long double b) {
      printf("not implemened '%s'\n", __func__);
 }
 
 int __lttf2 (long double a, long double b) {
       printf("not implemened '%s'\n", __func__);
 }
 
int __gttf2 (long double a, long double b) {
       printf("not implemened '%s'\n", __func__);
}
#endif