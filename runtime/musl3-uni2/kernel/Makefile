MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)


CFLAGS=-fPIC -fPIE -pie -g -O2  -nostdinc -DCVM_MAX_SIZE=$(CONFIG_CVM_MAX_SIZE) \
	-I cheri-libc/include \
	$(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_PURE) -B$(CROSS_COMPILE) $(ARCH_PURE) -Iarch/$(TARGET_ARCH)/include -I.\
	-I unikraft/lib/nolibc/include -I unikraft/include/ -I unikraft/arch/arm/arm64/include/ -I unikraft/gen/include -I unikraft/lib/nolibc/arch/arm64/ \
	-I unikraft/lib/ukdebug/include/  -I unikraft/lib/uklibid/include/ \
	-I unikraft/lib/uklibparam/include/ -I unikraft/lib/ukatomic/include/ -I unikraft/lib/vfscore/include/ -I unikraft/lib/uklock/include/ -I unikraft/lib/ukargparse/include/\
	-I unikraft/lib/uksched/include -I unikraft/lib/nolibc/musl-imported/include/ -I unikraft/lib/ukbitops/include/ -I unikraft/lib/ukbitops/arch/arm64/include/ -I unikraft/lib/posix-fdtab/include/ \
	-I unikraft/lib/nolibc/musl-imported/arch/generic/ -I unikraft/lib/syscall_shim/include/ -I unikraft/lib/syscall_shim/arch/arm64/include/ -I unikraft/lib/ukfile/include/ -I unikraft/lib/posix-fdtab/include \
	-I unikraft/lib/posix-fdio/include -I unikraft/lib/devfs/include -I unikraft/lib/ramfs/include -I unikraft/lib/ukswrand/include -I unikraft/lib/posix-pipe/include -I unikraft/lib/posix-sysinfo/include/ \
	-I unikraft/lib/posix-socket/include/ -I unikraft/lib/posix-futex/include

ifeq ($(CONFIG_KERNEL_CONFIGURED_DDC_RELATIVE), y)
CFLAGS +=-DKERNEL_CONFIGURED_DDC_RELATIVE
endif

CFLAGS += -DINTRAVISOR 
#-DUK_LIBC_SYSCALLS=0

ifneq ($(MODE),sim)
endif

DEPS = 
OBJDIR = obj
SRC = main.c tramps.c hostcalls.c unikraft_init.c unikraft_stub.c
#used cheri-libc/include
SRC += dlmalloc_nonreuse.c 
SRC += unikraft/plat/intravisor/console.c unikraft/plat/intravisor/shutdown.c unikraft/plat/intravisor/time.c

SRC += $(wildcard unikraft/lib/nolibc/*.c)
#SRC += $(wildcard unikraft/lib/vfscore/*.c)
SRC += unikraft/lib/vfscore/main.c unikraft/lib/vfscore/vnode.c unikraft/lib/vfscore/lookup.c unikraft/lib/vfscore/dentry.c unikraft/lib/vfscore/mount.c unikraft/lib/vfscore/task.c unikraft/lib/vfscore/stdio.c unikraft/lib/vfscore/file.c unikraft/lib/vfscore/fd.c
SRC += unikraft/lib/vfscore/syscalls.c unikraft/lib/vfscore/fops.c unikraft/lib/vfscore/subr_uio.c unikraft/lib/vfscore/automount.c

SRC += $(wildcard unikraft/lib/posix-time/*.c)
SRC += $(wildcard unikraft/lib/uklock/*.c)
SRC += $(wildcard unikraft/lib/posix-fdtab/*.c)
SRC += $(wildcard unikraft/lib/posix-fdio/*.c)
SRC += $(wildcard unikraft/lib/devfs/*.c)
SRC += $(wildcard unikraft/lib/ramfs/*.c)
SRC += $(wildcard unikraft/lib/posix-pipe/*.c)
SRC += $(wildcard unikraft/lib/ukfile/*.c)
SRC += $(wildcard unikraft/lib/posix-sysinfo/*.c)
SRC += $(wildcard unikraft/lib/posix-socket/*.c)
SRC += $(wildcard unikraft/lib/posix-host-inetsocket/*.c)
SRC += $(wildcard unikraft/lib/posix-futex/*.c)
SRC += unikraft/lib/ukdebug/print.c
SRC += unikraft/lib/ukswrand/dev.c unikraft/lib/ukswrand/swrand.c unikraft/lib/ukswrand/mwc.c unikraft/lib/ukswrand/getrandom.c
#SRC += arch/${TARGET_ARCH}/nolibc_math.c 

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

