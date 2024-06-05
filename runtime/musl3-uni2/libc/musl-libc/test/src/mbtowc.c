#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");

    char *input = "Ứ";
    wchar_t output[11];

    /* Encoding should be stateless so null will return 0. */
    if(mbtowc(output, NULL, 1) != 0)
    {
        fprintf(stderr, "Incorrect mbtowc return value for NULL string.\n");
        return 1;
    }

    /*
     * Fail to read character as we do not allow mbtwoc to read more than 1 byte ahread.
     * Fail to read enough bytes to know UTF-8 character encoding.
     */
    if(mbtowc(output, input, 1) != -1)
    {
        fprintf(stderr, "Incorrect mbtowc return value when reading too few bytes.\n");
        return 2;
    }

    /* Ứ is encoded with 3 bytes, so mbtowc should output 3. */
    if(mbtowc(output, input, 3) != 3)
    {
        fprintf(stderr, "Failed to convert character after reading correct number of bytes.\n");
        return 3;
    }

    return 0;
}
