#ifdef __CHERI_PURE_CAPABILITY__
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>

static const char hexdigitslw[16] = "0123456789abcdef";
static const char hexdigitsup[16] = "0123456789ABCDEF";

#define HEX_PREPEND_FL (1U << 0)
#define RIGHT_PAD_FL  (1U << 1)
#define ZERO_PAD_FL (1U << 2)
#define HEX_UP_FL (1U << 3)
#define HEX_LOW_FL (1U << 4)
#define HEX_ANY_FL (HEX_UP_FL | HEX_LOW_FL)

//str assumed backwards (for what will be written e.g. "delaes" for "sealed") and null-terminated here
static char* write_str_to_buf(char* buf, char* buf_end, const char* str, int str_length)
{
	for(int i = 0; i < str_length; ++i)
	{
		if(buf < buf_end) *buf = str[i];
		--buf;
	}
	return buf;
}

//Length of string converted from a given size_t and base
static size_t size_t_str_len(size_t n, size_t base)
{
	if(n == 0) return 1;
	size_t len = 0;
	for(; n > 0; n /= base) ++len;
	return len;
}

//Convert a size_t to string with a radix given by base
static char* write_size_t_to_buf(char* buf, char* buf_end, char* digits, size_t n, size_t base)
{
	if(n == 0)
	{
		*buf = '0';
		--buf;
		return buf;
	}

	char digit;
	size_t nrem;
	for(; n > 0; n/= base, --buf)
	{
		nrem = n % base;
		digit = digits[nrem];
		if(buf < buf_end)
		{
			*buf = digit;
		}
	}
	return buf;
}

//size_t_full funcs assume hex formatting
//Returns number of hex digits to print n with, given how many bytes of the size_t to print
static size_t size_t_full_len(size_t n, size_t num_digits)
{
	return num_digits;
}

static char* write_size_t_full_to_buf(char* buf, char* buf_end, char* digits, size_t n, size_t num_digits)
{
	for(int i = 0; i < num_digits; ++i)
	{
		uint8_t nibble = (n >> (i*4)) & 15;
		if(buf < buf_end) *buf = digits[nibble];
		--buf;
	}
	return buf;
}

//Length of capability attributes string
static size_t attributes_str_len(bool capsentry, bool capsealed, bool capt)
{
	if(capsentry || capsealed || !capt)
	{
		size_t len = 2; //For chars '(' and ')'
		if(capsentry || capsealed) len += 6; //"sentry" or "sealed"
		if(!capt)
		{
			if(capsentry || capsealed) ++len; //","
			len += 7; //"invalid"
		}
		return len;
	}
	return 0;
}

//Write capability attributes to string
static char* write_attributes_to_buf(char* buf, char* buf_end, bool capsentry, bool capsealed, bool capt)
{
	if(capsentry || capsealed || !capt)
	{
		buf = write_str_to_buf(buf, buf_end, ")", 1);
		if(capsentry) buf = write_str_to_buf(buf, buf_end, "yrtnes", 6); //"sentry"
		else if(capsealed) buf = write_str_to_buf(buf, buf_end, "delaes", 6); //"sealed"
		if(!capt)
		{
			if(capsentry || capsealed) buf = write_str_to_buf(buf, buf_end, ",", 1);
			buf = write_str_to_buf(buf, buf_end, "dilavni", 7); //"invalid
		}
		buf = write_str_to_buf(buf, buf_end, "(", 1);
	}
	return buf;
}

//Length of capability permissions string
static size_t permissions_str_len(size_t perms)
{
	size_t len = 0;
#ifdef __ARM_CAP_PERMISSION_EXECUTIVE__
	if(perms & __ARM_CAP_PERMISSION_EXECUTIVE__) ++len; //'E'
#endif
	if(perms & __CHERI_CAP_PERMISSION_PERMIT_STORE_CAPABILITY__) ++len; //'W'
	if(perms & __CHERI_CAP_PERMISSION_PERMIT_LOAD_CAPABILITY__) ++len; //'R'
	if(perms & __CHERI_CAP_PERMISSION_PERMIT_EXECUTE__) ++len; //'x'
	if(perms & __CHERI_CAP_PERMISSION_PERMIT_STORE__) ++len; //'w'
	if(perms & __CHERI_CAP_PERMISSION_PERMIT_LOAD__) ++len; //'r'
	return len;
}

