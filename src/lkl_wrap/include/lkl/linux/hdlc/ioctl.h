/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__HDLC_IOCTL_H__
#define __LKL__HDLC_IOCTL_H__


#define LKL_GENERIC_HDLC_VERSION 4	/* For synchronization with sethdlc utility */

#define LKL_CLOCK_DEFAULT   0	/* Default setting */
#define LKL_CLOCK_EXT	1	/* External TX and RX clock - DTE */
#define LKL_CLOCK_INT	2	/* Internal TX and RX clock - DCE */
#define LKL_CLOCK_TXINT	3	/* Internal TX and external RX clock */
#define LKL_CLOCK_TXFROMRX	4	/* TX clock derived from external RX clock */


#define LKL_ENCODING_DEFAULT	0 /* Default setting */
#define LKL_ENCODING_NRZ		1
#define LKL_ENCODING_NRZI		2
#define LKL_ENCODING_FM_MARK	3
#define LKL_ENCODING_FM_SPACE	4
#define LKL_ENCODING_MANCHESTER	5


#define LKL_PARITY_DEFAULT		0 /* Default setting */
#define LKL_PARITY_NONE		1 /* No parity */
#define LKL_PARITY_CRC16_PR0	2 /* CRC16, initial value 0x0000 */
#define LKL_PARITY_CRC16_PR1	3 /* CRC16, initial value 0xFFFF */
#define LKL_PARITY_CRC16_PR0_CCITT	4 /* CRC16, initial 0x0000, ITU-T version */
#define LKL_PARITY_CRC16_PR1_CCITT	5 /* CRC16, initial 0xFFFF, ITU-T version */
#define LKL_PARITY_CRC32_PR0_CCITT	6 /* CRC32, initial value 0x00000000 */
#define LKL_PARITY_CRC32_PR1_CCITT	7 /* CRC32, initial value 0xFFFFFFFF */

#define LKL_LMI_DEFAULT		0 /* Default setting */
#define LKL_LMI_NONE		1 /* No LMI, all PVCs are static */
#define LKL_LMI_ANSI		2 /* ANSI Annex D */
#define LKL_LMI_CCITT		3 /* ITU-T Annex A */
#define LKL_LMI_CISCO		4 /* The "original" LMI, aka Gang of Four */

#ifndef __ASSEMBLY__

typedef struct {
	unsigned int clock_rate; /* bits per second */
	unsigned int clock_type; /* internal, external, TX-internal etc. */
	unsigned short loopback;
} lkl_sync_serial_settings;          /* V.35, V.24, X.21 */

typedef struct {
	unsigned int clock_rate; /* bits per second */
	unsigned int clock_type; /* internal, external, TX-internal etc. */
	unsigned short loopback;
	unsigned int slot_map;
} lkl_te1_settings;                  /* T1, E1 */

typedef struct {
	unsigned short encoding;
	unsigned short parity;
} lkl_raw_hdlc_proto;

typedef struct {
	unsigned int t391;
	unsigned int t392;
	unsigned int n391;
	unsigned int n392;
	unsigned int n393;
	unsigned short lmi;
	unsigned short dce; /* 1 for DCE (network side) operation */
} lkl_fr_proto;

typedef struct {
	unsigned int dlci;
} lkl_fr_proto_pvc;          /* for creating/deleting FR PVCs */

typedef struct {
	unsigned int dlci;
	char master[LKL_IFNAMSIZ];	/* Name of master FRAD device */
}lkl_fr_proto_pvc_info;		/* for returning PVC information only */

typedef struct {
    unsigned int interval;
    unsigned int timeout;
} lkl_cisco_proto;

/* PPP doesn't need any info now - supply length = 0 to ioctl */

#endif /* __ASSEMBLY__ */
#endif /* __LKL__HDLC_IOCTL_H__ */
