#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

// swscanf eventually calls fwscanf where most of the tests are done
// this is just to test the intermediary functions
int main (int argc, char *argv[])
{
    /* ISO C standard sets default locale to 'C', update to be musl default locale. */
    setlocale(LC_ALL, "");

    const wchar_t* input_ascii = L"this is 12";
    const wchar_t* format_ascii = L"%s %*s %lld";

    const wchar_t* input_wc = L"française française 010";
    const wchar_t* format_wc = L"%ls %*ls %lld";

    char string[10] = {'\0'};
    wchar_t wstring[10] = {'\0'};
    long long big_int = 0;

    int swscanf_output_value = 0;
    int return_value = 0;

    switch (argv[1][0]) {
        case '0':
        if ((swscanf_output_value = swscanf(input_ascii, format_ascii, string, &big_int)) != 2) {
            return_value |= 1;
            printf("swscanf returned %d instead of 2 assigned variables.\n",swscanf_output_value);
        }
        if (strcmp(string,"this")) {
            return_value |= 2;
            printf("swscanf scanned %s instead of \"this\"\n",string);
        }
        if (big_int != 12) {
            return_value |= 4;
            printf("swscanf scanned %lld instead of 4\n",big_int);
        }
        break;
        case '1':
        if ((swscanf_output_value = swscanf(input_wc,format_wc, wstring, &big_int)) != 2) {
            return_value |= 1;
            printf("swscanf returned %d instead of 2 assigned variables.\n",swscanf_output_value);
        }
        if (wcscmp(wstring,L"française")) {
            return_value |= 2;
            // The proper print is disabled because jenkins's runner don't like multibyte chars.
            printf("swscanf scanned %ls instead of %ls\n",wstring,L"française");
            printf("swscanf did not scan the correct string\n");
        }
        if (big_int != 10) {
            return_value |= 4;
            printf("swscanf scanned %lld instead of 10\n",big_int);
        }
        break;
    default:
        return 3;
    }
    return return_value;
}
