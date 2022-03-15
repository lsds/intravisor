include ../../../config.mak

CFLAGS=-fPIC -fPIE -pie -g -O2

ifneq ($(MODE),sim)
endif

DEPS = 
OBJ = main.o tramps.o hostcalls.o

default: libouter_p.so

%.o: %.c $(DEPS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $@ $< $(CFLAGS)

tramps.o: tramps.S
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -c -o tramps.o tramps.S

libouter_p.so: $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdinc -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ)

clean:
	rm -rf ./*.o ./*.so