MAKEFILE := $(shell git rev-parse --show-toplevel)/cfg.mak
include $(MAKEFILE)

LIBOS_PATH := ../..

CFLAGS=-fPIC -fPIE -pie -g -O2  -nostdinc \
	$(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_PURE) -B$(CROSS_COMPILE) $(ARCH_PURE) \
	 -I $(LIBOS_PATH)/musl-host/include  \
	

DEPS = 
OBJDIR = obj
SRC = main.c

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


default: libpolybench-c.so


$(OBJDIR)/%.o: %.c $(DEPS) $(PASS1) $(PASS2) 
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS)


libpolybench-c.so: $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ) $(LD_FLAGS) $(LIBOS_PATH)/libmusl-uni.a

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR)

install:
	sudo mkdir -p ${INSTALL_PATH}
	sudo cp ./*.yaml ./*.so ./*.ci  ${INSTALL_PATH}
