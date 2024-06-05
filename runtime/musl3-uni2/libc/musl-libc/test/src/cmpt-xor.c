#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <cmpt.h>

typedef struct
{
	char* input;
	char* output;
	uint32_t length; //With xor encryption, data length betweeen buffers will always be equal
} msg_buffer_t;

static void print_cap(void* cap, const char* name)
{
	char out[256] = {};
	strfcap(out, 256, "0x%v:%B | %l | %C | Otype: %s | Perms: %P", cap);
	printf("CAP %s | %s\n", name, out);
}

void xor_msg_data(void* keyv, void* msg_buf_arg)
{
	msg_buffer_t* msg_buf = (msg_buffer_t*)msg_buf_arg;
	//Verify correct properties for keyv
	if(__builtin_cheri_sealed_get(keyv))
	{
		printf("Error: In xor_msg_data, keyv is sealed\n");
		exit(-1);
	}
	if(!__builtin_cheri_tag_get(keyv))
	{
		printf("Error: Int xor_msg_data, keyv's tag is cleared\n");
		exit(-2);
	}

	char* key = (char*)keyv;
	for(int i = 0; i < msg_buf->length; ++i)
	{
		msg_buf->output[i] = msg_buf->input[i]^(*key);
	}
}

#define MSG_LENGTH 16
int main(void)
{
	//Test data setup
	printf("Enter encryption key:\n");
	char* encryption_key_buf = malloc(2);
	fgets(encryption_key_buf, 2, stdin);

	printf("Allocating message buffers\n");
	char *unencrypted_msg_buf = malloc(MSG_LENGTH);
	char *encrypted_msg_buf = malloc(MSG_LENGTH);
	char *comparison_msg_buf = malloc(MSG_LENGTH);

	printf("Writing messages into buffers\n");

	for(int i = 0; i < MSG_LENGTH; ++i)
	{
		unencrypted_msg_buf[i] = i;
		comparison_msg_buf[i] = i;
		//Start with explicitly encrypting arbitrary message for comparison purposes
		encrypted_msg_buf[i] = (unencrypted_msg_buf[i])^encryption_key_buf[0];
	}

	//===============================

	//Actual user story case w/ tests
	msg_buffer_t msg_buf;
	msg_buf.input = encrypted_msg_buf;
	msg_buf.output = unencrypted_msg_buf;
	msg_buf.length = MSG_LENGTH;

	//Setup secure storage

	printf("Creating encryption key capability cmpt\n");
	cmpt_t key_cmpt;
	create_cmpt(&key_cmpt, encryption_key_buf, 1, xor_msg_data);
	free(encryption_key_buf);

	void **key_cmpt_code = &key_cmpt.__opaque[0];
	void **key_cmpt_data = &key_cmpt.__opaque[1];
	void **key_cmpt_mem = &key_cmpt.__opaque[3];

	print_cap(*key_cmpt_mem, "CMPT MEM");
	print_cap(*key_cmpt_code, "CMPT CODE");
	print_cap(*key_cmpt_data, "CMPT DATA");

	if(!is_cmpt_valid(&key_cmpt))
	{
		printf("Error: Key cmpt not valid after creation\n");
		return 2;
	}

	printf("Decrypting message\n");
	//Decrypt given encrypted message
	call_to_cmpt(&key_cmpt, &msg_buf);

	if(!is_cmpt_valid(&key_cmpt))
	{
		printf("Error: Key cmpt not valid after first call to xor_msg_data\n");
		print_cap(*key_cmpt_code, "ERROR KEY CODE");
		print_cap(*key_cmpt_data, "ERROR KEY DATA");
		return 3;
	}

	//Test that encryption function works as intended
	if(memcmp(msg_buf.output, comparison_msg_buf, msg_buf.length) != 0)
	{
		printf("Error: xor_msg_data failed to decrypt message\n");
		return 4;
	}

	//Encryption function works as expected
	memcpy(comparison_msg_buf, msg_buf.input, msg_buf.length);
	msg_buf.input = unencrypted_msg_buf;
	msg_buf.output = encrypted_msg_buf;

	printf("Encrypting message\n");
	//Demonstrate that the sealed key cmpt can be used multiple times
	call_to_cmpt(&key_cmpt, &msg_buf);
	if(memcmp(msg_buf.output, comparison_msg_buf, msg_buf.length) != 0)
	{
		printf("Error: xor_msg_data failed to encrypt message\n");
		return 5;
	}

	//Destroy pointer to key
	if(destroy_cmpt(&key_cmpt))
	{
		printf("Error: Cmpt destruction failed\n");
		return 7;
	}

	//Test that the cmpt cannot be used any longer, no matter what their values are after destruct
	if(is_cmpt_valid(&key_cmpt))
	{
		printf("Error: Key cmpt valid after destruction\n");
		print_cap(*key_cmpt_code, "ERROR KEY CODE");
		print_cap(*key_cmpt_data, "ERROR KEY DATA");
		return 6;
	}
	return 0;
}
