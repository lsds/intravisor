#include <stdio.h>
#include <uchar.h>
#include <wchar.h>
#include <locale.h>

int check_result(size_t len, size_t expected_len, void* wcp, mbstate_t* stp)
{
    unsigned return_value = 0;
    if (len == (size_t) -1) {
        printf("error in mbrtowc: invalid multibyte sequence\n");
        return_value |= 1;
    }
    if (len == (size_t) -2) {
        printf("error in mbrtowc: couldn't parse a complete multibyte character\n");
        return_value |= 1;
    }
    if (len != expected_len) {
        printf("mbrtowc did not read the correct number of byte. Expected %zu but got %zu\n",expected_len,len);
        return_value |= 2;
    }

    if (!__builtin_cheri_tag_get(wcp) || !__builtin_cheri_tag_get(stp)) {
        printf("mbrtowc cleared the capability tag of its IO parameters\n");
        return_value |= 4;
    }
    if (*(unsigned *) stp != 0) {
        printf("mbrtowc outputed a non clean mbstate\n");
        return_value |= 8;
    }

    if (return_value) {
        printf("chars %hhx %hhx %hhx %hhx (assuming little endian)\n",((char*) wcp)[3],((char*) wcp)[2],((char*) wcp)[1],((char*) wcp)[0]);
    }
    return return_value;
}

int test_mbrtowc(void)
{
    wchar_t wc = 0;
    mbstate_t st = (mbstate_t){0};
    wchar_t* wcp = &wc;
    mbstate_t* stp = &st;
    const char* src = "z\u00df\u6c34\U0001d10b"; // or u8"zß水𝄋"
                      // or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9d\x84\x8b";
    unsigned int remaining_char = 11;
    int return_value = 0;
    size_t len;

    len = mbrtowc(wcp, src, remaining_char, stp);
    if ((return_value = check_result(len,1,(void*)wcp,stp))) return return_value;
    src += len, remaining_char -= len;

    len = mbrtowc(wcp, src, remaining_char, stp);
    if ((return_value = check_result(len,2,(void*)wcp,stp))) return return_value;
    src += len, remaining_char -= len;

    len = mbrtowc(wcp, src, remaining_char, stp);
    if ((return_value = check_result(len,3,(void*)wcp,stp))) return return_value;
    src += len, remaining_char -= len;

    len = mbrtowc(wcp, src, remaining_char, stp);
    if ((return_value = check_result(len,4,(void*)wcp,stp))) return return_value;
    src += len, remaining_char -= len;

    return 0;
}

int test_mbtoc16(void) {
    mbstate_t st = (mbstate_t){0};
    char16_t c16p[2];
    mbstate_t* stp = &st;
    const char* src = "z\u00df\u6c34\U0001d10b"; // or u8"zß水𝄋"
                      // or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9d\x84\x8b";
    unsigned int remaining_char = 11;
    int return_value = 0;
    size_t len;

    len = mbrtoc16(c16p, src, remaining_char, stp);
    if ((return_value = check_result(len,1,(void*)c16p,stp))) return return_value;
    src += len, remaining_char -= len;

    len = mbrtoc16(c16p, src, remaining_char, stp);
    if ((return_value = check_result(len,2,(void*)c16p,stp))) return return_value;
    src += len, remaining_char -= len;

    len = mbrtoc16(c16p, src, remaining_char, stp);
    if (*(int*)stp && mbrtoc16(&c16p[1], src, remaining_char, stp) != -3) return 16;
    if ((return_value = check_result(len,3,(void*)c16p,stp))) return return_value;
    src += len, remaining_char -= len;

    len = mbrtoc16(c16p, src, remaining_char, stp);
    if (*(int*)stp && mbrtoc16(&c16p[1], src, remaining_char, stp) != -3) return 16;
    if ((return_value = check_result(len,4,(void*)c16p,stp))) return return_value;
    src += len, remaining_char -= len;

    return 0;
}

int test_mbsnrtowcs(void) {
    mbstate_t st = (mbstate_t){0};
    wchar_t wcp[10];
    mbstate_t* stp = &st;
    const char* src = "z\u00df\u6c34\U0001d10b"; // or u8"zß水𝄋"
                      // or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9d\x84\x8b";
    size_t expected_len = 4;
    int return_value = 0;
    size_t len;

    len = mbsnrtowcs(wcp, &src, 11, expected_len, stp);
    if ((return_value = check_result(len,expected_len,(void*)wcp,stp))) return return_value;
    if (len != expected_len) return 16;
    return 0;
}

int test_mbsrtowcs(void) {
    __attribute__((aligned(16)))
    static const char str[] = "1234";
    const char *cs;
    mbstate_t st = {0};

    // This is a crucial step.
    if (NULL == setlocale(LC_CTYPE, "")) {
        printf("setlocale returned NULL\n");
        return 1;
    }

    // Used to have an OOB access here.
    size_t ret = mbsrtowcs(NULL, (cs=&str[0],&cs), 1, &st);
    if (ret == -1)
        return 2;

    return 0;
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "en_GB.utf8");

    if (argc < 2) return 1;
    switch (argv[1][0]) {
    case '0':
        return test_mbrtowc();
    case '1':
        return test_mbtoc16();
    case '2':
        return test_mbsnrtowcs();
    case '3':
        return test_mbsrtowcs();
    default:
        return 2;
    }
}
