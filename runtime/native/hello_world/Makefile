MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)


CFLAGS=-fPIC -fPIE -pie   -nostdinc -DCVM_MAX_SIZE=$(CONFIG_CVM_MAX_SIZE)

ifneq ($(MODE),sim)
endif

DEPS = 
OBJ = main.o tramps.o hostcalls.o

default: libnative-hello.so

%.o: %.c $(DEPS)
	$(CC_MON) $(CC_MON_FLAGS) -c -o $@ $< $(CFLAGS)

tramps.o: arch/$(TARGET_ARCH)/tramps.S
	$(CC_MON) $(CC_MON_FLAGS) $(CFLAGS) -c -o tramps.o arch/$(TARGET_ARCH)/tramps.S

libnative-hello.so: $(OBJ)
	$(CC_MON) $(CC_MON_FLAGS) $(CFLAGS) -o $@ -nostdinc -nostdlib -Wl,-eout_c -fPIE -fPIC $(OBJ)


clean:
	rm -rf ./*.o ./*.so

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.so  ${INSTALL_PATH}
