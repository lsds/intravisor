ROOT_FS=disk_docker_redis.img
ALPINE_CONTAINER="intravisor/alpine-test"
ALPINE_CONTAINER_CID=alpine-test.cid
ALPINE_TAR=alpine-test.tar.gz
MOUNTPOINT=/media/ext4disk
IMAGE_SIZE_MB=20
USER=`whoami`
ESCALATE_CMD=sudo

.DELETE_ON_ERROR:
.PHONY: all clean

all: $(ROOT_FS)

clean:
	test -f $(ROOT_FS) && rm $(ROOT_FS) || true
	test -f $(ALPINE_CONTAINER_CID) && rm $(ALPINE_CONTAINER_CID) || true
	test -f loader && rm loader || true
	rm -rf ./$(ALPINE_TAR)

$(ALPINE_CONTAINER_CID):
	docker pull $(ALPINE_CONTAINER)
	docker run --cidfile $(ALPINE_CONTAINER_CID) -d $(ALPINE_CONTAINER) sh

$(ALPINE_TAR): $(ALPINE_CONTAINER_CID)
	docker export -o $(ALPINE_TAR) $(shell cat alpine-test.cid)

$(ROOT_FS): $(ALPINE_TAR)
	dd if=/dev/zero of=$(ROOT_FS) count=$(IMAGE_SIZE_MB) bs=1M
	mkfs.ext4 $(ROOT_FS)
	$(ESCALATE_CMD) mkdir -p $(MOUNTPOINT)
	$(ESCALATE_CMD) mount -t ext4 -o loop $(ROOT_FS) $(MOUNTPOINT)
	$(ESCALATE_CMD) tar -C $(MOUNTPOINT) -xvf $(ALPINE_TAR)
	$(ESCALATE_CMD) cp redis.conf  $(MOUNTPOINT)/redis.conf; \
	$(ESCALATE_CMD) umount $(MOUNTPOINT)
	$(ESCALATE_CMD) chown $(USER) "$(ROOT_FS)"

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.img ${INSTALL_PATH}
