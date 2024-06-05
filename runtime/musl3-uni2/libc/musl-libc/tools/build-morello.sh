#!/usr/bin/env bash

# How to build Morello toolchain using this script
# ================================================
#
# Prerequisites
# -------------
#  - Host LLVM (11.0 or above).
#  - Cmake (3.13.4 or above)
#  - Make (4.2)
#  - Python (3.6 or above)
#
# Note: be aware of use of the env variables in the below commands.
# Note: all paths should be absolute.
#
# Configure and build Clang
# -------------------------
#
# LLVM_TARGETS="<targets>" LLVM_LIT_ARGS="<args-for-tests>" \
#   bash build-morello.sh clang \
#   /path/to/llvm-project \
#   /path/to/host/llvm \
#   /path/to/morello/llvm \
#   /path/to/build/directory
#
# For targets use "AArch64" for AArch64-hosted toolchain and "X86;AArch64" for x86-hosted
# toolchain. Clang will be installed in the "/path/to/morello/llvm" directory.
#
# Install Musl headers
# --------------------
#
# This installs Musl headers for Morello:
#
# CC=/path/to/morello/llvm/bin/clang \
#   bash build-morello.sh musl-headers \
#   /path/to/musl/sources \
#   /path/to/morello/musl/install \
#   aarch64-unknown-linux-musl_purecap
#
# To install headers for AArch64, use `aarch64-unknown-linux-gnu` triple.
#
# Build CRT objects
# -----------------
#
# This builds CRT objects for Morello:
#
# CC=/path/to/morello/llvm/bin/clang \
#   bash build-morello.sh crt \
#   /path/to/llvm-project \
#   /path/to/morello/musl/install \
#   aarch64-unknown-linux-musl_purecap
#
# To build CRT objects for AArch64, use `aarch64-unknown-linux-gnu` triple.
#
#
# Built Compiler-RT
# -----------------
#
# This builds Compiler-RT for Morello:
#
# bash build-morello.sh compiler-rt \
#   /path/to/llvm-project \
#   /path/to/morello/llvm \
#   /path/to/comp-rt/build/directory \
#   /path/to/morello/musl/install \
#   aarch64-unknown-linux-musl_purecap
#
# To build Compiler-RT for AArch64, use `aarch64-unknown-linux-gnu` triple.
#
# Build Musl libc
# ---------------
#
# CC=/path/to/morello/llvm/bin/clang \
#   bash build-morello.sh musl \
#   /path/to/musl/sources \
#   /path/to/musl/install -- \
#   aarch64-unknown-linux-musl_purecap
#
# Musl will be installed in the "/path/to/musl/install" directory.
#
# Compile a hello world app
# -------------------------
#
# /path/to/morello/llvm/bin/clang --target=aarch64-linux-musl_purecap \
#   -march=morello --sysroot /path/to/musl/install \
#   hello.c -o hello [--static]
#
# END-OF-HOWTO

STAGE=${1} # stage to run: clang, clang-test, crt, compiler-rt, musl, etc...

case ${STAGE} in
  -help|--help|help)
      echo "Usage: ${0} STAGE [ARGS]"
      echo "Stages: clang, musl-headers, crt, compiler-rt, musl, libunwind, libcxxabi, libcxx"
      echo "        clang-test, musl-test, libc-test, package"
      echo ""
      exit 0
      ;;
esac

set -x
set -e

MORELLO_TRIPLE=aarch64-unknown-linux-musl_purecap
AARCH64_TRIPLE=aarch64-unknown-linux-gnu

function __configure_clang() {
    local LLVM_PROJECT=${1}
    local HOST_LLVM_BIN=${2}
    local MORELLO_HOME=${3}
    mkdir -p ${MORELLO_HOME}
    cmake -Wno-dev \
        -DCMAKE_C_COMPILER=${HOST_LLVM_BIN}/clang \
        -DCMAKE_C_COMPILER_WORKS=YES \
        -DCMAKE_ASM_COMPILER=${HOST_LLVM_BIN}/clang \
        -DCMAKE_ASM_COMPILER_WORKS=YES \
        -DCMAKE_CXX_COMPILER=${HOST_LLVM_BIN}/clang++ \
        -DCMAKE_CXX_COMPILER_WORKS=YES \
        -DCMAKE_AR=${HOST_LLVM_BIN}/llvm-ar \
        -DCMAKE_RANLIB=${HOST_LLVM_BIN}/llvm-ranlib \
        -DCMAKE_NM=${HOST_LLVM_BIN}/llvm-nm \
        -DCMAKE_LINKER=${HOST_LLVM_BIN}/ld.lld \
        -DCMAKE_OBJDUMP=${HOST_LLVM_BIN}/llvm-objdump \
        -DCMAKE_OBJCOPY=${HOST_LLVM_BIN}/llvm-objcopy \
        -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld" \
        -DCMAKE_SHARED_LINKER_FLAGS="-fuse-ld=lld" \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=${MORELLO_HOME} \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
        -DCMAKE_SKIP_BUILD_RPATH=OFF \
        -DCMAKE_INSTALL_RPATH=\$ORIGIN/../lib \
        -DCMAKE_BUILD_WITH_INSTALL_RPATH=ON \
        -DLLVM_ENABLE_PROJECTS="clang;lld;lldb;libcxx;libcxxabi;compiler-rt;libunwind" \
        -DLLVM_TARGETS_TO_BUILD="${LLVM_TARGETS}" \
        -DLLVM_ENABLE_ASSERTIONS=OFF \
        -DLLVM_ENABLE_LIBCXX=ON \
        -DLLVM_ENABLE_LLD=ON \
        -DLLVM_ENABLE_EH=ON \
        -DLLVM_ENABLE_RTTI=ON \
        -DBUILD_SHARED_LIBS=ON \
        -DCOMPILER_RT_BUILD_BUILTINS=ON \
        -DCOMPILER_RT_BUILD_XRAY=OFF \
        -DCOMPILER_RT_BUILD_LIBFUZZER=OFF \
        -DCOMPILER_RT_BUILD_PROFILE=OFF \
        -DLIBCXX_CXX_ABI=libcxxabi \
        -DLIBCXX_CXX_ABI_INCLUDE_PATHS="${LLVM_PROJECT}/libcxxabi/include" \
        -DLIBCXX_USE_COMPILER_RT=ON \
        -DLIBCXX_ENABLE_THREADS=ON \
        -DLIBCXXABI_ENABLE_THREADS=ON \
        -DLIBCXXABI_USE_LLVM_UNWINDER=ON \
        -DLIBCXXABI_USE_COMPILER_RT=ON \
        -DLIBUNWIND_ENABLE_THREADS=ON \
        -DLLVM_LIT_ARGS="${LLVM_LIT_ARGS}" \
        -DCLANG_DEFAULT_RTLIB="compiler-rt" \
        -DCLANG_DEFAULT_CXX_STDLIB="libc++" \
        -DCLANG_DEFAULT_LINKER="lld" \
        -DCLANG_DEFAULT_OBJCOPY="llvm-objcopy" \
        ${LLVM_PROJECT}/llvm
}

