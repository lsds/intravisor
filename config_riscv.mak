#hybrid Intravisor, pure cVMs
MAKEFILE := $(shell git rev-parse --show-toplevel)/config_new.mak
include $(MAKEFILE)


CHERI_SDK=${HOME}/cheri/output/sdk
#CHERI_SDK=/full/path/to/cheri/output/sdk

TARGET_ARCH=riscv
TARGET_FLAGS_BSD=-target riscv64-unknown-freebsd
TARGET_FLAGS_LINUX=-target riscv64-unknown-linux
TARGET_FLAGS=$(TARGET_FLAGS_BSD)
DEBUG_FLAGS=-g
#OPT_FLAGS=-O2
SYSROOT_FLAGS_HYBRID=--sysroot='$(CHERI_SDK)/sysroot-riscv64-hybrid'
SYSROOT_FLAGS_PURE=--sysroot='$(CHERI_SDK)/sysroot-riscv64-purecap'
LINKER_FLAGS=-fuse-ld=lld -mno-relax
DIAG_FLAGS=-Wall -Wcheri
ARCH_PURE=-march=rv64imafdcxcheri -mabi=l64pc128d
ARCH_HYBRID=-march=rv64gcxcheri -mabi=lp64d
CONFIG_HW=1