//Write capability permissions to string
static char* write_permissions_to_buf(char* buf, char* buf_end, size_t perms)
{
#ifdef __ARM_CAP_PERMISSION_EXECUTIVE__
	if(perms & __ARM_CAP_PERMISSION_EXECUTIVE__) buf = write_str_to_buf(buf, buf_end, "E", 1);
#endif
	if(perms & __CHERI_CAP_PERMISSION_PERMIT_STORE_CAPABILITY__) buf = write_str_to_buf(buf, buf_end, "W", 1);
	if(perms & __CHERI_CAP_PERMISSION_PERMIT_LOAD_CAPABILITY__) buf = write_str_to_buf(buf, buf_end, "R", 1);
	if(perms & __CHERI_CAP_PERMISSION_PERMIT_EXECUTE__) buf = write_str_to_buf(buf, buf_end, "x", 1);
	if(perms & __CHERI_CAP_PERMISSION_PERMIT_STORE__) buf = write_str_to_buf(buf, buf_end, "w", 1);
	if(perms & __CHERI_CAP_PERMISSION_PERMIT_LOAD__) buf = write_str_to_buf(buf, buf_end, "r", 1);
	return buf;
}

//Returns total length of specifier string (excluding hex prepend)
static size_t spec_str_length_by_type(char type, size_t base, const void* cap)
{
	size_t cap_addr = __builtin_cheri_address_get(cap);
	size_t cap_base = __builtin_cheri_base_get(cap);
	size_t cap_hi = __builtin_cheri_copy_from_high(cap);
	size_t cap_lo = (size_t)cap;
	size_t cap_length = __builtin_cheri_length_get(cap);
	size_t cap_limit = cap_base + cap_length;
	size_t cap_perms = __builtin_cheri_perms_get(cap);
	size_t cap_offset = __builtin_cheri_offset_get(cap);
	ptrdiff_t cap_otype = __builtin_cheri_type_get(cap);
	bool cap_tag = __builtin_cheri_tag_get(cap);
	bool cap_null_derived = !cap_tag && __builtin_cheri_equal_exact(cap, (uintcap_t)(ptraddr_t)cap);
	bool cap_sealed = __builtin_cheri_sealed_get(cap);
	bool cap_sentry = cap_sealed && (cap_perms & __CHERI_CAP_PERMISSION_PERMIT_EXECUTE__);
	switch(type)
	{
		case 'a': return size_t_str_len(cap_addr, base);
		case 'A': return attributes_str_len(cap_sentry, cap_sealed, cap_tag);
		case 'b': return size_t_str_len(cap_base, base);
		case 'B': return size_t_full_len(cap_lo, 16) + size_t_full_len(cap_hi, 16);
		case 'C':
		{
			size_t length = 0;
			//Sum str length for any capability
			length += size_t_str_len(cap_addr, 16) + 2; //Hex address plus "0x"
			//Sum str length for not null-derived capabilities
			if(!cap_null_derived)
			{
				size_t attrs_length = attributes_str_len(cap_sentry, cap_sealed, cap_tag);
				length += attrs_length;
				if(attrs_length > 0) length += 1; //There is a ' ' if the attributes string length > 0
				length += 8; //Constant chars (e.g. "0x", "]" etc.)
				length += size_t_str_len(cap_limit, 16);
				length += size_t_str_len(cap_base, 16);
				length += permissions_str_len(cap_perms);
			}
			return length;
		}
		case 'l': return size_t_str_len(cap_length, base);
		case 'o': return size_t_str_len(cap_offset, base);
		case 'p': return size_t_full_len(cap_perms, 5);
		case 'P': return permissions_str_len(cap_perms);
		case 's': return size_t_str_len(cap_otype, base);
		case 'S':
		{
			if(cap_sentry) return 8; //"<sentry>"
			else if(!cap_sealed) return 10; //"<sealed>"
			else return size_t_str_len(cap_otype, base);
		}
		case 't': return size_t_str_len(cap_limit, base);
		case 'v': return 1;
		default: return 0;
	}
}

static uint8_t isflagchar(const char c)
{
	switch(c)
	{
		case '#': return HEX_PREPEND_FL;
		case '-': return RIGHT_PAD_FL;
		case '0': return ZERO_PAD_FL;
		case 'X': return HEX_UP_FL;
		case 'x': return HEX_LOW_FL;
		default:  return 0;
	}
}

