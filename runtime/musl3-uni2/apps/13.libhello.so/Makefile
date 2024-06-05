MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)

PROG=app13
OBJDIR = obj

CROSS_LIBC_PATH=../../libc/build/
CFLAGS= -I../../libc/build/include -DINTRAVISOR -O2

CFLAGS+= -I.

SRC += main.c 

OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

SO = libso_test.so

ROOTFS := root.cpio

all: $(ROOTFS)

$(OBJDIR)/%.o: %.c
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS)

$(OBJDIR)/$(SO): so_test.c
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -o $(basename $@).so $(basename $@).ll $(CFLAGS) -shared -lc -L$(CROSS_LIBC_PATH)/lib -nostdlib -nostartfiles

$(PROG): $(OBJ) $(OBJDIR)/$(SO)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -nostdlib -nostartfiles -o $@ $(OBJ) $(CROSS_LIBC_PATH)/lib/crt1.o $(CROSS_LIBC_PATH)/lib/crti.o $(CROSS_LIBC_PATH)/lib/crtn.o \
	-L$(CROSS_LIBC_PATH)/lib -Wl,-dynamic-linker=/lib/ld-linux-aarch64_purecap.so.1 ../../libc/libcompiler_rt.a -lc -pie -L$(OBJDIR) -lso_test

clean:
	rm -rf $(ROOTFS) $(PROG) *.o ./$(OBJDIR) rootfs/app1 rootfs/usr/lib/$(SO)

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.ci ./libldso.so ${INSTALL_PATH}
	sudo cp $(ROOTFS) ${INSTALL_PATH}/$(ROOTFS)_$(shell basename $(shell ls *.yaml) .yaml)

$(ROOTFS): $(PROG) $(CROSS_LIBC_PATH)/lib/libc.so $(OBJDIR)/$(SO)
	cp $(PROG) rootfs/app1
	cp $(OBJDIR)/$(SO) rootfs/usr/lib/
	cp $(CROSS_LIBC_PATH)/lib/libc.so ./libldso.so
	cd rootfs && find . -print -depth | sort | $(CPIO) -vo -H newc > ../$(ROOTFS)

