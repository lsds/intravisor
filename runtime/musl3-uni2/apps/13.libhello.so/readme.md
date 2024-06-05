# About 

Test for loading shared libraries


# Expected Output 


```
root@cheribsd-morello-hybrid:/e # ./intravisor -y musl-uni-ldso.yaml
Using yaml.cfg = musl-uni-ldso.yaml
***************** [16] Deploy 'musl-libc' ***************
BUILDING cvm: name=musl-libc, disk=(null), runtime=libos.so, net=(null), args='/ld.so /app/sc_main', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
Extra payload: old 76000, new 75d98
mmap: 400000000, +76000, ret= 400000000
[2]: 721e0621000 400000000 e25c e25c 721e0621000 e25c
[3]: 721e062f260 40001e260 20644 20644 721e062f260 20644
end of RO: 40004e8b0
[4]: 721e064f8b0 40004e8b0 17d0 17d0 721e064f8b0 17d0
[5]: 721e0651080 400060080 11f0 15cd8 721e0651080 11f0
ELF BASE = 0x400000000, MAP SIZE = 75d98, ENTRY = 0x1fce5
encl_map.entry = 0x1fce5
encl_map.ret = 0x1f444
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x43e000000 -- 440000000]
Convrting free memory into cVM Heap: 400076000 -- 43e000000 +3df8a000 ( 991.539062 MB)
cVM has cvm_heap_begin (6be50) and cvm_heap_size (6be30)
SEALED RET FROM MON 0x81015080 0x81015070
ACHTUNG: 'libos.so' has syscall handler 'syscall_handler' at 0x1f47d
Deploy 16 in 0.023000, SHA-256 Hash: 7f023631a00d8013b40ae9e784f564a867c86e6eac2145ecf77f30adcb38905f
***************** [17] Deploy 'musl' ***************
BUILDING cvm: name=musl, disk=(null), runtime=libldso.so, net=(null), args='/ld.so /app/sc_main', base=0x440000000, size=0x40000000, begin=0x440000000, end=0x480000000, cb_in = '(null)', cb_out = 'libos.so' wait = -1s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
Extra payload: old e3000, new e2100
mmap: 440000000, +e3000, ret= 440000000
[2]: 721e0621000 440000000 4eda4 4eda4 721e0621000 4eda4
[3]: 721e066fdb0 44005edb0 58d78 58d78 721e066fdb0 58d78
end of RO: 4400c7b30
[4]: 721e06c8b30 4400c7b30 3ad0 3ad0 721e06c8b30 3ad0
[5]: 721e06cc600 4400db600 660 6ac0 721e06cc600 660
ELF BASE = 0x440000000, MAP SIZE = e2100, ENTRY = 0xb0471
encl_map.entry = 0xb0471
encl_map.ret = 0x96b6c
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x47e000000 -- 480000000]
Convrting free memory into cVM Heap: 4400e3000 -- 47e000000 +3df1d000 ( 991.113281 MB)
cVM has cvm_heap_begin (dc840) and cvm_heap_size (dc820)
SEALED RET FROM MON 0x81015080 0x81015070
Deploy 17 in 0.027000, SHA-256 Hash: d6792f7fa8ac6e40e2036bd66d7ee06b6a6b3f0320765999c2e45cadeae07b66
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
WARNING: copy_file_into_cvm is unsafe and doesnt check where (0x400079f80/14336) and what (root.cpio) it loads
size2 = 14336, size = 14336
., 79ff0 (size 0)
app1, 7a064 (size 6240)
writing file '/app1', ret = 6240, size = 6240
libso_test.so, 7b940 (size 3376)
writing file '/libso_test.so', ret = 3376, size = 3376
usr, 7c6e4 (size 0)
creating dir '/usr', ret = 0
usr/lib, 7c75c (size 0)
creating dir '/usr/lib', ret = 0
usr/lib/.gitkeep, 7c7dc (size 0)
creating dir '/usr/lib/.gitkeep', ret = 0
usr/lib/libso_test.so, 7c860 (size 3376)
writing file '/usr/lib/libso_test.so', ret = 3376, size = 3376
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
ldso: Loading ELF:	 allocated 0x4400e4000, +31000
Version: 0x1 Entry = 0x1061d Machine b7 Type = 3
ldso: Loading ELF:	 allocated 0x440116000, +31000
CAPINIT: 44009b831 --> 440146580, tag 1 
RELATIVE: 440116380 --> 440136440, tag 1
CAPINIT: 44009b831 --> 440114c30, tag 1 
CAPINIT: 4401263ed --> 440114c40, tag 1 
CAPINIT: 44006716d --> 440114c50, tag 1 
CAPINIT: 44006678d --> 440114c60, tag 1 
RELATIVE: 4400e4540 --> 440104a90, tag 1
RELATIVE: 4400f45e1 --> 440104bf0, tag 1
app main
hello world from lib
root@cheribsd-morello-hybrid:/e # 
```