function __configure_comp_rt() {
    local LLVM_PROJECT=${1}         # path to LLVM sources
    local MORELLO_LLVM_PATH=${2}    # path where Morello LLVM has been installed
    local BUILD_PATH=${3}           # path to the build folder
    local SYSROOT=${4}              # path to sysroot with the required libc headers
    local TRIPLE=${5}               # triple to target
    if [[ "${TRIPLE}" == "${MORELLO_TRIPLE}" ]]; then
        local TFLAGS="-march=morello -mabi=purecap"
    else
        local TFLAGS="-march=armv8"
    fi
    mkdir -p ${BUILD_PATH}
    pushd ${BUILD_PATH}
    cat << EOF > toolchain.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_ASM_COMPILER_TARGET "${TRIPLE} ${TFLAGS}")
set(CMAKE_C_COMPILER_TARGET "${TRIPLE} ${TFLAGS}")

set(CMAKE_ASM_COMPILER_WORKS 1 CACHE INTERNAL "")
set(CMAKE_C_COMPILER_WORKS 1 CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER_WORKS 1 CACHE INTERNAL "")

set(CMAKE_ASM_COMPILER "${MORELLO_LLVM_PATH}/bin/clang" CACHE FILEPATH "" FORCE)
set(CMAKE_C_COMPILER "${MORELLO_LLVM_PATH}/bin/clang" CACHE FILEPATH "" FORCE)
set(CMAKE_CXX_COMPILER "${MORELLO_LLVM_PATH}/bin/clang++" CACHE FILEPATH "" FORCE)
set(CMAKE_AR "${MORELLO_LLVM_PATH}/bin/llvm-ar" CACHE FILEPATH "" FORCE)
set(CMAKE_RANLIB "${MORELLO_LLVM_PATH}/bin/llvm-ranlib" CACHE FILEPATH "" FORCE)
set(CMAKE_NM "${MORELLO_LLVM_PATH}/bin/llvm-nm" CACHE FILEPATH "" FORCE)
set(CMAKE_LINKER "${MORELLO_LLVM_PATH}/bin/ld.lld" CACHE FILEPATH "" FORCE)
set(CMAKE_OBJDUMP "${MORELLO_LLVM_PATH}/bin/llvm-objdump" CACHE FILEPATH "" FORCE)
set(CMAKE_OBJCOPY "${MORELLO_LLVM_PATH}/bin/llvm-objcopy" CACHE FILEPATH "" FORCE)

set(LLVM_CONFIG_PATH "${MORELLO_LLVM_PATH}/bin/llvm-config" CACHE FILEPATH "" FORCE)
EOF
    cmake -Wno-dev \
        -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_C_FLAGS="-nostdinc -isystem ${SYSROOT}/include" \
        -DCMAKE_ASM_FLAGS="-nostdinc -isystem ${SYSROOT}/include" \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
        -DCMAKE_SKIP_BUILD_RPATH=OFF \
        -DCMAKE_INSTALL_RPATH=\$ORIGIN/../lib \
        -DCMAKE_BUILD_WITH_INSTALL_RPATH=ON \
        -DLLVM_TARGETS_TO_BUILD="AArch64" \
        -DLLVM_ENABLE_ASSERTIONS=OFF \
        -DBUILD_SHARED_LIBS=ON \
        -DCOMPILER_RT_DEFAULT_TARGET_TRIPLE=${TRIPLE} \
        -DCOMPILER_RT_BUILD_BUILTINS=ON \
        -DCOMPILER_RT_BUILD_SANITIZERS=OFF \
        -DCOMPILER_RT_BUILD_XRAY=OFF \
        -DCOMPILER_RT_BUILD_LIBFUZZER=OFF \
        -DCOMPILER_RT_BUILD_PROFILE=OFF \
        ${LLVM_PROJECT}/compiler-rt
    popd
}

function __configure_libunwind() {
    local LLVM_PROJECT=${1}         # path to LLVM sources
    local MORELLO_LLVM_PATH=${2}    # path where Morello LLVM has been installed
    local BUILD_PATH=${3}           # path to the build folder
    local SYSROOT=${4}              # path to sysroot with the required libc headers
    local TRIPLE=${5}               # triple to target
    if [[ "${TRIPLE}" == "${MORELLO_TRIPLE}" ]]; then
        local TFLAGS="-march=morello -mabi=purecap"
    else
        local TFLAGS="-march=armv8"
    fi
    mkdir -p ${BUILD_PATH}
    pushd ${BUILD_PATH}
    cat << EOF > toolchain.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_ASM_COMPILER_TARGET "${TRIPLE}")
set(CMAKE_C_COMPILER_TARGET "${TRIPLE}")
set(CMAKE_CXX_COMPILER_TARGET "${TRIPLE}")

set(CMAKE_ASM_COMPILER_WORKS 1 CACHE INTERNAL "")
set(CMAKE_C_COMPILER_WORKS 1 CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER_WORKS 1 CACHE INTERNAL "")

