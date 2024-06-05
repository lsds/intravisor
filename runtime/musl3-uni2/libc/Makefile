MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)

SUBDIR := musl-libc
BUILD_DIR := build
# Default target
.PHONY: all
all: configure build

# Configure target
.PHONY: configure
configure:
	@echo "Running ./configure in $(SUBDIR)"
	cd $(SUBDIR) && LIBCC=" " CC=$(CC) CFLAGS="-DINTRAVISOR" ./configure --enable-morello --prefix=../$(BUILD_DIR) --target=aarch64-linux-musl_purecap --enable-wrapper=clang --enable-wrapper=gcc --with-malloc=dlmalloc

# Build target
#this is not real install
.PHONY: build
build:
	@echo "Running make in $(SUBDIR)"
	cd $(SUBDIR) && $(MAKE) install

#
.PHONY: install
install:
	@echo "Running make in $(SUBDIR)"
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./$(BUILD_DIR)/lib/libc.so ${INSTALL_PATH}/libldso.so


# Clean target
.PHONY: clean
clean:
	@echo "Running make clean in $(SUBDIR)"
	cd $(SUBDIR) && $(MAKE) distclean
	rm -rf $(BUILD_DIR)

# Phony target to clean and build
.PHONY: rebuild
rebuild: clean all