#include <stdlib.h>
#include <stdio.h>

void atexit_func(void) {
    printf("exit() called\n");
}

void at_quick_exit_func(void) {
    printf("quick_exit() called\n");
}

void test_exit() {
    atexit(&atexit_func);
    exit(1);
}

void test_quick_exit() {
    at_quick_exit(&at_quick_exit_func);
    quick_exit(1);
}

int main(int argc, char **argv) {
    if (argc < 2) return -1;

    switch(argv[1][0]) {
        case '0':
            test_exit();
        case '1':
            test_quick_exit();
        case '2':
            abort();
        default:
            return -1;
    }

    return 2;
}