set(CMAKE_ASM_COMPILER "${MORELLO_LLVM_PATH}/bin/clang" CACHE FILEPATH "" FORCE)
set(CMAKE_C_COMPILER "${MORELLO_LLVM_PATH}/bin/clang" CACHE FILEPATH "" FORCE)
set(CMAKE_CXX_COMPILER "${MORELLO_LLVM_PATH}/bin/clang++" CACHE FILEPATH "" FORCE)
set(CMAKE_AR "${MORELLO_LLVM_PATH}/bin/llvm-ar" CACHE FILEPATH "" FORCE)
set(CMAKE_RANLIB "${MORELLO_LLVM_PATH}/bin/llvm-ranlib" CACHE FILEPATH "" FORCE)
set(CMAKE_NM "${MORELLO_LLVM_PATH}/bin/llvm-nm" CACHE FILEPATH "" FORCE)
set(CMAKE_LINKER "${MORELLO_LLVM_PATH}/bin/ld.lld" CACHE FILEPATH "" FORCE)
set(CMAKE_OBJDUMP "${MORELLO_LLVM_PATH}/bin/llvm-objdump" CACHE FILEPATH "" FORCE)
set(CMAKE_OBJCOPY "${MORELLO_LLVM_PATH}/bin/llvm-objcopy" CACHE FILEPATH "" FORCE)

set(LLVM_CONFIG_PATH "${MORELLO_LLVM_PATH}/bin/llvm-config" CACHE FILEPATH "" FORCE)
set(CMAKE_ASM_FLAGS "--sysroot=${SYSROOT} ${TFLAGS}" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS "--sysroot=${SYSROOT} ${TFLAGS}" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "--sysroot=${SYSROOT} ${TFLAGS}" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "-fuse-ld=lld -nostdlib --rtlib=compiler-rt" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS "-fuse-ld=lld -nostdlib --rtlib=compiler-rt" CACHE STRING "" FORCE)
EOF
    cmake -S ${LLVM_PROJECT}/libunwind \
    -B ${BUILD_PATH}\
    -Wno-dev \
    -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_TARGETS_TO_BUILD="AArch64" \
    -DLIBUNWIND_TARGET_TRIPLE=${TRIPLE} \
    -DLIBUNWIND_SYSROOT=${SYSROOT} \
    -DLIBUNWIND_ENABLE_STATIC=ON \
    -DLIBUNWIND_ENABLE_SHARED=ON \
    -DLIBUNWIND_ENABLE_THREADS=ON \
    -DLIBUNWIND_USE_COMPILER_RT=ON \
    -DCMAKE_INSTALL_PREFIX=${SYSROOT}
    popd
}

function __configure_libcxxabi() {
    local LLVM_PROJECT=${1}         # path to LLVM sources
    local MORELLO_LLVM_PATH=${2}    # path where Morello LLVM has been installed
    local BUILD_PATH=${3}           # path to the build folder
    local SYSROOT=${4}              # path to sysroot with the required libc headers
    local TRIPLE=${5}              # triple to target
    local LIBUNWIND_HEADERS=${LLVM_PROJECT}/libunwind/include
    local LIBCXX_HEADERS=${MORELLO_LLVM_PATH}/include/c++/v1
    if [[ "${TRIPLE}" == "${MORELLO_TRIPLE}" ]]; then
        local TFLAGS="-march=morello -mabi=purecap"
    else
        local TFLAGS="-march=armv8"
    fi
    mkdir -p ${BUILD_PATH}
    pushd ${BUILD_PATH}
    cat << EOF > toolchain.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_ASM_COMPILER_TARGET "${TRIPLE}")
set(CMAKE_C_COMPILER_TARGET "${TRIPLE}")
set(CMAKE_CXX_COMPILER_TARGET "${TRIPLE}")

set(LIBCXXABI_TARGET_TRIPLE "${TRIPLE}" CACHE STRING "" FORCE)

set(CMAKE_ASM_COMPILER_WORKS 1 CACHE INTERNAL "")
set(CMAKE_C_COMPILER_WORKS 1 CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER_WORKS 1 CACHE INTERNAL "")

set(CMAKE_ASM_COMPILER "${MORELLO_LLVM_PATH}/bin/clang" CACHE FILEPATH "" FORCE)
set(CMAKE_C_COMPILER "${MORELLO_LLVM_PATH}/bin/clang" CACHE FILEPATH "" FORCE)
set(CMAKE_CXX_COMPILER "${MORELLO_LLVM_PATH}/bin/clang++" CACHE FILEPATH "" FORCE)
set(CMAKE_AR "${MORELLO_LLVM_PATH}/bin/llvm-ar" CACHE FILEPATH "" FORCE)
set(CMAKE_RANLIB "${MORELLO_LLVM_PATH}/bin/llvm-ranlib" CACHE FILEPATH "" FORCE)
set(CMAKE_NM "${MORELLO_LLVM_PATH}/bin/llvm-nm" CACHE FILEPATH "" FORCE)
set(CMAKE_LINKER "${MORELLO_LLVM_PATH}/bin/ld.lld" CACHE FILEPATH "" FORCE)
set(CMAKE_OBJDUMP "${MORELLO_LLVM_PATH}/bin/llvm-objdump" CACHE FILEPATH "" FORCE)
set(CMAKE_OBJCOPY "${MORELLO_LLVM_PATH}/bin/llvm-objcopy" CACHE FILEPATH "" FORCE)

set(LLVM_CONFIG_PATH "${MORELLO_LLVM_PATH}/bin/llvm-config" CACHE FILEPATH "" FORCE)
set(CMAKE_ASM_FLAGS "--sysroot=${SYSROOT} ${TFLAGS}" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS "--sysroot=${SYSROOT} ${TFLAGS}" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "--sysroot=${SYSROOT} ${TFLAGS}" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "-fuse-ld=lld -nostdlib --rtlib=compiler-rt" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS "-fuse-ld=lld -nostdlib --rtlib=compiler-rt" CACHE STRING "" FORCE)
EOF
    cmake -S ${LLVM_PROJECT}/libcxxabi \
    -B ${BUILD_PATH}\
    -Wno-dev \
    -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DLIBCXXABI_ENABLE_STATIC=ON \
    -DLIBCXXABI_ENABLE_SHARED=ON \
    -DLIBCXXABI_USE_COMPILER_RT=ON \
    -DLIBCXXABI_USE_LLVM_UNWINDER=ON \
    -DLIBCXXABI_SYSROOT="${SYSROOT}" \
    -DLIBCXXABI_LIBUNWIND_INCLUDES="${LIBUNWIND_HEADERS}" \
    -DLIBCXXABI_LIBUNWIND_PATH="${SYSROOT}/lib" \
    -DLIBCXXABI_LIBCXX_INCLUDES="${LIBCXX_HEADERS}" \
    -DCMAKE_INSTALL_PREFIX=${SYSROOT}
    popd
}

