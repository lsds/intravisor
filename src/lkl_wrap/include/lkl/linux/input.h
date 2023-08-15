/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (c) 1999-2002 Vojtech Pavlik
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 */
#ifndef _LKL_INPUT_H
#define _LKL_INPUT_H


#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <lkl/linux/types.h>

#include "input-event-codes.h"

/*
 * The event structure itself
 * Note that __USE_TIME_BITS64 is defined by libc based on
 * application's request to use 64 bit lkl_time_t.
 */

struct lkl_input_event {
#if (__LKL__BITS_PER_LONG != 32 || !defined(__USE_TIME_BITS64)) && !defined(__LKL__KERNEL__)
	struct lkl_timeval time;
#define lkl_input_event_sec time.tv_sec
#define lkl_input_event_usec time.tv_usec
#else
	__lkl__kernel_ulong_t __sec;
#if defined(__sparc__) && defined(__arch64__)
	unsigned int __usec;
	unsigned int __pad;
#else
	__lkl__kernel_ulong_t __usec;
#endif
#define lkl_input_event_sec  __sec
#define lkl_input_event_usec __usec
#endif
	__lkl__u16 type;
	__lkl__u16 code;
	__lkl__s32 value;
};

/*
 * Protocol version.
 */

#define LKL_EV_VERSION		0x010001

/*
 * IOCTLs (0x00 - 0x7f)
 */

struct lkl_input_id {
	__lkl__u16 bustype;
	__lkl__u16 vendor;
	__lkl__u16 product;
	__lkl__u16 version;
};

/**
 * struct lkl_input_absinfo - used by LKL_EVIOCGABS/LKL_EVIOCSABS ioctls
 * @value: latest reported value for the axis.
 * @minimum: specifies minimum value for the axis.
 * @maximum: specifies maximum value for the axis.
 * @fuzz: specifies fuzz value that is used to filter noise from
 *	the event stream.
 * @flat: values that are within this value will be discarded by
 *	joydev interface and reported as 0 instead.
 * @resolution: specifies resolution for the values reported for
 *	the axis.
 *
 * Note that input core does not clamp reported values to the
 * [minimum, maximum] limits, such task is left to userspace.
 *
 * The default resolution for main axes (LKL_ABS_X, LKL_ABS_Y, LKL_ABS_Z,
 * LKL_ABS_MT_POSITION_X, LKL_ABS_MT_POSITION_Y) is reported in units
 * per millimeter (units/mm), resolution for rotational axes
 * (LKL_ABS_RX, LKL_ABS_RY, LKL_ABS_RZ) is reported in units per radian.
 * The resolution for the size axes (LKL_ABS_MT_TOUCH_MAJOR,
 * LKL_ABS_MT_TOUCH_MINOR, LKL_ABS_MT_WIDTH_MAJOR, LKL_ABS_MT_WIDTH_MINOR)
 * is reported in units per millimeter (units/mm).
 * When LKL_INPUT_PROP_ACCELEROMETER is set the resolution changes.
 * The main axes (LKL_ABS_X, LKL_ABS_Y, LKL_ABS_Z) are then reported in
 * units per g (units/g) and in units per degree per second
 * (units/deg/s) for rotational axes (LKL_ABS_RX, LKL_ABS_RY, LKL_ABS_RZ).
 */
struct lkl_input_absinfo {
	__lkl__s32 value;
	__lkl__s32 minimum;
	__lkl__s32 maximum;
	__lkl__s32 fuzz;
	__lkl__s32 flat;
	__lkl__s32 resolution;
};

/**
 * struct lkl_input_keymap_entry - used by LKL_EVIOCGKEYCODE/LKL_EVIOCSKEYCODE ioctls
 * @scancode: scancode represented in machine-endian form.
 * @len: length of the scancode that resides in @scancode buffer.
 * @index: index in the keymap, may be used instead of scancode
 * @flags: allows to specify how kernel should handle the request. For
 *	example, setting LKL_INPUT_KEYMAP_BY_INDEX flag indicates that kernel
 *	should perform lookup in keymap by @index instead of @scancode
 * @keycode: key code assigned to this scancode
 *
 * The structure is used to retrieve and modify keymap data. Users have
 * option of performing lookup either by @scancode itself or by @index
 * in keymap entry. LKL_EVIOCGKEYCODE will also return scancode or index
 * (depending on which element was used to perform lookup).
 */
