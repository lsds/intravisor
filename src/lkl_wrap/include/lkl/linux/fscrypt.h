/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/*
 * fscrypt user API
 *
 * These ioctls can be used on filesystems that support fscrypt.  See the
 * "User API" section of Documentation/filesystems/fscrypt.rst.
 */
#ifndef _LKL_LINUX_FSCRYPT_H
#define _LKL_LINUX_FSCRYPT_H

#include <lkl/linux/ioctl.h>
#include <lkl/linux/types.h>

/* Encryption policy flags */
#define LKL_FSCRYPT_POLICY_FLAGS_PAD_4		0x00
#define LKL_FSCRYPT_POLICY_FLAGS_PAD_8		0x01
#define LKL_FSCRYPT_POLICY_FLAGS_PAD_16		0x02
#define LKL_FSCRYPT_POLICY_FLAGS_PAD_32		0x03
#define LKL_FSCRYPT_POLICY_FLAGS_PAD_MASK		0x03
#define LKL_FSCRYPT_POLICY_FLAG_DIRECT_KEY		0x04
#define LKL_FSCRYPT_POLICY_FLAG_IV_INO_LBLK_64	0x08
#define LKL_FSCRYPT_POLICY_FLAG_IV_INO_LBLK_32	0x10

/* Encryption algorithms */
#define LKL_FSCRYPT_MODE_AES_256_XTS		1
#define LKL_FSCRYPT_MODE_AES_256_CTS		4
#define LKL_FSCRYPT_MODE_AES_128_CBC		5
#define LKL_FSCRYPT_MODE_AES_128_CTS		6
#define LKL_FSCRYPT_MODE_ADIANTUM			9
#define LKL_FSCRYPT_MODE_AES_256_HCTR2		10
/* If adding a mode number > 10, update FSCRYPT_MODE_MAX in fscrypt_private.h */

/*
 * Legacy policy version; ad-hoc KDF and no key verification.
 * For new encrypted directories, use fscrypt_policy_v2 instead.
 *
 * Careful: the .version field for this is actually 0, not 1.
 */
#define LKL_FSCRYPT_POLICY_V1		0
#define LKL_FSCRYPT_KEY_DESCRIPTOR_SIZE	8
struct lkl_fscrypt_policy_v1 {
	__lkl__u8 version;
	__lkl__u8 contents_encryption_mode;
	__lkl__u8 filenames_encryption_mode;
	__lkl__u8 flags;
	__lkl__u8 master_key_descriptor[LKL_FSCRYPT_KEY_DESCRIPTOR_SIZE];
};

/*
 * Process-subscribed "logon" key description prefix and payload format.
 * Deprecated; prefer LKL_FS_IOC_ADD_ENCRYPTION_KEY instead.
 */
#define LKL_FSCRYPT_KEY_DESC_PREFIX		"fscrypt:"
#define LKL_FSCRYPT_KEY_DESC_PREFIX_SIZE	8
#define LKL_FSCRYPT_MAX_KEY_SIZE		64
struct lkl_fscrypt_key {
	__lkl__u32 mode;
	__lkl__u8 raw[LKL_FSCRYPT_MAX_KEY_SIZE];
	__lkl__u32 size;
};

/*
 * New policy version with HKDF and key verification (recommended).
 */
#define LKL_FSCRYPT_POLICY_V2		2
#define LKL_FSCRYPT_KEY_IDENTIFIER_SIZE	16
struct lkl_fscrypt_policy_v2 {
	__lkl__u8 version;
	__lkl__u8 contents_encryption_mode;
	__lkl__u8 filenames_encryption_mode;
	__lkl__u8 flags;
	__lkl__u8 __reserved[4];
	__lkl__u8 master_key_identifier[LKL_FSCRYPT_KEY_IDENTIFIER_SIZE];
};

