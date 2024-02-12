MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)

LIBOS_PATH := ../..

CFLAGS=-fPIC -fPIE -pie -g -O2  -nostdinc \
	$(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_PURE) -B$(CROSS_COMPILE) $(ARCH_PURE) \
	 -I $(LIBOS_PATH)/musl-host/include  -I.\
	-I darknet/include

URL_PREFIX = https://pjreddie.com/media/files/
WEIGHTS = alexnet.weights 
CPIO = root.cpio

DEPS = 
OBJDIR = obj
SRC = main.c

SRC += $(wildcard darknet/src/*.c)
SRC += $(wildcard darknet/examples/*.c)


OBJ := $(SRC:%.c=$(OBJDIR)/%.o)


default: libdarknet.so

$(WEIGHTS):
	@for file in $(WEIGHTS); do \
		if [ ! -f rootfs/$$file ]; then \
			echo "Downloading $$file"; \
			curl -L --output rootfs/$$file $(URL_PREFIX)/$$file; \
		else \
			echo "$$file already exists"; \
		fi \
	done


$(OBJDIR)/%.o: %.c $(DEPS) $(PASS1) $(PASS2) 
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS)


$(CPIO): $(WEIGHTS)
#$(CPIO):
	cd rootfs && find . -print -depth | cpio -vo -H newc > ../root.cpio

libdarknet.so: $(OBJ) $(CPIO)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ) $(LD_FLAGS) $(LIBOS_PATH)/libmusl-uni.a

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR)

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.so ./*.cpio ./*.ci ${INSTALL_PATH}