# Standalone libcxx build supported up to clang-13.
function __configure_libcxx() {
    local LLVM_PROJECT=${1}         # path to LLVM sources
    local MORELLO_LLVM_PATH=${2}    # path where Morello LLVM has been installed
    local BUILD_PATH=${3}           # path to the build folder
    local SYSROOT=${4}              # path to sysroot with the required libc header
    local TRIPLE=${5}               # triple to target
    local KERNEL_BRANCH=${6}        # (optional default: latest) version of kernel headers to download
    if [[ "${TRIPLE}" == "${MORELLO_TRIPLE}" ]]; then
        local TFLAGS="-march=morello -mabi=purecap"
    else
        local TFLAGS="-march=armv8"
    fi
    mkdir -p ${BUILD_PATH}
    pushd ${BUILD_PATH}

    __download_kernel_headers "${BUILD_PATH}/" ${KERNEL_BRANCH}
    cat << EOF > toolchain.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_ASM_COMPILER_TARGET "${TRIPLE}")
set(CMAKE_C_COMPILER_TARGET "${TRIPLE}")
set(CMAKE_CXX_COMPILER_TARGET "${TRIPLE}")

set(CMAKE_ASM_COMPILER_WORKS 1 CACHE INTERNAL "")
set(CMAKE_C_COMPILER_WORKS 1 CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER_WORKS 1 CACHE INTERNAL "")

set(LIBCXX_TARGET_TRIPLE "${TARGET}" CACHE STRING "" FORCE)

set(CMAKE_ASM_COMPILER "${MORELLO_LLVM_PATH}/bin/clang" CACHE FILEPATH "" FORCE)
set(CMAKE_C_COMPILER "${MORELLO_LLVM_PATH}/bin/clang" CACHE FILEPATH "" FORCE)
set(CMAKE_CXX_COMPILER "${MORELLO_LLVM_PATH}/bin/clang++" CACHE FILEPATH "" FORCE)
set(CMAKE_AR "${MORELLO_LLVM_PATH}/bin/llvm-ar" CACHE FILEPATH "" FORCE)
set(CMAKE_RANLIB "${MORELLO_LLVM_PATH}/bin/llvm-ranlib" CACHE FILEPATH "" FORCE)
set(CMAKE_NM "${MORELLO_LLVM_PATH}/bin/llvm-nm" CACHE FILEPATH "" FORCE)
set(CMAKE_LINKER "${MORELLO_LLVM_PATH}/bin/ld.lld" CACHE FILEPATH "" FORCE)
set(CMAKE_OBJDUMP "${MORELLO_LLVM_PATH}/bin/llvm-objdump" CACHE FILEPATH "" FORCE)
set(CMAKE_OBJCOPY "${MORELLO_LLVM_PATH}/bin/llvm-objcopy" CACHE FILEPATH "" FORCE)

set(LLVM_CONFIG_PATH "${MORELLO_LLVM_PATH}/bin/llvm-config" CACHE FILEPATH "" FORCE)
set(CMAKE_ASM_FLAGS "--sysroot=${SYSROOT} ${TFLAGS} -isystem ${BUILD_PATH}/kernel-headers/usr/include" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS "--sysroot=${SYSROOT} ${TFLAGS} -isystem ${BUILD_PATH}/kernel-headers/usr/include" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "--sysroot=${SYSROOT} ${TFLAGS} -isystem ${BUILD_PATH}/kernel-headers/usr/include" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "-fuse-ld=lld -nostdlib --rtlib=compiler-rt" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS "-fuse-ld=lld -nostdlib --rtlib=compiler-rt" CACHE STRING "" FORCE)
EOF
    cmake -S ${LLVM_PROJECT}/libcxx \
    -B ${BUILD_PATH}\
    -Wno-dev \
    -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DLIBCXX_ENABLE_STATIC=ON \
    -DLIBCXX_ENABLE_SHARED=ON \
    -DLIBCXX_INCLUDE_TESTS=ON \
    -DLIBCXX_INCLUDE_BENCHMARKS=OFF \
    -DLIBCXX_ENABLE_EXPERIMENTAL_LIBRARY=NO \
    -DLIBCXXABI_USE_LLVM_UNWINDER=ON \
    -DLIBCXX_USE_COMPILER_RT=ON \
    -DLIBCXX_TARGET_TRIPLE=${TRIPLE} \
    -DLIBCXX_HAS_MUSL_LIBC=ON \
    -DLIBCXX_ENABLE_EXCEPTIONS=ON \
    -DLIBCXX_SYSROOT="${SYSROOT}" \
    -DLIBCXX_CXX_ABI="libcxxabi" \
    -DLIBCXX_ENABLE_ABI_LINKER_SCRIPT=OFF \
    -DLIBCXX_INSTALL_INCLUDE_TARGET_DIR="${MORELLO_LLVM_PATH}/include/${TRIPLE}/c++/v1" \
    -DCMAKE_INSTALL_PREFIX=${SYSROOT} \
    -DLIBCXX_TARGET_INFO="libcxx.test.target_info.LinuxLocalTI" \
    -DLIBCXX_TEST_COMPILER_FLAGS="--sysroot=${SYSROOT} ${TFLAGS} -isystem ${BUILD_PATH}/kernel-headers/usr/include" \
    -DLIBCXX_TEST_LINKER_FLAGS="--sysroot=${SYSROOT} -fuse-ld=lld -nostdlib --rtlib=compiler-rt -Wl,--dynamic-linker=${SYSROOT}/lib/libc.so ${SYSROOT}/lib/crt1.o ${SYSROOT}/lib/crti.o ${SYSROOT}/lib/crtn.o" \
    -DLIBCXX_CXX_ABI_LIBRARY_PATH="${SYSROOT}/lib"
    popd
}

