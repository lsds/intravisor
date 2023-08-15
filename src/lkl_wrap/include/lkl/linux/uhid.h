/* SPDX-License-Identifier: GPL-2.0+ WITH Linux-syscall-note */
#ifndef __LKL__UHID_H_
#define __LKL__UHID_H_

/*
 * User-space I/O driver support for HID subsystem
 * Copyright (c) 2012 David Herrmann
 */

/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

/*
 * Public header for user-space communication. We try to keep every structure
 * aligned but to be safe we also use __attribute__((__packed__)). Therefore,
 * the communication should be ABI compatible even between architectures.
 */

#include <lkl/linux/input.h>
#include <lkl/linux/types.h>
#include <lkl/linux/hid.h>

enum lkl_uhid_event_type {
	__LKL__UHID_LEGACY_CREATE,
	LKL_UHID_DESTROY,
	LKL_UHID_START,
	LKL_UHID_STOP,
	LKL_UHID_OPEN,
	LKL_UHID_CLOSE,
	LKL_UHID_OUTPUT,
	__LKL__UHID_LEGACY_OUTPUT_EV,
	__LKL__UHID_LEGACY_INPUT,
	LKL_UHID_GET_REPORT,
	LKL_UHID_GET_REPORT_REPLY,
	LKL_UHID_CREATE2,
	LKL_UHID_INPUT2,
	LKL_UHID_SET_REPORT,
	LKL_UHID_SET_REPORT_REPLY,
};

struct lkl_uhid_create2_req {
	__lkl__u8 name[128];
	__lkl__u8 phys[64];
	__lkl__u8 uniq[64];
	__lkl__u16 rd_size;
	__lkl__u16 bus;
	__lkl__u32 vendor;
	__lkl__u32 product;
	__lkl__u32 version;
	__lkl__u32 country;
	__lkl__u8 rd_data[LKL_HID_MAX_DESCRIPTOR_SIZE];
} __attribute__((__packed__));

enum lkl_uhid_dev_flag {
	LKL_UHID_DEV_NUMBERED_FEATURE_REPORTS			= (1ULL << 0),
	LKL_UHID_DEV_NUMBERED_OUTPUT_REPORTS			= (1ULL << 1),
	LKL_UHID_DEV_NUMBERED_INPUT_REPORTS				= (1ULL << 2),
};

struct lkl_uhid_start_req {
	__lkl__u64 dev_flags;
};

#define LKL_UHID_DATA_MAX 4096

enum lkl_uhid_report_type {
	LKL_UHID_FEATURE_REPORT,
	LKL_UHID_OUTPUT_REPORT,
	LKL_UHID_INPUT_REPORT,
};

struct lkl_uhid_input2_req {
	__lkl__u16 size;
	__lkl__u8 data[LKL_UHID_DATA_MAX];
} __attribute__((__packed__));

struct lkl_uhid_output_req {
	__lkl__u8 data[LKL_UHID_DATA_MAX];
	__lkl__u16 size;
	__lkl__u8 rtype;
} __attribute__((__packed__));

struct lkl_uhid_get_report_req {
	__lkl__u32 id;
	__lkl__u8 rnum;
	__lkl__u8 rtype;
} __attribute__((__packed__));

struct lkl_uhid_get_report_reply_req {
	__lkl__u32 id;
	__lkl__u16 err;
	__lkl__u16 size;
	__lkl__u8 data[LKL_UHID_DATA_MAX];
} __attribute__((__packed__));

struct lkl_uhid_set_report_req {
	__lkl__u32 id;
	__lkl__u8 rnum;
	__lkl__u8 rtype;
	__lkl__u16 size;
	__lkl__u8 data[LKL_UHID_DATA_MAX];
} __attribute__((__packed__));

struct lkl_uhid_set_report_reply_req {
	__lkl__u32 id;
	__lkl__u16 err;
} __attribute__((__packed__));

/*
 * Compat Layer
 * All these commands and requests are obsolete. You should avoid using them in
 * new code. We support them for backwards-compatibility, but you might not get
 * access to new feature in case you use them.
 */

enum lkl_uhid_legacy_event_type {
	LKL_UHID_CREATE			= __LKL__UHID_LEGACY_CREATE,
	LKL_UHID_OUTPUT_EV			= __LKL__UHID_LEGACY_OUTPUT_EV,
	LKL_UHID_INPUT			= __LKL__UHID_LEGACY_INPUT,
	LKL_UHID_FEATURE			= LKL_UHID_GET_REPORT,
	LKL_UHID_FEATURE_ANSWER		= LKL_UHID_GET_REPORT_REPLY,
};

/* Obsolete! Use LKL_UHID_CREATE2. */
struct lkl_uhid_create_req {
	__lkl__u8 name[128];
	__lkl__u8 phys[64];
	__lkl__u8 uniq[64];
	__lkl__u8 *rd_data;
	__lkl__u16 rd_size;

	__lkl__u16 bus;
	__lkl__u32 vendor;
	__lkl__u32 product;
	__lkl__u32 version;
	__lkl__u32 country;
} __attribute__((__packed__));

/* Obsolete! Use LKL_UHID_INPUT2. */
struct lkl_uhid_input_req {
	__lkl__u8 data[LKL_UHID_DATA_MAX];
	__lkl__u16 size;
} __attribute__((__packed__));

/* Obsolete! Kernel uses LKL_UHID_OUTPUT exclusively now. */
struct lkl_uhid_output_ev_req {
	__lkl__u16 type;
	__lkl__u16 code;
	__lkl__s32 value;
} __attribute__((__packed__));

/* Obsolete! Kernel uses ABI compatible LKL_UHID_GET_REPORT. */
struct lkl_uhid_feature_req {
	__lkl__u32 id;
	__lkl__u8 rnum;
	__lkl__u8 rtype;
} __attribute__((__packed__));

/* Obsolete! Use ABI compatible LKL_UHID_GET_REPORT_REPLY. */
struct lkl_uhid_feature_answer_req {
	__lkl__u32 id;
	__lkl__u16 err;
	__lkl__u16 size;
	__lkl__u8 data[LKL_UHID_DATA_MAX];
} __attribute__((__packed__));

/*
 * UHID Events
 * All UHID events from and to the kernel are encoded as "struct lkl_uhid_event".
 * The "type" field contains a UHID_* type identifier. All payload depends on
 * that type and can be accessed via ev->u.XYZ accordingly.
 * If user-space writes short events, they're extended with 0s by the kernel. If
 * the kernel writes short events, user-space shall extend them with 0s.
 */

struct lkl_uhid_event {
	__lkl__u32 type;

	union {
		struct lkl_uhid_create_req create;
		struct lkl_uhid_input_req input;
		struct lkl_uhid_output_req output;
		struct lkl_uhid_output_ev_req output_ev;
		struct lkl_uhid_feature_req feature;
		struct lkl_uhid_get_report_req get_report;
		struct lkl_uhid_feature_answer_req feature_answer;
		struct lkl_uhid_get_report_reply_req get_report_reply;
		struct lkl_uhid_create2_req create2;
		struct lkl_uhid_input2_req input2;
		struct lkl_uhid_set_report_req set_report;
		struct lkl_uhid_set_report_reply_req set_report_reply;
		struct lkl_uhid_start_req start;
	} u;
} __attribute__((__packed__));

#endif /* __LKL__UHID_H_ */
