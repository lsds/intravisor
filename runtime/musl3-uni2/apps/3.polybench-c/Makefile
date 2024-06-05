MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)

PROG=app3
OBJDIR = obj

CROSS_LIBC_PATH=../../libc/build/
CFLAGS= -I../../libc/build/include -DINTRAVISOR -O2

CFLAGS+= -I.

SRC += main.c 

SRC+=polybench-c-3.2/datamining/correlation/correlation.c 
SRC+=polybench-c-3.2/datamining/covariance/covariance.c
SRC+=polybench-c-3.2/linear-algebra/kernels/2mm/2mm.c
SRC+=polybench-c-3.2/linear-algebra/kernels/3mm/3mm.c
SRC+=polybench-c-3.2/linear-algebra/kernels/atax/atax.c
SRC+=polybench-c-3.2/linear-algebra/kernels/bicg/bicg.c
SRC+=polybench-c-3.2/linear-algebra/kernels/cholesky/cholesky.c
SRC+=polybench-c-3.2/linear-algebra/kernels/doitgen/doitgen.c
SRC+=polybench-c-3.2/linear-algebra/kernels/gemm/gemm.c
SRC+=polybench-c-3.2/linear-algebra/kernels/gemver/gemver.c
SRC+=polybench-c-3.2/linear-algebra/kernels/gesummv/gesummv.c
SRC+=polybench-c-3.2/linear-algebra/kernels/mvt/mvt.c
SRC+=polybench-c-3.2/linear-algebra/kernels/symm/symm.c
SRC+=polybench-c-3.2/linear-algebra/kernels/syr2k/syr2k.c
SRC+=polybench-c-3.2/linear-algebra/kernels/syrk/syrk.c
SRC+=polybench-c-3.2/linear-algebra/kernels/trisolv/trisolv.c
SRC+=polybench-c-3.2/linear-algebra/kernels/trmm/trmm.c
SRC+=polybench-c-3.2/linear-algebra/solvers/durbin/durbin.c
SRC+=polybench-c-3.2/linear-algebra/solvers/dynprog/dynprog.c
SRC+=polybench-c-3.2/linear-algebra/solvers/gramschmidt/gramschmidt.c
SRC+=polybench-c-3.2/linear-algebra/solvers/lu/lu.c
SRC+=polybench-c-3.2/linear-algebra/solvers/ludcmp/ludcmp.c
SRC+=polybench-c-3.2/medley/floyd-warshall/floyd-warshall.c
SRC+=polybench-c-3.2/medley/reg_detect/reg_detect.c
SRC+=polybench-c-3.2/stencils/adi/adi.c
SRC+=polybench-c-3.2/stencils/fdtd-2d/fdtd-2d.c
SRC+=polybench-c-3.2/stencils/fdtd-apml/fdtd-apml.c
SRC+=polybench-c-3.2/stencils/jacobi-1d-imper/jacobi-1d-imper.c
SRC+=polybench-c-3.2/stencils/jacobi-2d-imper/jacobi-2d-imper.c
SRC+=polybench-c-3.2/stencils/seidel-2d/seidel-2d.c

SRC +=polybench-c-3.2/utilities/polybench.c

CFLAGS += -Ipolybench-c-3.2/utilities/ -DPOLYBENCH_TIME


OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

ROOTFS := root.cpio

all: $(ROOTFS)

$(OBJDIR)/%.o: %.c
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS)

clean:
	rm -rf $(ROOTFS) $(PROG) *.o ./$(OBJDIR) rootfs/app1

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.ci ./libldso.so ${INSTALL_PATH}
	sudo cp $(ROOTFS) ${INSTALL_PATH}/$(ROOTFS)_$(shell basename $(shell ls *.yaml) .yaml)

$(PROG): $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -nostdlib -nostartfiles -o $@ $(OBJ) $(CROSS_LIBC_PATH)/lib/crt1.o $(CROSS_LIBC_PATH)/lib/crti.o $(CROSS_LIBC_PATH)/lib/crtn.o \
	-L$(CROSS_LIBC_PATH)/lib -Wl,-dynamic-linker=/lib/ld-linux-aarch64_purecap.so.1 ../../libc/libcompiler_rt.a -lc -pie


$(ROOTFS): $(PROG) $(CROSS_LIBC_PATH)/lib/libc.so
	cp $(PROG) rootfs/app1
	cp $(CROSS_LIBC_PATH)/lib/libc.so ./libldso.so
	cd rootfs && find . -print -depth | sort | $(CPIO) -vo -H newc > ../$(ROOTFS)

