#include <string.h>
#include <locale.h>

int main(int argc, char **argv) {
    setlocale(LC_ALL, "C.UTF-8");

    const char sentence[] = "19 letters sentence";
    const size_t sentence_length = strlen(sentence);
    const size_t sentence_size = sizeof(sentence);

    char buffer[sentence_size];
    memset(buffer, 0, sizeof(buffer));

    size_t original_sentence_cap_length = __builtin_cheri_length_get(sentence);
    size_t original_buffer_cap_length = __builtin_cheri_length_get(buffer);

    size_t planned_length;
    switch (argv[1][0]) {
    case '0':
        // first use : get the output string size
        planned_length = strxfrm(NULL, sentence, 0);

        if (sentence_length != planned_length) return 1;
        if (__builtin_cheri_tag_get(sentence) != 1) return 2;
        if (__builtin_cheri_length_get(sentence) != original_sentence_cap_length) return 3;
        break;

    case '1':
        // second use : actually write in the output
        strxfrm(buffer, sentence, sentence_size);

        if (__builtin_cheri_tag_get(sentence) != 1) return 4;
        if (__builtin_cheri_tag_get(buffer) != 1) return 5;
        if (__builtin_cheri_length_get(sentence) != original_sentence_cap_length) return 6;
        if (__builtin_cheri_length_get(buffer) != original_buffer_cap_length) return 7;

        if (strcmp(sentence,buffer)) return 8;
        break;

    default:
        return 9;
    }
    return 0;
}
