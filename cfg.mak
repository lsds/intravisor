MAKEFILE := $(shell git rev-parse --show-toplevel)/.config
include $(MAKEFILE)

### common, clang-based

CHERI_SDK	?= $(CONFIG_CHERI_SDK:"%"=%)
CC_MON = $(CHERI_SDK)/bin/clang
AS_MON = $(CHERI_SDK)/bin/clang

CC=$(CHERI_SDK)/bin/clang
CC_CPP=$(CHERI_SDK)/bin/clang++
OPT=$(CHERI_SDK)/bin/opt

##########################

DEBUG_FLAGS=-g
LINKER_FLAGS=-fuse-ld=lld -mno-relax
DIAG_FLAGS=-Wall
ifdef CONFIG_MODE_PURE
DIAG_FLAGS +=-Wcheri
endif


#############################3 RISCV ############

ifdef CONFIG_ARCH_RV
LKL_TARGET=riscv64
#don't use objcopy from this sdk, it doesn't set  ELF OS/ABI field for binary->ELF conversion
#CROSS_COMPILE="$(CHERI_SDK)/bin/"
CROSS_COMPILE=riscv64-linux-gnu-

TARGET_FLAGS_BSD=-target riscv64-unknown-freebsd
TARGET_FLAGS_LINUX=-target riscv64-unknown-linux
SYSROOT_FLAGS_HYBRID=--sysroot='$(CHERI_SDK)/sysroot-riscv64-hybrid'
SYSROOT_FLAGS_PURE=--sysroot='$(CHERI_SDK)/sysroot-riscv64-purecap'
ARCH_PURE=-march=rv64imafdcxcheri -mabi=l64pc128d
ARCH_HYBRID=-march=rv64gcxcheri -mabi=lp64d

ifdef CONFIG_MODE_PURE
TARGET_ARCH=riscv
endif
ifdef CONFIG_MODE_HYB
TARGET_ARCH=riscv_hyb
endif
ifdef CONFIG_MODE_SIM
TARGET_ARCH=riscv_sim
endif
endif

############################### ARM  ##############

ifdef CONFIG_ARCH_ARM
LKL_TARGET=aarch64
CROSS_COMPILE=aarch64-linux-gnu-
TARGET_FLAGS_BSD=-target aarch64-unknown-freebsd
TARGET_FLAGS_LINUX=-target aarch64-unknown-linux
SYSROOT_FLAGS_HYBRID=--sysroot='$(CHERI_SDK)/sysroot-morello-hybrid'
SYSROOT_FLAGS_PURE=--sysroot='$(CHERI_SDK)/sysroot-morello-purecap'
ARCH_PURE=-march=morello+c64 -mabi=purecap -Xclang -morello-vararg=new 
#-Xclang -msoft-float -Xclang -no-implicit-float
ARCH_HYBRID=-march=morello -mabi=aapcs -Xclang -morello-vararg=new


ifdef CONFIG_MODE_PURE
TARGET_ARCH=arm
endif
ifdef CONFIG_MODE_HYB
TARGET_ARCH=arm_hyb
endif
ifdef CONFIG_MODE_SIM
TARGET_ARCH=arm_sim
endif

endif #CONFIG_ARCH_ARM


#############################3 X86 ############

ifdef CONFIG_ARCH_X86
LKL_TARGET=x86
CC_MON = clang
AS_MON = clang

CC=clang
CC_CPP=clang
OPT=
LINKER_FLAGS=
DIAG_FLAGS =

CROSS_COMPILE=/usr/bin/

TARGET_FLAGS_BSD=
TARGET_FLAGS_LINUX=
SYSROOT_FLAGS_HYBRID=
SYSROOT_FLAGS_PURE=
ARCH_PURE=
ARCH_HYBRID=

ifdef CONFIG_MODE_SIM
TARGET_ARCH=x86_sim
endif

endif #CONFIG_ARCH_X86
########################## OS ################

ifdef CONFIG_OS_CHERIBSD
TARGET_FLAGS=$(TARGET_FLAGS_BSD)
endif
ifdef CONFIG_OS_LINUX
TARGET_FLAGS=$(TARGET_FLAGS_LINUX)
endif


########################### MONITOR
CC_MON_FLAGS = $(DEBUG_FLAGS) $(TARGET_FLAGS) $(SYSROOT_FLAGS_HYBRID) $(ARCH_HYBRID) $(DIAG_FLAGS) $(LINKER_FLAGS)
AS_MON_FLAGS = $(DEBUG_FLAGS) $(TARGET_FLAGS) $(SYSROOT_FLAGS_HYBRID) $(ARCH_HYBRID) $(DIAG_FLAGS) $(LINKER_FLAGS)

CC_LKL_FLAGS = $(DEBUG_FLAGS) $(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_HYBRID) $(ARCH_HYBRID) $(DIAG_FLAGS) $(LINKER_FLAGS)
AS_LKL_FLAGS = $(DEBUG_FLAGS) $(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_HYBRID) $(ARCH_HYBRID) $(DIAG_FLAGS) $(LINKER_FLAGS)

CC_CHERI_PURE = $(CHERI_SDK)/bin/clang
CC_CHERI_PURE_FLAGS = $(TARGET_FLAGS_LINUX) -fPIE -mno-relax $(ARCH_PURE)



#musl-lkl

#CC_SYSROOT=$(SYSROOT_FLAGS_PURE)
#CC_FLAGS = $(TARGET_FLAGS_LINUX) -fPIE -mno-relax $(SYSROOT_FLAGS_PURE) $(ARCH_PURE)

#CC_CHERI_HYB = $(CHERI_SDK)/bin/clang
#CC_CHERI_HYB_FLAGS = $(TARGET_FLAGS_LINUX) -fPIE -mno-relax $(SYSROOT_FLAGS_PURE) $(ARCH_PURE)


