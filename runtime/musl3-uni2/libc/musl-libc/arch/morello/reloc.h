#if __BYTE_ORDER == __BIG_ENDIAN
#define ENDIAN_SUFFIX "_be"
#else
#define ENDIAN_SUFFIX ""
#endif

#define LDSO_ARCH "aarch64" ENDIAN_SUFFIX

#define NO_LEGACY_INITFINI

#define TPOFF_K 0

#define REL_SYMBOLIC    R_AARCH64_ABS64
#define REL_GOT         R_MORELLO_GLOB_DAT
#define REL_PLT         R_MORELLO_JUMP_SLOT
#define REL_RELATIVE    R_MORELLO_RELATIVE
#define REL_COPY        R_AARCH64_COPY
#define REL_DTPMOD      R_AARCH64_TLS_DTPMOD64
#define REL_DTPOFF      R_AARCH64_TLS_DTPREL64
#define REL_TPOFF       R_AARCH64_TLS_TPREL64
#define REL_TLSDESC     R_MORELLO_TLSDESC
#define REL_CAPINIT     R_MORELLO_CAPINIT

#define MORELLO_RELA_PERM_RX 4
#define MORELLO_RELA_PERM_RW 2
#define MORELLO_RELA_PERM_R 1

#define CRTJMP(pc,sp) __asm__ __volatile__( \
	"mov csp,%1 ; br %0" : : "r"(pc), "r"(sp) : "memory" )

typedef struct {
	uint64_t address;
	uint64_t length : 56;
	uint64_t perms : 8;
} morello_reloc_cap_t;
