#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include "temp_file_helpers.h"

char DIR_PATH[PATH_MAX];

int wchar_file();
int wchar_std();
int wstr_file();

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "");
	switch (argv[1][0])
	{
	case '0':
		return wchar_file();
	case '1':
		return wchar_std();
	case '2':
		return wstr_file();
	default:
		return 0;
	}
}

int wchar_file()
{
	FILE *f;
	char *filename;
	char filename_buffer[PATH_MAX];
	wint_t read_char;
	wchar_t write_char = L'ç';

	if(create_temp_directory("morello-musl-tests-wchar/", DIR_PATH) != 0)
	{
		fprintf(stderr, "Failed to create temporary directory.\n");
		return 1;
	}

	filename = create_temp_file(DIR_PATH, "wcharXXXXXX", filename_buffer);
	if(strcmp(filename, "") == 0)
	{
		fprintf(stderr, "Failed to create temporary file.\n");
		return 2;
	}

	f = fopen(filename, "w");
	if(f == NULL)
	{
		fprintf(stderr, "Failed to open temporary file for writing.\n");
		return 3;
	}

	fputwc(write_char, f);

	fclose(f);

	f = fopen(filename, "r");
	if(f == NULL)
	{
		fprintf(stderr, "Failed to open temporary file for reading.\n");
		return 4;
	}

	read_char = fgetwc(f);

	fclose(f);

	if(read_char != write_char)
	{
		fprintf(stderr, "Read character and write character are not the same.\n");
		return 5;
	}

	return 0;
}

int wchar_std()
{
	wchar_t read_char;
	wchar_t write_char;

	read_char = getwchar();
	if(read_char != L'ç')
	{
		fprintf(stderr, "Failed to read wide character from stdin.\n");
		return 1;
	}

	write_char = putwchar(read_char);
	if(write_char != read_char)
	{
		fprintf(stderr, "Failed to write wide character to stdout.\n");
		return 2;
	}

	return 0;
}

int wstr_file()
{
	FILE *f;
	char *filename;
	char filename_buffer[PATH_MAX];
	wchar_t read_wstr[10];
	wchar_t* write_wstr = L"française";

	if(create_temp_directory("morello-musl-tests-wchar/", DIR_PATH) != 0)
	{
		fprintf(stderr, "Failed to create temporary directory.\n");
		return 1;
	}

	filename = create_temp_file(DIR_PATH, "wstrXXXXXX", filename_buffer);
	if(strcmp(filename, "") == 0)
	{
		fprintf(stderr, "Failed to create temporary file.\n");
		return 2;
	}

	f = fopen(filename, "w");
	if(f == NULL)
	{
		fprintf(stderr, "Failed to open temporary file for writing.\n");
		return 3;
	}

	fputws(write_wstr, f);

	fclose(f);

	f = fopen(filename, "r");
	if(f == NULL)
	{
		fprintf(stderr, "Failed to open temporary file for reading.\n");
		return 4;
	}

	fgetws(read_wstr, 10, f);

	fclose(f);

	if(wcscmp(read_wstr, write_wstr) != 0)
	{
		fprintf(stderr, "Read character and write character are not the same.\n");
		return 5;
	}

	return 0;
}
