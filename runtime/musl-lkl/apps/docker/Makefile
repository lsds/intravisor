# ggml, tf1 are 0x80000000 and not built in all

ifeq ($(origin DSUBDIRS), undefined)
  OR_IFEQ_DSUBDIRS := true
endif

ifeq ($(DSUBDIRS), default)
  OR_IFEQ_DSUBDIRS := true
endif

ifeq ($(OR_IFEQ_DSUBDIRS), true)
DSUBDIRS := hello

ifeq ($(LKL_MUSL_BUILD), riscv64)
DSUBDIRS += redis
endif

ifeq ($(LKL_MUSL_BUILD), aarch64)
DSUBDIRS += sysbench pandas
endif

endif

.PHONY: all clean install

all:
	@for dir in $(DSUBDIRS); do \
	if [ -f "$$dir/Makefile" ]; then \
            $(MAKE) -C $$dir || { echo "Make failed in $$dir"; exit 1; }; \
        fi \
	done

install:
	@for dir in $(DSUBDIRS); do \
	if [ -f "$$dir/Makefile" ]; then \
            $(MAKE) -C $$dir install || { echo "Make install failed in $$dir"; exit 1; }; \
        fi \
	done

clean:
	@for dir in $(DSUBDIRS); do \
        if [ -f "$$dir/Makefile" ]; then \
            $(MAKE) -C $$dir clean; \
        fi \
	done

