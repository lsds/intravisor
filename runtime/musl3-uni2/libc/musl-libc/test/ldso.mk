
LFLAGS = -L./src/lib '-Wl,-rpath,$$ORIGIN/lib'

LIBRARY_SOURCES := $(wildcard src/lib/*.c)
SLOBJS := $(patsubst src/lib/%.c, src/lib/lib%.so, $(LIBRARY_SOURCES))
SSLOBJS := $(patsubst %.c, %.o, $(LIBRARY_SOURCES))

# Third-Party Library
src/shared-lib.lo src/shared-lib.o: CFLAGS += -I src/lib
src/shared-lib-static.exe: private LDFLAGS += src/lib/third-party-library.o
src/shared-lib-static.exe: src/lib/third-party-library.o
src/shared-lib-dynamic.exe: private LDLIBS += -lthird-party-library $(LFLAGS)
src/shared-lib-dynamic.exe: src/lib/libthird-party-library.so

# Symbol library
src/symbol-lib.lo src/symbol-lib.o: CFLAGS += -I src/lib
src/symbol-lib-static.exe: private LDFLAGS += src/lib/symbol-library.o
src/symbol-lib-static.exe: src/lib/symbol-library.o
src/symbol-lib-dynamic.exe: private LDLIBS += -lsymbol-library $(LFLAGS)
src/symbol-lib-dynamic.exe: src/lib/libsymbol-library.so

# Multiple Library
src/multiple-lib.lo src/multiple-lib.o: CFLAGS += -I src/lib
src/multiple-lib-static.exe: private LDFLAGS += src/lib/multi-lib1.o src/lib/multi-lib2.o
src/multiple-lib-static.exe: src/lib/multi-lib1.o src/lib/multi-lib2.o
src/multiple-lib-dynamic.exe: src/lib/libmulti-lib1.so src/lib/libmulti-lib2.so
src/multiple-lib-dynamic.exe: private LDLIBS += -lmulti-lib1 -lmulti-lib2 $(LFLAGS)

# Symbol Multi Library
src/symbol-multi-lib.lo src/symbol-multi-lib.o: CFLAGS += -I src/lib
src/symbol-multi-lib-static.exe: private LDFLAGS += src/lib/symbol-library.o src/lib/third-party-library.o
src/symbol-multi-lib-static.exe: src/lib/symbol-library.o src/lib/third-party-library.o
src/symbol-multi-lib-dynamic.exe: src/lib/libsymbol-library.so src/lib/libthird-party-library.so
src/symbol-multi-lib-dynamic.exe: private LDLIBS += -lsymbol-library -lthird-party-library $(LFLAGS)

# Dependency Library
src/dependency-lib.lo src/dependency-lib.o: CFLAGS += -I src/lib
src/lib/libdependency-lib2.so: src/lib/libdependency-lib1.so
src/lib/libdependency-lib2.so: private LDFLAGS += -ldependency-lib1 $(LFLAGS)
src/dependency-lib-static.exe: src/lib/dependency-lib1.o src/lib/dependency-lib2.o
src/dependency-lib-static.exe: private LDFLAGS += src/lib/dependency-lib1.o src/lib/dependency-lib2.o
src/dependency-lib-dynamic.exe: src/lib/libdependency-lib2.so
src/dependency-lib-dynamic.exe: private LDLIBS += -ldependency-lib2 $(LFLAGS)

# Pointer Library
src/pointer-lib.lo src/pointer-lib.o: CFLAGS += -I src/lib
src/pointer-lib-static.exe: src/lib/third-party-pointer-lib.o
src/pointer-lib-static.exe: private LDFLAGS += src/lib/third-party-pointer-lib.o
src/pointer-lib-dynamic.exe: src/lib/libthird-party-pointer-lib.so
src/pointer-lib-dynamic.exe: private LDLIBS += -lthird-party-pointer-lib $(LFLAGS)

# Variadic Library
src/variadic-lib.lo src/variadic-lib.o: CFLAGS += -I src/lib
src/variadic-lib-static.exe: src/lib/variadic-lib.o
src/variadic-lib-static.exe: private LDFLAGS += src/lib/variadic-lib.o
src/variadic-lib-dynamic.exe: src/lib/libvariadic-lib.so
src/variadic-lib-dynamic.exe: private LDLIBS += -lvariadic-lib $(LFLAGS)

# CAPINIT Relocation
src/capinit.lo src/capinit.o: CFLAGS += -I src/lib
src/capinit-static.exe: src/lib/capinit-lib.o
src/capinit-static.exe: private LDFLAGS += src/lib/capinit-lib.o

src/capinit-dynamic.exe: src/lib/libcapinit-lib.so
src/capinit-dynamic.exe: private LDLIBS += -lcapinit-lib $(LFLAGS)

# stt-tls-symbol Library
src/stt_tls_symboltest.lo src/stt_tls_symboltest.o: CFLAGS += -I src/lib
src/stt_tls_symboltest-dynamic.exe: src/lib/libstt-tls-symbol-lib.so
src/stt_tls_symboltest-dynamic.exe: private LDLIBS += -lstt-tls-symbol-lib $(LFLAGS)
