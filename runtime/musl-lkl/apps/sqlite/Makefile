PROG=speedtest
PROG_C=$(PROG).c

MOUNTPOINT=/media/ext4disk

DISK=disk_sqlite.img

LOOP_DEVICE=loop9
IMAGE_SIZE_MB=100

ESCALATE_CMD=sudo

.DELETE_ON_ERROR:
.PHONY: all clean

all: $(DISK)

clean:
	rm -f $(DISK) $(PROG) *.o

$(PROG): $(PROG_C) sqlite3.c
	../../build/musl-host/bin/musl-clang-target -fPIE -pie -c -g -o $@.o $(PROG_C) -O2
	../../build/musl-host/bin/musl-clang-target -fPIE -pie -c -g -o sqlite3.o sqlite3.c -O2 -DSQLITE_OMIT_LOAD_EXTENSION -DSQLITE_THREADSAFE=0 -DSQLITE_OMIT_FLOATING_POINT=1 -DSQLITE_OMIT_DEPRECATED=1 -DSQLITE_OMIT_RANDOMNESS=1
	../../build/musl-host/bin/ld.musl-clang-target -g -pie -dynamic-linker /ld.so  speedtest.o sqlite3.o -o speedtest

$(DISK): $(PROG) 
	dd if=/dev/zero of="$@" count=$(IMAGE_SIZE_MB) bs=1M
#	mkfs.ext4 -E nodiscard "$@"
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

