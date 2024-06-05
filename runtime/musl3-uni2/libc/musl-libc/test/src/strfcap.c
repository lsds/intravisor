#ifdef __CHERI_PURE_CAPABILITY__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#define BUFFER_SIZE 2048

static const char* hello_world = "Hello World";

static int test_strfcap_specifier_one_property(const char* strfcap_format, const char* verify_format, void* cap, size_t cap_property)
{
	char output_buffer[BUFFER_SIZE] = {};
	char verify_buffer[BUFFER_SIZE] = {};

	strfcap(output_buffer, BUFFER_SIZE, strfcap_format, cap);
	snprintf(verify_buffer, BUFFER_SIZE, verify_format, cap_property);

	printf	(	"Test strfcap\n"
			"strfcap format:  \"%s\"\n"
			"verify format:   \"%s\"\n"
			"strfcap result:  \"%s\"\n"
			"intended result: \"%s\"\n",
			strfcap_format, verify_format, output_buffer, verify_buffer
		);

	return strcmp(output_buffer, verify_buffer);
}

static int test_strfcap_specifier_two_properties(const char* strfcap_format, const char* verify_format, void* cap, size_t cap_property_0, size_t cap_property_1)
{
	char output_buffer[BUFFER_SIZE] = {};
	char verify_buffer[BUFFER_SIZE] = {};

	strfcap(output_buffer, BUFFER_SIZE, strfcap_format, cap);
	snprintf(verify_buffer, BUFFER_SIZE, verify_format, cap_property_0, cap_property_1);

	printf	(	"Test strfcap\n"
			"strfcap format:  \"%s\"\n"
			"verify format:   \"%s\"\n"
			"strfcap result:  \"%s\"\n"
			"intended result: \"%s\"\n",
			strfcap_format, verify_format, output_buffer, verify_buffer
		);

	return strcmp(output_buffer, verify_buffer);
}

static int test_strfcap_specifier_padding(const char* strfcap_format, const char* verify_format, const char* tmp_format, void* cap, size_t cap_property_0, size_t cap_property_1)
{
	char output_buffer[BUFFER_SIZE] = {};
	char verify_buffer[BUFFER_SIZE] = {};
	char tmp_buffer[128] = {};

	strfcap(output_buffer, BUFFER_SIZE, strfcap_format, cap);
	snprintf(tmp_buffer, 128, tmp_format, cap_property_0, cap_property_1);
	snprintf(verify_buffer, BUFFER_SIZE, verify_format, tmp_buffer);

	printf	(	"Test strfcap\n"
			"strfcap format:  \"%s\"\n"
			"verify format:   \"%s\"\n"
			"strfcap result:  \"%s\"\n"
			"intended result: \"%s\"\n",
			strfcap_format, verify_format, output_buffer, verify_buffer
		);

	return strcmp(output_buffer, verify_buffer);
}

static int test_strfcap_specifier_no_properties(const char* strfcap_format, const char* verify_format, void* cap)
{
	char output_buffer[BUFFER_SIZE] = {};
	char verify_buffer[BUFFER_SIZE] = {};

	strfcap(output_buffer, BUFFER_SIZE, strfcap_format, cap);
	snprintf(verify_buffer, BUFFER_SIZE, "%s", verify_format);

	printf	(	"Test strfcap\n"
			"strfcap format:  \"%s\"\n"
			"verify format:   \"%s\"\n"
			"strfcap result:  \"%s\"\n"
			"intended result: \"%s\"\n",
			strfcap_format, verify_format, output_buffer, verify_buffer
		);

	return strcmp(output_buffer, verify_buffer);
}

static int test_strfcap_compare(const char* strfcap_format, const char* verify_format, void* cap)
{
	char output_buffer[BUFFER_SIZE] = {};
	char verify_buffer[BUFFER_SIZE] = {};

	strfcap(output_buffer, BUFFER_SIZE, strfcap_format, cap);
	strfcap(verify_buffer, BUFFER_SIZE, verify_format, cap);

	printf	(	"Test strfcap\n"
			"strfcap format:  \"%s\"\n"
			"verify format:   \"%s\"\n"
			"strfcap result:  \"%s\"\n"
			"intended result: \"%s\"\n",
			strfcap_format, verify_format, output_buffer, verify_buffer
		);

	return strcmp(output_buffer, verify_buffer);
}