# From clang-14 onwards, use a single CMake invocation
# when building libcxx and libcxxabi and libunwind.
function __configure_libruntimes() {
    local LLVM_PROJECT=${1}         # path to LLVM sources
    local MORELLO_LLVM_PATH=${2}    # path where Morello LLVM has been installed
    local BUILD_PATH=${3}           # path to the build folder
    local SYSROOT=${4}              # path to sysroot with the required libc header
    local TRIPLE=${5}               # triple to target
    local KERNEL_BRANCH=${6}        # (optional default: latest) version of kernel headers to download
    if [[ "${TRIPLE}" == "${MORELLO_TRIPLE}" ]]; then
        local TFLAGS="-march=morello -mabi=purecap"
    else
        local TFLAGS="-march=armv8"
    fi
    local LIBUNWIND_HEADERS=${LLVM_PROJECT}/libunwind/include
    local LIBCXX_HEADERS=${MORELLO_LLVM_PATH}/include/c++/v1
    mkdir -p ${BUILD_PATH}
    pushd ${BUILD_PATH}

    __download_kernel_headers "${BUILD_PATH}/" ${KERNEL_BRANCH}
    cat << EOF > toolchain.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_ASM_COMPILER_TARGET "${TRIPLE}")
set(CMAKE_C_COMPILER_TARGET "${TRIPLE}")
set(CMAKE_CXX_COMPILER_TARGET "${TRIPLE}")

set(CMAKE_ASM_COMPILER_WORKS 1 CACHE INTERNAL "")
set(CMAKE_C_COMPILER_WORKS 1 CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER_WORKS 1 CACHE INTERNAL "")

set(CMAKE_ASM_COMPILER "${MORELLO_LLVM_PATH}/bin/clang" CACHE FILEPATH "" FORCE)
set(CMAKE_C_COMPILER "${MORELLO_LLVM_PATH}/bin/clang" CACHE FILEPATH "" FORCE)
set(CMAKE_CXX_COMPILER "${MORELLO_LLVM_PATH}/bin/clang++" CACHE FILEPATH "" FORCE)
set(CMAKE_AR "${MORELLO_LLVM_PATH}/bin/llvm-ar" CACHE FILEPATH "" FORCE)
set(CMAKE_RANLIB "${MORELLO_LLVM_PATH}/bin/llvm-ranlib" CACHE FILEPATH "" FORCE)
set(CMAKE_NM "${MORELLO_LLVM_PATH}/bin/llvm-nm" CACHE FILEPATH "" FORCE)
set(CMAKE_LINKER "${MORELLO_LLVM_PATH}/bin/ld.lld" CACHE FILEPATH "" FORCE)
set(CMAKE_OBJDUMP "${MORELLO_LLVM_PATH}/bin/llvm-objdump" CACHE FILEPATH "" FORCE)
set(CMAKE_OBJCOPY "${MORELLO_LLVM_PATH}/bin/llvm-objcopy" CACHE FILEPATH "" FORCE)

set(LLVM_CONFIG_PATH "${MORELLO_LLVM_PATH}/bin/llvm-config" CACHE FILEPATH "" FORCE)
set(CMAKE_ASM_FLAGS "--sysroot=${SYSROOT} ${TFLAGS} -isystem ${BUILD_PATH}/kernel-headers/usr/include" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS "--sysroot=${SYSROOT} ${TFLAGS} -isystem ${BUILD_PATH}/kernel-headers/usr/include" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "--sysroot=${SYSROOT} ${TFLAGS} -isystem ${BUILD_PATH}/kernel-headers/usr/include" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "-fuse-ld=lld -nostdlib --rtlib=compiler-rt" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS "-fuse-ld=lld -nostdlib --rtlib=compiler-rt" CACHE STRING "" FORCE)
EOF
    cmake -S ${LLVM_PROJECT}/runtimes \
    -B ${BUILD_PATH}\
    -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" \
    -Wno-dev \
    -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DLIBUNWIND_ENABLE_THREADS=ON \
    -DLIBCXX_ENABLE_STATIC=ON \
    -DLIBCXX_ENABLE_SHARED=ON \
    -DLIBCXX_INCLUDE_TESTS=ON \
    -DLIBCXX_INCLUDE_BENCHMARKS=OFF \
    -DLIBCXX_ENABLE_EXPERIMENTAL_LIBRARY=NO \
    -DLIBCXXABI_USE_LLVM_UNWINDER=ON \
    -DLIBUNWIND_USE_COMPILER_RT=ON \
    -DLIBCXXABI_USE_COMPILER_RT=ON \
    -DLIBCXX_USE_COMPILER_RT=ON \
    -DLIBCXXABI_LIBUNWIND_INCLUDES="${LIBUNWIND_HEADERS}" \
    -DLIBCXXABI_LIBUNWIND_PATH="${SYSROOT}/lib" \
    -DLIBCXXABI_LIBCXX_INCLUDES="${LIBCXX_HEADERS}" \
    -DLIBCXX_HAS_MUSL_LIBC=ON \
    -DLIBCXX_ENABLE_EXCEPTIONS=ON \
    -DCMAKE_SYSROOT="${SYSROOT}" \
    -DLIBCXX_CXX_ABI="libcxxabi" \
    -DLIBCXX_ENABLE_ABI_LINKER_SCRIPT=OFF \
    -DLIBCXX_INSTALL_INCLUDE_TARGET_DIR="${MORELLO_LLVM_PATH}/include/${TRIPLE}/c++/v1" \
    -DCMAKE_INSTALL_PREFIX=${SYSROOT} \
    -DLIBCXX_TARGET_INFO="libcxx.test.target_info.LinuxLocalTI" \
    -DLIBCXX_TEST_COMPILER_FLAGS="--sysroot=${SYSROOT} ${TFLAGS} -isystem ${BUILD_PATH}/kernel-headers/usr/include" \
    -DLIBCXX_TEST_LINKER_FLAGS="--sysroot=${SYSROOT} -fuse-ld=lld -nostdlib --rtlib=compiler-rt -Wl,--dynamic-linker=${SYSROOT}/lib/libc.so ${SYSROOT}/lib/crt1.o ${SYSROOT}/lib/crti.o ${SYSROOT}/lib/crtn.o" \
    -DLIBCXX_CXX_ABI_LIBRARY_PATH="${SYSROOT}/lib"
    popd
}

