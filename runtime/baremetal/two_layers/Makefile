include ../../../config.mak

CFLAGS=-fPIC -fPIE -pie

ifneq ($(MODE),sim)
endif

DEPS = 
OBJ = main.o tramps.o hostcalls.o

default: libouter.so

%.o: %.c $(DEPS)
	$(CC_CHERI) $(CC_CHERI_FLAGS) -c -o $@ $< $(CFLAGS)

tramps.o: tramps.S
	$(CC_CHERI) $(CC_CHERI_FLAGS) $(CFLAGS) -c -o tramps.o tramps.S

libouter.so: $(OBJ)
	$(CC_CHERI) $(CC_CHERI_FLAGS) $(CFLAGS) -o $@ -nostdinc -nostdlib -Wl,-eouter_asm -fPIE -fPIC $(OBJ)


clean:
	rm -rf ./*.o ./*.so