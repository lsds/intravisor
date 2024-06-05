#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <limits.h>
#include "temp_file_helpers.h"

char DIR_PATH[PATH_MAX];

static void try_write(wchar_t* input_ptr, FILE* fp)
{
    size_t input_length = wcslen(input_ptr);
    if (fwrite ( (void*)input_ptr, sizeof(wchar_t), input_length, fp ) != input_length)
    {
        fprintf(stderr, "fwrite failed to write entire message to file.\n");
        exit(3);
    }
}

int main (int argc, char *argv[])
{
    if (create_temp_directory("morello-musl-tests-fwscanf/", DIR_PATH) != 0)
    {
        fprintf(stderr, "Failed to create temp directory.\n");
        return -1;
    }

    /* ISO C standard sets default locale to 'C', update to be musl default locale. */
    setlocale(LC_ALL, "");

    char small_int = 0;
    long expected_int = 2;

    unsigned int tmp = 0;

    char filename_buffer[PATH_MAX];
    char* filename = create_temp_file(DIR_PATH, "fwscanfXXXXXX", &filename_buffer[0]);

    FILE *fp = fopen(filename, "w+");
    try_write(L"25", fp);

    // We don't have fseek or rewind. As a work around we can probably close and reopen the file to set the read head back to the start
    fclose(fp);
    fp = fopen(filename,"r");

    // int, be it signed or not, or even other base
    if ((tmp=fwscanf(fp,L"%hhd",&small_int)) != 1)
    {
        printf("fwscanf returned %d\n",tmp);
        return 1;
    }
    if (small_int != expected_int)
    {
        printf("expected : %ld\nreceived : %hhd\n",expected_int,small_int);
        return 2;
    }

	return 0;
}
