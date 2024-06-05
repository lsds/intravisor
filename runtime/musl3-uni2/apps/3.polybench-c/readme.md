

# Expected Output 


```
root@cheribsd-morello-hybrid:/e # ./intravisor -y musl-uni-ldso.yaml
Using yaml.cfg = musl-uni-ldso.yaml
***************** [16] Deploy 'musl-libc' ***************
BUILDING cvm: name=musl-libc, disk=(null), runtime=libos.so, net=(null), args='/ld.so /app/sc_main', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
Extra payload: old 76000, new 75d98
mmap: 400000000, +76000, ret= 400000000
[2]: 5169a8221000 400000000 e25c e25c 5169a8221000 e25c
[3]: 5169a822f260 40001e260 20644 20644 5169a822f260 20644
end of RO: 40004e8b0
[4]: 5169a824f8b0 40004e8b0 17d0 17d0 5169a824f8b0 17d0
[5]: 5169a8251080 400060080 11f0 15cd8 5169a8251080 11f0
ELF BASE = 0x400000000, MAP SIZE = 75d98, ENTRY = 0x1fce5
encl_map.entry = 0x1fce5
encl_map.ret = 0x1f444
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x43e000000 -- 440000000]
Convrting free memory into cVM Heap: 400076000 -- 43e000000 +3df8a000 ( 991.539062 MB)
cVM has cvm_heap_begin (6be50) and cvm_heap_size (6be30)
SEALED RET FROM MON 0x80459a90 0x80459a80
ACHTUNG: 'libos.so' has syscall handler 'syscall_handler' at 0x1f47d
Deploy 16 in 0.023000, SHA-256 Hash: 7f023631a00d8013b40ae9e784f564a867c86e6eac2145ecf77f30adcb38905f
***************** [17] Deploy 'musl' ***************
BUILDING cvm: name=musl, disk=(null), runtime=libldso.so, net=(null), args='/ld.so /app/sc_main', base=0x440000000, size=0x40000000, begin=0x440000000, end=0x480000000, cb_in = '(null)', cb_out = 'libos.so' wait = -1s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
Extra payload: old e3000, new e2100
mmap: 440000000, +e3000, ret= 440000000
[2]: 5169a8221000 440000000 4eda4 4eda4 5169a8221000 4eda4
[3]: 5169a826fdb0 44005edb0 58d78 58d78 5169a826fdb0 58d78
end of RO: 4400c7b30
[4]: 5169a82c8b30 4400c7b30 3ad0 3ad0 5169a82c8b30 3ad0
[5]: 5169a82cc600 4400db600 660 6ac0 5169a82cc600 660
ELF BASE = 0x440000000, MAP SIZE = e2100, ENTRY = 0xb0471
encl_map.entry = 0xb0471
encl_map.ret = 0x96b6c
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x47e000000 -- 480000000]
Convrting free memory into cVM Heap: 4400e3000 -- 47e000000 +3df1d000 ( 991.113281 MB)
cVM has cvm_heap_begin (dc840) and cvm_heap_size (dc820)
SEALED RET FROM MON 0x80459a90 0x80459a80
Deploy 17 in 0.026000, SHA-256 Hash: d6792f7fa8ac6e40e2036bd66d7ee06b6a6b3f0320765999c2e45cadeae07b66
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 43fffc000, old TP = 43ffffbe0 sp_read = 0x440000000, me->stacl = 0x43ff80000, getSP()=0x43ffff970, me->c_tp = 0x43ffffbd0 43ffffbc0
[1] '/app/sc_main'
&env0 = 0x43fffc040, &env2=0x43fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 000000000001fce5
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 000000000024a410
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0003717d type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 000000000024a478
ca6: sealed ret from mon
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 000000000001f445
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000043ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 43ffffa40
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000043ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x43fffc000, tp = 0x43ffff9f0, &cinv_args = 0x43ffffa70
TP_ARGS: 43e001000, 10, 43ff81000
-----------------------------------------------
hello musl2-uni2 
prepare nolibos init

cVM Heap: 400076000 -- 7df916000 +3df8a000 ( %f MB)
ptr = 0x400076040, 76040
67
69
72
74
76
78
80
82
86
Size of libos stat: 128
Offset of st_dev:	0, Size: 8
Offset of st_ino:	8, Size: 8
Offset of st_mode:	16, Size: 4
Offset of st_nlink:	20, Size: 4
Offset of st_uid:	24, Size: 4
Offset of st_gid:	28, Size: 4
Offset of st_rdev:	32, Size: 8
Offset of __pad:	40, Size: 8
Offset of si_size:	48, Size: 8
Offset of st_blksize:	56, Size: 4
Offset of __pad2:	60, Size: 4
Offset of st_blocks:	64, Size: 8
Offset of st_atim:	72, Size: 16
Offset of st_mtim:	88, Size: 16
Offset of st_ctim:	104, Size: 16
Offset of unused:	120, Size: 8
S_IFMT = f000, S_IFDIR = 4000
O_DIRECTORY = 0x4000
88
90
92
fd = 3
wrote 12 
fd = 3
read 12 from file = hello world
....testing /dev/zero
/dev/zero fd = 3
read 128 bytes from /dev/zero
....testing /dev/random
/dev/zero fd = 3
read 8 bytes from /dev/random, rd=15eb5fb9fffa783a
....testing /dev/stdout
/dev/stdout fd = 3
write 19 bytes to /dev/stdout ('Hello /dev/stdout
')
Hello /dev/stdout
--------- LibOS is ok,  ------- 

app_main inside kernel, just init ramfs

WARNING: get_file_size is unsafe and doesnt filename (root.cpio) when it loads
WARNING: copy_file_into_cvm is unsafe and doesnt check where (0x400079f80/65536) and what (root.cpio) it loads
size2 = 65536, size = 65536
., 79ff0 (size 0)
app1, 7a064 (size 64784)
writing file '/app1', ret = 64784, size = 64784
.gitkeep, 89dec (size 0)
creating dir '/.gitkeep', ret = 0
target SP = 47fffc000, old TP = 47ffffbe0 sp_read = 0x480000000, me->stacl = 0x47ff80000, getSP()=0x47ffff970, me->c_tp = 0x47ffffbd0 47ffffbc0
[1] '/app/sc_main'
&env0 = 0x47fffc040, &env2=0x47fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000440000000 length 0000000040000000 ofset 00000000000b0471
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000440000000 length 0000000040000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
    base 0000000440000000 length 0000000040000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 000000000001f47d
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 0 s 0 perms 00000000 type 0000000000000000
    base 0000000000000000 length ffffffffffffffff ofset 0000000000202fe0
ca6: sealed ret from mon
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000440000000 length 0000000040000000 ofset 0000000000096b6d
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000047ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 47ffffa40
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000047ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x47fffc000, tp = 0x47ffff9f0, &cinv_args = 0x47ffffa70
TP_ARGS: 47e001000, 11, 47ff81000
-----------------------------------------------
ldso.phdr = 440000040, base = 440000000/440000000 40
Version: 0x1 Entry = 0xb0471 Machine b7 Type = 3
tid = 550000
cVM Heap: 4400e3000 -- 47e000000 +3df1d000 ( 991.113281 MB)
ldso: Loading ELF:	 allocated 0x4400e4000, +3d000
Version: 0x1 Entry = 0x1c045 Machine b7 Type = 3
CAPINIT: 44009b831 --> 440120ec0, tag 1 
CAPINIT: 44006716d --> 440120ed0, tag 1 
CAPINIT: 44007c6fd --> 440120ee0, tag 1 
CAPINIT: 4400a44fd --> 440120ef0, tag 1 
CAPINIT: 440099c75 --> 440120f00, tag 1 
CAPINIT: 44006f235 --> 440120f10, tag 1 
CAPINIT: 44006f1b9 --> 440120f20, tag 1 
CAPINIT: 440066ec5 --> 440120f30, tag 1 
CAPINIT: 4400ad3b5 --> 440120f40, tag 1 
CAPINIT: 440070775 --> 440120f50, tag 1 
CAPINIT: 44006678d --> 440120f60, tag 1 
RELATIVE: 4400e541d --> 440110520, tag 1
RELATIVE: 4400e54a4 --> 440110530, tag 1
RELATIVE: 4400e53ed --> 440110540, tag 1
RELATIVE: 4400e5386 --> 440110550, tag 1
RELATIVE: 4400e5396 --> 440110560, tag 1
RELATIVE: 4400e540e --> 440110570, tag 1
RELATIVE: 4400e54ab --> 440110580, tag 1
RELATIVE: 4400e54ff --> 440110590, tag 1
RELATIVE: 4400e5490 --> 4401105a0, tag 1
RELATIVE: 4400e5506 --> 4401105b0, tag 1
RELATIVE: 4400e542a --> 4401105c0, tag 1
RELATIVE: 4400e5431 --> 4401105d0, tag 1
RELATIVE: 4400e539b --> 4401105e0, tag 1
RELATIVE: 4400e53b7 --> 4401105f0, tag 1
RELATIVE: 4400e54b2 --> 440110600, tag 1
RELATIVE: 4400e53fa --> 440110610, tag 1
RELATIVE: 4400e5330 --> 440110620, tag 1
RELATIVE: 4400e5413 --> 440110630, tag 1
RELATIVE: 4400e549c --> 440110640, tag 1
RELATIVE: 4400e53ca --> 440110650, tag 1
RELATIVE: 4400e54f5 --> 440110660, tag 1
RELATIVE: 4400e53d3 --> 440110670, tag 1
RELATIVE: 4400e54a6 --> 440110680, tag 1
RELATIVE: 4400e54c5 --> 440110690, tag 1
RELATIVE: 4400e543a --> 4401106a0, tag 1
RELATIVE: 4400e5402 --> 4401106b0, tag 1
RELATIVE: 4400e53bd --> 4401106c0, tag 1
RELATIVE: 4400e537c --> 4401106d0, tag 1
RELATIVE: 4400e547f --> 4401106e0, tag 1
RELATIVE: 4400e53a6 --> 4401106f0, tag 1
RELATIVE: 4400e5337 --> 440110700, tag 1
RELATIVE: 4400e54ce --> 440110710, tag 1
RELATIVE: 4400e54b9 --> 440110720, tag 1
RELATIVE: 4400e54a4 --> 440110730, tag 1
RELATIVE: 4400e54ce --> 440110740, tag 1
RELATIVE: 4400e54b9 --> 440110750, tag 1
RELATIVE: 4400e54a4 --> 440110760, tag 1
RELATIVE: 4400e54ce --> 440110770, tag 1
RELATIVE: 4400e54b9 --> 440110780, tag 1
RELATIVE: 4400e54a4 --> 440110790, tag 1
RELATIVE: 4400e54ce --> 4401107a0, tag 1
RELATIVE: 4400e54b9 --> 4401107b0, tag 1
RELATIVE: 4400e54a4 --> 4401107c0, tag 1
RELATIVE: 4400e54ce --> 4401107d0, tag 1
RELATIVE: 4400e54b9 --> 4401107e0, tag 1
RELATIVE: 4400e54a4 --> 4401107f0, tag 1
RELATIVE: 4400e54ce --> 440110800, tag 1
RELATIVE: 4400e54b9 --> 440110810, tag 1
RELATIVE: 4400e54a4 --> 440110820, tag 1
RELATIVE: 4400e54ce --> 440110830, tag 1
RELATIVE: 4400e54b9 --> 440110840, tag 1
RELATIVE: 4400e54a4 --> 440110850, tag 1
RELATIVE: 4400e54ce --> 440110860, tag 1
RELATIVE: 4400e54b9 --> 440110870, tag 1
RELATIVE: 4400e54a4 --> 440110880, tag 1
RELATIVE: 4400e54ce --> 440110890, tag 1
RELATIVE: 4400e54b9 --> 4401108a0, tag 1
RELATIVE: 4400e54a4 --> 4401108b0, tag 1
RELATIVE: 4400e54ce --> 4401108c0, tag 1
RELATIVE: 4400e54b9 --> 4401108d0, tag 1
RELATIVE: 4400e54a4 --> 4401108e0, tag 1
RELATIVE: 4400e54ce --> 4401108f0, tag 1
RELATIVE: 4400e54b9 --> 440110900, tag 1
RELATIVE: 4400e54a4 --> 440110910, tag 1
RELATIVE: 4400e54ce --> 440110920, tag 1
RELATIVE: 4400e54b9 --> 440110930, tag 1
RELATIVE: 4400e54a4 --> 440110940, tag 1
RELATIVE: 4400e54ce --> 440110950, tag 1
RELATIVE: 4400e54b9 --> 440110960, tag 1
RELATIVE: 4400e54a4 --> 440110970, tag 1
RELATIVE: 4400e54ce --> 440110980, tag 1
RELATIVE: 4400e54b9 --> 440110990, tag 1
RELATIVE: 4400e54a4 --> 4401109a0, tag 1
RELATIVE: 4400e54ce --> 4401109b0, tag 1
RELATIVE: 4400e54b9 --> 4401109c0, tag 1
RELATIVE: 4400e54a4 --> 4401109d0, tag 1
RELATIVE: 4400e54ce --> 4401109e0, tag 1
RELATIVE: 4400e54b9 --> 4401109f0, tag 1
RELATIVE: 4400e54a4 --> 440110a00, tag 1
RELATIVE: 4400e54ce --> 440110a10, tag 1
RELATIVE: 4400e54b9 --> 440110a20, tag 1
RELATIVE: 4400e54a4 --> 440110a30, tag 1
RELATIVE: 4400e54ce --> 440110a40, tag 1
RELATIVE: 4400e54b9 --> 440110a50, tag 1
RELATIVE: 4400e54a4 --> 440110a60, tag 1
RELATIVE: 4400e54ce --> 440110a70, tag 1
RELATIVE: 4400e54c1 --> 440110a80, tag 1
RELATIVE: 4400e54a4 --> 440110a90, tag 1
RELATIVE: 4400e54ce --> 440110aa0, tag 1
RELATIVE: 4400e54b9 --> 440110ab0, tag 1
RELATIVE: 4400e54a4 --> 440110ac0, tag 1
RELATIVE: 4400e54ce --> 440110ad0, tag 1
RELATIVE: 4400e54b9 --> 440110ae0, tag 1
RELATIVE: 4400e54a4 --> 440110af0, tag 1
RELATIVE: 4400e54ce --> 440110b00, tag 1
RELATIVE: 4400e54b9 --> 440110b10, tag 1
RELATIVE: 4400e54a4 --> 440110b20, tag 1
RELATIVE: 4400e54ce --> 440110b30, tag 1
RELATIVE: 4400e54b9 --> 440110b40, tag 1
RELATIVE: 4400e54a4 --> 440110b50, tag 1
RELATIVE: 4400e54ce --> 440110b60, tag 1
RELATIVE: 4400e54c1 --> 440110b70, tag 1
RELATIVE: 4400e54a4 --> 440110b80, tag 1
RELATIVE: 4400e54ce --> 440110b90, tag 1
RELATIVE: 4400e54b9 --> 440110ba0, tag 1
RELATIVE: 4400e54a4 --> 440110bb0, tag 1
RELATIVE: 4400e54ce --> 440110bc0, tag 1
RELATIVE: 4400e54b9 --> 440110bd0, tag 1
RELATIVE: 4400e54a4 --> 440110be0, tag 1
RELATIVE: 4400e54ce --> 440110bf0, tag 1
RELATIVE: 4400e54b9 --> 440110c00, tag 1
RELATIVE: 4400e54a4 --> 440110c10, tag 1
RELATIVE: 4400e54ce --> 440110c20, tag 1
RELATIVE: 4400e54b9 --> 440110c30, tag 1
RELATIVE: 4400e54a4 --> 440110c40, tag 1
RELATIVE: 4400e54ce --> 440110c50, tag 1
RELATIVE: 4400e54b9 --> 440110c60, tag 1
RELATIVE: 4400e54a4 --> 440110c70, tag 1
RELATIVE: 4400e54ce --> 440110c80, tag 1
RELATIVE: 4400e54b9 --> 440110c90, tag 1
RELATIVE: 4400e54a4 --> 440110ca0, tag 1
RELATIVE: 4400e53e1 --> 440110cb0, tag 1
RELATIVE: 4400e54cf --> 440110cc0, tag 1
RELATIVE: 4400e5366 --> 440110cd0, tag 1
RELATIVE: 4400e53c3 --> 440110ce0, tag 1
RELATIVE: 4400e5343 --> 440110cf0, tag 1
RELATIVE: 4400e544c --> 440110d00, tag 1
RELATIVE: 4400f61e1 --> 440110e50, tag 1
RELATIVE: 440120f90 --> 440110e70, tag 1
RELATIVE: 440120f98 --> 440110e80, tag 1
CAPINIT: 4400c9fa0 --> 440110e60, tag 1 
hello world

correlation	1.300656
princovariance	1.251255
2mm	15.419167
3mm	22.154001
atax_	0.027407
bicg_	0.073224
cholensky_	0.204819
doitgen_	0.438154
gemm_	8.251726
gemver_	0.165290
getsummv_	0.072901
mvt_	0.116968
symm_	9.879971
syr2k_	2.263697
syrk_	1.344885
trisolv_	0.011404
trimm_	0.879959
durbin_	0.181234
dynprog_	0.284007
gramschmidt_	0.951705
lu_	0.294896
ludcmp_	0.886180
foloyd_warshall_	1.292714
reg_detect	0.012642
adi_	0.971783
fdtd_2d 	0.234405
jacobi_1d_imper	0.000879
jacobi_2d_imper	0.052863
seidel_2d 	0.205260
root@cheribsd-morello-hybrid:/e # 
```