struct lkl_input_keymap_entry {
#define LKL_INPUT_KEYMAP_BY_INDEX	(1 << 0)
	__lkl__u8  flags;
	__lkl__u8  len;
	__lkl__u16 index;
	__lkl__u32 keycode;
	__lkl__u8  scancode[32];
};

struct lkl_input_mask {
	__lkl__u32 type;
	__lkl__u32 codes_size;
	__lkl__u64 codes_ptr;
};

#define LKL_EVIOCGVERSION		_LKL_IOR('E', 0x01, int)			/* get driver version */
#define LKL_EVIOCGID		_LKL_IOR('E', 0x02, struct lkl_input_id)	/* get device ID */
#define LKL_EVIOCGREP		_LKL_IOR('E', 0x03, unsigned int[2])	/* get repeat settings */
#define LKL_EVIOCSREP		_LKL_IOW('E', 0x03, unsigned int[2])	/* set repeat settings */

#define LKL_EVIOCGKEYCODE		_LKL_IOR('E', 0x04, unsigned int[2])        /* get keycode */
#define LKL_EVIOCGKEYCODE_V2	_LKL_IOR('E', 0x04, struct lkl_input_keymap_entry)
#define LKL_EVIOCSKEYCODE		_LKL_IOW('E', 0x04, unsigned int[2])        /* set keycode */
#define LKL_EVIOCSKEYCODE_V2	_LKL_IOW('E', 0x04, struct lkl_input_keymap_entry)

#define LKL_EVIOCGNAME(len)		_LKL_IOC(_LKL_IOC_READ, 'E', 0x06, len)		/* get device name */
#define LKL_EVIOCGPHYS(len)		_LKL_IOC(_LKL_IOC_READ, 'E', 0x07, len)		/* get physical location */
#define LKL_EVIOCGUNIQ(len)		_LKL_IOC(_LKL_IOC_READ, 'E', 0x08, len)		/* get unique identifier */
#define LKL_EVIOCGPROP(len)		_LKL_IOC(_LKL_IOC_READ, 'E', 0x09, len)		/* get device properties */

/**
 * LKL_EVIOCGMTSLOTS(len) - get MT slot values
 * @len: size of the data buffer in bytes
 *
 * The ioctl buffer argument should be binary equivalent to
 *
 * struct lkl_input_mt_request_layout {
 *	__lkl__u32 code;
 *	__lkl__s32 values[num_slots];
 * };
 *
 * where num_slots is the (arbitrary) number of MT slots to extract.
 *
 * The ioctl size argument (len) is the size of the buffer, which
 * should satisfy len = (num_slots + 1) * sizeof(__lkl__s32).  If len is
 * too small to fit all available slots, the first num_slots are
 * returned.
 *
 * Before the call, code is set to the wanted ABS_MT event type. On
 * return, values[] is filled with the slot values for the specified
 * ABS_MT code.
 *
 * If the request code is not an ABS_MT value, -LKL_EINVAL is returned.
 */
#define LKL_EVIOCGMTSLOTS(len)	_LKL_IOC(_LKL_IOC_READ, 'E', 0x0a, len)

#define LKL_EVIOCGKEY(len)		_LKL_IOC(_LKL_IOC_READ, 'E', 0x18, len)		/* get global key state */
#define LKL_EVIOCGLED(len)		_LKL_IOC(_LKL_IOC_READ, 'E', 0x19, len)		/* get all LEDs */
#define LKL_EVIOCGSND(len)		_LKL_IOC(_LKL_IOC_READ, 'E', 0x1a, len)		/* get all sounds status */
#define LKL_EVIOCGSW(len)		_LKL_IOC(_LKL_IOC_READ, 'E', 0x1b, len)		/* get all switch states */

#define LKL_EVIOCGBIT(ev,len)	_LKL_IOC(_LKL_IOC_READ, 'E', 0x20 + (ev), len)	/* get event bits */
#define LKL_EVIOCGABS(abs)		_LKL_IOR('E', 0x40 + (abs), struct lkl_input_absinfo)	/* get abs value/limits */
#define LKL_EVIOCSABS(abs)		_LKL_IOW('E', 0xc0 + (abs), struct lkl_input_absinfo)	/* set abs value/limits */

#define LKL_EVIOCSFF		_LKL_IOW('E', 0x80, struct lkl_ff_effect)	/* send a force effect to a force feedback device */
#define LKL_EVIOCRMFF		_LKL_IOW('E', 0x81, int)			/* Erase a force effect */
#define LKL_EVIOCGEFFECTS		_LKL_IOR('E', 0x84, int)			/* Report number of effects playable at the same time */

