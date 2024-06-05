#!/bin/sh -ex

case "$1" in
	"cheri128"|"")
		MABI="purecap"
		CPUFLAGS="-mcpu=cheri128"
		;;
	"cheri256"|"")
		MABI="purecap"
		;;
	"hybrid")
		MABI="n64"
		;;
	*)
		echo 'must specify either "cheri128" "cheri256" or "hybrid"'
		exit 1
esac

CHERI_ROOT=${CHERI_ROOT:-${HOME}/cheri}
CHERISDK=${CHERISDK:-${CHERI_ROOT}/output/sdk256/bin}
CHERIBSD_SYSROOT=${CHERIBSD_SYSROOT:-${CHERI_ROOT}/output/sdk256/sysroot}
INSTALL_DIR=${INSTALL_DIR:-${CHERI_ROOT}/output/rootfs256}

# This needs to be done first.  Nginx doesn't support cross-building;
# if you try to tell it to use cheri compiler, it will try to execute
# the output binary and the build will fail.
sh auto/configure --with-debug --without-pcre --without-http_rewrite_module

COMMON_FLAGS="-pipe --sysroot=${CHERIBSD_SYSROOT} -B${CHERISDK} -target cheri-unknown-freebsd -mabi=${MABI} ${CPUFLAGS} -mxgot -O2 -msoft-float -ggdb -static -integrated-as"
COMPILE_FLAGS="${COMMON_FLAGS} -Wcheri-capability-misuse -Werror=implicit-function-declaration -Werror=format -Werror=undefined-internal"

export CFLAGS="${COMPILE_FLAGS}"
export CFLAGS="${COMPILE_FLAGS}"
export PATH="${CHERISDK}:${CHERILDDIR}:$PATH"
export CC="${CHERISDK}/clang"

#sed -i '' "s!^CC .*!CC = ${CC}!;s!^CFLAGS .*!CFLAGS = ${CFLAGS}!;s!^CPP .*!CPP = ${CC} -E!;s!^LINK .*!LINK = ${CC} ${CFLAGS} -fuse-ld=lld!;s!-Wl,-E!!" objs/Makefile
sed -i '' "s!^CC .*!CC = ${CC}!;s!^CFLAGS .*!CFLAGS = ${CFLAGS}!;s!^CPP .*!CPP = ${CC} -E!;s!^LINK .*!LINK = ${CC} ${CFLAGS}!;s!-Wl,-E!!" objs/Makefile
make -j8
make install DESTDIR=${INSTALL_DIR}
chmod -R a+rX ${INSTALL_DIR}

cp fetchbench ${INSTALL_DIR}/usr/local/nginx/sbin/fetchbench
#chown 0:0 ${INSTALL_DIR}/usr/local/nginx/sbin/fetchbench
chmod 755 ${INSTALL_DIR}/usr/local/nginx/sbin/fetchbench

cp nginx-benchmark.sh ${INSTALL_DIR}/
#chown 0:0 ${INSTALL_DIR}/nginx-benchmark.sh
chmod 755 ${INSTALL_DIR}/nginx-benchmark.sh