static int test_strfcap_ordinary_chars()
{
	char output_buffer[BUFFER_SIZE] = {};

	ssize_t first_ret = strfcap(output_buffer, BUFFER_SIZE, "", NULL);
	int first_cmp = strcmp(output_buffer, "");

	printf	(	"Test strfcap\n"
			"strfcap format:  \"%s\"\n"
			"strfcap result:  \"%s\"\n"
			"intended result: \"%s\"\n",
			"", output_buffer, ""
		);

	memset(output_buffer, 0, BUFFER_SIZE);

	ssize_t second_ret = strfcap(output_buffer, BUFFER_SIZE, hello_world, NULL);
	int second_cmp = strcmp(output_buffer, hello_world);

	printf	(	"Test strfcap\n"
			"strfcap format:  \"%s\"\n"
			"strfcap result:  \"%s\"\n"
			"intended result: \"%s\"\n",
			hello_world, output_buffer, hello_world
		);

	return !(!first_cmp && !second_cmp && first_ret == 0 && second_ret == strlen(hello_world));
}

static int test_strfcap_padding_and_width()
{
	char output_buffer[BUFFER_SIZE] = {};

	//Left pad
	ssize_t first_ret = strfcap(output_buffer, BUFFER_SIZE, "%25a", NULL);
	char first_pad = output_buffer[0];

	printf	(	"Test strfcap\n"
			"strfcap format: \"%s\"\n"
			"strfcap result: \"%s\"\n",
			"%25a", output_buffer
		);

	memset(output_buffer, 0, BUFFER_SIZE);

	//Right pad
	ssize_t second_ret = strfcap(output_buffer, BUFFER_SIZE, "%-25a", NULL);
	char second_pad = output_buffer[24];

	memset(output_buffer, 0, BUFFER_SIZE);

	//0 pad
	ssize_t third_ret = strfcap(output_buffer, BUFFER_SIZE, "%025a", NULL);
	char third_pad = output_buffer[0];

	return !(first_ret == 25 && second_ret == 25 && third_ret == 25 && first_pad == ' ' && second_pad == ' ' && third_pad == '0');
}

static int test_strfcap_maxsize()
{
	char output_buffer[BUFFER_SIZE] = {};
	memset(output_buffer, 1, BUFFER_SIZE);

	ssize_t ret = strfcap(output_buffer, 5, hello_world, NULL);
	printf	(	"Test strfcap\n"
			"maxsize:          %d\n"
			"strfcap format:  \"%s\"\n"
			"strfcap result:  \"%.5s\"\n"
			"intended result: \"%s\"\n"
			"strfcap return:   %ld\n"
			"intended return:  %lu\n",
			5, hello_world, output_buffer, "Hello", ret, strlen(hello_world)
		);

	int first_test = !(output_buffer[5] == 1 && ret == strlen(hello_world));

	memset(output_buffer, 1, BUFFER_SIZE);

	void* cap = __builtin_cheri_stack_get();
	ret = strfcap(output_buffer, 5, "%S", cap);
	printf	(	"Test strfcap\n"
			"maxsize:          %d\n"
			"strfcap format:  \"%s\"\n"
			"strfcap result:  \"%.5s\"\n"
			"intended result: \"%s\"\n"
			"strfcap return:   %ld\n"
			"intended return:  %lu\n",
			5, "%S", output_buffer, "<unse", ret, strlen("<unsealed>")
		);

	int second_test = !(output_buffer[5] == 1 && ret == strlen("<unsealed>"));

	return first_test || second_test;
}

static int test_strfcap_NULL_terminated()
{
	char output_buffer[BUFFER_SIZE] = {};
	memset(output_buffer, 1, BUFFER_SIZE);

	strfcap(output_buffer, BUFFER_SIZE, hello_world, NULL);
	printf	(	"Test strfcap\n"
			"strfcap format: \"%s\"\n"
			"strfcap result: \"%s\"\n",
			hello_world, output_buffer);

	return !(output_buffer[strlen(hello_world)] == 0 && output_buffer[strlen(hello_world)+1] == 1);
}