#define LKL_EVIOCGRAB		_LKL_IOW('E', 0x90, int)			/* Grab/Release device */
#define LKL_EVIOCREVOKE		_LKL_IOW('E', 0x91, int)			/* Revoke device access */

/**
 * LKL_EVIOCGMASK - Retrieve current event mask
 *
 * This ioctl allows user to retrieve the current event mask for specific
 * event type. The argument must be of type "struct lkl_input_mask" and
 * specifies the event type to query, the address of the receive buffer and
 * the size of the receive buffer.
 *
 * The event mask is a per-client mask that specifies which events are
 * forwarded to the client. Each event code is represented by a single bit
 * in the event mask. If the bit is set, the event is passed to the client
 * normally. Otherwise, the event is filtered and will never be queued on
 * the client's receive buffer.
 *
 * Event masks do not affect global state of the input device. They only
 * affect the file descriptor they are applied to.
 *
 * The default event mask for a client has all bits set, i.e. all events
 * are forwarded to the client. If the kernel is queried for an unknown
 * event type or if the receive buffer is larger than the number of
 * event codes known to the kernel, the kernel returns all zeroes for those
 * codes.
 *
 * At maximum, codes_size bytes are copied.
 *
 * This ioctl may fail with LKL_ENODEV in case the file is revoked, LKL_EFAULT
 * if the receive-buffer points to invalid memory, or LKL_EINVAL if the kernel
 * does not implement the ioctl.
 */
#define LKL_EVIOCGMASK		_LKL_IOR('E', 0x92, struct lkl_input_mask)	/* Get event-masks */

/**
 * LKL_EVIOCSMASK - Set event mask
 *
 * This ioctl is the counterpart to LKL_EVIOCGMASK. Instead of receiving the
 * current event mask, this changes the client's event mask for a specific
 * type.  See LKL_EVIOCGMASK for a description of event-masks and the
 * argument-type.
 *
 * This ioctl provides full forward compatibility. If the passed event type
 * is unknown to the kernel, or if the number of event codes specified in
 * the mask is bigger than what is known to the kernel, the ioctl is still
 * accepted and applied. However, any unknown codes are left untouched and
 * stay cleared. That means, the kernel always filters unknown codes
 * regardless of what the client requests.  If the new mask doesn't cover
 * all known event-codes, all remaining codes are automatically cleared and
 * thus filtered.
 *
 * This ioctl may fail with LKL_ENODEV in case the file is revoked. LKL_EFAULT is
 * returned if the receive-buffer points to invalid memory. LKL_EINVAL is returned
 * if the kernel does not implement the ioctl.
 */
#define LKL_EVIOCSMASK		_LKL_IOW('E', 0x93, struct lkl_input_mask)	/* Set event-masks */

#define LKL_EVIOCSCLOCKID		_LKL_IOW('E', 0xa0, int)			/* Set clockid to be used for timestamps */

/*
 * IDs.
 */

#define LKL_ID_BUS			0
#define LKL_ID_VENDOR		1
#define LKL_ID_PRODUCT		2
#define LKL_ID_VERSION		3

#define LKL_BUS_PCI			0x01
#define LKL_BUS_ISAPNP		0x02
#define LKL_BUS_USB			0x03
#define LKL_BUS_HIL			0x04
#define LKL_BUS_BLUETOOTH		0x05
#define LKL_BUS_VIRTUAL		0x06

#define LKL_BUS_ISA			0x10
#define LKL_BUS_I8042		0x11
#define LKL_BUS_XTKBD		0x12
#define LKL_BUS_RS232		0x13
#define LKL_BUS_GAMEPORT		0x14
#define LKL_BUS_PARPORT		0x15
#define LKL_BUS_AMIGA		0x16
#define LKL_BUS_ADB			0x17
#define LKL_BUS_I2C			0x18
#define LKL_BUS_HOST		0x19
#define LKL_BUS_GSC			0x1A
#define LKL_BUS_ATARI		0x1B
#define LKL_BUS_SPI			0x1C
#define LKL_BUS_RMI			0x1D
#define LKL_BUS_CEC			0x1E
#define LKL_BUS_INTEL_ISHTP		0x1F
#define LKL_BUS_AMD_SFH		0x20

/*
 * MT_TOOL types
 */
