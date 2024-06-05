#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "temp_file_helpers.h"

char DIR_PATH[PATH_MAX];
#define IN_TMP_DIR(f) TMP_DIR f

static int test_putw_read_only();
static int test_putw_write_only();

int main(int argc, char *argv[]) {
    if (argc < 2) return -1;

    if(create_temp_directory("morello-musl-tests-open/", DIR_PATH) != 0)
        return -1;

    switch(argv[1][0]) {
        case '0':
            return test_putw_read_only();
        case '1':
            return test_putw_write_only();
    }

    return -1;
}

static int test_putw_read_only() {
    if (putw(0, stdin) != EOF) return 1;

    return 0;
}

static int test_putw_write_only() {
    char filename_buffer[PATH_MAX];
    char *filename = create_temp_file(DIR_PATH, "testXXXXXX", &filename_buffer[0]);

    FILE *f = fopen(filename, "w");
    if (!f) return 1;

    if (putw(0, f) == EOF) return 1;

    return 0;
}