static int test_strfcap_specifier_a(void** test_capabilities, const char** test_capability_names, int num_capabilities)
{
	const char* strfcap_formats[] = {"%a", "%#a", "%#xa", "%#Xa", "%10a", "%-10a", "%010a"};
	const char* verify_formats[] = {"%lu", "%lu", "0x%lx", "0X%lX", "%10lu", "%-10lu", "%010lu"};

	int num_formats = sizeof(strfcap_formats)/sizeof(const char*);

	for(int i = 0; i < num_capabilities; ++i)
	{
		void* cap = test_capabilities[i];
		size_t cap_addr = __builtin_cheri_address_get(cap);
		for(int j = 0; j < num_formats; ++j)
		{
			int test_result = test_strfcap_specifier_one_property(strfcap_formats[j], verify_formats[j], cap, cap_addr);
			if(test_result)
			{
				printf("Failure for capability %s with strfcap format %s and verify format %s\n", test_capability_names[i], strfcap_formats[j], verify_formats[j]);
				return test_result;
			}
		}
	}
	return 0;
}

static int test_strfcap_specifier_A()
{
	char test_buffer[16] = {};
	int first_test = test_strfcap_specifier_no_properties("%A", "(invalid)", NULL);
	int second_test = test_strfcap_specifier_no_properties("%A", "(sentry)", __builtin_cheri_seal_entry(__builtin_cheri_program_counter_get()));
	int third_test = test_strfcap_specifier_no_properties("%A", "(sealed)", __builtin_cheri_seal_entry(__builtin_cheri_perms_and(__builtin_cheri_program_counter_get(), ~__CHERI_CAP_PERMISSION_PERMIT_EXECUTE__)));
	int fourth_test = test_strfcap_specifier_no_properties("%A", "", test_buffer);

	return first_test || second_test || third_test || fourth_test;
}

static int test_strfcap_specifier_b(void** test_capabilities, const char** test_capability_names, int num_capabilities)
{
	const char* strfcap_formats[] = {"%b", "%#b", "%#xb", "%#Xb", "%10b", "%-10b", "%010b"};
	const char* verify_formats[] = {"%lu", "%lu", "0x%lx", "0X%lX", "%10lu", "%-10lu", "%010lu"};

	int num_formats = sizeof(strfcap_formats)/sizeof(const char*);

	for(int i = 0; i < num_capabilities; ++i)
	{
		void* cap = test_capabilities[i];
		size_t cap_base = __builtin_cheri_base_get(cap);
		for(int j = 0; j < num_formats; ++j)
		{
			int test_result = test_strfcap_specifier_one_property(strfcap_formats[j], verify_formats[j], cap, cap_base);
			if(test_result)
			{
				printf("Failure for capability %s with strfcap format %s and verify format %s\n", test_capability_names[i], strfcap_formats[j], verify_formats[j]);
				return test_result;
			}
		}
	}
	return 0;
}

static int test_strfcap_specifier_B(void** test_capabilities, const char** test_capability_names, int num_capabilities)
{
	const char* strfcap_formats_no_pad[] = {"%B","%#B", "%#xB", "%#XB"};
	const char* verify_formats_no_pad[] = {"%.16lx%.16lx", "0x%.16lx%.16lx", "0x%.16lx%.16lx", "0X%.16lX%.16lX"};
	const char* strfcap_formats_pad[] = {"%32B", "%-32B"};
	const char* verify_formats_0_pad[] = {"%32s", "%-32s"};
	const char* verify_formats_1_pad[] = {"%.16lx%.16lx", "%.16lx%.16lx"};

	int num_formats_no_pad = sizeof(strfcap_formats_no_pad)/sizeof(const char*);
	int num_formats_pad = sizeof(strfcap_formats_pad)/sizeof(const char*);

	for(int i = 0; i < num_capabilities; ++i)
	{
		void* cap = test_capabilities[i];
		size_t cap_hi = __builtin_cheri_copy_from_high(cap);
		size_t cap_lo = __builtin_cheri_address_get(cap);
		for(int j = 0; j < num_formats_no_pad; ++j)
		{
			int test_result = test_strfcap_specifier_two_properties(strfcap_formats_no_pad[j], verify_formats_no_pad[j], cap, cap_hi, cap_lo);
			if(test_result)
			{
				printf("Failure for capability %s with strfcap format %s and verify format %s\n", test_capability_names[i], strfcap_formats_no_pad[j], verify_formats_no_pad[j]);
				return test_result;
			}
		}
		for(int j = 0; j < num_formats_pad; ++j)
		{
			int test_result = test_strfcap_specifier_padding(strfcap_formats_pad[j], verify_formats_0_pad[j], verify_formats_1_pad[j], cap, cap_hi, cap_lo);
			if(test_result)
			{
				printf("Failure for capability %s with strfcap format %s and verify format %s\n", test_capability_names[i], strfcap_formats_pad[j], verify_formats_1_pad[j]);
				return test_result;
			}
		}
	}
	return 0;
}

