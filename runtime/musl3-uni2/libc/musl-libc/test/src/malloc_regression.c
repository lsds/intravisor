#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>

#include "alloc_helpers.h"

int group_map_not_cleaned_on_create()
{
    int **list = NULL;
    int len = 0;
    for (int cnt = 0; cnt < 64; cnt++) {
        if (cnt >= len) {
            len = (len * 2) + 1;
            list = realloc(list, len * sizeof(int *));
            testptr(list, len * sizeof(int *));
        }
        list[cnt] = malloc(sizeof(int));
        testptr(list[cnt], sizeof(int));
        *list[cnt] = cnt;
    }
    return TEST_SUCCESS;
}

int unmap_move_corrupt_nested_group()
{
    struct dirent **namelist = NULL;

    int n = scandir("/proc/self", &namelist, NULL, alphasort);
    printf("%d\n", n);
    return TEST_SUCCESS;
}

int main(int argc, char **argv) {

    switch (argv[1][0]) {
    case '0':
        return group_map_not_cleaned_on_create();
    break;
    case '1':
        return unmap_move_corrupt_nested_group();
    break;
    default:
        return BAD_TEST_NUMBER;
    }
    return TEST_SUCCESS;
}
