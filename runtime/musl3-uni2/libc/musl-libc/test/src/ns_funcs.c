#include <arpa/nameser.h>
#include <resolv.h>
#include <string.h>

int put_get(void) {
	unsigned i, u16 = 0xABCD;
	unsigned long u32 = 0x12345678;
	unsigned char c_arr[4];
	unsigned char c_exp32[] = {0x12, 0x34, 0x56, 0x78};
	unsigned char c_exp16[] = {0xAB, 0xCD, 0x56, 0x78};

	ns_put32(u32, c_arr);
	for(i=0;i<4;i++) {
		if (c_arr[i] != c_exp32[i]) return 1;
	}
	if (ns_get16(c_arr) != (u32 >> 16)) return 2;
	if (ns_get16(c_arr+2) != (u32 & 0xFFFF)) return 3;

	ns_put16(u16, c_arr);
	for(i=0;i<4;i++) {
		if (c_arr[i] != c_exp16[i]) return 4;
	}
	if (ns_get32(c_arr) != 0xABCD5678) return 5;
	return 0;
}


int search_parse(void) {
	int len;
	char name[100];
	unsigned char answer[280];
	unsigned char *dnptrs[] = {answer, NULL, NULL};
	unsigned char cmp_name[100];
	ns_msg msg;
	ns_rr rr;

	// Fetch example DNS
	if ((len=res_search("example.com", C_IN, ns_t_ns, answer, 280)) == -1)
		return 1;
	if (ns_initparse(answer, len, &msg) == -1) return 2;

	// Parse RR for answer from handle and check valid type
	if ((ns_parserr(&msg, ns_s_an, 0, &rr)) != 0) return 3;

	if (ns_rr_type(rr) == ns_t_invalid) return 4;

	if (ns_name_uncompress(
		ns_msg_base(msg),
		ns_msg_end(msg),
		ns_rr_rdata(rr),
		name,
		100
		) < 0) return 5;

	// Compress name and compare
	len = dn_comp(name, cmp_name, 100, dnptrs, dnptrs+2);
	if (memcmp(cmp_name, ns_rr_rdata(rr), len)) return 6;
	return 0;
}


int main(int argc, char **argv) {
	if (argc < 2) return -1;
	switch (argv[1][0]){
	case '0':
		return put_get();
	case '1':
		return search_parse();
	default:
		return -1;
	}
}