function __download_kernel_headers() {
    local BUILD_PATH=${1}               # folder where kernel headers will be stored
    local BRANCH=${2}                   # branch of kernel headers to download
    local TAR=$(python -c "print('${KERNEL_BRANCH}'.replace('/', '-'))")
    local URL="https://git.morello-project.org/morello/morello-linux-headers/-/archive/$BRANCH/morello-linux-headers-$TAR.tar.gz"
    mkdir -p ${BUILD_PATH}/kernel-headers
    pushd ${BUILD_PATH}
    wget -q ${URL}
    tar -xf morello-linux-headers-$TAR.tar.gz -C kernel-headers --strip-components 1
    rm -rf morello-linux-headers-$TAR.tar.gz
    popd
}

# Environment variables:
#  - LLVM_TARGETS: AArch64 or X86;AArch64
#  - LLVM_LIT_ARGS: LIT args for tests (can be unset or empty)
#  - MORELLO_NPROC: number of parallel jobs (default: 16)
function build_clang() {
    local LLVM_PROJECT=${1}         # path to LLVM sources
    local HOST_LLVM_PATH=${2}       # path to host LLVM (11.0 or newer)
    local MORELLO_LLVM_PATH=${3}    # path to install Morello LLVM
    local BUILD_PATH=${4}           # path to the build folder
    local TPIP_PATH=${MORELLO_LLVM_PATH}/thirdpartylicences
    local -r HOST_LLVM_BIN_PATH=${HOST_LLVM_PATH}/bin
    mkdir -p ${BUILD_PATH}
    pushd ${BUILD_PATH}
    __configure_clang ${LLVM_PROJECT} ${HOST_LLVM_BIN_PATH} ${MORELLO_LLVM_PATH}
    make -j${MORELLO_NPROC:-16}
    make install
    popd
    mkdir -p ${TPIP_PATH}
    declare -a files=(
        llvm/LICENSE.TXT,LLVM-LICENSE.TXT
        clang/LICENSE.TXT,CLANG-LICENSE.TXT
        lldb/LICENSE.TXT,LLDB-LICENSE.TXT
        lld/LICENSE.TXT,LLD-LICENSE.TXT
        libcxx/LICENSE.TXT,LIBCXX-LICENSE.TXT
        libcxxabi/LICENSE.TXT,LIBCXXABI-LICENSE.TXT
        libunwind/LICENSE.TXT,LIBUNWIND-LICENSE.TXT
        compiler-rt/LICENSE.TXT,COMPILER-RT-LICENSE.TXT
        libclc/LICENSE.TXT,LIBCLC-LICENSE.TXT
        openmp/LICENSE.TXT,OPENMP-LICENSE.TXT
        parallel-libs/acxxel/LICENSE.TXT,PARALLEL-LIBS-ACXXEL-LICENSE.TXT
        polly/LICENSE.TXT,POLLY-LICENSE.TXT
        pstl/LICENSE.TXT,PSTL-LICENSE.TXT
        clang-tools-extra/LICENSE.TXT,CLANG-TOOLS-EXTRA-LICENSE.TXT
    )
    for t in ${files[@]}; do
        IFS="," read src dst <<< "${t}"
        if [ -f "${LLVM_PROJECT}/${src}" ]; then
            cp ${LLVM_PROJECT}/${src} ${TPIP_PATH}/${dst}
        fi
    done
}

# Environment variables:
#  - LD_LIBRARY_PATH: path to the `lib` folder in the LLVM build directory
#  - MORELLO_NPROC: number of parallel jobs (default: 16)
function build_clang_test() {
    local BUILD_PATH=${1}           # path to the LLVM build folder
    pushd ${BUILD_PATH}
    make -j${MORELLO_NPROC:-16} UnitTests
    make check-llvm
    popd
}

# Environment variables:
#  - CC: path to Morello clang
function build_musl_headers() {
    local MUSL_PATH=${1}            # path to Musl sources
    local PREFIX_PATH=${2}          # where to install Musl headers
    local TRIPLE=${3}               # target triple
    if [[ "${TRIPLE}" == "${MORELLO_TRIPLE}" ]]; then
        local CFGFLAGS="--enable-morello --disable-shared"
    else
        local CFGFLAGS="--disable-morello --disable-shared"
    fi
    rm -rf ${PREFIX_PATH}
    pushd ${MUSL_PATH}
    make distclean
    ./configure ${CFGFLAGS} --prefix=${PREFIX_PATH} --target=${TRIPLE}
    make install-headers
    popd
}

# Environment variables:
#  - CC: path to Morello clang
function build_crt() {
    local LLVM_PROJECT=${1}         # path to LLVM sources
    local SYSROOT=${2}              # path to sysroot with the required libc headers
    local TRIPLE=${3}               # expanded target triple
    local CRT=${LLVM_PROJECT}/compiler-rt/lib/crt
    local DESTDIR=$(${CC} -print-resource-dir)/lib/${TRIPLE}
    local INCLUDE=${SYSROOT}/include
    if [[ "${TRIPLE}" == "${MORELLO_TRIPLE}" ]]; then
        local XFLAGS="--target=${TRIPLE} -march=morello -mabi=purecap -nostdinc -isystem ${INCLUDE}"
    else
        local XFLAGS="--target=${TRIPLE} -nostdinc -isystem ${INCLUDE}"
    fi
    mkdir -p ${DESTDIR}
    ${CC} ${XFLAGS} -c ${CRT}/crtbegin.c -o ${DESTDIR}/clang_rt.crtbegin.o
    ${CC} ${XFLAGS} -c ${CRT}/crtend.c -o ${DESTDIR}/clang_rt.crtend.o
}

# Environment variables:
#  - MORELLO_NPROC: number of parallel jobs (default: 4)
function build_compiler_rt() {
    local LLVM_PROJECT=${1}         # path to LLVM sources
    local MORELLO_LLVM_PATH=${2}    # path where Morello LLVM has been installed
    local BUILD_PATH=${3}           # path to the build folder
    local SYSROOT=${4}              # path to sysroot with the required libc headers
    local TRIPLE=${5}               # expanded target triple
    local DESTDIR=$(${MORELLO_LLVM_PATH}/bin/clang -print-resource-dir)/lib/${TRIPLE}
    rm -rf ${BUILD_PATH}
    __configure_comp_rt ${LLVM_PROJECT} ${MORELLO_LLVM_PATH} ${BUILD_PATH} ${SYSROOT} ${TRIPLE}
    pushd ${BUILD_PATH}
    make -j ${MORELLO_NPROC:-4} clang_rt.builtins-aarch64
    mkdir -p ${DESTDIR}
    cp lib/linux/libclang_rt.builtins-aarch64.a ${DESTDIR}/libclang_rt.builtins.a
    popd
}

