#ifndef	_LINUX_BITOPS_H_
#define	_LINUX_BITOPS_H_

#include <errno.h>
#include <uk/essentials.h>
#include <uk/bitcount.h>

#define howmany(n, d) (((n) + ((d) - 1)) / (d))
#define roundup(n, d) (howmany(n, d) * (d))
#define powerof2(n) !(((n) - 1) & (n))

#define	UK_BITS_PER_LONG		64
#define	UK_BITS_TO_LONGS(n)               howmany((n), UK_BITS_PER_LONG)
#define UK_BIT_WORD(nr)                   ((nr) / UK_BITS_PER_LONG)

#define	UK_BITMAP_FIRST_WORD_MASK(start)  (~0UL << ((start) % UK_BITS_PER_LONG))
#define	UK_BITMAP_LAST_WORD_MASK(n)       (~0UL >> (UK_BITS_PER_LONG - (n)))

#define BITS_PER_BYTE  8

#define	uk_hweight8(x)	uk_bitcount((uint8_t)(x))
#define	uk_hweight16(x)	uk_bitcount16(x)
#define	uk_hweight32(x)	uk_bitcount32(x)
#define	uk_hweight64(x)	uk_bitcount64(x)
#define	uk_hweight_long(x)	uk_bitcountl(x)


enum {
	REG_OP_ISFREE,
	REG_OP_ALLOC,
	REG_OP_RELEASE,
};


/**
 * Find first (lowest) set bit in word.
 * @param x The word to operate on
 *
 * @return The index of the least significant 1-bit of x, or if x is zero,
 *   the result is undefined. ffs(1)=0, ffs(3)=0, ffs(0x80000000)=31
 */
static inline unsigned int ukarch_ffs(unsigned int x)
{
	return __builtin_ffs(x) - 1;
}

/**
 * Find last (highest) set bit in word.
 * @param x The word to operate on
 *
 * @return The index of the most significant 1-bit of x, or if x is zero,
 *   the result is undefined. fls(1)=0, fls(3)=1, fls(0x80000001)=31
 */
static inline unsigned int ukarch_fls(unsigned int x)
{
	return sizeof(x) * 8 - __builtin_clz(x) - 1;
}

/**
 * Find first (lowest) set bit in long word.
 * @param x The long word to operate on
 *
 * @return The index of the least significant 1-bit of x, or if x is zero,
 *    the result is undefined. ffs(1)=0, ffs(3)=0, ffs(0x80000000)=31
 */
static inline unsigned int ukarch_ffsl(unsigned long x)
{
	return __builtin_ffsl(x) - 1;
}

/**
 * Find last (highest) set bit in long word.
 * @param x The long word to operate on
 *
 * @return The index of the most significant 1-bit of x, or if x is zero,
 *   the result is undefined. fls(1)=0, fls(3)=1, fls(0x80000001)=31
 */
static inline unsigned int ukarch_flsl(unsigned long x)
{
	return sizeof(x) * 8 - __builtin_clzl(x) - 1;
}

static inline int
__uk_bitopts_reg_op(unsigned long *bitmap, int pos, int order, int reg_op)
{
	int nbits_reg;
	int index;
	int offset;
	int nlongs_reg;
	int nbitsinlong;
	unsigned long mask;
	int i;
	int ret = 0;

	nbits_reg = 1 << order;
	index = pos / UK_BITS_PER_LONG;
	offset = pos - (index * UK_BITS_PER_LONG);
	nlongs_reg = UK_BITS_TO_LONGS(nbits_reg);
	nbitsinlong = MIN(nbits_reg,  UK_BITS_PER_LONG);

	mask = (1UL << (nbitsinlong - 1));
	mask += mask - 1;
	mask <<= offset;

	switch (reg_op) {
	case REG_OP_ISFREE:
		for (i = 0; i < nlongs_reg; i++) {
			if (bitmap[index + i] & mask)
				goto done;
		}
		ret = 1;
		break;

	case REG_OP_ALLOC:
		for (i = 0; i < nlongs_reg; i++)
			bitmap[index + i] |= mask;
		break;

	case REG_OP_RELEASE:
		for (i = 0; i < nlongs_reg; i++)
			bitmap[index + i] &= ~mask;
		break;
	}
done:
	return ret;
}

static inline int uk_test_bit(int nr, const volatile unsigned long *addr)
{
	const volatile __u8 *ptr = (const __u8 *) addr;
	int ret =  ((1 << (nr & 7)) & (ptr[nr >> 3])) != 0;

	return ret;
}

#endif