MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)

LIBOS_PATH := ../..

CFLAGS=-fPIC -fPIE -pie -g -O2  -nostdinc \
	$(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_PURE) -B$(CROSS_COMPILE) $(ARCH_PURE) \
	 -I $(LIBOS_PATH)/musl-host/include  -I.\

CPIO=root_libvirt.cpio

DEPS = 
OBJDIR = obj
SRC = main.c

SRC += $(wildcard 3rd/xdr/*.c)
CFLAGS += -I3rd/tirpc


SRC_LIBVIRT += libvirt/src/cvm/cvm_conf.c libvirt/src/cvm/cvm_driver.c 
SRC_LIBVIRT += libvirt/src/remote/remote_daemon.c libvirt/src/remote/remote_daemon_config.c libvirt/src/remote/remote_daemon_dispatch.c libvirt/src/remote/remote_protocol.c libvirt/src/remote/remote_daemon_stream.c
SRC_LIBVIRT += $(wildcard libvirt/src/util/*.c)
SRC_LIBVIRT += $(wildcard libvirt/src/conf/*.c)
SRC_LIBVIRT += $(wildcard libvirt/src/access/*.c)
SRC_LIBVIRT += $(wildcard libvirt/src/rpc/*.c)
SRC_LIBVIRT += $(wildcard libvirt/src/*.c)

SRC_LIBVIRT += $(wildcard libvirt/libxml2/*.c)
SRC_LIBVIRT += libvirt/gnulib/lib/nonblocking.c libvirt/gnulib/lib/areadlink.c libvirt/gnulib/lib/dirname-lgpl.c libvirt/gnulib/lib/secure_getenv.c libvirt/gnulib/lib/mgetgroups.c libvirt/gnulib/lib/getugroups.c libvirt/gnulib/lib/basename-lgpl.c libvirt/gnulib/lib/careadlinkat.c libvirt/gnulib/lib/allocator.c libvirt/gnulib/lib/base64.c libvirt/gnulib/lib/c-ctype.c

CFLAGS += -Ilibvirt -Ilibvirt/include -Ilibvirt/src/util -Ilibvirt/gnulib/lib -Ilibvirt/libxml2/include -Ilibvirt/src -Ilibvirt/src/conf/ -Ilibvirt/libxml2/include -Ilibvirt/src/access -Ilibvirt/src/remote
CFLAGS += -Ilibvirt/src/rpc
CFLAGS += -DLIBVIRT -DHOST_NAME_MAX=1024 -Dabs_topbuilddir=\"/\" -Dabs_topsrcdir=\"/\"

SRC += $(SRC_LIBVIRT)

OBJ := $(SRC:%.c=$(OBJDIR)/%.o)


default: liblibvirt.so


$(OBJDIR)/%.o: %.c $(DEPS) $(PASS1) $(PASS2) 
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS)


$(CPIO): $(WEIGHTS)
	cd rootfs && find . -print -depth | cpio -vo -H newc > ../root_libvirt.cpio


liblibvirt.so: $(OBJ) $(CPIO)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ) $(LD_FLAGS) $(LIBOS_PATH)/libmusl-uni.a

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR)

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.so ./*.cpio ${INSTALL_PATH}