# Environment variables:
#  - CC: path to Morello clang
#  - MORELLO_NPROC: number of parallel jobs (default: 8)
function build_musl() {
    local MUSL_PATH=${1}            # path to Musl sources
    local PREFIX_PATH=${2}          # where to install Musl
    local TRIPLE=${4:-${3}}         # target triple
    if [[ "${TRIPLE}" == "${MORELLO_TRIPLE}" ]]; then
        local CFGFLAGS="--enable-morello"
    else
        local CFGFLAGS="--disable-morello"
    fi
    rm -rf ${PREFIX_PATH}
    pushd ${MUSL_PATH}
    make distclean
    ./configure --prefix=${PREFIX_PATH} --target=${TRIPLE} ${CFGFLAGS} --enable-debug
    make -j${MORELLO_NPROC:-8}
    make install
    mkdir -p ${PREFIX_PATH}/share
    cp COPYRIGHT ${PREFIX_PATH}/share/MUSL-LICENSE.txt
    wget -q https://www.apache.org/licenses/LICENSE-2.0.txt -O ${PREFIX_PATH}/LICENSE.txt
    cat << EOF > ${PREFIX_PATH}/NOTICE.txt
This product embeds and uses the following pieces of software
which have additional or alternate licenses:
 - Musl libc: share/MUSL-LICENSE.txt
EOF
    popd
}

# Environment variables:
#  - MORELLO_NPROC: number of parallel jobs (default: 4)
function build_libunwind() {
    local LLVM_PROJECT=${1}         # path to LLVM sources
    local MORELLO_LLVM_PATH=${2}    # path where Morello LLVM has been installed
    local BUILD_PATH=${3}           # path to the build folder
    local SYSROOT=${4}              # path to sysroot with the required libc headers
    local TRIPLE=${5}               # triple to target
    rm -rf ${BUILD_PATH}
    __configure_libunwind ${LLVM_PROJECT} ${MORELLO_LLVM_PATH} ${BUILD_PATH} ${SYSROOT} ${TRIPLE}
    pushd ${BUILD_PATH}
    make -j${MORELLO_NPROC:-4}
    make install
    popd
}

# Environment variables:
#  - MORELLO_NPROC: number of parallel jobs (default: 4)
function build_libcxxabi() {
    local LLVM_PROJECT=${1}         # path to LLVM sources
    local MORELLO_LLVM_PATH=${2}    # path where Morello LLVM has been installed
    local BUILD_PATH=${3}           # path to the build folder
    local SYSROOT=${4}              # path to sysroot with the required libc headers
    local TRIPLE=${5}               # triple to target
    rm -rf ${BUILD_PATH}
    __configure_libcxxabi ${LLVM_PROJECT} ${MORELLO_LLVM_PATH} ${BUILD_PATH} ${SYSROOT} ${TRIPLE}
    pushd ${BUILD_PATH}
    make -j${MORELLO_NPROC:-4}
    make install
    popd
}

# Environment variables:
#  - MORELLO_NPROC: number of parallel jobs (default: 4)
function build_libcxx() {
    local LLVM_PROJECT=${1}                      # path to LLVM sources
    local MORELLO_LLVM_PATH=${2}                 # path where Morello LLVM has been installed
    local BUILD_PATH=${3}                        # path to the build folder
    local SYSROOT=${4}                           # path to sysroot with the required libc headers
    local TRIPLE=${5}                            # triple to target
    local KERNEL_BRANCH=${6:-"morello/master"}   # (optional default: latest) version of kernel headers to download
    local TARGET_INCLUDE_PATH=${MORELLO_LLVM_PATH}/include/${TRIPLE}/c++/v1
    rm -rf ${BUILD_PATH}
    mkdir -p ${TARGET_INCLUDE_PATH}
    __configure_libcxx ${LLVM_PROJECT} ${MORELLO_LLVM_PATH} ${BUILD_PATH} ${SYSROOT} ${TRIPLE} ${KERNEL_BRANCH}
    pushd ${BUILD_PATH}
    make -j${MORELLO_NPROC:-4}
    make install
    popd
}

# Environment variables:
#  - MORELLO_NPROC: number of parallel jobs (default: 4)
function build_libruntimes() {
    local LLVM_PROJECT=${1}                      # path to LLVM sources
    local MORELLO_LLVM_PATH=${2}                 # path where Morello LLVM has been installed
    local BUILD_PATH=${3}                        # path to the build folder
    local SYSROOT=${4}                           # path to sysroot with the required libc headers
    local TRIPLE=${5}                            # triple to target
    local KERNEL_BRANCH=${6:-"morello/master"}   # (optional default: latest) version of kernel headers to download
    local TARGET_INCLUDE_PATH=${MORELLO_LLVM_PATH}/include/${TRIPLE}/c++/v1
    rm -rf ${BUILD_PATH}
    mkdir -p ${TARGET_INCLUDE_PATH}
    __configure_libruntimes ${LLVM_PROJECT} ${MORELLO_LLVM_PATH} ${BUILD_PATH} ${SYSROOT} ${TRIPLE} ${KERNEL_BRANCH}
    pushd ${BUILD_PATH}
    make -j${MORELLO_NPROC:-4}
    make install
    popd
}

# Environment variables:
#  - TEST_DRIVER: path to the test driver script or Morello IE
#  - CC: path to Morello clang (when libc-test tests are used)
#  - MORELLO_NPROC: number of parallel jobs (default: 8)
function build_musl_test() {
    local MUSL_PATH=${1}            # path to Musl sources
    local PREFIX_PATH=${2}          # where Musl has been installed
    local TRIPLE=${3}               # target triple
    local SKIP_TEST_RUN=${5:-${4:-NO}} # whether to skip running tests
    if [[ "${TRIPLE}" == "${MORELLO_TRIPLE}" ]]; then  # these tests are only for Morello
        local ARCHFLAGS=${ARCHFLAGS:--march=morello}
        local CFGFLAGS="--enable-morello"
        pushd ${MUSL_PATH}
        make distclean
        ./configure --prefix=${PREFIX_PATH} --target=${TRIPLE} ${CFGFLAGS}
        make -C test build -j${MORELLO_NPROC:-8}
        if [[ "${SKIP_TEST_RUN}" == "NO" ]]; then
            make -k -C test test
        fi
        popd
    fi
}