#define LKL_MT_TOOL_FINGER		0x00
#define LKL_MT_TOOL_PEN		0x01
#define LKL_MT_TOOL_PALM		0x02
#define LKL_MT_TOOL_DIAL		0x0a
#define LKL_MT_TOOL_MAX		0x0f

/*
 * Values describing the status of a force-feedback effect
 */
#define LKL_FF_STATUS_STOPPED	0x00
#define LKL_FF_STATUS_PLAYING	0x01
#define LKL_FF_STATUS_MAX		0x01

/*
 * Structures used in ioctls to upload effects to a device
 * They are pieces of a bigger structure (called ff_effect)
 */

/*
 * All duration values are expressed in ms. Values above 32767 ms (0x7fff)
 * should not be used and have unspecified results.
 */

/**
 * struct lkl_ff_replay - defines scheduling of the force-feedback effect
 * @length: duration of the effect
 * @delay: delay before effect should start playing
 */
struct lkl_ff_replay {
	__lkl__u16 length;
	__lkl__u16 delay;
};

/**
 * struct lkl_ff_trigger - defines what triggers the force-feedback effect
 * @button: number of the button triggering the effect
 * @interval: controls how soon the effect can be re-triggered
 */
struct lkl_ff_trigger {
	__lkl__u16 button;
	__lkl__u16 interval;
};

/**
 * struct lkl_ff_envelope - generic force-feedback effect envelope
 * @attack_length: duration of the attack (ms)
 * @attack_level: level at the beginning of the attack
 * @fade_length: duration of fade (ms)
 * @fade_level: level at the end of fade
 *
 * The @attack_level and @fade_level are absolute values; when applying
 * envelope force-feedback core will convert to positive/negative
 * value based on polarity of the default level of the effect.
 * Valid range for the attack and fade levels is 0x0000 - 0x7fff
 */
struct lkl_ff_envelope {
	__lkl__u16 attack_length;
	__lkl__u16 attack_level;
	__lkl__u16 fade_length;
	__lkl__u16 fade_level;
};

/**
 * struct lkl_ff_constant_effect - defines parameters of a constant force-feedback effect
 * @level: strength of the effect; may be negative
 * @envelope: envelope data
 */
struct lkl_ff_constant_effect {
	__lkl__s16 level;
	struct lkl_ff_envelope envelope;
};

/**
 * struct lkl_ff_ramp_effect - defines parameters of a ramp force-feedback effect
 * @start_level: beginning strength of the effect; may be negative
 * @end_level: final strength of the effect; may be negative
 * @envelope: envelope data
 */
struct lkl_ff_ramp_effect {
	__lkl__s16 start_level;
	__lkl__s16 end_level;
	struct lkl_ff_envelope envelope;
};

/**
 * struct lkl_ff_condition_effect - defines a spring or friction force-feedback effect
 * @right_saturation: maximum level when joystick moved all way to the right
 * @left_saturation: same for the left side
 * @right_coeff: controls how fast the force grows when the joystick moves
 *	to the right
 * @left_coeff: same for the left side
 * @deadband: size of the dead zone, where no force is produced
 * @center: position of the dead zone
 */
struct lkl_ff_condition_effect {
	__lkl__u16 right_saturation;
	__lkl__u16 left_saturation;

	__lkl__s16 right_coeff;
	__lkl__s16 left_coeff;

	__lkl__u16 deadband;
	__lkl__s16 center;
};

/**
 * struct lkl_ff_periodic_effect - defines parameters of a periodic force-feedback effect
 * @waveform: kind of the effect (wave)
 * @period: period of the wave (ms)
 * @magnitude: peak value
 * @offset: mean value of the wave (roughly)
 * @phase: 'horizontal' shift
 * @envelope: envelope data
 * @custom_len: number of samples (LKL_FF_CUSTOM only)
 * @custom_data: buffer of samples (LKL_FF_CUSTOM only)
 *
 * Known waveforms - LKL_FF_SQUARE, LKL_FF_TRIANGLE, LKL_FF_SINE, LKL_FF_SAW_UP,
 * LKL_FF_SAW_DOWN, LKL_FF_CUSTOM. The exact syntax LKL_FF_CUSTOM is undefined
 * for the time being as no driver supports it yet.
 *
 * Note: the data pointed by custom_data is copied by the driver.
 * You can therefore dispose of the memory after the upload/update.
 */