static int test_strfcap_specifier_C()
{
	void* cap = NULL;
	int first_test = test_strfcap_compare("%C", "%#xa", cap);

	cap = __builtin_cheri_stack_get();
	int second_test = test_strfcap_compare("%C", "%#xa[%P,%#xb-%#xt]%? %A", cap);

	cap = __builtin_cheri_program_counter_get();
	int third_test = test_strfcap_compare("%C", "%#xa[%P,%#xb-%#xt]%? %A", cap);

	return first_test || second_test || third_test;
}

static int test_strfcap_specifier_l(void** test_capabilities, const char** test_capability_names, int num_capabilities)
{
	const char* strfcap_formats[] = {"%l", "%#l", "%#xl", "%#Xl", "%10l", "%-10l", "%010l"};
	const char* verify_formats[] = {"%lu", "%lu","0x%lx", "0X%lX", "%10lu", "%-10lu", "%010lu"};
	int num_formats = sizeof(strfcap_formats)/sizeof(const char*);

	for(int i = 0; i < num_capabilities; ++i)
	{
		void* cap = test_capabilities[i];
		size_t cap_len = __builtin_cheri_length_get(cap);
		for(int j = 0; j < num_formats; ++j)
		{
			int test_result = test_strfcap_specifier_one_property(strfcap_formats[j], verify_formats[j], cap, cap_len);
			if(test_result)
			{
				printf("Failure for capability %s with strfcap format %s and verify format %s\n", test_capability_names[i], strfcap_formats[j], verify_formats[j]);
				return test_result;
			}
		}
	}
	return 0;
}

static int test_strfcap_specifier_o(void** test_capabilities, const char** test_capability_names, int num_capabilities)
{
	const char* strfcap_formats[] = {"%o", "%#o", "%#xo", "%#Xo", "%10o", "%-10o", "%010o"};
	const char* verify_formats[] = {"%lu", "%lu", "0x%lx", "0X%lX", "%10lu", "%-10lu", "%010lu"};
	int num_formats = sizeof(strfcap_formats)/sizeof(const char*);

	for(int i = 0; i < num_capabilities; ++i)
	{
		void* cap = test_capabilities[i];
		size_t cap_offset = __builtin_cheri_offset_get(cap);
		for(int j = 0; j < num_formats; ++j)
		{
			int test_result = test_strfcap_specifier_one_property(strfcap_formats[j], verify_formats[j], cap, cap_offset);
			if(test_result)
			{
				printf("Failure for capability %s with strfcap format %s and verify format %s\n", test_capability_names[i], strfcap_formats[j], verify_formats[j]);
				return test_result;
			}
		}
	}
	return 0;
}

