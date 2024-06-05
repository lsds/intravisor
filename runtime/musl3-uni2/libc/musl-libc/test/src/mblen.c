#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");

    // Look at unicode character encoding. Some characters will not work.
    int length = 0;
    char *ascii = "a";
    char *utf8_2 = "\u0100";
    char *utf8_3 = "\u10348";
    size_t max_length = 6;

    length = mblen(NULL, max_length);
    if(length != 0)
    {
        fprintf(stderr, "Incorrect mblen for NULL.\n");
        return 1;
    }

    length = mblen(ascii, max_length);
    if(length != 1)
    {
        fprintf(stderr, "Incorrect mblen for ascii character.\n");
        return 2;
    }

    length = mblen(utf8_2, max_length);
    if(length != 2)
    {
        fprintf(stderr, "Incorrect mblen for UTF-8 character %d.\n", length);
        return 3;
    }

    length = mblen(utf8_3, max_length);
    if(length != 3)
    {
        fprintf(stderr, "Incorrect mblen for UTF-8 character %d.\n", length);
        return 3;
    }

    return 0;
}
