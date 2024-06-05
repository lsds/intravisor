#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <link.h>

int main(void)
{
    void *handle;
    double (*pow)(double, double);
    char *error;
    struct link_map *map;
    Dl_info info;

#ifndef DYNAMIC
    /* If compiled statically, just return 0 as dlfcn functions will not work. */
    return 0;
#endif

    handle = dlopen("libm.so.6", RTLD_LAZY);
    if (handle == NULL)
    {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    error = dlerror();
    if (error != NULL)
    {
        fprintf(stderr, "DLOpen: %s\n", error);
        return 2;
    }

    pow = (double (*)(double, double))dlsym(handle, "pow");

    error = dlerror();
    if (error != NULL)
    {
        fprintf(stderr, "DLSYM: %s\n", error);
        return 3;
    }

    dlinfo(handle, RTLD_DI_LINKMAP, &map);
    error = dlerror();
    if (error != NULL)
    {
        fprintf(stderr, "DLInfo: %s\n", error);
        return 4;
    }

    dladdr((void *)pow, &info);

    if(strcmp("pow", info.dli_sname) != 0)
    {
        fprintf(stderr, "DLaddr returned unexpected information.\n");
        return 5;
    }

    if (((*pow)(2.0, 2.0)) != 4.0)
    {
        fprintf(stderr, "Failed to use function pow, incorrect result.\n");
        return 6;
    }

    dlclose(handle);

    return 0;
}
