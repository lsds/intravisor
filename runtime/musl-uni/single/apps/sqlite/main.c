#include <stdio.h>
#include <stdlib.h>

extern int speedtest_main(int argc, char **argv);



void app_main() {
    speedtest_main(1, 0);
}