include ../../../../config.mak

CFLAGS=-fPIC -fPIE -pie

ifneq ($(MODE),sim)
endif

DEPS = 
OBJ = main.o tramps.o hostcalls.o

default: libinner_p.so

%.o: %.c $(DEPS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $@ $< $(CFLAGS)

tramps.o: tramps.S
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -c -o tramps.o tramps.S

libinner_p.so: $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdinc -nostdlib -Wl,-ehello_c -fPIE -fPIC $(OBJ)


clean:
	rm -rf ./*.o ./*.so