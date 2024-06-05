MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)

PROG=app10
OBJDIR = obj

CROSS_LIBC_PATH=../../libc/build/
CFLAGS= -I../../libc/build/include -DINTRAVISOR -O2

CFLAGS+= -I.

SRC += main.c 

CFLAGS += -I nginx/src/ -I nginx/objs/ -I nginx/src/core -I nginx/src/os/unix/ -I nginx/src/event/ -I nginx/src/http/ -I nginx/src/http/modules/

SRC += nginx/src/core/nginx.c
SRC += nginx/src/core/ngx_log.c
SRC += nginx/src/core/ngx_palloc.c
SRC += nginx/src/core/ngx_array.c
SRC += nginx/src/core/ngx_list.c
SRC += nginx/src/core/ngx_hash.c
SRC += nginx/src/core/ngx_buf.c
SRC += nginx/src/core/ngx_queue.c
SRC += nginx/src/core/ngx_output_chain.c
SRC += nginx/src/core/ngx_string.c
SRC += nginx/src/core/ngx_parse.c
SRC += nginx/src/core/ngx_parse_time.c
SRC += nginx/src/core/ngx_inet.c
SRC += nginx/src/core/ngx_file.c
SRC += nginx/src/core/ngx_crc32.c
SRC += nginx/src/core/ngx_murmurhash.c
SRC += nginx/src/core/ngx_md5.c
SRC += nginx/src/core/ngx_sha1.c
SRC += nginx/src/core/ngx_rbtree.c
SRC += nginx/src/core/ngx_radix_tree.c
SRC += nginx/src/core/ngx_slab.c
SRC += nginx/src/core/ngx_times.c
SRC += nginx/src/core/ngx_shmtx.c
SRC += nginx/src/core/ngx_connection.c
SRC += nginx/src/core/ngx_cycle.c
SRC += nginx/src/core/ngx_spinlock.c
SRC += nginx/src/core/ngx_rwlock.c
SRC += nginx/src/core/ngx_cpuinfo.c
SRC += nginx/src/core/ngx_conf_file.c
SRC += nginx/src/core/ngx_module.c
SRC += nginx/src/core/ngx_resolver.c
SRC += nginx/src/core/ngx_open_file_cache.c
SRC += nginx/src/core/ngx_crypt.c
SRC += nginx/src/core/ngx_proxy_protocol.c
SRC += nginx/src/core/ngx_syslog.c
SRC += nginx/src/event/ngx_event.c
SRC += nginx/src/event/ngx_event_timer.c
SRC += nginx/src/event/ngx_event_posted.c
SRC += nginx/src/event/ngx_event_accept.c
SRC += nginx/src/event/ngx_event_connect.c
SRC += nginx/src/event/ngx_event_pipe.c
SRC += nginx/src/os/unix/ngx_time.c
SRC += nginx/src/os/unix/ngx_errno.c
SRC += nginx/src/os/unix/ngx_alloc.c
SRC += nginx/src/os/unix/ngx_files.c
SRC += nginx/src/os/unix/ngx_socket.c
SRC += nginx/src/os/unix/ngx_recv.c
SRC += nginx/src/os/unix/ngx_readv_chain.c
SRC += nginx/src/os/unix/ngx_udp_recv.c
SRC += nginx/src/os/unix/ngx_send.c
SRC += nginx/src/os/unix/ngx_writev_chain.c
SRC += nginx/src/os/unix/ngx_udp_send.c
SRC += nginx/src/os/unix/ngx_udp_sendmsg_chain.c
SRC += nginx/src/os/unix/ngx_channel.c
SRC += nginx/src/os/unix/ngx_shmem.c
SRC += nginx/src/os/unix/ngx_process.c
SRC += nginx/src/os/unix/ngx_daemon.c
SRC += nginx/src/os/unix/ngx_setaffinity.c
SRC += nginx/src/os/unix/ngx_setproctitle.c
SRC += nginx/src/os/unix/ngx_posix_init.c
SRC += nginx/src/os/unix/ngx_user.c
SRC += nginx/src/os/unix/ngx_dlopen.c
SRC += nginx/src/os/unix/ngx_process_cycle.c
SRC += nginx/src/os/unix/ngx_linux_init.c
SRC += nginx/src/event/modules/ngx_poll_module.c
SRC += nginx/src/event/modules/ngx_select_module.c
SRC += nginx/src/os/unix/ngx_linux_sendfile_chain.c
SRC += nginx/src/http/ngx_http.c
SRC += nginx/src/http/ngx_http_core_module.c
SRC += nginx/src/http/ngx_http_special_response.c
SRC += nginx/src/http/ngx_http_request.c
SRC += nginx/src/http/ngx_http_parse.c
SRC += nginx/src/http/modules/ngx_http_log_module.c
SRC += nginx/src/http/ngx_http_request_body.c
SRC += nginx/src/http/ngx_http_variables.c
SRC += nginx/src/http/ngx_http_script.c
#SRC += nginx/src/http/ngx_http_upstream.c
#SRC += nginx/src/http/ngx_http_upstream_round_robin.c
SRC += nginx/src/http/ngx_http_file_cache.c
SRC += nginx/src/http/ngx_http_write_filter_module.c
SRC += nginx/src/http/ngx_http_header_filter_module.c
SRC += nginx/src/http/modules/ngx_http_chunked_filter_module.c
SRC += nginx/src/http/modules/ngx_http_range_filter_module.c
#SRC += nginx/src/http/modules/ngx_http_gzip_filter_module.c
SRC += nginx/src/http/ngx_http_postpone_filter_module.c
SRC += nginx/src/http/modules/ngx_http_ssi_filter_module.c
SRC += nginx/src/http/modules/ngx_http_charset_filter_module.c
SRC += nginx/src/http/modules/ngx_http_userid_filter_module.c
SRC += nginx/src/http/modules/ngx_http_headers_filter_module.c
SRC += nginx/src/http/ngx_http_copy_filter_module.c
SRC += nginx/src/http/modules/ngx_http_not_modified_filter_module.c
SRC += nginx/src/http/modules/ngx_http_static_module.c
SRC += nginx/src/http/modules/ngx_http_autoindex_module.c
SRC += nginx/src/http/modules/ngx_http_index_module.c
SRC += nginx/src/http/modules/ngx_http_mirror_module.c
SRC += nginx/src/http/modules/ngx_http_try_files_module.c
SRC += nginx/src/http/modules/ngx_http_auth_basic_module.c
SRC += nginx/src/http/modules/ngx_http_access_module.c
SRC += nginx/src/http/modules/ngx_http_limit_conn_module.c
SRC += nginx/src/http/modules/ngx_http_limit_req_module.c
SRC += nginx/src/http/modules/ngx_http_geo_module.c
SRC += nginx/src/http/modules/ngx_http_map_module.c
SRC += nginx/src/http/modules/ngx_http_split_clients_module.c
SRC += nginx/src/http/modules/ngx_http_referer_module.c
#SRC += nginx/src/http/modules/ngx_http_proxy_module.c
#SRC += nginx/src/http/modules/ngx_http_fastcgi_module.c
#SRC += nginx/src/http/modules/ngx_http_uwsgi_module.c
#SRC += nginx/src/http/modules/ngx_http_scgi_module.c
#SRC += nginx/src/http/modules/ngx_http_memcached_module.c
SRC += nginx/src/http/modules/ngx_http_empty_gif_module.c
SRC += nginx/src/http/modules/ngx_http_browser_module.c
#SRC += nginx/src/http/modules/ngx_http_upstream_hash_module.c
#SRC += nginx/src/http/modules/ngx_http_upstream_ip_hash_module.c
#SRC += nginx/src/http/modules/ngx_http_upstream_least_conn_module.c
#SRC += nginx/src/http/modules/ngx_http_upstream_keepalive_module.c
#SRC += nginx/src/http/modules/ngx_http_upstream_zone_module.c

SRC += ngx_modules.c


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