static int test_strfcap_specifier_p(void** test_capabilities, const char** test_capability_names, int num_capabilities)
{
	const char* strfcap_formats[] = {"%p", "%#p", "%#xp", "%#Xp", "%10p", "%-10p", "%010p"};
	const char* verify_formats[] = {"%.5lx", "0x%.5lx", "0x%.5lx", "0X%.5lX", "%10.5lx", "%-10.5lx", "%010lx"};
	int num_formats = sizeof(strfcap_formats)/sizeof(const char*);

	for(int i = 0; i < num_capabilities; ++i)
	{
		void* cap = test_capabilities[i];
		size_t perms = __builtin_cheri_perms_get(cap);
		for(int j = 0; j < num_formats; ++j)
		{
			int test_result = test_strfcap_specifier_one_property(strfcap_formats[j], verify_formats[j], cap, perms);
			if(test_result)
			{
				printf("Failure for capability %s with strfcap format %s and verify format %s\n", test_capability_names[i], strfcap_formats[j], verify_formats[j]);
				return test_result;
			}
		}
	}
	return 0;
}

static int test_strfcap_specifier_P()
{
	void* cap = __builtin_cheri_stack_get();
	cap = __builtin_cheri_perms_and(cap, ~__ARM_CAP_PERMISSION_EXECUTIVE__);
	cap = __builtin_cheri_perms_and(cap, ~__CHERI_CAP_PERMISSION_PERMIT_EXECUTE__);
	int first_test = test_strfcap_specifier_no_properties("%P", "rwRW", cap);

	cap = __builtin_cheri_perms_and(cap, ~__CHERI_CAP_PERMISSION_PERMIT_LOAD__);
	int second_test = test_strfcap_specifier_no_properties("%P", "wRW", cap);

	cap = __builtin_cheri_perms_and(cap, ~__CHERI_CAP_PERMISSION_PERMIT_STORE__);
	int third_test = test_strfcap_specifier_no_properties("%P", "RW", cap);

	cap = __builtin_cheri_perms_and(cap, ~__CHERI_CAP_PERMISSION_PERMIT_LOAD_CAPABILITY__);
	int fourth_test = test_strfcap_specifier_no_properties("%P", "W", cap);

	cap = __builtin_cheri_perms_and(cap, ~__CHERI_CAP_PERMISSION_PERMIT_STORE_CAPABILITY__);
	int fifth_test = test_strfcap_specifier_no_properties("%P", "", cap);

	cap = __builtin_cheri_program_counter_get();
	int sixth_test = test_strfcap_specifier_no_properties("%P", "rxRE", cap);

	cap = NULL;
	int seventh_test = test_strfcap_specifier_no_properties("%P", "", cap);

	return first_test || second_test || third_test || fourth_test || fifth_test || sixth_test || seventh_test;
}

static int test_strfcap_specifier_s()
{
	void* cap = __builtin_cheri_stack_get();
	int first_test = test_strfcap_specifier_no_properties("%s", "0", cap);

	cap = __builtin_cheri_seal_entry(cap);
	int second_test = test_strfcap_specifier_no_properties("%s", "1", cap);

	cap = __builtin_cheri_stack_get();
	__asm__ volatile ("seal %0, %0, lpb" : "+C"(cap));
	int third_test = test_strfcap_specifier_no_properties("%s", "2", cap);

	cap = __builtin_cheri_stack_get();
	__asm__ volatile ("seal %0, %0, lb" : "+C"(cap));
	int fourth_test = test_strfcap_specifier_no_properties("%s", "3", cap);

	return first_test || second_test || third_test || fourth_test;
}

static int test_strfcap_specifier_S()
{
	void* cap = __builtin_cheri_stack_get();
	int first_test = test_strfcap_specifier_no_properties("%S", "<unsealed>", cap);

	cap = __builtin_cheri_perms_and(__builtin_cheri_seal(cap, cap), ~__CHERI_CAP_PERMISSION_PERMIT_EXECUTE__);
	int second_test = test_strfcap_specifier_one_property("%S", "%lu", cap, __builtin_cheri_type_get(cap));

	cap = __builtin_cheri_seal_entry(__builtin_cheri_program_counter_get());
	int third_test = test_strfcap_specifier_no_properties("%S", "<sentry>", cap);

	return first_test || second_test || third_test;
}

