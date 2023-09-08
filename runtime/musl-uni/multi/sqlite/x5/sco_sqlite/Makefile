MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)

CFLAGS=-fPIC -fPIE -pie -g -O2 -DSQLITE_OMIT_LOAD_EXTENSION -DSQLITE_THREADSAFE=0  -DSQLITE_OMIT_FLOATING_POINT=1 -DSQLITE_OMIT_DEPRECATED=1 -DSQLITE_OMIT_RANDOMNESS=1 -DSQLITE_OS_UNIX=1 -DSQLITE_MAX_MMAP_SIZE=0 -nostdinc \
	-I musl-host/include -I cheri-libc/include \
	$(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_PURE) -B$(CROSS_COMPILE) $(ARCH_PURE) -Iarch/$(TARGET_ARCH)/include\
	-Wno-unused-command-line-argument -Werror=implicit-function-declaration -Werror=format -Werror=incompatible-pointer-types -Werror=cheri-capability-misuse -Werror=cheri-bitwise-operations -Werror=cheri-prototypes -Werror=pass-failed -Werror=undefined-internal -Wno-error=cheri-capability-misuse

#	-I nolibc/include 
		
ifdef CONFIG_KERNEL_CONFIGURED_DDC_RELATIVE
$(error multi-party SQLite was not tested on a CheriBSD with enabled DDC/PCC-relative compartments)
endif

ifneq ($(MODE),sim)
endif

DEPS = 
OBJDIR = obj
SRC = main.c tramps.c hostcalls.c speedtest1.c sqlite3.c scoLibc.c scoLibc_file.c
OBJ := $(SRC:%.c=$(OBJDIR)/%.o)


PASS_DIR1 = build_break
PASS1 = $(PASS_DIR1)/libBRKGEPPass.so

PASS_DIR2 = build_loc
PASS2 = $(PASS_DIR2)/libLocPass.so

default: libsco_sqlite.so

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
	@$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	@$(OPT) -S -mem2reg -instnamer $(basename $@).ll -o $(basename $@)2.ll
	@$(OPT) -load-pass-plugin $(PASS1) -passes="breakgep" $(basename $@)2.ll -o $(basename $@)3.ll -S
	@$(OPT) -load-pass-plugin $(PASS2) -passes="localise" $(basename $@)3.ll -o $(basename $@)4.ll -S
	@$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@)4.ll $(CFLAGS) 

$(OBJDIR)/tramps.o: arch/$(TARGET_ARCH)/tramps.S
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -c -o $(OBJDIR)/tramps.o arch/$(TARGET_ARCH)/tramps.S

libsco_sqlite.so: $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ)

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR)

mrproper:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR) $(PASS_DIR1) $(PASS_DIR2)

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.so  ${INSTALL_PATH}
