#include ../../../../../config_arm_sim.mak
MAKEFILE := $(shell git rev-parse --show-toplevel)/config_arm.mak
include $(MAKEFILE)


CFLAGS=-fPIC -fPIE -pie -g -O2  -nostdinc -DCVM_MAX_SIZE=$(CONFIG_CVM_MAX_SIZE)\
	-I cheri-libc/include \
	$(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_PURE) -B$(CROSS_COMPILE) $(ARCH_PURE) -Iarch/$(TARGET_ARCH)/include\
	-Iunikraft/vfscore/include -Iunikraft/devfs/include -I unikraft/ukswrand/include \
	-I musl-host/src/internal -I musl-host/src/include -I musl-host/include  -I musl-host/arch/morello -I musl-host/src/math \
	-I ffmpeg -DHAVE_AV_CONFIG_H

#CFLAGS_ALL += -D_XOPEN_SOURCE=700 -I$(srcdir)/arch/$(ARCH) -I$(srcdir)/arch/generic -Iobj/src/internal -I$(srcdir)/src/include -I$(srcdir)/src/internal -Iobj/include -I$(srcdir)/include
#	-Wno-unused-command-line-argument -Werror=implicit-function-declaration -Werror=format -Werror=incompatible-pointer-types -Werror=cheri-capability-misuse -Werror=cheri-bitwise-operations -Werror=cheri-prototypes -Werror=pass-failed -Werror=undefined-internal -Wno-error=cheri-capability-misuse \

ifneq ($(MODE),sim)
endif

DEPS = 
OBJDIR = obj
SRC = main.c tramps.c hostcalls.c nolibc_printf.c

OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

PASS_DIR1 = build_break
PASS1 = $(PASS_DIR1)/libBRKGEPPass.so

PASS_DIR2 = build_loc
PASS2 = $(PASS_DIR2)/libLocPass.so


default: libu_ffmpeg.so

$(OBJDIR)/%.o: %.c $(DEPS)
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS)

LD_FLAGS = 
ifdef CONFIG_SIM
LD_FLAGS += -lgcc
else
LD_FLAGS += -Wl,-error-limit=0
endif


$(OBJDIR)/tramps.o: arch/$(TARGET_ARCH)/tramps.S
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -c -o $(OBJDIR)/tramps.o arch/$(TARGET_ARCH)/tramps.S

libu_ffmpeg.so: $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ) $(LD_FLAGS)

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR)