static int test_strfcap_specifier_t(void** test_capabilities, const char** test_capability_names, int num_capabilities)
{
	const char* strfcap_formats[] = {"%t", "%#t", "%#xt", "%#Xt", "%10t", "%-10t", "%010t"};
	const char* verify_formats[] = {"%lu", "%lu", "0x%lx", "0X%lX", "%10lu", "%-10lu", "%010lu"};
	int num_formats = sizeof(strfcap_formats)/sizeof(const char*);

	for(int i = 0; i < num_capabilities; ++i)
	{
		void* cap = test_capabilities[i];
		size_t limit = __builtin_cheri_base_get(cap) + __builtin_cheri_length_get(cap);
		for(int j = 0; j < num_formats; ++j)
		{
			int test_result = test_strfcap_specifier_one_property(strfcap_formats[j], verify_formats[j], cap, limit);
			if(test_result)
			{
				printf("Failure for capability %s with strfcap format %s and verify format %s\n", test_capability_names[i], strfcap_formats[j], verify_formats[j]);
				return test_result;
			}
		}
	}
	return 0;
}

static int test_strfcap_specifier_T()
{
	void* cap = __builtin_cheri_stack_get();
	int first_test = test_strfcap_specifier_no_properties("%T", "", cap);
	int second_test = test_strfcap_specifier_no_properties("%THello%T", "Hello", cap);
	return first_test || second_test;
}

static int test_strfcap_specifier_v()
{
	void* cap = __builtin_cheri_stack_get();
	int first_test = test_strfcap_specifier_no_properties("%v", "1", cap);

	cap = NULL;
	int second_test = test_strfcap_specifier_no_properties("%v", "0", cap);

	return first_test || second_test;
}

static int test_strfcap_specifier_percent()
{
	void* cap = __builtin_cheri_stack_get();
	int first_test = test_strfcap_specifier_no_properties("%%hello%%", "%hello%", cap);
	int second_test = test_strfcap_specifier_no_properties("%?Hello%v", "Hello1", cap);
	int third_test = test_strfcap_specifier_no_properties("%?Hello%T", "", cap);
	return first_test || second_test || third_test;
}

static int test_strfcap_large_formats(void** test_capabilities, const char** test_capability_names, const char** test_capability_perms, int num_capabilities)
{
	char output_buffer[BUFFER_SIZE] = {};
	char verify_buffer[BUFFER_SIZE] = {};
	const char* strfcap_formats[] = {
					"%?Capability %B with address: %a\n"
					"Length: %l offset: %o and permissions: %p\n"
					"Otype: %s\n"
					"Tag: %v%T Tag: %v\n"
					"Cap printed 100%%%?This won't be however%T\n",

					"%#xv:%B\n"
					"Tag: %v\n"
					"Value: %#xa\n"
					"Base: %#xb\n"
					"Limit: %#xt\n"
					"Length: %l\n"
					"Offset: %o\n"
					"Permissions: %P (%p)\n"
					"OType: %S\n"
					};
	const char* verify_formats[] = 	{
					"Capability %.16lx%.16lx with address: %lu\n"
					"Length: %lu offset: %lu and permissions: %.5lx\n"
					"Otype: %ld\n"
					"Tag: %d Tag: 1\n"
					"Cap printed 100%%\n",

					"0x%x:%.16lx%.16lx\n"
					"Tag: %d\n"
					"Value: 0x%lx\n"
					"Base: 0x%lx\n"
					"Limit: 0x%lx\n"
					"Length: %lu\n"
					"Offset: %lu\n"
					"Permissions: %s (%.5lx)\n"
					"OType: %s\n"
					};

	for(int i = 0; i < num_capabilities; ++i)
	{
		void* cap = test_capabilities[i];
		size_t cap_addr = __builtin_cheri_address_get(cap);
		size_t cap_len = __builtin_cheri_length_get(cap);
		size_t cap_off = __builtin_cheri_offset_get(cap);
		size_t cap_perms = __builtin_cheri_perms_get(cap);
		size_t cap_hi = __builtin_cheri_copy_from_high(cap);
		size_t cap_lo = __builtin_cheri_address_get(cap);
		ptrdiff_t cap_otype = __builtin_cheri_type_get(cap);
		bool cap_tag = __builtin_cheri_tag_get(cap);

		strfcap(output_buffer, BUFFER_SIZE, strfcap_formats[0], cap);
		snprintf(verify_buffer, BUFFER_SIZE, verify_formats[0], cap_hi, cap_lo, cap_addr, cap_len, cap_off, cap_perms, cap_otype, cap_tag);

		int test_result = strcmp(output_buffer, verify_buffer);
		printf	(	"Test strfcap for capability %s\n"
				"Strfcap result:"
				"\n\n%s\n\n"
				"Intended result:\n"
				"\n\n%s\n\n",
				test_capability_names[i], output_buffer, verify_buffer
			);
		if(test_result)
		{
			return test_result;
		}
		memset(output_buffer, 0, BUFFER_SIZE);
		memset(verify_buffer, 0, BUFFER_SIZE);
	}

	for(int i = 0; i < num_capabilities; ++i)
	{
		void* cap = test_capabilities[i];
		bool cap_tag = __builtin_cheri_tag_get(cap);
		size_t cap_hi = __builtin_cheri_copy_from_high(cap);
		size_t cap_lo = __builtin_cheri_address_get(cap);
		size_t cap_addr = __builtin_cheri_address_get(cap);
		size_t cap_base = __builtin_cheri_base_get(cap);
		size_t cap_length = __builtin_cheri_length_get(cap);
		size_t cap_limit = cap_base + cap_length;
		size_t cap_offset = __builtin_cheri_offset_get(cap);
		size_t cap_perms = __builtin_cheri_perms_get(cap);

		strfcap(output_buffer, BUFFER_SIZE, strfcap_formats[1], cap);
		snprintf(verify_buffer, BUFFER_SIZE, verify_formats[1], cap_tag, cap_hi, cap_lo, cap_tag, cap_addr, cap_base, cap_limit, cap_length, cap_offset, test_capability_perms[i], cap_perms, "<unsealed>");
		int test_result = strcmp(output_buffer, verify_buffer);
		printf	(	"Test strfcap for capability %s\n"
				"Strfcap result:"
				"\n\n%s\n\n"
				"Intended result:\n"
				"\n\n%s\n\n",
				test_capability_names[i], output_buffer, verify_buffer
			);
		if(test_result)
		{
			return test_result;

		}
	}
	return 0;
}

