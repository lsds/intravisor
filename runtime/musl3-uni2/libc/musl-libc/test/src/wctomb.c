#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");

    wchar_t input = 0x1EE8;
    char output[11];

    /* Encoding should be stateless so null will return 0. */
    if(wctomb(NULL, input) != 0)
    {
        fprintf(stderr, "Incorrect mbtowc return value for NULL string.\n");
        return 1;
    }

    if(wctomb(output, input) != 3)
    {
        fprintf(stderr, "Incorrect mbtowc return value when reading too few bytes.\n");
        return 2;
    }

    return 0;
}
