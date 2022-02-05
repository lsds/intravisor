#todo: track changes in headers
include ../config.mak

all:

OBJDIR := build
SRC_LKL := lkl_wrap/iomem.c lkl_wrap/jmp_buf.c lkl_wrap/posix-host.c lkl_wrap/virtio_net_fd.c hostcalls.c main.c utils.c
SRC_YAML := libyaml/src/api.c libyaml/src/dumper.c libyaml/src/emitter.c libyaml/src/loader.c libyaml/src/parser.c libyaml/src/reader.c libyaml/src/scanner.c libyaml/src/writer.c libyaml/intra_parser.c libyaml/intravisor.c
SRC_LOADER := load_elf/load_elf.c

CFILES  := $(SRC_LKL)  $(SRC_LOADER) $(SRC_YAML)
ASFILES := arch/riscv/asm.S
CFLAGS	:= -I lkl_wrap/include -I load_elf/ -I lkl_wrap -I libyaml/include -Ilibyaml/src -DHAVE_CONFIG_H -Ilibyaml/

target_c = ${OBJDIR}/$(patsubst %.c,%.o,$(notdir ${1})) 
target_s = ${OBJDIR}/$(patsubst %.S,%.o,$(notdir ${1})) 
obj.c :=
obj.S :=
define obj_c
  $(call target_c,${1}) : ${1} | ${OBJDIR}
  obj$(suffix ${1}) += $(call target_c,${1})
endef

define obj_s
  $(call target_s,${1}) : ${1} | ${OBJDIR}
  obj$(suffix ${1}) += $(call target_s,${1})
endef

define SOURCES_C
  $(foreach src,${1},$(eval $(call obj_c,${src})))
endef

define SOURCES_S
  $(foreach src,${1},$(eval $(call obj_s,${src})))
endef


$(eval $(call SOURCES_C,${CFILES}))
$(eval $(call SOURCES_S,${ASFILES}))

all : ${OBJDIR} ${obj.c} ${obj.S} monitor

${obj.c} : % :
	$(CC_MON) $(CC_MON_FLAGS) $(CFLAGS) -c -o $@ $^

${obj.S} : % :
	$(AS_MON) $(AS_MON_FLAGS) -c -o $@ $^

${OBJDIR} :
	mkdir $@

monitor : ${OBJDIR} 
	$(CC_MON) $(CC_MON_FLAGS) -ldl -lrt -lpthread -o ${OBJDIR}/monitor ${obj.c} ${obj.S} 

clean:
	rm -rf ${OBJDIR}

all: monitor

.PHONY: all clean
