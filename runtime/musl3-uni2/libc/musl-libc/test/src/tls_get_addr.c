#include <stdio.h>
#include <dlfcn.h>
#include <link.h>
#include <unistd.h>

int main(void)
{

#ifndef DYNAMIC
    /* If built statically, return 0 as dlsym functions will not work. */
    return 0;
#endif

    int result = 0;

    /* Due to this relative path, the dynamic test will only work
     * when run from /musl/test/src (which is where the automatic
     * tester runs). */
    void *handle = dlopen("./lib/libstt-tls-symbol-lib.so", RTLD_LAZY);
    if (handle == NULL) return 1;

    void *cap_foo = dlsym(handle, "foo");
    void *cap_bar = dlsym(handle, "bar");
    void *cap_baz = dlsym(handle, "baz");

    printf("foo: %#p\n", cap_foo);
    printf("bar: %#p\n", cap_bar);
    printf("baz: %#p\n", cap_baz);

    if (cap_foo == NULL || cap_bar == NULL || cap_baz == NULL) {
        result = 2; goto done;
    }

    if (__builtin_cheri_length_get(cap_foo) != sizeof(int)
        || !__builtin_cheri_tag_get(cap_foo)) {
        result = 3; goto done;
    }

    if (__builtin_cheri_length_get(cap_bar) != sizeof(double)
        || !__builtin_cheri_tag_get(cap_bar)) {
        result = 3; goto done;
    }

    if (__builtin_cheri_length_get(cap_baz) != sizeof(double)
        || !__builtin_cheri_tag_get(cap_baz)) {
        result = 3; goto done;
    }

done:
    dlclose(handle);
    return result;
}
