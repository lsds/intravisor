#define _GNU_SOURCE

#include <stdio.h>

static int test_fgetln_with_newline();
static int test_fgetln_with_eof();
static int test_fgetln_at_eof();

int main(int argc, char *argv[]) {
    if (argc < 2) return -1;

    switch(argv[1][0]) {
        case '0':
            return test_fgetln_with_newline();
        case '1':
            return test_fgetln_with_eof();
        case '2':
            return test_fgetln_at_eof();
    }

    return -1;
}

static int test_fgetln_with_newline() {
    const char *filename = "resources/test-fgetln-with-newline.dat";
    FILE *f = fopen(filename, "r");
    if (!f) return 1;

    size_t len;
    char *s = fgetln(f, &len);
    if (!__builtin_cheri_tag_get(s)) return 1;
    if (__builtin_cheri_length_get(s) < len) return 1;

    return 0;
}

static int test_fgetln_with_eof() {
    const char *filename = "resources/test-fgetln-with-eof.dat";
    FILE *f = fopen(filename, "r");
    if (!f) return 1;

    size_t len;
    char *s = fgetln(f, &len);
    if (!s) return 1;
    if (!__builtin_cheri_tag_get(s)) return 1;
    if (__builtin_cheri_length_get(s) < len) return 1;

    return 0;
}

static int test_fgetln_at_eof() {
    const char *filename = "resources/test-fgetln-at-eof.dat";
    FILE *f = fopen(filename, "r");
    if (!f) return 1;

    size_t len;
    char *s = fgetln(f, &len);
    if (s) return 1;

    return 0;
}
