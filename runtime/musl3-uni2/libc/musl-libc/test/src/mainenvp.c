#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[], char *envp[])
{
	if (!__builtin_cheri_tag_get(envp))
	{
		printf("envp tag is not set: %#p\n", (void *)envp);
		return 1;
	}

	size_t envp_num_elements = 0;
	for (; (envp)[envp_num_elements]; envp_num_elements++);
	const size_t envp_representable_length = __builtin_cheri_round_representable_length((envp_num_elements + 1) * sizeof(char *));
	const size_t envp_representable_mask = __builtin_cheri_representable_alignment_mask(envp_representable_length);
	if (envp_representable_length != __builtin_cheri_length_get(envp))
	{
		printf("envp has unexpected length:\nenvp: %#p\nrepresentable length: 0x%lx\n",
		       (void *)envp, envp_representable_length);
		return 2;
	}

	if ((uintptr_t)envp != ((uintptr_t)envp & envp_representable_mask)) 
	{
		printf("envp has unexpected alignment:\nenvp: %#p\nrepresentable mask: 0x%lx\n",
		       (void *)envp, envp_representable_mask);
		return 3;
	}

	void *cap = NULL;
	size_t tag = 0;
	size_t sz = 0;
	int n = 0;
	while (*envp) 
	{
		cap = envp;
		if (!(tag = __builtin_cheri_tag_get(cap)))
		{
			printf("envp[%d] has tag %zu\n", n, tag);
			return 4;
		}

		size_t xsz = __builtin_cheri_round_representable_length(strlen(*envp) + 1);
		if ((sz = __builtin_cheri_length_get(*envp)) != xsz)
		{
			return 5;
		}

		printf("envp[%d] has length %zu (expected %zu)\n", n, sz, xsz);
		envp++;
		n++;
	}

	if (__builtin_cheri_length_get(envp) != ((n + 1) * sizeof(char *)))
	{
		printf("envp length is not set correctly: %zu\n", __builtin_cheri_length_get(envp));
	}

	return 0;
}
