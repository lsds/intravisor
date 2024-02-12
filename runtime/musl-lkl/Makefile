include config.mak

.PHONY: musl-host lkl musl-target-config target-musl target-lkl tools clean

PREFIX=/usr/local

# Boot memory reserved for LKL/kernel (in MB), deprecated
BOOT_MEM=32 # Default in LKL is 64

HW_MODE=yes

default: all

# Default is to build everything
all: musl-target target-lkl

sim: HW_MODE=no
sim: all

# Vanilla Musl compiler
musl-host ${HOST_MUSL_CC}: | ${HOST_MUSL_BUILD}
	cd ${HOST_MUSL}; [ -f config.mak ] || CFLAGS="$(MUSL_CFLAGS)" ./configure \
		CROSS_COMPILE=$(CROSS_COMPILE) \
		CC=$(CC) \
		$(MUSL_CONFIGURE_OPTS) \
		CLANG_LD_EXTRA_FLAGS=$(CLANG_LD_EXTRA_FLAGS) \
		CLANG_EXTRA_FLAGS=$(CLANG_EXTRA_FLAGS) \
		--prefix=${HOST_MUSL_BUILD} --enable-wrapper=all --target=$(LKL_TARGET)
	+${MAKE} -C ${HOST_MUSL} CFLAGS="$(MUSL_CFLAGS)" -j`tools/ncore.sh` \
		install
	cp build/musl-host/include/endian.h build/musl-host/include/sys/
#TODO: Cross-compile Linux headers
#	ln -fs ${LINUX_HEADERS_INC}/linux/ ${HOST_MUSL_BUILD}/include/linux
#	ln -fs ${LINUX_HEADERS_INC}/asm/ ${HOST_MUSL_BUILD}/include/asm
#	ln -fs ${LINUX_HEADERS_INC}/asm-generic/ ${HOST_MUSL_BUILD}/include/asm-generic

	ln -fs ${LKL_BUILD}/include/linux/ ${HOST_MUSL_BUILD}/include/linux
	ln -fs ${LKL_BUILD}/include/asm/ ${HOST_MUSL_BUILD}/include/asm
	ln -fs ${LKL_BUILD}/include/asm-generic/ ${HOST_MUSL_BUILD}/include/asm-generic

#	# Fix musl-gcc for gcc version that have been built with --enable-default-pie
#	gcc -v 2>&1 | grep "\-\-enable-default-pie" > /dev/null && sed -i 's/"$$@"/-fpie -pie "\$$@"/g' ${HOST_MUSL_BUILD}/bin/musl-gcc || true

# LKL's static library and include/ header directory
lkl ${LIBLKL} ${LKL_BUILD}/include: ${HOST_MUSL_CC} | ${LKL_BUILD}
#	# Override lkl's defconfig with our own
#	cp -Rv src/lkl/override/defconfig ${LKL}/arch/lkl/defconfig
#	cp -Rv src/lkl/override/include/uapi/asm-generic/stat.h ${LKL}/include/uapi/asm-generic/stat.h
#	# Set bootmem size (default in LKL is 64MB)
#	sed -i 's/\#define K_SIZE .*/\#define K_SIZE (${CONFIG_LKL_HEAP_SIZE_MB}*1024*1024LL)/g' lkl/arch/lkl/mm/bootmem.c
ifdef CONFIG_ARCH_ARM
	cp lkl/arch/arm64/include/uapi/asm/fcntl.h lkl/arch/lkl/include/uapi/asm/fcntl.h 
endif
	+DESTDIR=${LKL_BUILD} ${MAKE} -C ${LKL}/tools/lkl -j`tools/ncore.sh` CC=${HOST_MUSL_CC} CROSS_COMPILE=${CROSS_COMPILE} PREFIX=""\
		${LKL}/tools/lkl/liblkl.a
	mkdir -p ${LKL_BUILD}/lib
	cp ${LKL}/tools/lkl/liblkl.a $(LKL_BUILD)/lib
	+DESTDIR=${LKL_BUILD} ${MAKE} -C ${LKL}/tools/lkl -j`tools/ncore.sh` CC=${HOST_MUSL_CC} PREFIX="" CFLAGS=${LKL_CFLAGS} \
		TARGETS="" headers_install
