/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__LINUX_BPF_COMMON_H__
#define __LKL__LINUX_BPF_COMMON_H__

/* Instruction classes */
#define LKL_BPF_CLASS(code) ((code) & 0x07)
#define		LKL_BPF_LD		0x00
#define		LKL_BPF_LDX		0x01
#define		LKL_BPF_ST		0x02
#define		LKL_BPF_STX		0x03
#define		LKL_BPF_ALU		0x04
#define		LKL_BPF_JMP		0x05
#define		LKL_BPF_RET		0x06
#define		LKL_BPF_MISC        0x07

/* ld/ldx fields */
#define LKL_BPF_SIZE(code)  ((code) & 0x18)
#define		LKL_BPF_W		0x00 /* 32-bit */
#define		LKL_BPF_H		0x08 /* 16-bit */
#define		LKL_BPF_B		0x10 /*  8-bit */
/* eBPF		LKL_BPF_DW		0x18    64-bit */
#define LKL_BPF_MODE(code)  ((code) & 0xe0)
#define		LKL_BPF_IMM		0x00
#define		LKL_BPF_ABS		0x20
#define		LKL_BPF_IND		0x40
#define		LKL_BPF_MEM		0x60
#define		LKL_BPF_LEN		0x80
#define		LKL_BPF_MSH		0xa0

/* alu/jmp fields */
#define LKL_BPF_OP(code)    ((code) & 0xf0)
#define		LKL_BPF_ADD		0x00
#define		LKL_BPF_SUB		0x10
#define		LKL_BPF_MUL		0x20
#define		LKL_BPF_DIV		0x30
#define		LKL_BPF_OR		0x40
#define		LKL_BPF_AND		0x50
#define		LKL_BPF_LSH		0x60
#define		LKL_BPF_RSH		0x70
#define		LKL_BPF_NEG		0x80
#define		LKL_BPF_MOD		0x90
#define		LKL_BPF_XOR		0xa0

#define		LKL_BPF_JA		0x00
#define		LKL_BPF_JEQ		0x10
#define		LKL_BPF_JGT		0x20
#define		LKL_BPF_JGE		0x30
#define		LKL_BPF_JSET        0x40
#define LKL_BPF_SRC(code)   ((code) & 0x08)
#define		LKL_BPF_K		0x00
#define		LKL_BPF_X		0x08

#ifndef LKL_BPF_MAXINSNS
#define LKL_BPF_MAXINSNS 4096
#endif

#endif /* __LKL__LINUX_BPF_COMMON_H__ */
