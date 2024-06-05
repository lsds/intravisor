override SHELL = /bin/bash

MORELLO_TESTS_PROCS = 8

CONFIG ?= $(CURDIR)/../config.mak

-include $(CONFIG)

override SYSROOT = $(prefix)
override MUSLLIB = $(SYSROOT)/lib
override TRIPLE = aarch64-linux-musl_purecap

override MUSL_BITS_STATIC = crt1.o crti.o crtn.o libc.a rcrt1.o Scrt1.o
override MUSL_BITS_DYNAMIC = crt1.o crti.o crtn.o libc.so rcrt1.o Scrt1.o

CFLAGS += --target=$(TRIPLE) --sysroot=$(SYSROOT)
CFLAGS += ${TEST_CFLAGS}
CFLAGS += $(CFLAGS_MORELLO)
CFLAGS += -g -fno-builtin-mempcpy
CFLAGS += -Wall -Wpedantic -Werror
CFLAGS += -Wno-gnu-empty-initializer -Wno-gnu-folding-constant -Wno-gnu-statement-expression

LDFLAGS += --target=$(TRIPLE) --sysroot=$(SYSROOT) $(LDFLAGS_MORELLO)
LDFLAGS += ${TEST_LDFLAGS}
LDFLAGS += -g -fuse-ld=lld
LDLIBS += -lc

SOURCES := $(wildcard src/*.c)
OBJS := $(patsubst %.c, %.o, $(SOURCES))
LOBJS := $(patsubst %.c, %.lo, $(SOURCES))
MKFS := $(patsubst %.c, %.mk, $(SOURCES))
EXE_STATIC := $(patsubst %.c, %-static.exe, $(SOURCES))
EXE_DYNAMIC := $(patsubst %.c, %-dynamic.exe, $(SOURCES))

MIE_ARGS ?=

all: test

-include $(MKFS)

test: check-test-driver test-static test-dynamic

test-static: $(TEST_DRIVER) $(EXE_STATIC) runner.py morello-tests.json
	python3 runner.py static $(MORELLO_TESTS_PROCS) \
	$(CURDIR)/src morello-tests.json $(TEST_DRIVER) custom morello-custom-static-results.xml \
	$(TEST_RUNNER_TAGS)

test-dynamic: $(TEST_DRIVER) $(EXE_DYNAMIC) runner.py morello-tests.json
	python3 runner.py dynamic $(MORELLO_TESTS_PROCS) \
	$(CURDIR)/src morello-tests.json $(TEST_DRIVER) custom morello-custom-dynamic-results.xml \
	$(TEST_RUNNER_TAGS)

build: $(EXE_STATIC) $(EXE_DYNAMIC)

check-test-driver:
ifndef TEST_DRIVER
	$(error TEST_DRIVER is undefined - please supply a path to a valid test driver)
else ifeq ("$(wildcard $(TEST_DRIVER))", "")
	$(error TEST_DRIVER file does not exist - please supply a path to a valid test driver)
endif

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.lo: %.c
	$(CC) $(CFLAGS) -D DYNAMIC -fPIC -c $< -o $@

src/lib/lib%.so: src/lib/%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -shared $< -o $@

include ldso.mk

%-static.exe: %.o $(addprefix $(MUSLLIB)/,$(MUSL_BITS_STATIC))
	$(CC) $(LDFLAGS) $< -o $@ $(LDLIBS) -static $(CFLAGS_MORELLO_STATIC)

%-dynamic.exe: %.lo $(addprefix $(MUSLLIB)/,$(MUSL_BITS_DYNAMIC))
	$(CC) $(LDFLAGS) $< -o $@ $(LDLIBS) -Wl,--dynamic-linker,$(MUSLLIB)/libc.so

run-%: src/%.exe
	$< $(TEST_ARGS)

ifdef USER
NAMESPACE := $(USER)
else
NAMESPACE := morello-tests
endif

BUNDLE_NAME = morello-musl-tests
TEST_RUNNER_SHELL_SCRIPT_NAME = test-runner.sh

shell-script: src/$(TEST_RUNNER_SHELL_SCRIPT_NAME)

bundle-tests: $(BUNDLE_NAME).tar

$(BUNDLE_NAME).tar: $(EXE_STATIC) $(EXE_DYNAMIC) src/$(TEST_RUNNER_SHELL_SCRIPT_NAME)
	@rm -rf $(BUNDLE_NAME)
	@mkdir -p $(BUNDLE_NAME)/lib $(BUNDLE_NAME)/resources
	cp $^ $(BUNDLE_NAME)
	cp src/lib/*.so $(BUNDLE_NAME)/lib
	cp src/resources/* $(BUNDLE_NAME)/resources/
	cp $(MUSLLIB)/libc.so $(BUNDLE_NAME)/lib
	find $(BUNDLE_NAME) -type f -name \*-dynamic.exe -exec patchelf --set-interpreter ./lib/libc.so {} \;
	find $(BUNDLE_NAME) -type f -name \*-dynamic.exe -exec patchelf --set-rpath '$$ORIGIN/lib' {} \;
	tar -cf $@ $(BUNDLE_NAME)
	@rm -rf $(BUNDLE_NAME)

src/$(TEST_RUNNER_SHELL_SCRIPT_NAME): $(EXE_STATIC) $(EXE_DYNAMIC) runner.py shell-runner-gen.py morello-tests.json
	python3 shell-runner-gen.py $@ $(CURDIR)/src morello-tests.json custom $(TEST_RUNNER_TAGS)

.PHONY: clean check-test-driver test build test-static test-dynamic shared-libraries
.PNONY: shell-script bundle-tests

clean:
	@rm -vf *-results.xml $(EXE_STATIC) $(EXE_DYNAMIC) $(OBJS) $(LOBJS) $(SLOBJS) $(SSLOBJS)
	@rm -vrf /tmp/$(NAMESPACE)/morello-musl-tests-*
	@rm -vf src/$(TEST_RUNNER_SHELL_SCRIPT_NAME) $(BUNDLE_NAME).tar
	@rm -rf $(BUNDLE_NAME)