#	# Bugfix, prefix symbol that collides with musl's one
#	find ${LKL_BUILD}/include/ -type f -exec sed -i 's/struct ipc_perm/struct lkl_ipc_perm/' {} \;
#	# Bugfix, lkl_host.h redefines struct iovec in older versions of LKL.
#	grep "CONFIG_AUTO_LKL_POSIX_HOST" ${LKL_BUILD}/include/lkl_host.h > /dev/null && find ${LKL_BUILD}/include/ -type f -exec sed -i 's/struct iovec/struct lkl__iovec/' {} \; || true # struct lkl_iovec already exists
	+${MAKE} headers_install -C ${LKL} ARCH=lkl INSTALL_HDR_PATH=${LKL_BUILD}/

tools: ${TOOLS_OBJ}

# Generic tool rule (doesn't actually depend on lkl_lib, but on LKL headers)
${TOOLS_BUILD}/%: ${TOOLS}/%.c ${LKL_LIB} | ${TOOLS_BUILD}
	gcc ${HOST_TOOLS_CFLAGS} --static -I${LKL_BUILD}/include/ -o $@ $<

# More headers required by SGX-Musl not exported by LKL, given by a custom tool's output
${TARGET_LKL_MUSL_HEADERS}: ${LKL_BUILD}/include/lkl/%.h: ${TOOLS_BUILD}/lkl_%
	$< > $@

# musl-target
musl-target-config:
	cd ${TARGET_LKL_MUSL}; [ -f config.mak ] || CFLAGS="$(MUSL_CFLAGS)" ./configure \
		$(MUSL_CONFIGURE_OPTS) \
		CROSS_COMPILE=$(CROSS_COMPILE) \
		CC=$(CC) \
		--prefix=${TARGET_LKL_MUSL_BUILD} \
		--disable-static \
		--with-malloc=oldmalloc --target=$(LKL_TARGET)

musl-target: ${LIBLKL} ${TARGET_LKL_MUSL_HEADERS}  musl-target-config target-lkl | ${TARGET_LKL_MUSL_BUILD}
	+${MAKE} -C ${TARGET_LKL_MUSL} CFLAGS="$(MUSL_CFLAGS)" -j`tools/ncore.sh`
	cp $(TARGET_LKL_MUSL)/lib/libc.so $(BUILD_DIR)/libmusl-lkl.so

target-lkl: musl-target-config 
	make -C lkl_loader CC=${HOST_MUSL_CC} ARCH=${TARGET_ARCH} CVM_MAX_SIZE=$(CONFIG_CVM_MAX_SIZE)

# Build directories (one-shot after git clone or clean)
${BUILD_DIR} ${TOOLS_BUILD} ${LKL_BUILD} ${HOST_MUSL_BUILD} ${TARGET_LKL_MUSL_BUILD}:
	@mkdir -p $@

clean:
	rm -rf ${BUILD_DIR}
	+${MAKE} -C ${HOST_MUSL} distclean || true
	+${MAKE} -C ${TARGET_LKL_MUSL} distclean || true
	+${MAKE} -C ${LKL} clean || true
	+${MAKE} -C ${LKL}/tools/lkl clean || true
	+${MAKE} -C lkl_loader clean || true
	rm -rf lkl/tools/lkl/Makefile.conf || true
	rm -rf lkl/arch/lkl/include/uapi/asm/fcntl.h  || true
	rm -f ${HOST_MUSL}/config.mak
	rm -f ${TARGET_LKL_MUSL}/config.mak
	rm -rf /tmp/carrie/*
