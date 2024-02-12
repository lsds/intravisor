PROG=darknet/darknet

WEIGHTS = alexnet.weights 
#too slow: yolov3.weights tiny.weights
URL_PREFIX = https://pjreddie.com/media/files/

MOUNTPOINT=/media/ext4disk

DISK=disk_darknet.img

LOOP_DEVICE=loop9
IMAGE_SIZE_KB=400000

ESCALATE_CMD=sudo
USER=`whoami`

.DELETE_ON_ERROR:
.PHONY: all clean

all: $(DISK) $(WEIGHTS) $(PROG)

clean:
	make -C darknet clean
	rm -f $(DISK) $(PROG) *.o

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.img ./*.ci ${INSTALL_PATH}


$(WEIGHTS):
	@for file in $(WEIGHTS); do \
		if [ ! -f $$file ]; then \
			echo "Downloading $$file"; \
			curl -L --output $$file $(URL_PREFIX)/$$file; \
		else \
			echo "$$file already exists"; \
		fi \
	done

$(PROG):
	make -C darknet "CC=../../../build/musl-host/bin/musl-gcc"

$(DISK): $(PROG) $(WEIGHTS)
	dd if=/dev/zero of="$@" count=$(IMAGE_SIZE_KB) bs=1K
	mkfs.ext4 "$@"
	$(ESCALATE_CMD) /bin/bash -euxo pipefail -c '\
		mkdir -p $(MOUNTPOINT); \
		mount -t ext4 -o loop "$@" $(MOUNTPOINT); \
		mkdir -p $(MOUNTPOINT)/app; \
		cp darknet/darknet  $(MOUNTPOINT)/; \
		cp darknet/libdarknet.so  $(MOUNTPOINT)/; \
#		cp darknet/tiny.weights  $(MOUNTPOINT)/; \
		cp alexnet.weights  $(MOUNTPOINT)/; \
		cp -r darknet/cfg  $(MOUNTPOINT)/; \
		cp -r darknet/data  $(MOUNTPOINT)/; \
		umount $(MOUNTPOINT); \
		chown $(USER) "$@"; \
	'

