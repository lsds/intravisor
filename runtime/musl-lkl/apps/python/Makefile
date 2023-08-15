ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

PROG=helloworld.py
BUILD_DIR=Python-3.9.1
DEST_DIR=$(ROOT_DIR)/dest
MOUNTPOINT=/media/ext4disk
LIBFFI_BUILD_DIR=libffi-3.4.4
LIBFFI_SRC=libffi-3.4.4.tar.gz

CFFI_BUILD_DIR=cffi-1.15.1
CFFI_SRC=cffi-1.15.1.tar.gz


CFLAGS="-I$(DEST_DIR)/usr/include"
LDFLAGS="-L$(DEST_DIR)/usr/lib"

#full path would be better
CC=../../../build/musl-host/bin/musl-gcc

P_CFG = --host=$(LKL_MUSL_HOST)  --build=$(LKL_MUSL_BUILD) --disable-ipv6 --target=$(LKL_MUSL_HOST) \
		--prefix=/usr --exec-prefix=/usr --sysconfdir=/etc --localstatedir=/var --program-prefix= \
		LIBFFI_INCLUDEDIR=abba


DISK=disk_python.img

LOOP_DEVICE=loop9
IMAGE_SIZE_MB=100

ESCALATE_CMD=sudo
USER=`whoami`

.DELETE_ON_ERROR:
.PHONY: all clean

all: $(DISK)

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.img ${INSTALL_PATH}


clean:
#	echo "uncomment clean"
	make -C $(BUILD_DIR) distclean || true
	rm -rf $(DISK) *.o $(DEST_DIR) $(CFFI_BUILD_DIR) $(LIBFFI_BUILD_DIR) *.so

python_conf:
	mkdir -p $(DEST_DIR)
	cd $(BUILD_DIR) && LIBFFI_INCLUDEDIR=$(DEST_DIR)/usr/include CROSS_COMPILE_TARGET=yes CONFIG_SITE=../config.site CFLAGS=$(CFLAGS) LDFLAGS=$(LDFLAGS) CC=$(CC) ./configure $(P_CFG)
	cat $(BUILD_DIR)/pyconfig.h \
	| grep -v "HAVE_DECL_ISFINITE"   \
	| grep -v "HAVE_DECL_ISINF"  \
	| grep -v "HAVE_DECL_ISNAN"   \
	> /tmp/pyconfig.h
	mv /tmp/pyconfig.h $(BUILD_DIR)/pyconfig.h

#	| grep -v "HAVE_EXECV"   \
#	| grep -v "HAVE_FORK"   \


python_build: python_conf
	CC=$(CC) CROSS_COMPILE_TARGET=yes make -C $(BUILD_DIR)

python_install: python_build
	DESTDIR=$(DEST_DIR) make -C $(BUILD_DIR) install
	rm -rf $(DEST_DIR)/usr/lib/libpython*.a
	rm -rf $(DEST_DIR)/usr/lib/python*/test
	rm -rf $(DEST_DIR)/usr/lib/python*/config-*

libffi_conf:
	mkdir -p $(DEST_DIR)
	tar -xf $(LIBFFI_SRC) 
	cd $(LIBFFI_BUILD_DIR) && CC=../$(CC) ./configure --host=$(LKL_MUSL_HOST) --build=$(LKL_MUSL_BUILD)  --prefix=/usr


libffi_build: libffi_conf
	make -C $(LIBFFI_BUILD_DIR)

libffi_install: libffi_build
	DESTDIR=$(DEST_DIR) make -C $(LIBFFI_BUILD_DIR) install

#cffi requires change naming
cffi_build:
	tar -xf $(CFFI_SRC) 
	cd $(CFFI_BUILD_DIR)  &&  OPT="" CFLAGS="" LDFLAGS="" LDSHARED="../../../build/musl-host/bin/musl-gcc -L../libffi-3.4.4/riscv64-unknown-linux-gnu/.libs/ -shared" CC="../../../build/musl-host/bin/musl-gcc -DHAVE_STDINT_H -DHAVE_MEMALIGN -nostdlib -I../Python-3.9.1/Include/ -I../Python-3.9.1/ -I../libffi-3.4.4/riscv64-unknown-linux-gnu/include/" python setup.py build

cffi_install: cffi_build
	cp -r $(CFFI_BUILD_DIR)/build/lib.linux-x86_64-cpython-39/cffi $(DEST_DIR)/usr/lib/python3.9/
	cp -r $(CFFI_BUILD_DIR)/build/lib.linux-x86_64-cpython-39/_cffi_backend.cpython-39-x86_64-linux-gnu.so $(DEST_DIR)/usr/lib/python3.9/_cffi_backend.cpython-39-riscv-64-linux-gnu.so


#$(DISK): libffi_install python_install cffi_install
#while cffi works, we don't include it so far
$(DISK): libffi_install python_install
#$(DISK):
	dd if=/dev/zero of="$@" count=$(IMAGE_SIZE_MB) bs=1M
	mkfs.ext4 "$@"
	$(ESCALATE_CMD) /bin/bash -euxo pipefail -c '\
		mkdir -p $(MOUNTPOINT); \
		mount -t ext4 -o loop "$@" $(MOUNTPOINT); \
		mkdir -p $(MOUNTPOINT)/app; \
		cp ./*.py  $(MOUNTPOINT)/app; \
		REALGCC=$(REALGCC) ../../build/musl-host/bin/musl-gcc test.c -o libtest.so -shared ; \
		cp libtest.so $(MOUNTPOINT)/app; \
		cp -r  $(DEST_DIR)/*  $(MOUNTPOINT)/; \
		umount $(MOUNTPOINT); \
		chown $(USER) "$@"; \
	'

