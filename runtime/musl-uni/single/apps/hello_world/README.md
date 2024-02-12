# basic hello world for pure-cap environment

## expected output

```
Using yaml.cfg = /intravisor/cvm.yaml
***************** [16] Deploy 'hello' ***************
BUILDING cvm: name=hello, disk=(null), runtime=libhello_world.so, net=(null), args='/ld.so /app/sc_main', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
[2]: 8a838000 400000000 66b4 66b4 8a838000 66b4
[3]: 8a83e6b8 4000166b8 eb1c eb1c 8a83e6b8 eb1c
end of RO: 4000351e0
[4]: 8a84d1e0 4000351e0 9e0 9e0 8a84d1e0 9e0
[5]: 8a84dbc0 400045bc0 650 18528 8a84dbc0 650
ELF BASE = 0x400000000, MAP SIZE = 5e0e8, ENTRY = 0x17685
encl_map.entry = 0x17685
encl_map.ret = 0x17594
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x43e000000 -- 440000000]
Convrting free memory into cVM Heap: 40005f000 -- 43e000000 +3dfa1000 ( 991.628906 MB)
cVM has cvm_heap_begin (54210) and cvm_heap_size (541f0)
SEALED RET FROM MON 0x8101c840 0x8101c830
ACHTUNG: 'libhello_world.so' has syscall handler 'syscall_handler' at 0x175cd
Deploy 16 in 0.935000, SHA-256 Hash: 9d5b8181f41ffa0088a3f4d31d098f0db37be707c7e92ea71f72a331c461329a
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 43fffc000, old TP = 43ffffbe0 sp_read = 0x440000000, me->stacl = 0x43ff80000, getSP()=0x43ffff970, me->c_tp = 0x43ffffbd0 43ffffbc0
[1] '/app/sc_main'
&env0 = 0x43fffc040, &env2=0x43fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000017685
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
    base 0000000400000000 length 0000000040000000 ofset 0000000000017595
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
prepare nolibos initcVM Heap: 40005f000 -- 7dfa6f000 +3dfa1000 ( 991.628906 MB)
ptr = 0x40005f040, 5f040
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
hello world from pure-cap musl-uni
```
