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

PASS_DIR1 = build_break
PASS1 = $(PASS_DIR1)/libBRKGEPPass.so

PASS_DIR2 = build_loc
PASS2 = $(PASS_DIR2)/libLocPass.so


default: libshared.sco

$(PASS1):
	mkdir -p $(PASS_DIR1)
	CC=$(CHERI_SDK)/bin/clang CXX=$(CHERI_SDK)/bin/clang cmake -HBRKGEPPass -B$(PASS_DIR1) -DLLVM_CONFIG=$(CHERI_SDK)/bin/llvm-config -DCHERI_SDK=$(CHERI_SDK)
	make -C $(PASS_DIR1)

$(PASS2):
	mkdir -p $(PASS_DIR2)
	CC=$(CHERI_SDK)/bin/clang CXX=$(CHERI_SDK)/bin/clang cmake -HLocPass -B$(PASS_DIR2) -DLLVM_CONFIG=$(CHERI_SDK)/bin/llvm-config -DCHERI_SDK=$(CHERI_SDK)
	make -C $(PASS_DIR2)


$(OBJDIR)/%.o: %.c $(DEPS) $(PASS1) $(PASS2) 
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
ifdef CONFIG_SIM
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS)
else
	$(OPT) -S -mem2reg -instnamer $(basename $@).ll -o $(basename $@).st2.ll
	$(OPT) -load-pass-plugin $(PASS1) -passes="breakgep" $(basename $@).st2.ll -o $(basename $@).st3.ll -S
	$(OPT) -load-pass-plugin $(PASS2) -passes="localise" $(basename $@).st3.ll -o $(basename $@).st4.ll -S
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).st4.ll $(CFLAGS) 
endif



LD_FLAGS = 
ifdef CONFIG_SIM
LD_FLAGS += -lgcc
else
LD_FLAGS += -Wl,-error-limit=0
endif


$(OBJDIR)/tramps.o: arch/$(TARGET_ARCH)/tramps.S
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -c -o $(OBJDIR)/tramps.o arch/$(TARGET_ARCH)/tramps.S

libshared.sco: $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ) $(LD_FLAGS)

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR)

mrproper:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR) $(PASS_DIR1) $(PASS_DIR2)