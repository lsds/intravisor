MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)

PROG=app9
OBJDIR = obj

CROSS_LIBC_PATH=../../libc/build/
CFLAGS= -I../../libc/build/include -DINTRAVISOR -O2

CFLAGS+= -I.

SRC += main.c 

CFLAGS += -I mosquitto/src  -I mosquitto/ -I mosquitto/include -I mosquitto/lib -DWITH_BRIDGE -DWITH_PERSISTENCE -DWITH_MEMORY_TRACKING -DWITH_SYS_TREE -DWITH_EC -DWITH_CONTROL -DWITH_UNIX_SOCKETS -I mosquitto/deps -Wall -ggdb -O2 -Wconversion -Wextra -DVERSION="\"2.0.18\"" -DWITH_BROKER

SRC += mosquitto/src/mosquitto.c
SRC += mosquitto/lib/alias_mosq.c
SRC += mosquitto/src/bridge.c
SRC += mosquitto/src/bridge_topic.c
SRC += mosquitto/src/conf.c
SRC += mosquitto/src/conf_includedir.c
SRC += mosquitto/src/context.c
SRC += mosquitto/src/control.c
SRC += mosquitto/src/database.c
SRC += mosquitto/src/handle_auth.c
SRC += mosquitto/src/handle_connack.c
SRC += mosquitto/src/handle_connect.c
SRC += mosquitto/src/handle_disconnect.c
SRC += mosquitto//lib/handle_ping.c
SRC += mosquitto//lib/handle_pubackcomp.c
SRC += mosquitto/src/handle_publish.c
SRC += mosquitto//lib/handle_pubrec.c
SRC += mosquitto//lib/handle_pubrel.c
SRC += mosquitto//lib/handle_suback.c
SRC += mosquitto/src/handle_subscribe.c
SRC += mosquitto//lib/handle_unsuback.c
SRC += mosquitto/src/handle_unsubscribe.c
SRC += mosquitto/src/keepalive.c
SRC += mosquitto/src/logging.c
SRC += mosquitto/src/loop.c
SRC += mosquitto//lib/memory_mosq.c
SRC += mosquitto/src/memory_public.c
SRC += mosquitto//lib/misc_mosq.c
SRC += mosquitto/src/mux.c
SRC += mosquitto/src/mux_epoll.c
SRC += mosquitto/src/mux_poll.c
SRC += mosquitto/src/net.c
SRC += mosquitto//lib/net_mosq.c
SRC += mosquitto//lib/net_mosq_ocsp.c
SRC += mosquitto//lib/packet_datatypes.c
SRC += mosquitto//lib/packet_mosq.c
SRC += mosquitto/src/password_mosq.c
SRC += mosquitto/src/property_broker.c
SRC += mosquitto//lib/property_mosq.c
SRC += mosquitto/src/persist_read.c
SRC += mosquitto/src/persist_read_v234.c
SRC += mosquitto/src/persist_read_v5.c
SRC += mosquitto/src/persist_write.c
SRC += mosquitto/src/persist_write_v5.c
SRC += mosquitto/src/plugin.c
SRC += mosquitto/src/plugin_public.c
SRC += mosquitto/src/read_handle.c
SRC += mosquitto/src/retain.c
SRC += mosquitto/src/security.c
SRC += mosquitto/src/security_default.c
SRC += mosquitto/src/send_auth.c
SRC += mosquitto/src/send_connack.c
SRC += mosquitto//lib/send_connect.c
SRC += mosquitto//lib/send_disconnect.c
SRC += mosquitto/lib/send_mosq.c
SRC += mosquitto/lib/send_publish.c
SRC += mosquitto/src/send_suback.c
SRC += mosquitto/lib/send_subscribe.c
SRC += mosquitto/src/send_unsuback.c
SRC += mosquitto/lib/send_unsubscribe.c
SRC += mosquitto/src/service.c
SRC += mosquitto/src/session_expiry.c
SRC += mosquitto/src/signals.c
SRC += mosquitto/lib/strings_mosq.c
SRC += mosquitto/src/subs.c
SRC += mosquitto/src/sys_tree.c
SRC += mosquitto/lib/time_mosq.c
SRC += mosquitto/src/topic_tok.c
SRC += mosquitto/lib/tls_mosq.c
SRC += mosquitto/lib/utf8_mosq.c
SRC += mosquitto/lib/util_mosq.c
SRC += mosquitto/lib/util_topic.c
SRC += mosquitto/src/websockets.c
SRC += mosquitto/src/will_delay.c
SRC += mosquitto/lib/will_mosq.c
SRC += mosquitto/src/xtreport.c

OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

ROOTFS := root.cpio

all: $(ROOTFS)

$(OBJDIR)/%.o: %.c
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS)

$(PROG): $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -nostdlib -nostartfiles -o $@ $(OBJ) $(CROSS_LIBC_PATH)/lib/crt1.o $(CROSS_LIBC_PATH)/lib/crti.o $(CROSS_LIBC_PATH)/lib/crtn.o \
	-L$(CROSS_LIBC_PATH)/lib -Wl,-dynamic-linker=/lib/ld-linux-aarch64_purecap.so.1 ../../libc/libcompiler_rt.a -lc -pie

clean:
	rm -rf $(ROOTFS) $(PROG) *.o ./$(OBJDIR) rootfs/app1

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.ci ./libldso.so ${INSTALL_PATH}
	sudo cp $(ROOTFS) ${INSTALL_PATH}/$(ROOTFS)_$(shell basename $(shell ls *.yaml) .yaml)

$(ROOTFS): $(PROG) $(CROSS_LIBC_PATH)/lib/libc.so
	cp $(PROG) rootfs/app1
	cp $(CROSS_LIBC_PATH)/lib/libc.so ./libldso.so
	cd rootfs && find . -print -depth | sort | $(CPIO) -vo -H newc > ../$(ROOTFS)

