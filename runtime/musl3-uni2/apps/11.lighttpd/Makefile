MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)

PROG=app11
OBJDIR = obj

CROSS_LIBC_PATH=../../libc/build/
CFLAGS= -I../../libc/build/include -DINTRAVISOR -O2

CFLAGS+= -I.

SRC += main.c 

CFLAGS += -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGE_FILES -D_DEFAULT_SOURCE -D_GNU_SOURCE -DHAVE_CONFIG_H -I lighttpd-1.4.75/src/

SRC += lighttpd-1.4.75/src/algo_md5.c
SRC += lighttpd-1.4.75/src/algo_sha1.c
SRC += lighttpd-1.4.75/src/algo_splaytree.c
SRC += lighttpd-1.4.75/src/array.c
SRC += lighttpd-1.4.75/src/base64.c
SRC += lighttpd-1.4.75/src/buffer.c
SRC += lighttpd-1.4.75/src/burl.c
SRC += lighttpd-1.4.75/src/chunk.c
SRC += lighttpd-1.4.75/src/configfile-glue.c
SRC += lighttpd-1.4.75/src/http_etag.c
SRC += lighttpd-1.4.75/src/fdevent.c
SRC += lighttpd-1.4.75/src/fdevent_fdnode.c
SRC += lighttpd-1.4.75/src/fdlog_maint.c
SRC += lighttpd-1.4.75/src/fdlog.c
SRC += lighttpd-1.4.75/src/gw_backend.c
SRC += lighttpd-1.4.75/src/http_cgi.c
SRC += lighttpd-1.4.75/src/http_chunk.c
SRC += lighttpd-1.4.75/src/http_date.c
SRC += lighttpd-1.4.75/src/http_header.c
SRC += lighttpd-1.4.75/src/http_kv.c
SRC += lighttpd-1.4.75/src/http-header-glue.c
SRC += lighttpd-1.4.75/src/keyvalue.c
SRC += lighttpd-1.4.75/src/log.c
SRC += lighttpd-1.4.75/src/rand.c
SRC += lighttpd-1.4.75/src/plugin.c
SRC += lighttpd-1.4.75/src/reqpool.c
SRC += lighttpd-1.4.75/src/request.c
SRC += lighttpd-1.4.75/src/ck.c
SRC += lighttpd-1.4.75/src/sock_addr.c
SRC += lighttpd-1.4.75/src/stat_cache.c
SRC += lighttpd-1.4.75/src/sys-setjmp.c

SRC += lighttpd-1.4.75/src/configfile.c
SRC += lighttpd-1.4.75/src/connections.c
SRC += lighttpd-1.4.75/src/data_config.c
SRC += lighttpd-1.4.75/src/h1.c
SRC += lighttpd-1.4.75/src/sock_addr_cache.c
SRC += lighttpd-1.4.75/src/fdevent_impl.c
SRC += lighttpd-1.4.75/src/http_range.c
SRC += lighttpd-1.4.75/src/network_write.c
SRC += lighttpd-1.4.75/src/network.c
SRC += lighttpd-1.4.75/src/response.c
SRC += lighttpd-1.4.75/src/server.c
SRC += configparser.c

SRC += lighttpd-1.4.75/src/mod_userdir.c
SRC += lighttpd-1.4.75/src/mod_sockproxy.c
SRC += lighttpd-1.4.75/src/mod_fastcgi.c
#SRC += lighttpd-1.4.75/src/mod_auth_api.c
#SRC += lighttpd-1.4.75/src/mod_mbedtls.c
SRC += lighttpd-1.4.75/src/mod_rewrite.c
SRC += lighttpd-1.4.75/src/mod_simple_vhost.c
SRC += lighttpd-1.4.75/src/mod_proxy.c
#SRC += lighttpd-1.4.75/src/mod_gnutls.c
#SRC += lighttpd-1.4.75/src/mod_vhostdb.c
SRC += lighttpd-1.4.75/src/mod_cgi.c
#SRC += lighttpd-1.4.75/src/mod_maxminddb.c
#SRC += lighttpd-1.4.75/src/mod_deflate.c
SRC += lighttpd-1.4.75/src/mod_expire.c
#SRC += lighttpd-1.4.75/src/mod_authn_dbi.c
#SRC += lighttpd-1.4.75/src/mod_auth.c
#SRC += lighttpd-1.4.75/src/mod_webdav.c
SRC += lighttpd-1.4.75/src/mod_skeleton.c
SRC += lighttpd-1.4.75/src/mod_indexfile.c
SRC += lighttpd-1.4.75/src/mod_ajp13.c
SRC += lighttpd-1.4.75/src/mod_status.c
SRC += lighttpd-1.4.75/src/mod_evhost.c
#SRC += lighttpd-1.4.75/src/mod_authn_file.c
SRC += lighttpd-1.4.75/src/mod_ssi.c
#SRC += lighttpd-1.4.75/src/mod_magnet_cache.c
SRC += lighttpd-1.4.75/src/mod_scgi.c
SRC += lighttpd-1.4.75/src/mod_accesslog.c
#SRC += lighttpd-1.4.75/src/mod_magnet.c
SRC += lighttpd-1.4.75/src/mod_rrdtool.c
#SRC += lighttpd-1.4.75/src/mod_authn_gssapi.c
SRC += lighttpd-1.4.75/src/mod_alias.c
#SRC += lighttpd-1.4.75/src/mod_vhostdb_api.c
#SRC += lighttpd-1.4.75/src/mod_authn_pam.c
#SRC += lighttpd-1.4.75/src/mod_vhostdb_ldap.c
#SRC += lighttpd-1.4.75/src/mod_vhostdb_mysql.c
SRC += lighttpd-1.4.75/src/mod_setenv.c
SRC += lighttpd-1.4.75/src/mod_dirlisting.c
#SRC += lighttpd-1.4.75/src/mod_openssl.c
#SRC += lighttpd-1.4.75/src/mod_wolfssl.c
#SRC += lighttpd-1.4.75/src/mod_vhostdb_dbi.c
SRC += lighttpd-1.4.75/src/mod_redirect.c
#SRC += lighttpd-1.4.75/src/mod_vhostdb_pgsql.c
SRC += lighttpd-1.4.75/src/mod_staticfile.c
SRC += lighttpd-1.4.75/src/mod_extforward.c
#SRC += lighttpd-1.4.75/src/mod_authn_sasl.c
#SRC += lighttpd-1.4.75/src/mod_authn_ldap.c
SRC += lighttpd-1.4.75/src/mod_access.c
SRC += lighttpd-1.4.75/src/mod_wstunnel.c
#SRC += lighttpd-1.4.75/src/mod_nss.c

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
