PROG=cap_file
PROG_C=$(PROG).c

MOUNTPOINT=/media/ext4disk

DISK=disk.img

LOOP_DEVICE=loop9
IMAGE_SIZE_KB=200

ESCALATE_CMD=sudo

.DELETE_ON_ERROR:
.PHONY: all clean

all: $(DISK)

clean:
	rm -f $(DISK) $(PROG) *.o

$(PROG): $(PROG_C)
	../../build/musl-host/bin/musl-clang-target -fPIE -pie -c -g -o $@.o $(PROG_C)
	../../build/musl-host/bin/ld.musl-clang-target -g -pie -dynamic-linker /ld.so cap_file.o -o cap_file

$(DISK): $(PROG) 
	dd if=/dev/zero of="$@" count=$(IMAGE_SIZE_KB) bs=1K
	mkfs.ext4 "$@"
	$(ESCALATE_CMD) /bin/bash -euxo pipefail -c '\
		mkdir -p $(MOUNTPOINT); \
		mount -t ext4 -o loop "$@" $(MOUNTPOINT); \
		mkdir -p $(MOUNTPOINT)/app; \
		cp $(PROG)  $(MOUNTPOINT)/app; \
		umount $(MOUNTPOINT); \
		chown $(USER) "$@"; \
	'

test: $(DISK)
	../../build/sgx-lkl-run $(DISK) app/$(PROG)

