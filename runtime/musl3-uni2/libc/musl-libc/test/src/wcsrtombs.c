#include <wchar.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>

int main(int argc, char **argv) {
    if (argc <=1)
        return 4;

    /* ISO C standard sets default locale to 'C', update to be musl default locale. */
    setlocale(LC_ALL, "");

    // UTF-8 narrow multibyte encoding
    const char* expected_str = "z\u00df\u6c34\U0001d10b"; // or u8"zß水𝄋"
                    // or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9d\x84\x8b";
    const wchar_t* expected_wcstr = L"z\u00df\u6c34\U0001d10b"; // or L"zß水𝄋"
    const size_t expected_size = 10;
    char mbstr[sizeof(expected_str)] = {0};
    wchar_t wcstr[sizeof(expected_wcstr)] = {0};
    mbstate_t state = (mbstate_t){0};

    unsigned int n = 0;

    n += mbrtowc(wcstr+0, expected_str+n, sizeof(expected_str)-n, &state);
    n += mbrtowc(wcstr+1, expected_str+n, sizeof(expected_str)-n, &state);
    n += mbrtowc(wcstr+2, expected_str+n, sizeof(expected_str)-n, &state);
    n += mbrtowc(wcstr+3, expected_str+n, sizeof(expected_str)-n, &state);
    wcstr[4] = L'\0';
    // quick check that the conversion from mb to wc work fine for sanity's sake
    if (n != expected_size || !mbsinit(&state)) {
        printf("mbrtowc failed while setting up the variable for testing wcsrtombs : ");
        if (!mbsinit(&state)) {
            printf("Bad mbstate -> invalid conversion ?\n");
        } else {
            printf("Number of byte consumed don't match expected. Expected %zu, got %u\n",expected_size,n);
        }
        return 1;
    }
    state = (mbstate_t){0};

    mbstate_t* state_ptr = &state;
    // Convert from array type to pointer type. Also make the char const otherwise clang complains when calling wcsrtombs
    const wchar_t* wcstr_ptr = (const wchar_t*) &wcstr;
    const wchar_t** wcstr_ptr_ptr = &wcstr_ptr;

    int len = 0;
    switch (argv[1][0]) {
    case '0':
        len = wcsrtombs(NULL, wcstr_ptr_ptr, 0, state_ptr);
        // test the usecase of using wcsrtombs to get the expected output string length
        if (__builtin_cheri_tag_get(state_ptr) != 1) return 2;
        if (__builtin_cheri_tag_get(wcstr_ptr_ptr) != 1) return 2;
        if (!mbsinit(&state)) return 3;
        if (expected_size != len) {
            printf("Size does not match expected. Got : %d, expected %zu\n",len,expected_size);
            return 4;
        }
        break;
    case '1':
        // test the usecase of using wcsrtombs to actually do the conversion
        wcsrtombs(mbstr, wcstr_ptr_ptr, sizeof(mbstr), state_ptr);
        if (__builtin_cheri_tag_get(state_ptr) != 1) return 2;
        if (__builtin_cheri_tag_get(wcstr_ptr_ptr) != 1) return 2;
        if (!mbsinit(&state)) return 3;
        if (strcmp(mbstr,expected_str)) {
            // The proper print is disabled because jenkins's runner don't like multibyte chars.
            //printf("string don't match what's expected. Got : %s, expected %s\n",mbstr,expected_str);
            printf("string does not match expected.");
            return 4;
        }
        break;
    default :
        return 3;
    }
    return 0;
}
