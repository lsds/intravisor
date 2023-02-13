MAKEFILE := $(shell git rev-parse --show-toplevel)/config_new.mak
include $(MAKEFILE)

#hybrid Intravisor, pure cVMs

CHERI_SDK=${HOME}/cheri/output/morello-sdk
#CHERI_SDK=/full/path/to/cheri/output/sdk

TARGET_ARCH=arm
TARGET_FLAGS_BSD=-target aarch64-unknown-freebsd
TARGET_FLAGS_LINUX=-target aarch64-unknown-linux
TARGET_FLAGS=$(TARGET_FLAGS_BSD)
DEBUG_FLAGS=-g
#OPT_FLAGS=-O2
SYSROOT_FLAGS_HYBRID=--sysroot='$(CHERI_SDK)/sysroot-morello-hybrid'
SYSROOT_FLAGS_PURE=--sysroot='$(CHERI_SDK)/sysroot-morello-purecap'
LINKER_FLAGS=-fuse-ld=lld -mno-relax
DIAG_FLAGS=-Wall -Wcheri
ARCH_PURE=-march=morello+c64 -mabi=purecap -Xclang -morello-vararg=new 
#-Xclang -msoft-float -Xclang -no-implicit-float
ARCH_HYBRID=-march=morello -mabi=aapcs -Xclang -morello-vararg=new
#CONFIG_LKL=1 broken
CONFIG_HW=1