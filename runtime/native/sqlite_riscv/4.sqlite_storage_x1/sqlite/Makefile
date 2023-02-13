include ../../../../../config.mak

CFLAGS=-fPIC -fPIE -pie -g -O2 -DSQLITE_OMIT_LOAD_EXTENSION -DSQLITE_THREADSAFE=0  -DSQLITE_OMIT_FLOATING_POINT=1 -DSQLITE_OMIT_DEPRECATED=1 -DSQLITE_OMIT_RANDOMNESS=1 -DSQLITE_OS_UNIX=1 -nostdinc \
	-I musl-host/include -I cheri-libc/include \
	$(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_PURE) -B$(CROSS_COMPILE) $(ARCH_PURE) \
	-Wno-unused-command-line-argument -Werror=implicit-function-declaration -Werror=format -Werror=incompatible-pointer-types -Werror=cheri-capability-misuse -Werror=cheri-bitwise-operations -Werror=cheri-prototypes -Werror=pass-failed -Werror=undefined-internal -Wno-error=cheri-capability-misuse \
	-Iunikraft/vfscore/include \
	-I musl-host/include


#	-I nolibc/include 
		

ifneq ($(MODE),sim)
endif

DEPS = 
OBJDIR = obj
SRC = main.c tramps.c hostcalls.c nolibc_printf.c nolibc_file.c  nolibc_strings.c dlmalloc_nonreuse.c sqlite3.c speedtest1.c
SRC += unikraft/vfscore/main.c unikraft/vfscore/fd.c unikraft/vfscore/rootfs.c unikraft/vfscore/task.c unikraft/vfscore/vnode.c  unikraft/vfscore/dentry.c unikraft/vfscore/file.c unikraft/vfscore/subr_uio.c unikraft/vfscore/fops.c unikraft/vfscore/lookup.c unikraft/vfscore/mount.c unikraft/vfscore/syscalls.c
SRC += unikraft/ramfs/ramfs_vnops.c unikraft/ramfs/ramfs_vfsops.c 
OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

default: libsco_libos.so


#%.o: %.c $(DEPS) 
$(OBJDIR)/%.o: %.c $(DEPS) 
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	@$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	@$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS) 

$(OBJDIR)/tramps.o: tramps.S
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -c -o $(OBJDIR)/tramps.o tramps.S

libsco_libos.so: $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ)

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR)

