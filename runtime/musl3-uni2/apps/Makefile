# List of subdirectories to traverse
ALL_SUBDIRS := $(wildcard */)

EXCLUDE_SUBDIR := 15.htop/
SUBDIRS := $(filter-out $(EXCLUDE_SUBDIR), $(ALL_SUBDIRS))

.PHONY: all clean install

all:
	@for dir in $(SUBDIRS); do \
	if [ -f "$$dir/Makefile" ]; then \
            $(MAKE) -C $$dir || { echo "Make failed in $$dir"; exit 1; }; \
        fi \
	done

install:
	@for dir in $(SUBDIRS); do \
	if [ -f "$$dir/Makefile" ]; then \
            $(MAKE) -C $$dir install || { echo "Make install failed in $$dir"; exit 1; }; \
        fi \
	done

clean:
	@for dir in $(SUBDIRS); do \
        if [ -f "$$dir/Makefile" ]; then \
            $(MAKE) -C $$dir clean; \
        fi \
	done

