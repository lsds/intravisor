#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

static int test_getw_eof();
static int test_getw_not_eof();

int main(int argc, char *argv[]) {
    if (argc < 2) return -1;

    switch(argv[1][0]) {
        case '0':
            return test_getw_eof();
        case '1':
            return test_getw_not_eof();
    }

    return -1;
}

static int test_getw_eof() {
    const char *filename = "resources/test-getw-eof.dat";
    FILE *f = fopen(filename, "r");
    if (!f) return 1;

    if (getw(f) != EOF) return 1;

    return 0;
}

static int test_getw_not_eof() {
  const char *filename = "resources/test-getw-not-eof.dat";
  FILE *f = fopen(filename, "r");
  if (!f) return 1;

  if (getw(f) != 0) return 1;
  if (getw(f) != 1) return 1;
  if (getw(f) != -1) return 1;

  return 0;
}
