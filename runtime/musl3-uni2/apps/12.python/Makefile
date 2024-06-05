MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)

PROG=app12
OBJDIR = obj

CROSS_LIBC_PATH=../../libc/build/
CFLAGS= -I../../libc/build/include -DINTRAVISOR -O2
CFLAGS += -DPREFIX='"/usr/local"' -DEXEC_PREFIX='"/usr/local"' -DVERSION='"3.8"' -DVPATH='""' -DPYTHONPATH='""' 
CFLAGS+= -I.

SRC += main.c 

CFLAGS += -DPy_BUILD_CORE -I python/Include/ -DNDEBUG -I python/Include/internal/ -DSOABI='"cpython-38-arm-linux-gnueabihf"'

SRC += python/Parser/acceler.c python/Parser/grammar1.c python/Parser/listnode.c python/Parser/node.c python/Parser/parser.c python/Parser/token.c  python/Parser/myreadline.c python/Parser/parsetok.c python/Parser/tokenizer.c 

SRC += python/Objects/abstract.c python/Objects/accu.c python/Objects/boolobject.c python/Objects/bytes_methods.c python/Objects/bytearrayobject.c python/Objects/bytesobject.c python/Objects/call.c python/Objects/capsule.c python/Objects/cellobject.c python/Objects/classobject.c python/Objects/codeobject.c python/Objects/complexobject.c python/Objects/descrobject.c python/Objects/enumobject.c python/Objects/exceptions.c python/Objects/genobject.c python/Objects/fileobject.c python/Objects/floatobject.c python/Objects/frameobject.c python/Objects/funcobject.c python/Objects/interpreteridobject.c python/Objects/iterobject.c python/Objects/listobject.c python/Objects/longobject.c python/Objects/dictobject.c python/Objects/odictobject.c python/Objects/memoryobject.c python/Objects/methodobject.c python/Objects/moduleobject.c python/Objects/namespaceobject.c python/Objects/object.c python/Objects/obmalloc.c python/Objects/picklebufobject.c python/Objects/pointerobject.c python/Objects/rangeobject.c python/Objects/setobject.c python/Objects/sliceobject.c python/Objects/structseq.c python/Objects/tupleobject.c python/Objects/typeobject.c python/Objects/unicodeobject.c python/Objects/unicodectype.c python/Objects/weakrefobject.c 

SRC += python/Python/_warnings.c python/Python/Python-ast.c python/Python/asdl.c python/Python/ast.c python/Python/ast_opt.c python/Python/ast_unparse.c python/Python/bltinmodule.c python/Python/ceval.c python/Python/codecs.c python/Python/compile.c python/Python/context.c 
SRC += python/Python/dynamic_annotations.c python/Python/errors.c python/Python/frozenmain.c python/Python/future.c 
SRC += python/Python/getargs.c python/Python/getcompiler.c python/Python/getcopyright.c python/Python/getplatform.c python/Python/getversion.c python/Python/graminit.c python/Python/hamt.c python/Python/import.c python/Python/importdl.c python/Python/initconfig.c 
SRC += python/Python/marshal.c python/Python/modsupport.c python/Python/mysnprintf.c python/Python/mystrtoul.c python/Python/pathconfig.c python/Python/peephole.c python/Python/preconfig.c python/Python/pyarena.c python/Python/pyctype.c python/Python/pyfpe.c 
SRC += python/Python/pyhash.c python/Python/pylifecycle.c python/Python/pymath.c python/Python/pystate.c python/Python/pythonrun.c python/Python/pytime.c python/Python/bootstrap_hash.c python/Python/structmember.c python/Python/symtable.c python/Python/sysmodule.c 
SRC += python/Python/thread.c python/Python/traceback.c python/Python/getopt.c python/Python/pystrcmp.c python/Python/pystrtod.c python/Python/pystrhex.c python/Python/dtoa.c python/Python/formatter_unicode.c python/Python/fileutils.c python/Python/dynload_shlib.c    
SRC += python/Python/frozen.c

SRC += python/Modules/getbuildinfo.c 
SRC += config.c
SRC += python/Modules/getpath.c python/Modules/main.c python/Modules/gcmodule.c python/Modules/posixmodule.c  python/Modules/errnomodule.c  python/Modules/pwdmodule.c  python/Modules/_sre.c  
SRC += python/Modules/_codecsmodule.c  python/Modules/_weakref.c  python/Modules/_functoolsmodule.c  python/Modules/_operator.c  python/Modules/_collectionsmodule.c  python/Modules/_abc.c  python/Modules/itertoolsmodule.c  python/Modules/atexitmodule.c  
SRC += python/Modules/signalmodule.c  python/Modules/_stat.c  python/Modules/timemodule.c  python/Modules/_threadmodule.c  python/Modules/_localemodule.c
SRC += python/Modules/_io/_iomodule.c  python/Modules/_io/iobase.c python/Modules/_io/fileio.c python/Modules/_io/bytesio.c 
SRC += python/Modules/_io/bufferedio.c python/Modules/_io/textio.c python/Modules/_io/stringio.c  python/Modules/faulthandler.c  python/Modules/_tracemalloc.c python/Modules/hashtable.c  python/Modules/symtablemodule.c  python/Modules/xxsubtype.c 

SRC += python/Programs/python.c

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