int main(int argc, char** argv)
{
	char test_buffer[64] = {};
	int num_capabilities = 4;
	void* test_capabilities[] = {__builtin_cheri_program_counter_get(), NULL, __builtin_cheri_copy_to_high(test_buffer, 0), __builtin_cheri_stack_get()};
	const char* capability_names[] = {"PC", "NULL", "NULL DERIVED", "STACK"};
	const char* capability_perms[] = {"rxRE", "", "", "rwxRWE"};

	switch(argv[1][0])
	{
		case '0': return test_strfcap_ordinary_chars();
		case '1': return test_strfcap_padding_and_width();
		case '2': return test_strfcap_maxsize();
		case '3': return test_strfcap_NULL_terminated();
		case '4': return test_strfcap_large_formats(test_capabilities, capability_names, capability_perms, num_capabilities - 1); //num_caps-1 passed here because of permissions weirdness with stack, ignored in this test
		case 'a': return test_strfcap_specifier_a(test_capabilities, capability_names, num_capabilities);
		case 'A': return test_strfcap_specifier_A();
		case 'b': return test_strfcap_specifier_b(test_capabilities, capability_names, num_capabilities);
		case 'B': return test_strfcap_specifier_B(test_capabilities, capability_names, num_capabilities);
		case 'C': return test_strfcap_specifier_C();
		case 'l': return test_strfcap_specifier_l(test_capabilities, capability_names, num_capabilities);
		case 'o': return test_strfcap_specifier_o(test_capabilities, capability_names, num_capabilities);
		case 'p': return test_strfcap_specifier_p(test_capabilities, capability_names, num_capabilities);
		case 'P': return test_strfcap_specifier_P();
		case 's': return test_strfcap_specifier_s();
		case 'S': return test_strfcap_specifier_S();
		case 't': return test_strfcap_specifier_t(test_capabilities, capability_names, num_capabilities);
		case 'T': return test_strfcap_specifier_T();
		case 'v': return test_strfcap_specifier_v();
		case '%': return test_strfcap_specifier_percent();
		default: return 2;
	}
}
#endif
