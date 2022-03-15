include ../../../../config.mak

CFLAGS=-fPIC -fPIE -pie

ifneq ($(MODE),sim)
endif

DEPS = 
OBJ = main.o tramps.o hostcalls.o

default: libinner_h.so

%.o: %.c $(DEPS)
	$(CC_CHERI) $(CC_CHERI_FLAGS) -c -o $@ $< $(CFLAGS)

tramps.o: tramps.S
	$(CC_CHERI) $(CC_CHERI_FLAGS) $(CFLAGS) -c -o tramps.o tramps.S

libinner_h.so: $(OBJ)
	$(CC_CHERI) $(CC_CHERI_FLAGS) $(CFLAGS) -o $@ -nostdinc -nostdlib -Wl,-ehello_asm -fPIE -fPIC $(OBJ)


clean:
	rm -rf ./*.o ./*.so