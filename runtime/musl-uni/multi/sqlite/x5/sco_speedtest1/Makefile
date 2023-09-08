MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)


CFLAGS=-fPIC -fPIE -pie -g -O2 -DSQLITE_OMIT_LOAD_EXTENSION -DSQLITE_THREADSAFE=0  -DSQLITE_OMIT_FLOATING_POINT=1 -DSQLITE_OMIT_DEPRECATED=1 -DSQLITE_OMIT_RANDOMNESS=1 -DSQLITE_OS_UNIX=1 -nostdinc \
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
OBJ = main.o tramps.o hostcalls.o speedtest1.o scoLibc.o
PASS = build/libLocPass.so

default: libsco_speedtest1.so

%.o: %.c $(DEPS) 
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $@ $< $(CFLAGS) 
#-Xclang -load -Xclang $(PASS)

tramps.o: arch/$(TARGET_ARCH)/tramps.S
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -c -o tramps.o arch/$(TARGET_ARCH)/tramps.S

libsco_speedtest1.so: $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ)

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.so  ${INSTALL_PATH}
