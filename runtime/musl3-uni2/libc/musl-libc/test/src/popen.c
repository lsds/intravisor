#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = malloc(64);
    FILE *fp = popen("cat /proc/self/cmdline", "r");
    if (!fp) return 1;

    if (!fgets(buf, 64, fp)) return 2;
    if (strcmp(buf, "cat")) return 3;

    if (pclose(fp)) return 4;

    return 0;
}
