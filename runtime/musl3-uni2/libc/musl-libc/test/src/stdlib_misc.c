#define _GNU_SOURCE

#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

int test_setkey_encrypt();
int test_realpath();
int test_system();

int main(int argc, char **argv) {
    if (argc < 2) return -1;

    switch(argv[1][0]) {
        case '0': // setkey, encrypt
            return test_setkey_encrypt();
        case '1': // realpath
            return test_realpath();
        case '2': // system
            return test_system();
    }

    return -1;
}

int test_setkey_encrypt() {
    char bytes[64] = {
        0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    };
    setkey(bytes);

    encrypt(bytes, 0);

    return 0;
}

int test_realpath() {
    char rp[PATH_MAX];
    if(!realpath("/proc/self/exe", rp)) return 1;

    return 0;
}

int test_system() {
    if(!system(NULL)) return 1;

    return 0;
}
