MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)

LIBOS_PATH := ../..



CFLAGS=-fPIC -fPIE -pie -g -O2  -nostdinc \
	$(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_PURE) -B$(CROSS_COMPILE) $(ARCH_PURE) \
	 -I $(LIBOS_PATH)/unikraft/include  \
	-I $(LIBOS_PATH)/unikraft/lib/nolibc/include -I $(LIBOS_PATH)/unikraft/include/ -I $(LIBOS_PATH)/unikraft/arch/arm/arm64/include/ -I $(LIBOS_PATH)/unikraft/gen/include -I $(LIBOS_PATH)/unikraft/lib/nolibc/arch/arm64/ \
	-I $(LIBOS_PATH)/unikraft/lib/ukdebug/include/  -I $(LIBOS_PATH)/unikraft/lib/uklibid/include/ \
	-I $(LIBOS_PATH)/unikraft/lib/uklibparam/include/ -I $(LIBOS_PATH)/unikraft/lib/ukatomic/include/ -I $(LIBOS_PATH)/unikraft/lib/vfscore/include/ -I $(LIBOS_PATH)/unikraft/lib/uklock/include/ -I $(LIBOS_PATH)/unikraft/lib/ukargparse/include/\
	-I $(LIBOS_PATH)/unikraft/lib/uksched/include -I $(LIBOS_PATH)/unikraft/lib/nolibc/musl-imported/include/ -I $(LIBOS_PATH)/unikraft/lib/ukbitops/include/ -I $(LIBOS_PATH)/unikraft/lib/ukbitops/arch/arm64/include/ -I $(LIBOS_PATH)/unikraft/lib/posix-fdtab/include/ \
	-I $(LIBOS_PATH)/unikraft/lib/nolibc/musl-imported/arch/generic/ -I $(LIBOS_PATH)/unikraft/lib/syscall_shim/include/ -I $(LIBOS_PATH)/unikraft/lib/syscall_shim/arch/arm64/include/ -I $(LIBOS_PATH)/unikraft/lib/ukfile/include/ \

CFLAGS += -DINTRAVISOR


DEPS = 
OBJDIR = obj
SRC = main.c cpio.c

OBJ := $(SRC:%.c=$(OBJDIR)/%.o)


default: libos.so


$(OBJDIR)/%.o: %.c $(DEPS) $(PASS1) $(PASS2) 
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS)


libos.so: $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ) $(LD_FLAGS) $(LIBOS_PATH)/libmusl-uni.a

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR)

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.so ${INSTALL_PATH}
