CHERI_SDK=${HOME}/cheri/output/sdk
#CHERI_SDK=/full/path/to/cheri/output/sdk

#MONITOR
CC_MON = $(CHERI_SDK)/bin/clang
CC_MON_FLAGS = -g -target riscv64-unknown-freebsd --sysroot="$(CHERI_SDK)/sysroot-riscv64-hybrid" -fuse-ld=lld -mno-relax -march=rv64gcxcheri -mabi=lp64d

AS_MON = $(CHERI_SDK)/bin/clang
AS_MON_FLAGS = -g -target riscv64-unknown-freebsd --sysroot="$(CHERI_SDK)/sysroot-riscv64-hybrid" -fuse-ld=lld -mno-relax -march=rv64gcxcheri -mabi=lp64d

#musl-lkl

#don't use objcopy from this sdk, it doesn't set  ELF OS/ABI field for binary->ELF conversion
CROSS_COMPILE="$(CHERI_SDK)/bin/"
#CROSS_COMPILE=riscv64-linux-gnu-
CC=$(CHERI_SDK)/bin/clang
CC_CPP=$(CHERI_SDK)/bin/clang++
OPT=$(CHERI_SDK)/bin/opt
CC_SYSROOT=--sysroot=\"$(CHERI_SDK)/sysroot-riscv64-purecap\"
CC_FLAGS = -target riscv64-unknown-linux -fPIE -mno-relax --sysroot="$(CHERI_SDK)/sysroot-riscv64-purecap" -march=rv64imafdcxcheri -mabi=l64pc128d

CC_CHERI = $(CHERI_SDK)/bin/clang
CC_CHERI_FLAGS = -target riscv64-unknown-linux -fPIE -mno-relax --sysroot="$(CHERI_SDK)/sysroot-riscv64-purecap" -march=rv64imafdcxcheri -mabi=l64pc128d

CC_CHERI_PURE = $(CHERI_SDK)/bin/clang
CC_CHERI_PURE_FLAGS = -target riscv64-unknown-linux -fPIE -mno-relax --sysroot="$(CHERI_SDK)/sysroot-riscv64-purecap" -march=rv64imafdcxcheri -mabi=l64pc128d

