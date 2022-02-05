PROG=helloworld.py
BUILD_DIR=Python-3.9.1
SRC_PY=Python-3.9.1.tgz
DEST_DIR=dest
MOUNTPOINT=/media/ext4disk

CFLAGS="-fPIE -fpie -O2"
LDFLAGS="-pie"

CC=../../../build/musl-host/bin/musl-clang-target

P_CFG = --host=riscv64-linux-gnu --build=riscv64 --disable-ipv6 --target=riscv64-unknown-linux \
		--prefix=/usr --exec-prefix=/usr --sysconfdir=/etc --localstatedir=/var --program-prefix= \
		--disable-gtk-doc --disable-gtk-doc-html --disable-doc --disable-docs --disable-documentation \
		--with-xmlto=no --with-fop=no --disable-dependency-tracking --disable-ipv6 --disable-nls --disable-static --disable-shared --disable-readline \
		--disable-curses --with-libmpdec=none --with-expat=none --disable-sqlite3 --disable-openssl --disable-codecs-cjk --disable-uuid --disable-bzip2 \
		--disable-xz --disable-zlib --disable-ossaudiodev --without-ensurepip --without-cxx-main  \
		--disable-pydoc --disable-test-modules --disable-lib2to3 --disable-tk --disable-nis --disable-idle3 --disable-pyc-build --disable-ffi

DISK=disk_python.img

LOOP_DEVICE=loop9
IMAGE_SIZE_MB=100

ESCALATE_CMD=sudo

.DELETE_ON_ERROR:
.PHONY: all clean

all: $(DISK)

clean:
#	echo "uncomment clean"
	rm -rf $(DISK) *.o $(BUILD_DIR) $(DEST_DIR)

python_conf:
	mkdir -p $(DEST_DIR)
	tar -xf $(SRC_PY) 
	cd $(BUILD_DIR) && CONFIG_SITE=../config.site CFLAGS=$(CFLAGS) LDFLAGS=$(LDFLAGS) CC=$(CC) ./configure $(P_CFG)
	cat $(BUILD_DIR)/pyconfig.h \
	| grep -v "HAVE_DECL_ISFINITE"   \
	| grep -v "HAVE_DECL_ISINF"  \
	| grep -v "HAVE_DECL_ISNAN"   \
	> /tmp/carrie/pyconfig.h
	mv /tmp/carrie/pyconfig.h $(BUILD_DIR)/pyconfig.h

#	| grep -v "HAVE_EXECV"   \
#	| grep -v "HAVE_FORK"   \


python_build: python_conf
	make -C $(BUILD_DIR)

python_install: python_build
	DESTDIR=../$(DEST_DIR) make -C $(BUILD_DIR) install
	rm -rf $(DEST_DIR)/usr/lib/libpython*.a
	rm -rf $(DEST_DIR)/usr/lib/python*/test
	rm -rf $(DEST_DIR)/usr/lib/python*/config-*


$(DISK): python_install
#$(DISK):
	dd if=/dev/zero of="$@" count=$(IMAGE_SIZE_MB) bs=1M
	mkfs.ext4 "$@"
	$(ESCALATE_CMD) /bin/bash -euxo pipefail -c '\
		mkdir -p $(MOUNTPOINT); \
		mount -t ext4 -o loop "$@" $(MOUNTPOINT); \
		mkdir -p $(MOUNTPOINT)/app; \
		cp $(PROG)  $(MOUNTPOINT)/app; \
		cp -r  $(DEST_DIR)/*  $(MOUNTPOINT)/; \
		umount $(MOUNTPOINT); \
		chown $(USER) "$@"; \
	'

