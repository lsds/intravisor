#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int test_atof();
int test_evct_fcvt_gcvt();

int main(int argc, char **argv) {
    if (argc < 2) return -1;

    switch(argv[1][0]) {
        case '0': // atof
            return test_atof();
        case '1': // evct
            return test_evct_fcvt_gcvt();
    }

    return -1;
}

int test_atof() {
    char str[] = "1.5";
    if(atof(str) != 1.5f) return 1;

    return 0;
}

int test_evct_fcvt_gcvt() {
    int decpt;
    int sign;

    double dvalue = 1.25;
    float fvalue = 1.25;

    char *str = ecvt(dvalue, 4, &decpt, &sign);
    if (strcmp(str, "1250")) return 1;
    if (decpt != 1) return 2;
    if (sign != 0) return 3;

    str = fcvt(fvalue, 4, &decpt, &sign);
    if (strcmp(str, "12500")) return 4;
    if (decpt != 1) return 5;
    if (sign != 0) return 6;

    char buf[32];
    gcvt(dvalue, 3, buf);
    if (strcmp(buf, "1.25")) return 7;

    return 0;
}
