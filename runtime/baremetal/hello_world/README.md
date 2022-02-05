# Hello world 

A simple 'hello world' program. 

After start, it probes the capability with text from the Intravisor, which allocated in filled it at boot following the yaml config.

Then, we read data via the cap and print it using the hostcall interface.

Expected output:
```
Using yaml.cfg = hello.yaml
MON: sc_cbs[0]: monitor, 0x3fffdff900, 0x3fffdff8f0, 0x4dd50
MON: CAP[0] 0x45169140 test1 32
MON: CAP[1] 0x45160000 test2 4096
***************** Deploy 'hello' ***************
BUILDING cvm: name=hello, disk=(null), runtime=libhello.so, net=(null), args='(null)', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = '(null)', cb_out = 'monitor' wait = 0s
Mapped 0x0, segment = 0x20000000, map_aaadr = 0x20000000, map_len = 4000
Mapped 0x12c4, segment = 0x20001000, map_aaadr = 0x20001000, map_len = 1000
Mapped 0x2498, segment = 0x20002000, map_aaadr = 0x20002000, map_len = 1000
Mapped 0x3518, segment = 0x20003000, map_aaadr = 0x20003000, map_len = 1000
ELF BASE = 0x20000000, MAP SIZE = 3520, ENTRY = 0x200012c4
encl_map.entry = 0x200012c4
encl_map.ret = 0x1390
[cVM STACKs] = [0x2e000000 -- 30000000]
MON: probe syscall handler for key monitor
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 2fffc000, sp_read = 0x30000000, me->stacl = 0x2ff80000, getSP()=0x2ffffaf0, me->c_tp = 0x2ff81000
&env0 = 0x2fffc018, &env1=0x2fffc020
72 sp = 0x2fffc000
ca0: sealed COMP PPC
tag 1 s 1 perms 00000107 type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 00000000000012c4
ca1: sealed COMP DDC
tag 1 s 1 perms 0000011d type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 0000011d type ffffffffffffffff
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 00068117 type 0000000000000000
        base 0000000000000000 length 0000004000000000 ofset 00000000000486c2
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0007817d type 0000000000000000
        base 0000000000000000 length 0000004000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 00068117 type 0000000000000000
        base 0000000000000000 length 0000004000000000 ofset 000000000004869a
ca6: sealed ret from mon
tag 1 s 1 perms 00000107 type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 0000000000001390
HW: sp = 0xfffc000, tp = 0xff81000
-----------------------------------------------
hello world, let's read cap 'test1' 
MON: probe for key test1, store at 0x2fffbfc0
Hello world

```
