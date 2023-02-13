MAKEFILE := $(shell git rev-parse --show-toplevel)/config_new.mak
include $(MAKEFILE)

#native Intravisor, native cVMs

CHERI_SDK=/usr/lib/llvm-14

TARGET_ARCH=arm_sim
TARGET_FLAGS_LINUX=-target aarch64-unknown-linux
TARGET_FLAGS=$(TARGET_FLAGS_LINUX)
DEBUG_FLAGS=-g
#OPT_FLAGS=-O2
SYSROOT_FLAGS_HYBRID=-DSIM
SYSROOT_FLAGS_PURE=-DSIM
LINKER_FLAGS=
DIAG_FLAGS=-Wall -Wcheri
ARCH_PURE=-DTARGET_ARCH="$(TARGET_ARCH)" -D$(TARGET_ARCH)
#-Xclang -msoft-float -Xclang -no-implicit-float
ARCH_HYBRID=
CONFIG_SIM=1