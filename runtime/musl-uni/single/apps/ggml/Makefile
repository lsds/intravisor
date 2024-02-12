MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)

LIBOS_PATH := ../..

CFLAGS=-fPIC -fPIE -pie -g -O2  -nostdinc \
	$(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_PURE) -B$(CROSS_COMPILE) $(ARCH_PURE) \
	 -I $(LIBOS_PATH)/musl-host/include  -I.\
	-Iggml/include/ggml -Iggml/scr/ -Iggml/include/ -Iggml/examples/ \


#	-Icheri-libc++/include -D_LIBCPP_PROVIDES_DEFAULT_RUNE_TABLE -D_LIBCPP_HAS_MUSL_LIBC -D_LIBCPP_BUILDING_LIBRARY -D_LIBCPP_HAS_NO_THREADS -D_LIBCPP_STD_VER=11 	-D_LIBCPP_NO_EXCEPTIONS -fno-threadsafe-statics

URL_PREFIX = https://huggingface.co/ggerganov/ggml/resolve/main/ggml-model-gpt-2-117M.bin
WEIGHTS = ggml-model.bin
CPIO = root_ggml.cpio

DEPS = 
OBJDIR = obj
SRC = main.c

SRC += ggml/src/ggml-alloc.c ggml/src/ggml.c 
SRC_CPP = ggml/examples/gpt-2/main.cpp ggml/examples/common.cpp 

CFLAGS += -Illvm/libcxx/build/include/c++/v1/ -D_LIBCPP_PROVIDES_DEFAULT_RUNE_TABLE -D_LIBCPP_HAS_MUSL_LIBC -D_LIBCPP_BUILDING_LIBRARY -D_LIBCPP_HAS_NO_THREADS -D_LIBCPP_STD_VER=11 	-D_LIBCPP_NO_EXCEPTIONS -fno-threadsafe-statics
CFLAGS += -D_LIBCPP_USING_IF_EXISTS="__attribute__((using_if_exists))"

SRC_CPP += llvm/libcxx/src/algorithm.cpp
SRC_CPP += llvm/libcxx/src/algorithm.cpp
SRC_CPP += llvm/libcxx/src/any.cpp
SRC_CPP += llvm/libcxx/src/atomic.cpp
SRC_CPP += llvm/libcxx/src/barrier.cpp
SRC_CPP += llvm/libcxx/src/bind.cpp
SRC_CPP += llvm/libcxx/src/charconv.cpp
SRC_CPP += llvm/libcxx/src/chrono.cpp
SRC_CPP += llvm/libcxx/src/condition_variable.cpp
SRC_CPP += llvm/libcxx/src/condition_variable_destructor.cpp
SRC_CPP += llvm/libcxx/src/debug.cpp
SRC_CPP += llvm/libcxx/src/exception.cpp
SRC_CPP += llvm/libcxx/src/experimental/memory_resource.cpp
SRC_CPP += llvm/libcxx/src/filesystem/directory_iterator.cpp
SRC_CPP += llvm/libcxx/src/filesystem/int128_builtins.cpp
SRC_CPP += llvm/libcxx/src/filesystem/operations.cpp
SRC_CPP += llvm/libcxx/src/format.cpp
SRC_CPP += llvm/libcxx/src/functional.cpp
SRC_CPP += llvm/libcxx/src/future.cpp
SRC_CPP += llvm/libcxx/src/hash.cpp
SRC_CPP += llvm/libcxx/src/ios.cpp
SRC_CPP += llvm/libcxx/src/ios.instantiations.cpp
SRC_CPP += llvm/libcxx/src/iostream.cpp
SRC_CPP += llvm/libcxx/src/locale.cpp
SRC_CPP += llvm/libcxx/src/memory.cpp
SRC_CPP += llvm/libcxx/src/mutex.cpp
SRC_CPP += llvm/libcxx/src/mutex_destructor.cpp
SRC_CPP += llvm/libcxx/src/new.cpp
SRC_CPP += llvm/libcxx/src/optional.cpp
SRC_CPP += llvm/libcxx/src/random.cpp
SRC_CPP += llvm/libcxx/src/random_shuffle.cpp
SRC_CPP += llvm/libcxx/src/regex.cpp
SRC_CPP += llvm/libcxx/src/shared_mutex.cpp
SRC_CPP += llvm/libcxx/src/stdexcept.cpp
SRC_CPP += llvm/libcxx/src/string.cpp
SRC_CPP += llvm/libcxx/src/strstream.cpp
SRC_CPP += llvm/libcxx/src/system_error.cpp
SRC_CPP += llvm/libcxx/src/thread.cpp
SRC_CPP += llvm/libcxx/src/typeinfo.cpp
SRC_CPP += llvm/libcxx/src/utility.cpp
SRC_CPP += llvm/libcxx/src/valarray.cpp
SRC_CPP += llvm/libcxx/src/variant.cpp
SRC_CPP += llvm/libcxx/src/vector.cpp

CFLAGS += -Illvm/libcxxabi/include/
SRC_CPP += llvm/libcxxabi/src/private_typeinfo.cpp


OBJ_C := $(SRC:%.c=$(OBJDIR)/%.o) 
OBJ_CPP := $(SRC_CPP:%.cpp=$(OBJDIR)/%.o) 
OBJ_CC := $(SRC_CC:%.cc=$(OBJDIR)/%.o) 


default: libggml.so

$(WEIGHTS):
	@for file in $(WEIGHTS); do \
		if [ ! -f rootfs/$$file ]; then \
			echo "Downloading $$file"; \
			curl -L --output rootfs/$$file $(URL_PREFIX); \
		else \
			echo "$$file already exists"; \
		fi \
	done


$(OBJDIR)/%.o: %.c $(DEPS) $(PASS1) $(PASS2) 
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $< $(CFLAGS)

$(OBJDIR)/%.o: %.cpp $(DEPS) $(PASS1) $(PASS2) 
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CPP_CHERI_PURE) $(CPP_CHERI_PURE_FLAGS) -c -o $(basename $@).o $< $(CFLAGS)

$(OBJDIR)/%.o: %.cc $(DEPS) $(PASS1) $(PASS2) 
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CPP_CHERI_PURE) $(CPP_CHERI_PURE_FLAGS) -c -o $(basename $@).o $< $(CFLAGS)



$(CPIO): $(WEIGHTS)
	cd rootfs && find . -print -depth | cpio -vo -H newc > ../$(CPIO)

libggml.so: $(OBJ_C) $(OBJ_CC) $(OBJ_CPP)  $(CPIO)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ_C)  $(OBJ_CC) $(OBJ_CPP) $(LD_FLAGS) $(LIBOS_PATH)/libmusl-uni.a -Wl,-error-limit=0 

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR)

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.so ./*.cpio ./*.ci ${INSTALL_PATH}