//Returns whether a hex prepend is allowed for a given specifier type
static bool type_allows_prepend(const char type, uint8_t flags, bool cap_sentry, bool cap_sealed)
{
	switch(type)
	{
		case 'A':
		case 'C':
		case 'P':
		case 'T':
		case '?':
			return false;
		case 'a':
		case 'b':
		case 'l':
		case 'o':
		case 's':
		case 't':
		case 'v':
			return flags & HEX_ANY_FL;
		case 'S':
			return (flags & HEX_ANY_FL) && !(cap_sentry || cap_sealed);
		default: return true;
	}
}

static int max(int a, int b)
{
	return (a > b) ? a : b;
}

static int min(int a, int b)
{
	return (a < b) ? a : b;
}

ssize_t strfcap(char *restrict buf, size_t maxsize, const char *restrict format, const void *cap)
{
	ssize_t written = 0;
	ssize_t prev_written = 0;
	size_t length_to_write = 0;
	const char *format_ptr = format;
	char* buf_end = buf + maxsize;
	bool in_question_mark_spec = false;

	size_t cap_addr = __builtin_cheri_address_get(cap);
	size_t cap_base = __builtin_cheri_base_get(cap);
	size_t cap_hi = __builtin_cheri_copy_from_high(cap);
	size_t cap_lo = (size_t)cap;
	size_t cap_length = __builtin_cheri_length_get(cap);
	size_t cap_limit = cap_base + cap_length;
	size_t cap_perms = __builtin_cheri_perms_get(cap);
	size_t cap_offset = __builtin_cheri_offset_get(cap);
	ptrdiff_t cap_otype = __builtin_cheri_type_get(cap);
	bool cap_tag = __builtin_cheri_tag_get(cap);
	bool cap_null_derived = !cap_tag && __builtin_cheri_equal_exact(cap, (uintcap_t)(ptraddr_t)cap);
	bool cap_sealed = __builtin_cheri_sealed_get(cap);
	bool cap_sentry = cap_sealed && (cap_perms & __CHERI_CAP_PERMISSION_PERMIT_EXECUTE__);
	for(;;)
	{
		written += length_to_write;
		if(format_ptr[0] == 0) break;
		//Iterate to next '%'
		const char* non_spec_str_ptr;
		for(non_spec_str_ptr = format_ptr; *format_ptr != 0 && *format_ptr != '%'; ++format_ptr);
		//Iterate past '%%' (if that is the spec str given)
		const char* double_pct_ptr;
		for(double_pct_ptr = format_ptr; format_ptr[0] == '%' && format_ptr[1] == '%'; ++double_pct_ptr, format_ptr += 2);
		//memcpy non specifier str chars to buf
		length_to_write = double_pct_ptr - non_spec_str_ptr;
		size_t length_to_copy = min(length_to_write, max(0, maxsize - written));
		memcpy(buf+written, non_spec_str_ptr, length_to_copy);
		if(length_to_write > 0)
		{
			prev_written = written;
			continue;
		}
		++format_ptr;

		//Read specifier
		//Read flags
		uint8_t flags = 0;
		for(uint8_t flag_candidate = isflagchar(*format_ptr); flag_candidate != 0; ++format_ptr, flag_candidate = isflagchar(*format_ptr)) flags |= flag_candidate;

		//Read width
		int spec_str_width;
		for(spec_str_width = 0; *format_ptr >= '0' && *format_ptr <= '9'; ++format_ptr) spec_str_width = 10*spec_str_width + ((*format_ptr) - '0');

		//Work out length of specifier str
		const char* digits = (flags & HEX_UP_FL) ? hexdigitsup : hexdigitslw;
		size_t base = (flags & (HEX_UP_FL | HEX_LOW_FL)) ? 16 : 10;
		bool should_prepend = (flags & HEX_PREPEND_FL) && type_allows_prepend(*format_ptr, flags, cap_sealed, cap_sentry);
		int spec_str_length = spec_str_length_by_type(*format_ptr, base, cap) + (should_prepend ? 2 : 0);

		//Revert chars copied after question mark encountered in format str
		if(spec_str_length == 0 && in_question_mark_spec)
		{
			written = prev_written;
			length_to_write = 0;
		}
		else
		{
			length_to_write = max(spec_str_width, spec_str_length);
		}
		in_question_mark_spec = false;

		//Write specifier str
		char* spec_str_ptr = buf + written + length_to_write - 1;

		//Right padding
		const char* pad_char = (flags & ZERO_PAD_FL) ? "0" : " ";
		spec_str_width -= spec_str_length;
		spec_str_width = max(spec_str_width, 0);
		if(flags & RIGHT_PAD_FL) for(; spec_str_width > 0; --spec_str_width) spec_str_ptr = write_str_to_buf(spec_str_ptr, buf_end, pad_char, 1);

		//Type
		switch(*format_ptr)
		{
			case 'a': spec_str_ptr = write_size_t_to_buf(spec_str_ptr, buf_end, digits, cap_addr, base); break;
			case 'A': spec_str_ptr = write_attributes_to_buf(spec_str_ptr, buf_end, cap_sentry, cap_sealed, cap_tag); break;
			case 'b': spec_str_ptr = write_size_t_to_buf(spec_str_ptr, buf_end, digits, cap_base, base); break;
			case 'B':
			{
				spec_str_ptr = write_size_t_full_to_buf(spec_str_ptr, buf_end, digits, cap_lo, 16);
				spec_str_ptr = write_size_t_full_to_buf(spec_str_ptr, buf_end, digits, cap_hi, 16);
				break;
			}
			case 'C':
			{
				if(!cap_null_derived)
				{
					char* prev_spec_str_ptr = spec_str_ptr;
					spec_str_ptr = write_attributes_to_buf(spec_str_ptr, buf_end, cap_sentry, cap_sealed, cap_tag);
					if(prev_spec_str_ptr - spec_str_ptr > 0) spec_str_ptr = write_str_to_buf(spec_str_ptr, buf_end, " ", 1);
					spec_str_ptr = write_str_to_buf(spec_str_ptr, buf_end, "]", 1);
					spec_str_ptr = write_size_t_to_buf(spec_str_ptr, buf_end, digits, cap_limit, 16);
					spec_str_ptr = write_str_to_buf(spec_str_ptr, buf_end, "x0-", 3);
					spec_str_ptr = write_size_t_to_buf(spec_str_ptr, buf_end, digits, cap_base, 16);
					spec_str_ptr = write_str_to_buf(spec_str_ptr, buf_end, "x0,", 3);
					spec_str_ptr = write_permissions_to_buf(spec_str_ptr, buf_end, cap_perms);
					spec_str_ptr = write_str_to_buf(spec_str_ptr, buf_end, "[", 1);
				}
				spec_str_ptr = write_size_t_to_buf(spec_str_ptr, buf_end, digits, cap_addr, 16);
				spec_str_ptr = write_str_to_buf(spec_str_ptr, buf_end, "x0", 2);
				break;
			}
			case 'l': spec_str_ptr = write_size_t_to_buf(spec_str_ptr, buf_end, digits, cap_length, base); break;
			case 'o': spec_str_ptr = write_size_t_to_buf(spec_str_ptr, buf_end, digits, cap_offset, base); break;
			case 'p':
			{
				spec_str_ptr = write_size_t_full_to_buf(spec_str_ptr, buf_end, digits, cap_perms, 5);
				break;
			}
			case 'P': spec_str_ptr = write_permissions_to_buf(spec_str_ptr, buf_end, cap_perms); break;
			case 's': spec_str_ptr = write_size_t_to_buf(spec_str_ptr, buf_end, digits, cap_otype, base); break;
			case 'S':
			{
				if(cap_sentry) spec_str_ptr = write_str_to_buf(spec_str_ptr, buf_end, ">yrtnes<", 8); //"<sentry>"
				else if(!cap_sealed) spec_str_ptr = write_str_to_buf(spec_str_ptr, buf_end, ">delaesnu<", 10); //"<unsealed>"
				else spec_str_ptr = write_size_t_to_buf(spec_str_ptr, buf_end, digits, cap_otype, base);
				break;
			}
			case 't': spec_str_ptr = write_size_t_to_buf(spec_str_ptr, buf_end, digits, cap_limit, base); break;
			case 'T': cap_tag = true; break;
			case 'v': spec_str_ptr = write_str_to_buf(spec_str_ptr, buf_end, (cap_tag) ? "1" : "0", 1); break;
			case '?': in_question_mark_spec = true; break;
			default:
			{
				errno = EINVAL;
				return -1;
			}
		}
		++format_ptr;

		//Prepend
		if(should_prepend)
		{
			const char* prepend = (flags & HEX_UP_FL) ? "X0" : "x0";
			spec_str_ptr = write_str_to_buf(spec_str_ptr, buf_end, prepend, 2);
		}

		//Left pad
		for(; spec_str_width > 0; --spec_str_width) spec_str_ptr = write_str_to_buf(spec_str_ptr, buf_end, pad_char, 1);
	}
	if(in_question_mark_spec)
	{
		written = prev_written;
	}
	if(written < maxsize) buf[written] = 0;

	return written;
}

#endif
