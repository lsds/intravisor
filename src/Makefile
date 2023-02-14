#todo: track changes in headers
#include ../config_arm.mak
include ../config_riscv.mak

CFLAGS	:= -I load_elf/ -I lkl_wrap -I libyaml/include -Ilibyaml/src -DHAVE_CONFIG_H -Ilibyaml/ -Iarch/$(TARGET_ARCH)/include -DTARGET_ARCH="$(TARGET_ARCH)" -D$(TARGET_ARCH) -DCVM_MAX_SIZE=$(CONFIG_CVM_MAX_SIZE)

#CFLAGS += -DEVAL
#CFLAGS += -DSCO
#CFLAGS += -DEXTRA_PAYLOAD="(100*1024*1024)"
CFLAGS += -DEXTRA_PAYLOAD="(0)"

ifdef CONFIG_LKL
CFILES	+= lkl_wrap/iomem.c lkl_wrap/jmp_buf.c lkl_wrap/posix-host.c lkl_wrap/virtio_net_fd.c
CFLAGS	+= -I lkl_wrap/include -DLKL
endif

ifdef CONFIG_SIM
CFLAGS	+= -DSIM
endif

DEPS = 
OBJDIR = obj
SRC_MAIN := hostcalls.c main.c utils.c host_cap_calls.c host_cap_files.c host_syscall_callbacs.c host_sc.c
SRC_YAML := libyaml/src/api.c libyaml/src/dumper.c libyaml/src/emitter.c libyaml/src/loader.c libyaml/src/parser.c libyaml/src/reader.c libyaml/src/scanner.c libyaml/src/writer.c libyaml/intra_parser.c libyaml/intravisor.c
SRC_LOADER := load_elf/load_elf.c

SRC  := $(CFILES) $(SRC_MAIN) $(SRC_LOADER) $(SRC_YAML)

OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

default: intravisor

$(OBJDIR)/%.o: %.c $(DEPS)
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_MON) $(CC_MON_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_MON) $(CC_MON_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS) 

ASFILES := arch/$(TARGET_ARCH)/asm.S

$(OBJDIR)/$(TARGET_ARCH)/asm.o: arch/$(TARGET_ARCH)/asm.S
	@mkdir -p '$(@D)'
	$(AS_MON) $(AS_MON_FLAGS) $(CFLAGS) -c -o $(OBJDIR)/$(TARGET_ARCH)/asm.o arch/$(TARGET_ARCH)/asm.S

intravisor: $(OBJ) $(OBJDIR)/$(TARGET_ARCH)/asm.o
	$(CC_MON) $(CC_MON_FLAGS) -lrt -lpthread -o $@ -fPIE -fPIC $(OBJ) $(OBJDIR)/$(TARGET_ARCH)/asm.o

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR) intravisor

