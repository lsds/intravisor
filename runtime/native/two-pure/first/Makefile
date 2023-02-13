#include ../../../../../config_arm_sim.mak
MAKEFILE := $(shell git rev-parse --show-toplevel)/config_arm.mak
include $(MAKEFILE)


CFLAGS=-fPIC -fPIE -pie -g -O2  -nostdinc -DCVM_MAX_SIZE=$(CONFIG_CVM_MAX_SIZE)\
	$(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_PURE) -B$(CROSS_COMPILE) $(ARCH_PURE) -Iarch/$(TARGET_ARCH)/include\

ifneq ($(MODE),sim)
endif

DEPS = 
OBJDIR = obj
SRC = main.c tramps.c hostcalls.c 

OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

default: libfirst.so



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

libfirst.so: $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ) $(LD_FLAGS)

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR)

