#todo: track changes in headers
include ../cfg.mak

CFLAGS	:= -I load_elf/ -I lkl_wrap -I libyaml/include -Ilibyaml/src -DHAVE_CONFIG_H -Ilibyaml/ -Iarch/$(TARGET_ARCH)/include -DTARGET_ARCH="$(TARGET_ARCH)" -D$(TARGET_ARCH) -DCVM_MAX_SIZE=$(CONFIG_CVM_MAX_SIZE)
LDFLAGS = -lrt -lpthread -lm

#CFLAGS += -DEVAL
#CFLAGS += -DEXTRA_PAYLOAD="(100*1024*1024)"
CFLAGS += -DEXTRA_PAYLOAD="(0)"


ifdef CONFIG_ORC
CFLAGS += -DSCO
endif

ifdef CONFIG_LKL
CFILES	+= lkl_wrap/iomem.c lkl_wrap/jmp_buf.c lkl_wrap/posix-host.c lkl_wrap/virtio_net_fd.c
CFLAGS	+= -I lkl_wrap/include -DLKL
endif

ifdef CONFIG_UNDERVISOR
CFLAGS	+= -DUNDERVISOR
endif


ifdef CONFIG_MODE_SIM
CFLAGS	+= -DMODE_SIM -DSIM
endif

ifdef CONFIG_MODE_PURE
CFLAGS	+= -DMODE_PURE
endif

ifdef CONFIG_MODE_HYB
CFLAGS	+= -DMODE_HYB
endif


DEPS = 
OBJDIR = obj
SRC_MAIN := hostcalls.c main.c utils.c host_cap_calls.c host_cap_files.c host_syscall_callbacs.c host_sc.c
SRC_YAML := libyaml/src/api.c libyaml/src/dumper.c libyaml/src/emitter.c libyaml/src/loader.c libyaml/src/parser.c libyaml/src/reader.c libyaml/src/scanner.c libyaml/src/writer.c libyaml/intra_parser.c libyaml/intravisor.c
SRC_LIBVIRT :=
SRC_LOADER := load_elf/load_elf.c

ifdef CONFIG_LIBVIRT
SRC_LIBVIRT += libvirt/src/uml/uml_conf.c libvirt/src/uml/uml_driver.c 
SRC_LIBVIRT += libvirt/src/remote/remote_daemon.c libvirt/src/remote/remote_daemon_config.c libvirt/src/remote/remote_daemon_dispatch.c libvirt/src/remote/remote_protocol.c libvirt/src/remote/remote_daemon_stream.c
SRC_LIBVIRT += $(wildcard libvirt/src/util/*.c)
SRC_LIBVIRT += $(wildcard libvirt/src/conf/*.c)
SRC_LIBVIRT += $(wildcard libvirt/src/access/*.c)
SRC_LIBVIRT += $(wildcard libvirt/src/rpc/*.c)
SRC_LIBVIRT += $(wildcard libvirt/src/*.c)


SRC_LIBVIRT += $(wildcard libvirt/libxml2/*.c)
SRC_LIBVIRT += libvirt/gnulib/lib/nonblocking.c libvirt/gnulib/lib/areadlink.c libvirt/gnulib/lib/dirname-lgpl.c libvirt/gnulib/lib/secure_getenv.c libvirt/gnulib/lib/mgetgroups.c libvirt/gnulib/lib/getugroups.c libvirt/gnulib/lib/basename-lgpl.c libvirt/gnulib/lib/careadlinkat.c libvirt/gnulib/lib/allocator.c libvirt/gnulib/lib/base64.c

CFLAGS	+= -Ilibvirt -Ilibvirt/include -Ilibvirt/src/util -Ilibvirt/gnulib/lib -Ilibvirt/libxml2/include -Ilibvirt/src -Ilibvirt/src/conf/ -Ilibvirt/libxml2/include -Ilibvirt/src/access -Ilibvirt/src/remote
CFLAGS += -Ilibvirt/src/rpc
CFLAGS += -DLIBVIRT -DHOST_NAME_MAX=1024 -Dabs_topbuilddir=\"/\" -Dabs_topsrcdir=\"/\"
endif

ifdef CONFIG_OPENSSL
CFLAGS += -DCONFIG_OPENSSL
LDFLAGS += -lssl -lcrypto
endif

SRC  := $(CFILES) $(SRC_MAIN) $(SRC_LOADER) $(SRC_YAML) $(SRC_LIBVIRT)

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
	$(CC_MON) $(CC_MON_FLAGS) $(LDFLAGS) -o $@ -fPIE -fPIC $(OBJ) $(OBJDIR)/$(TARGET_ARCH)/asm.o -Wl,-error-limit=0

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR) intravisor

