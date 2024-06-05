#define _GNU_SOURCE
#include <stdio.h>
#include <link.h>

#ifdef DYNAMIC
/**
 * This test is link with the libstt-tls-symbol-lib.so library
 * from the lib folder (see test_dl_iterate_phdr.mk).
 * This custom library has TLS symbols.
 */
#define EXP_SIZE 24
#else
/**
 * Use global TLS variable for statically linked test.
 */
__thread int tls_var = 0;
#define EXP_SIZE 4
#endif

static int callback(
    struct dl_phdr_info *info,
    size_t size, void *data);

int main(void)
{
    int res = 1;
    dl_iterate_phdr(callback, &res);
    return res;
}

static int callback(
    struct dl_phdr_info *info,
    size_t size, void *res)
{
    printf("%s: id = %lu tls = %#p\n",
        info->dlpi_name,
        info->dlpi_tls_modid,
        info->dlpi_tls_data);

    if (info->dlpi_tls_modid) {
        /* Bounds of the tls data should be set. */
        *(int *)res = (__builtin_cheri_length_get(info->dlpi_tls_data) == EXP_SIZE) ? 0 : 2;
    }

    return 0;
}
