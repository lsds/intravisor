# Hello world 

A simple 'hello world' program. 

After start, it probes the capability with text from the Intravisor, which allocated in filled it at boot following the yaml config.

Then, we read data via the cap and print it using the hostcall interface.

Expected output:

```
Using yaml.cfg = /intravisor/cvm.yaml
CF_ADV: 0x87412000, 32, test1
MON: CF[0] 0x87412000 test1 32
CF_ADV: 0x873e0000, 4096, test2
MON: CF[1] 0x873e0000 test2 4096
***************** [17] Deploy 'hello' ***************
BUILDING cvm: name=hello, disk=(null), runtime=libnative-hello.so, net=(null), args='/ld.so /app/main', base=0x440000000, size=0x40000000, begin=0x440000000, end=0x480000000, cb_in = '(null)', cb_out = 'monitor' wait = 0s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
[2]: 89558000 440000000 3d4 3d4 89558000 3d4
[3]: 895583d4 4400013d4 23c 23c 895583d4 23c
end of RO: 440002610
[4]: 89558610 440002610 90 90 89558610 90
[5]: 895586a0 4400036a0 8 8 895586a0 8
ELF BASE = 0x440000000, MAP SIZE = 36a8, ENTRY = 0x13d4
encl_map.entry = 0x13d4
encl_map.ret = 0x14ee
[cVM STACKs] = [0x47e000000 -- 480000000]
Convrting free memory into cVM Heap: 440004000 -- 47e000000 +3dffc000 ( 991.984375 MB)
cVM doesn't use heap or has a built-in one
SEALED RET FROM MON 0x80ffa740 0x80ffa730
Deploy 17 in 1.414000, SHA-256 Hash: 10c435a81978a01b568084c70d7bf4e3858fac470e7b957fefd36d22d05b6052
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 47fffc000, old TP = 47ffffc00 sp_read = 0x480000000, me->stacl = 0x47ff80000, getSP()=0x47ffff9a0, me->c_tp = 0x47ffffbf0 47ffffbe0
[1] '/app/main'
sp[i+1] = '/app/main'
&env0 = 0x47fffc020, &env1=0x47fffc028
ca0: sealed COMP PCC
tag 1 s 1 perms 00008117 type 0000000000000000
    base 0000000440000000 length 0000000040000000 ofset 00000000000013d4
ca1: sealed COMP DDC
tag 1 s 1 perms 0000817d type 0000000000000000
    base 0000000440000000 length 0000000040000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 0000817d type ffffffffffffffff
    base 0000000440000000 length 0000000040000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 00068117 type 0000000000000000
    base 0000000000000000 length 0000800000000000 ofset 0000000000048030
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0007817d type 0000000000000000
    base 0000000000000000 length 0000800000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 00068117 type 0000000000000000
    base 0000000000000000 length 0000800000000000 ofset 0000000000048008
ca6: sealed ret from mon
tag 1 s 1 perms 00008117 type 0000000000000000
    base 0000000440000000 length 0000000040000000 ofset 00000000000014ee
HW: sp = 0x3fffc000, tp = 0x47ffffa30, &cinv_args = 0x47ffffab0
TP_ARGS: 47e001000, 11, 47ff81000
-----------------------------------------------
hello world, let's read cap 'test1' 
MON: CF: probe for key test1, store at 0x47fffbfc0
Some random text
```
