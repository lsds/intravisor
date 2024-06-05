#include <sys/auxv.h>
#include <stdio.h>
#include <errno.h>

int main (int argc, char *argv[]) {
    char *platform = (char *) getauxptr(AT_PLATFORM);
    unsigned long perms = __builtin_cheri_perms_get(platform);

    if (!__builtin_cheri_tag_get(platform)) return 1;
    if (!(perms & __CHERI_CAP_PERMISSION_PERMIT_LOAD__)) return 2;

    void *x = getauxptr(AT_HWCAP);
    if (x) return 3;
    if (errno != ENOENT) return 4;

    long y = getauxval(AT_PHDR);
    if (y) return 5;
    if (errno != ENOENT) return 6;

    long arg_length = getauxval(AT_ARGC);
    if(arg_length != argc)
    {
        printf("Error: getauxval did not return correct arg count.\n");
        return 6;
    }

    void *arg = getauxptr(AT_ARGV);
    if(arg != argv)
    {
        printf("Error: getauxptr did not return correct arg address.\n");
        return 7;
    }

    return 0;
}
