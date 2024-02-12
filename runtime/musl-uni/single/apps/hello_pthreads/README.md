# basic pthreads


## expected output 

```
Using yaml.cfg = /intravisor/cvm.yaml
***************** [16] Deploy 'hello' ***************
BUILDING cvm: name=hello, disk=(null), runtime=libhello_pthreads.so, net=(null), args='/ld.so /app/sc_main', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
[2]: 89401000 400000000 8be4 8be4 89401000 8be4
[3]: 89409be8 400018be8 10444 10444 89409be8 10444
end of RO: 400039030
[4]: 8941a030 400039030 1090 1090 8941a030 1090
[5]: 8941b0c0 40004a0c0 6b0 186f8 8941b0c0 6b0
ELF BASE = 0x400000000, MAP SIZE = 627b8, ENTRY = 0x19745
encl_map.entry = 0x19745
encl_map.ret = 0x19654
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x43e000000 -- 440000000]
Convrting free memory into cVM Heap: 400063000 -- 43e000000 +3df9d000 ( 991.613281 MB)
cVM has cvm_heap_begin (588d0) and cvm_heap_size (588b0)
SEALED RET FROM MON 0x809ad090 0x809ad080
ACHTUNG: 'libhello_pthreads.so' has syscall handler 'syscall_handler' at 0x1968d
Deploy 16 in 1.171000, SHA-256 Hash: 497f921018bd71bfa0835ee5fe3b5fc33125878785383b3594605a63061eb969
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 43fffc000, old TP = 43ffffbe0 sp_read = 0x440000000, me->stacl = 0x43ff80000, getSP()=0x43ffff970, me->c_tp = 0x43ffffbd0 43ffffbc0
[1] '/app/sc_main'
&env0 = 0x43fffc040, &env2=0x43fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000019745
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
    base 0000000400000000 length 0000000040000000 ofset 0000000000019655
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
prepare nolibos initcVM Heap: 400063000 -- 7dfa33000 +3df9d000 ( 991.613281 MB)
ptr = 0x400063040, 63040
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
thread functionthread ret = bc, jret = 0
pthread_join works
```