# Environment variables:
#  - TEST_DRIVER: path to the test driver script or Morello IE
#  - TEST_RUNNER: path to the runner.py script in the Musl repository
#  - CC: path to Morello clang (when libc-test tests are used)
#  - MORELLO_NPROC: number of parallel jobs (default: 8)
function build_libc_test() {
    local PREFIX_PATH=${1}          # where Musl has been installed
    local TRIPLE=${2}               # target triple
    local LIBC_TEST_PATH=${3}       # path to libc-test suite sources
    local SKIP_TEST_RUN=${4:-NO}    # whether to skip running tests
    if [[ "${TRIPLE}" == "${MORELLO_TRIPLE}" ]]; then
        local ARCHFLAGS=${ARCHFLAGS:--march=morello}
    else
        local ARCHFLAGS=${ARCHFLAGS:--march=armv8-a}
    fi
    pushd ${LIBC_TEST_PATH}
    make clean
    make -j${MORELLO_NPROC:-8} build \
        SYSROOT=${PREFIX_PATH} TRIPLE=${TRIPLE} ARCHFLAGS=${ARCHFLAGS} MORELLO_STATIC_CFLAGS="-Wl,--local-caprelocs=elf"
    if [[ "${SKIP_TEST_RUN}" == "NO" ]]; then
        make -k run SYSROOT=${PREFIX_PATH} TRIPLE=${TRIPLE} ARCHFLAGS=${ARCHFLAGS}
    fi
    popd
}

function build_package() {
    local MORELLO_LLVM_PATH=${1}    # path where Morello LLVM has been installed
    local BUNDLE=${2}               # name of the tarball
    local CWD=$(pwd)
    local PDIR=$(dirname ${MORELLO_LLVM_PATH})
    local PNAME=$(basename ${MORELLO_LLVM_PATH})
    local TPIP_PATH=${MORELLO_LLVM_PATH}/thirdpartylicences
    wget -q https://www.apache.org/licenses/LICENSE-2.0.txt -O ${MORELLO_LLVM_PATH}/LICENSE.txt
    cat << EOF > ${MORELLO_LLVM_PATH}/NOTICE.txt
This product embeds and uses the following pieces of software which have
additional or alternate licenses:
EOF
    declare -a files=(
        LLVM,LLVM-LICENSE.TXT
        Clang,CLANG-LICENSE.TXT
        lldb,LLDB-LICENSE.TXT
        lld,LLD-LICENSE.TXT
        libc++,LIBCXX-LICENSE.TXT
        libc++abi,LIBCXXABI-LICENSE.TXT
        libunwind,LIBUNWIND-LICENSE.TXT
        libclc,LIBCLC-LICENSE.TXT
        openmp,OPENMP-LICENSE.TXT
        parallel-libs,PARALLEL-LIBS-ACXXEL-LICENSE.TXT
        polly,POLLY-LICENSE.TXT
        pstl,PSTL-LICENSE.TXT
        clang-tools-extra,CLANG-TOOLS-EXTRA-LICENSE.TXT
        compiler-rt,COMPILER-RT-LICENSE.TXT
    )
    for t in ${files[@]}; do
        IFS="," read name file <<< "${t}"
        if [ -f "${TPIP_PATH}/${file}" ]; then
            echo " - ${name}: ${file}" >> ${MORELLO_LLVM_PATH}/NOTICE.txt
        fi
    done
    pushd ${PDIR}
    tar --transform 's|^'${PNAME}'|'${BUNDLE}'|' -czf ${CWD}/${BUNDLE}-clang.tar.gz ${PNAME}
    popd
}

function build_package_sysroot() {
    local LLVM_PROJECT=${1}         # path to LLVM sources
    local SYSROOT_PATH=${2}         # path to the sysroot folder
    local BUNDLE=${3}               # name of the tarball
    local CWD=$(pwd)
    local PDIR=$(dirname ${SYSROOT_PATH})
    local PNAME=$(basename ${SYSROOT_PATH})
    declare -a files=(
        libc++,libcxx/LICENSE.TXT,LIBCXX-LICENSE.TXT
        libc++abi,libcxxabi/LICENSE.TXT,LIBCXXABI-LICENSE.TXT
        libunwind,libunwind/LICENSE.TXT,LIBUNWIND-LICENSE.TXT
    )
    for t in ${files[@]}; do
        IFS="," read name src dst <<< "${t}"
        if [ -f "${LLVM_PROJECT}/${src}" ]; then
            cp ${LLVM_PROJECT}/${src} ${SYSROOT_PATH}/share/${dst}
            echo " - ${name}: share/${dst}" >> ${SYSROOT_PATH}/NOTICE.txt
        fi
    done
    pushd ${PDIR}
    tar --transform 's|^'${PNAME}'|'${BUNDLE}'|' -czf ${CWD}/${BUNDLE}.tar.gz ${PNAME}
    popd
}

case ${STAGE} in
  clang)
      build_clang ${@:2};
      exit 0;
      ;;
  clang-test)
      build_clang_test ${@:2};
      exit 0;
      ;;
  musl-headers)
      build_musl_headers ${@:2};
      exit 0;
      ;;
  crt)
      build_crt ${@:2};
      exit 0;
      ;;
  compiler-rt)
      build_compiler_rt ${@:2};
      exit 0;
      ;;
  musl)
      build_musl ${@:2};
      exit 0;
      ;;
  libunwind)
      build_libunwind ${@:2};
      exit 0;
      ;;
  libcxxabi)
      build_libcxxabi ${@:2};
      exit 0;
      ;;
  libcxx)
      build_libcxx ${@:2};
      exit 0;
      ;;
  libruntimes)
      build_libruntimes ${@:2};
      exit 0;
      ;;
  musl-test)
      build_musl_test ${@:2};
      exit 0;
      ;;
  libc-test)
      build_libc_test ${@:2};
      exit 0;
      ;;
  package)
      build_package ${@:2};
      exit 0;
      ;;
  package-sysroot)
      build_package_sysroot ${@:2};
      exit 0;
      ;;

  *)
      echo "Unknown stage ${STAGE}"
      exit 1
      ;;
esac
