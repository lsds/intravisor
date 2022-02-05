/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_BYTEORDER_LITTLE_ENDIAN_H
#define _LKL_LINUX_BYTEORDER_LITTLE_ENDIAN_H

#ifndef __LKL__LITTLE_ENDIAN
#define __LKL__LITTLE_ENDIAN 1234
#endif
#ifndef __LKL__LITTLE_ENDIAN_BITFIELD
#define __LKL__LITTLE_ENDIAN_BITFIELD
#endif

#include <lkl/linux/types.h>
#include <lkl/linux/swab.h>

#define __lkl__constant_htonl(x) ((__lkl__be32)__lkl___constant_swab32((x)))
#define __lkl__constant_ntohl(x) __lkl___constant_swab32((__lkl__be32)(x))
#define __lkl__constant_htons(x) ((__lkl__be16)__lkl___constant_swab16((x)))
#define __lkl__constant_ntohs(x) __lkl___constant_swab16((__lkl__be16)(x))
#define __lkl__constant_cpu_to_le64(x) ((__lkl__le64)(__lkl__u64)(x))
#define __lkl__constant_le64_to_cpu(x) ((__lkl__u64)(__lkl__le64)(x))
#define __lkl__constant_cpu_to_le32(x) ((__lkl__le32)(__lkl__u32)(x))
#define __lkl__constant_le32_to_cpu(x) ((__lkl__u32)(__lkl__le32)(x))
#define __lkl__constant_cpu_to_le16(x) ((__lkl__le16)(__lkl__u16)(x))
#define __lkl__constant_le16_to_cpu(x) ((__lkl__u16)(__lkl__le16)(x))
#define __lkl__constant_cpu_to_be64(x) ((__lkl__be64)__lkl___constant_swab64((x)))
#define __lkl__constant_be64_to_cpu(x) __lkl___constant_swab64((__lkl__u64)(__lkl__be64)(x))
#define __lkl__constant_cpu_to_be32(x) ((__lkl__be32)__lkl___constant_swab32((x)))
#define __lkl__constant_be32_to_cpu(x) __lkl___constant_swab32((__lkl__u32)(__lkl__be32)(x))
#define __lkl__constant_cpu_to_be16(x) ((__lkl__be16)__lkl___constant_swab16((x)))
#define __lkl__constant_be16_to_cpu(x) __lkl___constant_swab16((__lkl__u16)(__lkl__be16)(x))
#define __lkl__cpu_to_le64(x) ((__lkl__le64)(__lkl__u64)(x))
#define __lkl__le64_to_cpu(x) ((__lkl__u64)(__lkl__le64)(x))
#define __lkl__cpu_to_le32(x) ((__lkl__le32)(__lkl__u32)(x))
#define __lkl__le32_to_cpu(x) ((__lkl__u32)(__lkl__le32)(x))
#define __lkl__cpu_to_le16(x) ((__lkl__le16)(__lkl__u16)(x))
#define __lkl__le16_to_cpu(x) ((__lkl__u16)(__lkl__le16)(x))
#define __lkl__cpu_to_be64(x) ((__lkl__be64)__lkl__swab64((x)))
#define __lkl__be64_to_cpu(x) __lkl__swab64((__lkl__u64)(__lkl__be64)(x))
#define __lkl__cpu_to_be32(x) ((__lkl__be32)__lkl__swab32((x)))
#define __lkl__be32_to_cpu(x) __lkl__swab32((__lkl__u32)(__lkl__be32)(x))
#define __lkl__cpu_to_be16(x) ((__lkl__be16)__lkl__swab16((x)))
#define __lkl__be16_to_cpu(x) __lkl__swab16((__lkl__u16)(__lkl__be16)(x))

static __lkl__always_inline __lkl__le64 __lkl__cpu_to_le64p(const __lkl__u64 *p)
{
	return (__lkl__le64)*p;
}
static __lkl__always_inline __lkl__u64 __lkl__le64_to_cpup(const __lkl__le64 *p)
{
	return (__lkl__u64)*p;
}
static __lkl__always_inline __lkl__le32 __lkl__cpu_to_le32p(const __lkl__u32 *p)
{
	return (__lkl__le32)*p;
}
static __lkl__always_inline __lkl__u32 __lkl__le32_to_cpup(const __lkl__le32 *p)
{
	return (__lkl__u32)*p;
}
static __lkl__always_inline __lkl__le16 __lkl__cpu_to_le16p(const __lkl__u16 *p)
{
	return (__lkl__le16)*p;
}
static __lkl__always_inline __lkl__u16 __lkl__le16_to_cpup(const __lkl__le16 *p)
{
	return (__lkl__u16)*p;
}
static __lkl__always_inline __lkl__be64 __lkl__cpu_to_be64p(const __lkl__u64 *p)
{
	return (__lkl__be64)__lkl__swab64p(p);
}
static __lkl__always_inline __lkl__u64 __lkl__be64_to_cpup(const __lkl__be64 *p)
{
	return __lkl__swab64p((__lkl__u64 *)p);
}
static __lkl__always_inline __lkl__be32 __lkl__cpu_to_be32p(const __lkl__u32 *p)
{
	return (__lkl__be32)__lkl__swab32p(p);
}
static __lkl__always_inline __lkl__u32 __lkl__be32_to_cpup(const __lkl__be32 *p)
{
	return __lkl__swab32p((__lkl__u32 *)p);
}
static __lkl__always_inline __lkl__be16 __lkl__cpu_to_be16p(const __lkl__u16 *p)
{
	return (__lkl__be16)__lkl__swab16p(p);
}
static __lkl__always_inline __lkl__u16 __lkl__be16_to_cpup(const __lkl__be16 *p)
{
	return __lkl__swab16p((__lkl__u16 *)p);
}
#define __lkl__cpu_to_le64s(x) do { (void)(x); } while (0)
#define __lkl__le64_to_cpus(x) do { (void)(x); } while (0)
#define __lkl__cpu_to_le32s(x) do { (void)(x); } while (0)
#define __lkl__le32_to_cpus(x) do { (void)(x); } while (0)
#define __lkl__cpu_to_le16s(x) do { (void)(x); } while (0)
#define __lkl__le16_to_cpus(x) do { (void)(x); } while (0)
#define __lkl__cpu_to_be64s(x) __lkl__swab64s((x))
#define __lkl__be64_to_cpus(x) __lkl__swab64s((x))
#define __lkl__cpu_to_be32s(x) __lkl__swab32s((x))
#define __lkl__be32_to_cpus(x) __lkl__swab32s((x))
#define __lkl__cpu_to_be16s(x) __lkl__swab16s((x))
#define __lkl__be16_to_cpus(x) __lkl__swab16s((x))


#endif /* _LKL_LINUX_BYTEORDER_LITTLE_ENDIAN_H */
