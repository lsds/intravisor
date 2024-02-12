MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)


CFLAGS=-fPIC -fPIE -pie -g -O2  -nostdinc -DCVM_MAX_SIZE=$(CONFIG_CVM_MAX_SIZE) \
	-I cheri-libc/include \
	$(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_PURE) -B$(CROSS_COMPILE) $(ARCH_PURE) -Iarch/$(TARGET_ARCH)/include -I.\
	-Iunikraft/vfscore/include -Iunikraft/devfs/include -I unikraft/ukswrand/include \
	-I musl-host/src/internal -I musl-host/src/include -I musl-host/include  -I musl-host/arch/${TARGET_ARCH}/ -I musl-host/src/math \

ifeq ($(CONFIG_KERNEL_CONFIGURED_DDC_RELATIVE), y)
CFLAGS +=-DKERNEL_CONFIGURED_DDC_RELATIVE
endif

#CFLAGS_ALL += -D_XOPEN_SOURCE=700 -I$(srcdir)/arch/$(ARCH) -I$(srcdir)/arch/generic -Iobj/src/internal -I$(srcdir)/src/include -I$(srcdir)/src/internal -Iobj/include -I$(srcdir)/include
#	-Wno-unused-command-line-argument -Werror=implicit-function-declaration -Werror=format -Werror=incompatible-pointer-types -Werror=cheri-capability-misuse -Werror=cheri-bitwise-operations -Werror=cheri-prototypes -Werror=pass-failed -Werror=undefined-internal -Wno-error=cheri-capability-misuse \

ifneq ($(MODE),sim)
endif

DEPS = 
OBJDIR = obj
SRC = main.c tramps.c hostcalls.c nolibc_printf2.c nolibc_printf.c nolibc_file.c  nolibc_strings.c nolibc_time.c nolibc_unsorted.c dlmalloc_nonreuse.c cpio.c nolibc_network.c nolibc_pthread.c
SRC += arch/${TARGET_ARCH}/nolibc_math.c 
SRC += $(wildcard musl-host/src/ctype/*.c)
SRC += $(wildcard musl-host/src/locale/*.c)
SRC += $(wildcard musl-host/src/termios/*.c)
SRC += $(wildcard musl-host/src/complex/*.c)
SRC += $(wildcard musl-host/src/fenv/*.c)
SRC += $(wildcard musl-host/src/math/*.c)
SRC += $(wildcard musl-host/src/string/*.c)
SRC += $(wildcard musl-host/src/stdlib/*.c)
SRC += $(wildcard musl-host/src/internal/*.c)
SRC += $(wildcard musl-host/src/stdio/*.c)
SRC += $(wildcard musl-host/src/multibyte/*.c)
SRC += $(wildcard musl-host/src/errno/*.c)
SRC += $(wildcard musl-host/src/prng/*.c)
SRC += $(wildcard musl-host/src/time/*.c)
SRC += $(wildcard musl-host/src/misc/*.c)
SRC += $(wildcard musl-host/src/regex/*.c)
SRC += $(wildcard musl-host/src/conf/*.c)
SRC += $(wildcard musl-host/src/network/*.c)
SRC += $(wildcard musl-host/src/unistd/*.c)
SRC += unikraft/vfscore/main.c unikraft/vfscore/fd.c unikraft/vfscore/rootfs.c unikraft/vfscore/task.c unikraft/vfscore/vnode.c  unikraft/vfscore/dentry.c unikraft/vfscore/file.c unikraft/vfscore/subr_uio.c unikraft/vfscore/fops.c unikraft/vfscore/lookup.c unikraft/vfscore/mount.c unikraft/vfscore/syscalls.c
SRC += unikraft/ramfs/ramfs_vnops.c unikraft/ramfs/ramfs_vfsops.c 
SRC += unikraft/devfs/devfs_vnops.c unikraft/devfs/device.c unikraft/devfs/null.c
SRC += unikraft/ukswrand/dev.c unikraft/ukswrand/swrand.c unikraft/ukswrand/mwc.c

OBJ := $(SRC:%.c=$(OBJDIR)/%.o)


default: libmusl-uni.a


$(OBJDIR)/%.o: %.c $(DEPS) $(PASS1) $(PASS2) 
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS)

LD_FLAGS = 
#-Wl,-error-limit=0 
ifdef CONFIG_SIM
LD_FLAGS += -lgcc
else
LD_FLAGS += arch/${TARGET_ARCH}/libcompiler_rt.a
endif


$(OBJDIR)/tramps.o: arch/$(TARGET_ARCH)/tramps.S
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -c -o $(OBJDIR)/tramps.o arch/$(TARGET_ARCH)/tramps.S

libmusl-uni.a: $(OBJ)
#	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ) $(LD_FLAGS)
	$(AR) rcs $@ $(OBJ) arch/${TARGET_ARCH}/libcompiler_rt/*

install:
	sudo mkdir -p ${INSTALL_PATH}/musl-host/
	sudo cp -r ./musl-host/include ${INSTALL_PATH}/musl-host/
	sudo cp ./libmusl-uni.a ${INSTALL_PATH}/

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR) ./*.a

