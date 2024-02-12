PROJ=sysbench
ROOT_FS=disk_docker_$(PROJ).img
ALPINE_CONTAINER="intravisor/alpine-musl-lkl-$(PROJ):$(LKL_MUSL_BUILD)"
ALPINE_CONTAINER_CID=alpine-musl-lkl-$(PROJ)-$(LKL_MUSL_BUILD).cid
ALPINE_TAR=alpine-musl-lkl-$(PROJ).tar.gz
MOUNTPOINT=/media/ext4disk
IMAGE_SIZE_MB=40
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
	docker $(HOST) pull $(ALPINE_CONTAINER) || (docker $(HOST) build $(LKL_MUSL_DOCKER_PLAT) . -t $(ALPINE_CONTAINER) && docker $(HOST) push $(ALPINE_CONTAINER))
	docker $(HOST) run $(LKL_MUSL_DOCKER_PLAT)  --cidfile $(ALPINE_CONTAINER_CID) -d $(ALPINE_CONTAINER) sh


$(ALPINE_TAR): $(ALPINE_CONTAINER_CID)
	docker $(HOST) export -o $(ALPINE_TAR) $(shell cat $(ALPINE_CONTAINER_CID))

$(ROOT_FS): $(ALPINE_TAR)
	dd if=/dev/zero of=$(ROOT_FS) count=$(IMAGE_SIZE_MB) bs=1M
	mkfs.ext4 $(ROOT_FS)
	$(ESCALATE_CMD) mkdir -p $(MOUNTPOINT)
	$(ESCALATE_CMD) mount -t ext4 -o loop $(ROOT_FS) $(MOUNTPOINT)
	$(ESCALATE_CMD) tar -C $(MOUNTPOINT) -xvf $(ALPINE_TAR)
	$(ESCALATE_CMD) umount $(MOUNTPOINT)
	$(ESCALATE_CMD) chown $(USER) "$(ROOT_FS)"

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.img ./*.ci ${INSTALL_PATH}