/* Struct passed to LKL_FS_IOC_GET_ENCRYPTION_POLICY_EX */
struct lkl_fscrypt_get_policy_ex_arg {
	__lkl__u64 policy_size; /* input/output */
	union {
		__lkl__u8 version;
		struct lkl_fscrypt_policy_v1 v1;
		struct lkl_fscrypt_policy_v2 v2;
	} policy; /* output */
};

/*
 * v1 policy keys are specified by an arbitrary 8-byte key "descriptor",
 * matching fscrypt_policy_v1::master_key_descriptor.
 */
#define LKL_FSCRYPT_KEY_SPEC_TYPE_DESCRIPTOR	1

/*
 * v2 policy keys are specified by a 16-byte key "identifier" which the kernel
 * calculates as a cryptographic hash of the key itself,
 * matching fscrypt_policy_v2::master_key_identifier.
 */
#define LKL_FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER	2

/*
 * Specifies a key, either for v1 or v2 policies.  This doesn't contain the
 * actual key itself; this is just the "name" of the key.
 */
struct lkl_fscrypt_key_specifier {
	__lkl__u32 type;	/* one of FSCRYPT_KEY_SPEC_TYPE_* */
	__lkl__u32 __reserved;
	union {
		__lkl__u8 __reserved[32]; /* reserve some extra space */
		__lkl__u8 descriptor[LKL_FSCRYPT_KEY_DESCRIPTOR_SIZE];
		__lkl__u8 identifier[LKL_FSCRYPT_KEY_IDENTIFIER_SIZE];
	} u;
};

/*
 * Payload of Linux keyring key of type "fscrypt-provisioning", referenced by
 * fscrypt_add_key_arg::key_id as an alternative to fscrypt_add_key_arg::raw.
 */
struct lkl_fscrypt_provisioning_key_payload {
	__lkl__u32 type;
	__lkl__u32 __reserved;
	__lkl__u8 raw[];
};

/* Struct passed to LKL_FS_IOC_ADD_ENCRYPTION_KEY */
struct lkl_fscrypt_add_key_arg {
	struct lkl_fscrypt_key_specifier key_spec;
	__lkl__u32 raw_size;
	__lkl__u32 key_id;
	__lkl__u32 __reserved[8];
	__lkl__u8 raw[];
};

/* Struct passed to LKL_FS_IOC_REMOVE_ENCRYPTION_KEY */
struct lkl_fscrypt_remove_key_arg {
	struct lkl_fscrypt_key_specifier key_spec;
#define LKL_FSCRYPT_KEY_REMOVAL_STATUS_FLAG_FILES_BUSY	0x00000001
#define LKL_FSCRYPT_KEY_REMOVAL_STATUS_FLAG_OTHER_USERS	0x00000002
	__lkl__u32 removal_status_flags;	/* output */
	__lkl__u32 __reserved[5];
};

/* Struct passed to LKL_FS_IOC_GET_ENCRYPTION_KEY_STATUS */
struct lkl_fscrypt_get_key_status_arg {
	/* input */
	struct lkl_fscrypt_key_specifier key_spec;
	__lkl__u32 __reserved[6];

	/* output */
#define LKL_FSCRYPT_KEY_STATUS_ABSENT		1
#define LKL_FSCRYPT_KEY_STATUS_PRESENT		2
#define LKL_FSCRYPT_KEY_STATUS_INCOMPLETELY_REMOVED	3
	__lkl__u32 status;
#define LKL_FSCRYPT_KEY_STATUS_FLAG_ADDED_BY_SELF   0x00000001
	__lkl__u32 status_flags;
	__lkl__u32 user_count;
	__lkl__u32 __out_reserved[13];
};

