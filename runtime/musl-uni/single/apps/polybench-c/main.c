#include <stdio.h>
#include <stdlib.h>

extern int correlation_main();
extern int covariance_main();
extern int mm2_main();
extern int mm3_main();
extern int atax_main();
extern int bicg_main();
extern int cholensky_main();
extern int doitgen_main();
extern int gemm_main();
extern int gemver_main();
extern int getsummv_main();
extern int mvt_main();
extern int symm_main();
extern int syr2k_main();
extern int syrk_main();
extern int trisolv_main();
extern int trimm_main();
extern int durbin_main();
extern int dynprog_main();
extern int gramschmidt_main();
extern int lu_main();
extern int ludcmp_main();
extern int foloyd_warshall_main();
extern int reg_detect_main();
extern int adi_main();
extern int fdtd_2d_main();
extern int fdtd_apml_main();
extern int jacobi_1d_imper_main();
extern int jacobi_2d_imper_main();
extern int seidel_2d_main();


void app_main() {
    printf("hello world\n");
    printf("\n");

    printf("correlation\t");	correlation_main();
    printf("princovariance\t");	covariance_main();
    printf("2mm\t");		mm2_main();
    printf("3mm\t");		mm3_main();
    printf("atax_\t");		atax_main();
    printf("bicg_\t");		bicg_main();
    printf("cholensky_\t");	cholensky_main();
    printf("doitgen_\t");	doitgen_main();
    printf("gemm_\t");		gemm_main();
    printf("gemver_\t");	gemver_main();
    printf("getsummv_\t");	getsummv_main();
    printf("mvt_\t");		mvt_main();
    printf("symm_\t");		symm_main();
    printf("syr2k_\t");		syr2k_main();
    printf("syrk_\t");		syrk_main();
    printf("trisolv_\t");	trisolv_main();
    printf("trimm_\t");		trimm_main();
    printf("durbin_\t");	durbin_main();
    printf("dynprog_\t");	dynprog_main();
    printf("gramschmidt_\t");	gramschmidt_main();
    printf("lu_\t");		lu_main();
    printf("ludcmp_\t");	ludcmp_main();
    printf("foloyd_warshall_\t");foloyd_warshall_main();
    printf("reg_detect\t");	reg_detect_main();
    printf("adi_\t");		adi_main();
    printf("fdtd_2d \t");	fdtd_2d_main();
//    printf("fdtd_apml \t");	fdtd_apml_main();
    printf("jacobi_1d_imper\t");jacobi_1d_imper_main();
    printf("jacobi_2d_imper\t");jacobi_2d_imper_main();
    printf("seidel_2d \t");	seidel_2d_main();
}