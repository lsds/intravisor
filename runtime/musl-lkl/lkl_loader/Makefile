#MODE=sim

CFLAGS=-I ../build/lkl/include -fPIC

CHERI_FLAGS = 

ifneq ($(MODE),sim)
#loader fetches headers from lkl and generates stubs for syscalls.
#this code becomes cap-aware. perhaps it adds memset/ and similar functions, and lkl crushes because registers don't have caps 
#so, long story short, CHERI_FLAGS should be used only with .S file
#why it worked previosly I have idea, maybe I missed some flags
CHERI_FLAGS= -target riscv64-unknown-linux -march=rv64gcxcheri -mabi=lp64d
endif


DEPS = 
OBJ = loader.o tramps.o lkl_int.o

default: lkl_loader.a

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tramps.o: tramps.S
	$(CC) -o tramps.o tramps.S -c -fPIC -fPIE $(CHERI_FLAGS)

lkl_loader.a: $(OBJ)
	ar rcs ../build/$@ loader.o tramps.o lkl_int.o

clean:
	rm -rf ./*.o ../build/lkl_loader.a