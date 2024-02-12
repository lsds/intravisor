MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)

LIBOS_PATH := ../..

CFLAGS=-fPIC -fPIE -pie -g -O2  -nostdinc \
	$(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_PURE) -B$(CROSS_COMPILE) $(ARCH_PURE) \
	-DSQLITE_OMIT_LOAD_EXTENSION -DSQLITE_THREADSAFE=0  -DSQLITE_OMIT_FLOATING_POINT=1 -DSQLITE_OMIT_DEPRECATED=1 -DSQLITE_OMIT_RANDOMNESS=1 -DSQLITE_OS_UNIX=1 \
	 -I $(LIBOS_PATH)/musl-host/include  -I.\
	

DEPS = 
OBJDIR = obj
SRC = main.c sqlite3.c speedtest1.c

OBJ := $(SRC:%.c=$(OBJDIR)/%.o)


default: libsqlite.so


$(OBJDIR)/%.o: %.c $(DEPS) $(PASS1) $(PASS2) 
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS)


libsqlite.so: $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ) $(LD_FLAGS) $(LIBOS_PATH)/libmusl-uni.a

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR)

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.so ./*.ci ${INSTALL_PATH}
