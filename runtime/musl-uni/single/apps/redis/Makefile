MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)


CFLAGS=-fPIC -fPIE -pie -g -O2  -nostdinc \
	$(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_PURE) -B$(CROSS_COMPILE) $(ARCH_PURE) \
	 -I ../../musl-host/include  -I.\
	-I redis-5.0.14/src -I redis-5.0.14/deps/hdr_histogram -I redis-5.0.14/deps/hiredis -I redis-5.0.14/deps/linenoise -I redis-5.0.14/deps/lua/src
	

DEPS = 
OBJDIR = obj
SRC = main.c

#redis
SRC += redis-5.0.14/src/adlist.c redis-5.0.14/src/quicklist.c redis-5.0.14/src/ae.c redis-5.0.14/src/anet.c redis-5.0.14/src/dict.c redis-5.0.14/src/server.c redis-5.0.14/src/sds.c redis-5.0.14/src/zmalloc.c redis-5.0.14/src/lzf_c.c redis-5.0.14/src/lzf_d.c redis-5.0.14/src/pqsort.c redis-5.0.14/src/zipmap.c redis-5.0.14/src/sha1.c redis-5.0.14/src/ziplist.c redis-5.0.14/src/release.c redis-5.0.14/src/networking.c redis-5.0.14/src/util.c redis-5.0.14/src/object.c redis-5.0.14/src/db.c redis-5.0.14/src/replication.c redis-5.0.14/src/rdb.c redis-5.0.14/src/t_string.c redis-5.0.14/src/t_list.c redis-5.0.14/src/t_set.c redis-5.0.14/src/t_zset.c redis-5.0.14/src/t_hash.c redis-5.0.14/src/config.c redis-5.0.14/src/aof.c redis-5.0.14/src/pubsub.c redis-5.0.14/src/multi.c redis-5.0.14/src/debug.c redis-5.0.14/src/sort.c redis-5.0.14/src/intset.c redis-5.0.14/src/syncio.c redis-5.0.14/src/cluster.c redis-5.0.14/src/crc16.c redis-5.0.14/src/endianconv.c redis-5.0.14/src/slowlog.c redis-5.0.14/src/bio.c redis-5.0.14/src/rio.c redis-5.0.14/src/rand.c redis-5.0.14/src/memtest.c redis-5.0.14/src/crc64.c redis-5.0.14/src/bitops.c redis-5.0.14/src/sentinel.c redis-5.0.14/src/notify.c redis-5.0.14/src/setproctitle.c redis-5.0.14/src/blocked.c redis-5.0.14/src/hyperloglog.c redis-5.0.14/src/latency.c redis-5.0.14/src/sparkline.c redis-5.0.14/src/redis-check-rdb.c redis-5.0.14/src/redis-check-aof.c redis-5.0.14/src/geo.c redis-5.0.14/src/lazyfree.c redis-5.0.14/src/module.c redis-5.0.14/src/evict.c redis-5.0.14/src/expire.c redis-5.0.14/src/geohash.c redis-5.0.14/src/geohash_helper.c redis-5.0.14/src/childinfo.c redis-5.0.14/src/defrag.c redis-5.0.14/src/siphash.c redis-5.0.14/src/rax.c redis-5.0.14/src/listpack.c redis-5.0.14/src/localtime.c  redis-5.0.14/src/lolwut5.c 
#5
SRC += redis-5.0.14/src/t_stream.c redis-5.0.14/src/lolwut.c redis-5.0.14/src/scripting.c
#lua
SRC += redis-5.0.14/deps/lua/src/lapi.c redis-5.0.14/deps/lua/src/lcode.c redis-5.0.14/deps/lua/src/ldebug.c redis-5.0.14/deps/lua/src/ldo.c redis-5.0.14/deps/lua/src/ldump.c redis-5.0.14/deps/lua/src/lfunc.c redis-5.0.14/deps/lua/src/lgc.c redis-5.0.14/deps/lua/src/llex.c redis-5.0.14/deps/lua/src/lmem.c redis-5.0.14/deps/lua/src/lobject.c redis-5.0.14/deps/lua/src/lopcodes.c redis-5.0.14/deps/lua/src/lparser.c redis-5.0.14/deps/lua/src/lstate.c redis-5.0.14/deps/lua/src/lstring.c redis-5.0.14/deps/lua/src/ltable.c redis-5.0.14/deps/lua/src/ltm.c redis-5.0.14/deps/lua/src/lundump.c redis-5.0.14/deps/lua/src/lvm.c redis-5.0.14/deps/lua/src/lzio.c redis-5.0.14/deps/lua/src/strbuf.c redis-5.0.14/deps/lua/src/fpconv.c
SRC += redis-5.0.14/deps/lua/src/lauxlib.c redis-5.0.14/deps/lua/src/lbaselib.c redis-5.0.14/deps/lua/src/ldblib.c redis-5.0.14/deps/lua/src/liolib.c redis-5.0.14/deps/lua/src/lmathlib.c redis-5.0.14/deps/lua/src/loslib.c redis-5.0.14/deps/lua/src/ltablib.c redis-5.0.14/deps/lua/src/lstrlib.c redis-5.0.14/deps/lua/src/loadlib.c redis-5.0.14/deps/lua/src/linit.c redis-5.0.14/deps/lua/src/lua_cjson.c redis-5.0.14/deps/lua/src/lua_struct.c redis-5.0.14/deps/lua/src/lua_cmsgpack.c redis-5.0.14/deps/lua/src/lua_bit.c
#hiredis
SRC += redis-5.0.14/deps/hiredis/net.c redis-5.0.14/deps/hiredis/hiredis.c redis-5.0.14/deps/hiredis/async.c redis-5.0.14/deps/hiredis/read.c 


OBJ := $(SRC:%.c=$(OBJDIR)/%.o)


default: libredis.so


$(OBJDIR)/%.o: %.c $(DEPS) $(PASS1) $(PASS2) 
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS)


libredis.so: $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ) $(LD_FLAGS) ../../libmusl-uni.a

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR)

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.so ${INSTALL_PATH}
