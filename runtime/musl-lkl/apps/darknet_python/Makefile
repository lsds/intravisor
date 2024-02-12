MOUNTPOINT=/media/ext4disk

DISK=disk_darknet_python.img

LOOP_DEVICE=loop9
IMAGE_SIZE_KB=400000

ESCALATE_CMD=sudo
USER=`whoami`

.DELETE_ON_ERROR:
.PHONY: all clean

all: $(DISK)

clean:
	rm -f $(DISK) $(PROG) *.o

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.img ./*.ci ${INSTALL_PATH}


$(DISK):
	dd if=/dev/zero of="$@" count=$(IMAGE_SIZE_KB) bs=1K
	mkfs.ext4 "$@"
	$(ESCALATE_CMD) /bin/bash -euxo pipefail -c '\
		mkdir -p $(MOUNTPOINT); \
		mount -t ext4 -o loop "$@" $(MOUNTPOINT); \
		mkdir -p $(MOUNTPOINT)/app; \
		cp ../darknet/darknet/libdarknet.so  $(MOUNTPOINT)/; \
		cp ../darknet/darknet/python/darknet.py  $(MOUNTPOINT)/; \
		cp ../darknet/alexnet.weights  $(MOUNTPOINT)/; \
		cp -r ../darknet/darknet/cfg  $(MOUNTPOINT)/; \
		cp -r ../darknet/darknet/data  $(MOUNTPOINT)/; \
		cp -r ../python/dest/*  $(MOUNTPOINT)/; \
		umount $(MOUNTPOINT); \
		chown $(USER) "$@"; \
	'

