ROOT_DIR ?= $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

include ../../config.mak

DISTRO=$(shell lsb_release -si)
#TODO: use autoconf or auto detect


FORCE_SUBMODULES_VERSION ?= false


BUILD_DIR ?= $(ROOT_DIR)/build

LINUX_HEADERS_INC ?= $(ROOT_DIR)/tools/lkl_musl_headers

TESTS ?= $(ROOT_DIR)/tests
TESTS_BUILD ?= $(BUILD_DIR)/tests
TESTS_SRC ?= $(sort $(wildcard $(TESTS)/*.c))
TESTS_OBJ ?= $(addprefix $(TESTS_BUILD)/, $(notdir $(TESTS_SRC:.c=)))

TOOLS ?= ${ROOT_DIR}/tools
TOOLS_BUILD ?= $(BUILD_DIR)/tools
TOOLS_SRC ?= $(wildcard $(TOOLS)/*.c)
TOOLS_OBJ ?= $(addprefix $(TOOLS_BUILD)/, $(notdir $(TOOLS_SRC:.c=)))

DEVICEMAPPER ?= ${ROOT_DIR}/third_party/devicemapper
UTILLINUX ?= ${ROOT_DIR}/third_party/util-linux
POPT ?= ${ROOT_DIR}/third_party/popt
JSONC ?= ${ROOT_DIR}/third_party/json-c

LKL ?= $(ROOT_DIR)/lkl
LKL_BUILD ?= ${BUILD_DIR}/lkl
LIBLKL ?= ${LKL_BUILD}/lib/liblkl.a

HOST_MUSL ?= $(ROOT_DIR)/musl-host
HOST_MUSL_BUILD ?= $(BUILD_DIR)/musl-host
HOST_MUSL_CC ?= ${HOST_MUSL_BUILD}/bin/musl-clang

CLANG_LD_EXTRA_FLAGS="$(CC_SYSROOT)"
CLANG_EXTRA_FLAGS="$(CC_FLAGS)"

TARGET_LKL_MUSL ?= $(ROOT_DIR)/musl-target
TARGET_LKL_MUSL_BUILD ?= ${BUILD_DIR}/musl-target
# Headers not exported by LKL and built by a custom tool's output cat to the file instead
TARGET_LKL_MUSL_HEADERS ?= ${LKL_BUILD}/include/lkl/bits.h ${LKL_BUILD}/include/lkl/syscalls.h

HOST_TOOLS_CFLAGS ?= -std=c11 -Wall -Werror -isystem ${TARGET_LKL_MUSL}/src/internal/ -DLKL_HOST_CONFIG_VIRTIO_NET=y -DLKL_HOST_CONFIG_POSIX=y -DOPENSSL_EXTRA

MUSL_CONFIGURE_OPTS ?=
MUSL_CFLAGS ?= -fPIC -D__USE_GNU ${CC_FLAGS}
#MUSL_CFLAGS ?= -fPIC -D__USE_GNU -fPIE -mno-relax -g -mno-relax 
#-fno-stack-protector

LKL_CFLAGS ?=-I${LKL_BUILD}/include/

