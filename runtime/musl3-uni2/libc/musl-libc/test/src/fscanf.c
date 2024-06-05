#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <stdint.h>

int floatCompare (const float f1, const float f2)
{
   return f1 == f2 || fabs(f1 - f2) <= 1.0e-5f * fmax(fabs(f1), fabs(f2));
}

int main (int argc, char *argv[])
{
    // slots to receive the values scanned
    char words[4][8] = {{'\0'},{'\0'},{'\0'},{'\0'}};
    char small_int = 0;
    long long big_int = 0;
    float small_float = 0.0f;
    double big_float = 0.0f;
    void * capability = &small_int; //filling it to later check parts being set to NULL
    char* undefined_string = NULL;

    // inputs expected on stdin
    char* expected_words[4] = {"match","those","words","exactly"};

    // 25 -63 101 3d
    long long expected_int[4] = {25, -63, 65, 61};

    // We are assuming that FLT_MAX == 3.402823e+38 here. We use something around 20 * FLT_MAX
    // The point here is that the second number can't fit in a float.
    double expected_double[2] = {-2.365, 6.805646e+39 };

    // some made up address trying to avoid some obvious patterns
    // 1111000011100011001011110000111000110010111100001110001100101010
    // F0E32F0E32F0E32A
    uintptr_t expected_adress = 17357769126846718762u;

    unsigned int tmp = 0;

    switch (argv[1][0]) {
    case '0': // int, be it signed or not, or even other base
        if ((tmp=fscanf(stdin,"%hhd",&small_int)) != 1) {
            printf("fscanf returned %d\n",tmp);
            return 1;
        }
        if (small_int != expected_int[0]) {
            printf("expected : %lld\nreceived : %hhd\n",expected_int[0],small_int);
            return 2;
        }

        if ((tmp=fscanf(stdin,"%lld",&big_int)) != 1) {
            printf("fscanf returned %d\n",tmp);
            return 1;
        }
        if (big_int != expected_int[1]) {
            printf("expected : %lld\nreceived : %lld\n",expected_int[1],big_int);
            return 2;
        }

        // base 8
        if ((tmp=fscanf(stdin,"%llo",&big_int)) != 1) {
            printf("fscanf returned %d\n",tmp);
            return 1;
        }
        if (big_int != expected_int[2]) {
            printf("expected : %lld\nreceived : %lld\n",expected_int[2],big_int);
            return 2;
        }

        // base 16
        if ((tmp=fscanf(stdin,"%llx",&big_int)) != 1) {
            printf("fscanf returned %d\n",tmp);
            return 1;
        }
        if (big_int != expected_int[3]) {
            printf("expected : %lld\nreceived : %lld\n",expected_int[3],big_int);
            return 2;
        }
        break;
    case '1': // exact words
        if ((tmp=fscanf(stdin,"match%lld",&big_int)) != 1) {
            printf("fscanf returned %d\n",tmp);
            return 1;
        }
        if (big_int != expected_int[1]) {
            printf("expected : %lld\nreceived : %lld\n",expected_int[1],big_int);
            return 2;
        }
        break;
    case '2': // float
        if ((tmp=fscanf(stdin,"%f",&small_float)) != 1) {
            printf("fscanf returned %d\n",tmp);
            return 1;
        }
        if (! floatCompare(small_float,expected_double[0])) {
            printf("expected : %lf\nreceived : %f\n",expected_double[0],small_float);
            return 2;
        }

        if ((tmp=fscanf(stdin,"%lf",&big_float)) != 1) {
            printf("fscanf returned %d\n",tmp);
            return 1;
        }
        if (! floatCompare(big_float,expected_double[1])) {
            printf("expected : %lf\nnreceived : %lf\n",expected_double[1],big_float);
            return 2;
        }
        break;
    case '3': // char
        if ((tmp=fscanf(stdin,"%c%c%c%c%c",&words[0][0],
                                      &words[0][1],
                                      &words[0][2],
                                      &words[0][3],
                                      &words[0][4])) != 5) {
            printf("fscanf returned %d\n",tmp);
            return 1;
        }
        words[0][5] = '\0';
        if (strcmp(words[0],expected_words[0])) {
            printf("expected : %s\nreceived : %s\n",expected_words[0],words[0]);
            return 2;
        }
        break;
    case '4': // string
        if ((tmp=fscanf(stdin,"%s%s%s%s",words[0],words[1],words[2],words[3])) != 4) {
            printf("fscanf returned %d\n",tmp);
            return 1;
        }
        for (unsigned int i=0; i<4; i++) {
            if (strcmp(words[i],expected_words[i])) {
                printf("expected : %s\nreceived : %s\n",expected_words[i],words[i]);
                return 2;
            }
        }
        break;
    case '5': // match only a set of letters
        if ((tmp=fscanf(stdin,"%[star]%[^star]",words[0],words[1])) != 2) {
            printf("fscanf returned %d\n",tmp);
            return 1;
        }
        if (strcmp(words[0],"start")) {
            printf("expected : %s\nreceived : %s\n","start",words[0]);
            return 2;
        }
        if (strcmp(words[1],"end")) {
            printf("expected : %s\nreceived : %s\n","end",words[1]);
            return 2;
        }
        break;
    case '6': // consume, but discard value (*)
        if ((tmp=fscanf(stdin,"%*lld %lld",&big_int)) != 1) {
            printf("fscanf returned %d\n",tmp);
            return 1;
        }
        if (big_int != expected_int[1]) {
            printf("expected : %lld\nreceived : %lld\n",expected_int[1],big_int);
            return 2;
        }
        break;
    case '7': // positional args
        if ((tmp=fscanf(stdin,"%2$hhd %1$lld",&big_int,&small_int)) != 2) {
            printf("fscanf returned %d\n",tmp);
            return 1;
        }
        if (small_int != expected_int[0]) {
            printf("expected : %lld\nreceived : %hhd\n",expected_int[0],small_int);
            return 2;
        }
        if (big_int != expected_int[1]) {
            printf("expected : %lld\nreceived : %lld\n",expected_int[1],big_int);
            return 2;
        }
        break;
    case '8': // pointers/capabilities
        if ((tmp=fscanf(stdin,"%p",&capability)) != 1) {
            printf("fscanf returned %d\n",tmp);
            return 1;
        }

        if (__builtin_cheri_address_get(capability) != expected_adress) return 2;
        if (
            __builtin_cheri_tag_get(capability) != 0 ||
            __builtin_cheri_perms_get(capability) != 0 ||
            __builtin_cheri_length_get(capability) != (0xFFFFFFFFFFFFFFFF)) {
            printf("fscanf didn't set the null capability metadata correctly : \n\
tag : %d\nperms : %lu\nlength : %lu",
                    __builtin_cheri_tag_get(capability),
                    __builtin_cheri_perms_get(capability),
                    __builtin_cheri_length_get(capability));
            return 3;
        }
        break;
    case '9': // %m
        if ((tmp=fscanf(stdin,"%ms",&undefined_string)) != 1) {
            printf("fscanf returned %d\n",tmp);
            return 1;
        }
        if (__builtin_cheri_tag_get(undefined_string) == 0 ||
            __builtin_cheri_perms_get(undefined_string) == 0 ||
            __builtin_cheri_length_get(undefined_string) < strlen(expected_words[0])+1 )
        {
            return 3;
        }
        if (strcmp(undefined_string,expected_words[0]) != 0) {
            printf("expected : %s\nreceived : %s\n",expected_words[0],undefined_string);
            return 2;
        }
        break;
    default:
        return 3;
    }
    return 0;
}
