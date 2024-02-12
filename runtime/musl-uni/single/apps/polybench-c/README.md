# polybench-c 

## expected output 

```
Using yaml.cfg = /intravisor/cvm.yaml
***************** [16] Deploy 'hello' ***************
BUILDING cvm: name=hello, disk=(null), runtime=libpolybench-c.so, net=(null), args='/ld.so /app/sc_main', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
[2]: 8a3db000 400000000 7d7c 7d7c 8a3db000 7d7c
[3]: 8a3e2d80 400017d80 1872c 1872c 8a3e2d80 1872c
end of RO: 4000404b0
[4]: 8a3fb4b0 4000404b0 e50 e50 8a3fb4b0 e50
[5]: 8a3fc300 400051300 800 18718 8a3fc300 800
ELF BASE = 0x400000000, MAP SIZE = 69a18, ENTRY = 0x22215
encl_map.entry = 0x22215
encl_map.ret = 0x22124
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x43e000000 -- 440000000]
Convrting free memory into cVM Heap: 40006a000 -- 43e000000 +3df96000 ( 991.585938 MB)
cVM has cvm_heap_begin (5fb30) and cvm_heap_size (5fb10)
SEALED RET FROM MON 0x80933ba0 0x80933b90
ACHTUNG: 'libpolybench-c.so' has syscall handler 'syscall_handler' at 0x2215d
Deploy 16 in 0.968000, SHA-256 Hash: ce785505686f9ec4606151615577ef7ce861810d27a268375e82d00bc6988c72
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 43fffc000, old TP = 43ffffbe0 sp_read = 0x440000000, me->stacl = 0x43ff80000, getSP()=0x43ffff970, me->c_tp = 0x43ffffbd0 43ffffbc0
[1] '/app/sc_main'
&env0 = 0x43fffc040, &env2=0x43fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000022215
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 0000000000249668
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0003717d type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 00000000002496d0
ca6: sealed ret from mon
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000022125
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000043ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 43ffffa40
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000043ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x43fffc000, tp = 0x43ffff9f0, &cinv_args = 0x43ffffa70
TP_ARGS: 43e001000, 10, 43ff81000
-----------------------------------------------
hello musl-uni 
prepare nolibos initcVM Heap: 40006a000 -- 7df9ca000 +3df96000 ( 991.585938 MB)
ptr = 0x40006a040, 6a040
424
426
Mount ramfs to /...
VFS: mounting ramfs at /
428
Mount devfs to /dev...VFS: mounting devfs at /dev
430
Register 'null' to devfs
Register 'zero' to devfs
432
Register 'urandom' and 'random' to devfs
434
Initialize random number generator...fd = 0
wrote 12 
fd = 3
read 12 from file = hello world
....testing /dev/zero/dev/zero fd = 3
read 128 bytes from /dev/zero
....testing /dev/random/dev/zero fd = 3
read 8 bytes from /dev/random, rd=a7135e24912251f8
--------- LibOS is ok,  ------- 
hello world
correlation	35.590580
princovariance	34.996460
2mm	158.169392
3mm	286.847631
atax_	1.558899
bicg_	2.335701
cholensky_	13.051987
doitgen_	13.896223
gemm_	84.606212
gemver_	3.948132
getsummv_	2.352736
mvt_	2.101429
symm_	230.047111
syr2k_	106.585331
syrk_	53.496771
trisolv_	0.746160
trimm_	32.896068
durbin_	3.725163
dynprog_	12.271812
gramschmidt_	13.088341
lu_	29.014978
ludcmp_	23.902411
foloyd_warshall_	61.866791
reg_detect	0.660707
adi_	17.756195
fdtd_2d 	9.190729
jacobi_1d_imper	0.086513
jacobi_2d_imper	2.336631
seidel_2d 	1.869417
```