#define LKL_FS_IOC_SET_ENCRYPTION_POLICY		_LKL_IOR('f', 19, struct lkl_fscrypt_policy_v1)
#define LKL_FS_IOC_GET_ENCRYPTION_PWSALT		_LKL_IOW('f', 20, __lkl__u8[16])
#define LKL_FS_IOC_GET_ENCRYPTION_POLICY		_LKL_IOW('f', 21, struct lkl_fscrypt_policy_v1)
#define LKL_FS_IOC_GET_ENCRYPTION_POLICY_EX		_LKL_IOWR('f', 22, __lkl__u8[9]) /* size + version */
#define LKL_FS_IOC_ADD_ENCRYPTION_KEY		_LKL_IOWR('f', 23, struct lkl_fscrypt_add_key_arg)
#define LKL_FS_IOC_REMOVE_ENCRYPTION_KEY		_LKL_IOWR('f', 24, struct lkl_fscrypt_remove_key_arg)
#define LKL_FS_IOC_REMOVE_ENCRYPTION_KEY_ALL_USERS	_LKL_IOWR('f', 25, struct lkl_fscrypt_remove_key_arg)
#define LKL_FS_IOC_GET_ENCRYPTION_KEY_STATUS	_LKL_IOWR('f', 26, struct lkl_fscrypt_get_key_status_arg)
#define LKL_FS_IOC_GET_ENCRYPTION_NONCE		_LKL_IOR('f', 27, __lkl__u8[16])

/**********************************************************************/

/* old names; don't add anything new here! */
#define lkl_fscrypt_policy			fscrypt_policy_v1
#define LKL_FS_KEY_DESCRIPTOR_SIZE		LKL_FSCRYPT_KEY_DESCRIPTOR_SIZE
#define LKL_FS_POLICY_FLAGS_PAD_4		LKL_FSCRYPT_POLICY_FLAGS_PAD_4
#define LKL_FS_POLICY_FLAGS_PAD_8		LKL_FSCRYPT_POLICY_FLAGS_PAD_8
#define LKL_FS_POLICY_FLAGS_PAD_16		LKL_FSCRYPT_POLICY_FLAGS_PAD_16
#define LKL_FS_POLICY_FLAGS_PAD_32		LKL_FSCRYPT_POLICY_FLAGS_PAD_32
#define LKL_FS_POLICY_FLAGS_PAD_MASK	LKL_FSCRYPT_POLICY_FLAGS_PAD_MASK
#define LKL_FS_POLICY_FLAG_DIRECT_KEY	LKL_FSCRYPT_POLICY_FLAG_DIRECT_KEY
#define LKL_FS_POLICY_FLAGS_VALID		0x07	/* contains old flags only */
#define LKL_FS_ENCRYPTION_MODE_INVALID	0	/* never used */
#define LKL_FS_ENCRYPTION_MODE_AES_256_XTS	LKL_FSCRYPT_MODE_AES_256_XTS
#define LKL_FS_ENCRYPTION_MODE_AES_256_GCM	2	/* never used */
#define LKL_FS_ENCRYPTION_MODE_AES_256_CBC	3	/* never used */
#define LKL_FS_ENCRYPTION_MODE_AES_256_CTS	LKL_FSCRYPT_MODE_AES_256_CTS
#define LKL_FS_ENCRYPTION_MODE_AES_128_CBC	LKL_FSCRYPT_MODE_AES_128_CBC
#define LKL_FS_ENCRYPTION_MODE_AES_128_CTS	LKL_FSCRYPT_MODE_AES_128_CTS
#define LKL_FS_ENCRYPTION_MODE_SPECK128_256_XTS	7	/* removed */
#define LKL_FS_ENCRYPTION_MODE_SPECK128_256_CTS	8	/* removed */
#define LKL_FS_ENCRYPTION_MODE_ADIANTUM	LKL_FSCRYPT_MODE_ADIANTUM
#define LKL_FS_KEY_DESC_PREFIX		LKL_FSCRYPT_KEY_DESC_PREFIX
#define LKL_FS_KEY_DESC_PREFIX_SIZE		LKL_FSCRYPT_KEY_DESC_PREFIX_SIZE
#define LKL_FS_MAX_KEY_SIZE			LKL_FSCRYPT_MAX_KEY_SIZE

#endif /* _LKL_LINUX_FSCRYPT_H */