struct lkl_ff_periodic_effect {
	__lkl__u16 waveform;
	__lkl__u16 period;
	__lkl__s16 magnitude;
	__lkl__s16 offset;
	__lkl__u16 phase;

	struct lkl_ff_envelope envelope;

	__lkl__u32 custom_len;
	__lkl__s16 *custom_data;
};

/**
 * struct lkl_ff_rumble_effect - defines parameters of a periodic force-feedback effect
 * @strong_magnitude: magnitude of the heavy motor
 * @weak_magnitude: magnitude of the light one
 *
 * Some rumble pads have two motors of different weight. Strong_magnitude
 * represents the magnitude of the vibration generated by the heavy one.
 */
struct lkl_ff_rumble_effect {
	__lkl__u16 strong_magnitude;
	__lkl__u16 weak_magnitude;
};

/**
 * struct lkl_ff_effect - defines force feedback effect
 * @type: type of the effect (LKL_FF_CONSTANT, LKL_FF_PERIODIC, LKL_FF_RAMP, LKL_FF_SPRING,
 *	LKL_FF_FRICTION, LKL_FF_DAMPER, LKL_FF_RUMBLE, LKL_FF_INERTIA, or LKL_FF_CUSTOM)
 * @id: an unique id assigned to an effect
 * @direction: direction of the effect
 * @trigger: trigger conditions (struct lkl_ff_trigger)
 * @replay: scheduling of the effect (struct lkl_ff_replay)
 * @u: effect-specific structure (one of ff_constant_effect, ff_ramp_effect,
 *	ff_periodic_effect, ff_condition_effect, ff_rumble_effect) further
 *	defining effect parameters
 *
 * This structure is sent through ioctl from the application to the driver.
 * To create a new effect application should set its @id to -1; the kernel
 * will return assigned @id which can later be used to update or delete
 * this effect.
 *
 * Direction of the effect is encoded as follows:
 *	0 deg -> 0x0000 (down)
 *	90 deg -> 0x4000 (left)
 *	180 deg -> 0x8000 (up)
 *	270 deg -> 0xC000 (right)
 */
struct lkl_ff_effect {
	__lkl__u16 type;
	__lkl__s16 id;
	__lkl__u16 direction;
	struct lkl_ff_trigger trigger;
	struct lkl_ff_replay replay;

	union {
		struct lkl_ff_constant_effect constant;
		struct lkl_ff_ramp_effect ramp;
		struct lkl_ff_periodic_effect periodic;
		struct lkl_ff_condition_effect condition[2]; /* One for each axis */
		struct lkl_ff_rumble_effect rumble;
	} u;
};

/*
 * Force feedback effect types
 */

#define LKL_FF_RUMBLE	0x50
#define LKL_FF_PERIODIC	0x51
#define LKL_FF_CONSTANT	0x52
#define LKL_FF_SPRING	0x53
#define LKL_FF_FRICTION	0x54
#define LKL_FF_DAMPER	0x55
#define LKL_FF_INERTIA	0x56
#define LKL_FF_RAMP		0x57

#define LKL_FF_EFFECT_MIN	LKL_FF_RUMBLE
#define LKL_FF_EFFECT_MAX	LKL_FF_RAMP

/*
 * Force feedback periodic effect types
 */

#define LKL_FF_SQUARE	0x58
#define LKL_FF_TRIANGLE	0x59
#define LKL_FF_SINE		0x5a
#define LKL_FF_SAW_UP	0x5b
#define LKL_FF_SAW_DOWN	0x5c
#define LKL_FF_CUSTOM	0x5d

#define LKL_FF_WAVEFORM_MIN	LKL_FF_SQUARE
#define LKL_FF_WAVEFORM_MAX	LKL_FF_CUSTOM

/*
 * Set ff device properties
 */

#define LKL_FF_GAIN		0x60
#define LKL_FF_AUTOCENTER	0x61

/*
 * ff->playback(effect_id = LKL_FF_GAIN) is the first effect_id to
 * cause a collision with another ff method, in this case ff->set_gain().
 * Therefore the greatest safe value for effect_id is LKL_FF_GAIN - 1,
 * and thus the total number of effects should never exceed LKL_FF_GAIN.
 */
#define LKL_FF_MAX_EFFECTS	LKL_FF_GAIN

#define LKL_FF_MAX		0x7f
#define LKL_FF_CNT		(LKL_FF_MAX+1)

#endif /* _LKL_INPUT_H */
