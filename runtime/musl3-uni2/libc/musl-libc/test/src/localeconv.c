#include <locale.h>
#include <limits.h>
#include <string.h>

int main (int argc, char *argv[])
{
    struct lconv * local = localeconv();

    unsigned long perm = __builtin_cheri_perms_get(local);

    switch (argv[1][0]) {
    case '0':// test validity of the capability
        if ( ! __builtin_cheri_tag_get(local) ) return 1;
        break;
    case '1':// test reading char
        if (((perm & __CHERI_CAP_PERMISSION_PERMIT_LOAD__) == 0) || (local->int_frac_digits != CHAR_MAX)) return 1;
        break;
    case '2':// test writing char (should fail)
        if ((perm & __CHERI_CAP_PERMISSION_PERMIT_STORE__) != 0) return 1;
        local->int_frac_digits = '\001';
        return 2;
        break;
    case '3':// test reading string
        if (((perm & __CHERI_CAP_PERMISSION_PERMIT_LOAD_CAPABILITY__) == 0) || (strcmp(local->decimal_point,".") != 0)) return 1;
        break;
    case '4':// test writing string (should fail)
        if ((perm & __CHERI_CAP_PERMISSION_PERMIT_STORE_CAPABILITY__) != 0) return 1;
        local->decimal_point[0] = ',';
        return 2;
        break;
    default:
        return 3;
    }
    return 0;
}
