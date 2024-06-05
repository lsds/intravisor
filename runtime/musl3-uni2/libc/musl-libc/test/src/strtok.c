#include <string.h>
#include <stdio.h>

int main(){
	char str[] = "a long   string split into tokens";
	char *words[] = {"a", "long", "string", "split", "into", "tokens"};
	size_t str_len = strlen(str) + 1;
	int i = 0;

	char *token = strtok(str, " ");

	do {
		if (__builtin_cheri_tag_get(token) != 1) return 1;
		if (__builtin_cheri_length_get(token) != str_len) return 2;
		if (strcmp(words[i++], token)) return 3;
	} while ((token = strtok(NULL, " ")));

	if (__builtin_cheri_tag_get(token) != 0) return 4;
	if (token != NULL) return 5;
  return 0;
}
