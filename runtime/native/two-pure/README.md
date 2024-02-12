# Two pure-cap cVMs

Intravisor deploys two pure-cap cVMs. The first one works as a syscall handler for the second one. When the 2nd uses its hostcall interface, the call is deliveried to the 1st and processed by it, then 
if redirects it to Intravisor. All arguments are passed as capabilitites.

```
   ┌────────┐              ┌────────┐
   │        │              │        │
   │syscall │◄─────────────┤out()   │
   │        │              │        │
   │  1st   │              │   2nd  │
   │        │              │        │
   │        │              │        │
   │        │              │        │
   │        │              │        │
   └─┬─┬──▲─┘              └──────▲─┘
     │ │  │hostcalls              │
     │ │  │                       │
    ┌▼─▼──┴───────────────────────┴─┐
    │                               │
    │        Intravisor             │
    │                               │
    └───────────────────────────────┘

```



## expected output


```
Using yaml.cfg = /intravisor/cvm.yaml
***************** [16] Deploy 'first' ***************
BUILDING cvm: name=first, disk=(null), runtime=libfirst.so, net=(null), args='/ld.so /app/sc_main', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
[2]: 8ac2f000 400000000 370 370 8ac2f000 370
[3]: 8ac2f370 400001370 190 190 8ac2f370 190
end of RO: 400002500
[4]: 8ac2f500 400002500 b0 b0 8ac2f500 b0
[5]: 8ac2f5b0 4000035b0 40 ac10 8ac2f5b0 40
ELF BASE = 0x400000000, MAP SIZE = e1c0, ENTRY = 0x13b4
encl_map.entry = 0x13b4
encl_map.ret = 0x1468
we have __cap_relocs, it is a purecap binary
create cap: 0x4000035b0 Base: 0x2c4 Length: 12 Perms: 4000000000000000 Unk = 0
create cap: 0x4000035c0 Base: 0x2a5 Length: 31 Perms: 4000000000000000 Unk = 0
create cap: 0x4000035d0 Base: 0x3600 Length: 43962 Perms: 0 Unk = 0
ACHTUNG: RISCV USES OUTDATED ABI
create cap: 0x4000035e0 Base: 0x1370 Length: 68 Perms: 8000000000000000 Unk = 0
[cVM STACKs] = [0x43e000000 -- 440000000]
Convrting free memory into cVM Heap: 40000f000 -- 43e000000 +3dff1000 ( 991.941406 MB)
cVM doesn't use heap or has a built-in one
SEALED RET FROM MON 0x80e0a350 0x80e0a340
ACHTUNG: 'libfirst.so' has syscall handler 'syscall_handler' at 0x1486
Deploy 16 in 1.343000, SHA-256 Hash: eb9721c03c99a3f7da58c7e821d9b722e551ae92c0d0eb59501f93d4c0e18a71
***************** [17] Deploy 'second' ***************
BUILDING cvm: name=second, disk=(null), runtime=libsecond.so, net=(null), args='/ld.so /app/sc_main', base=0x440000000, size=0x40000000, begin=0x440000000, end=0x480000000, cb_in = '(null)', cb_out = 'libfirst.so' wait = -1s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
[2]: 8a5c5000 440000000 330 330 8a5c5000 330
[3]: 8a5c5330 440001330 150 150 8a5c5330 150
end of RO: 440002480
[4]: 8a5c5480 440002480 b0 b0 8a5c5480 b0
[5]: 8a5c5530 440003530 30 ac10 8a5c5530 30
ELF BASE = 0x440000000, MAP SIZE = e140, ENTRY = 0x1330
encl_map.entry = 0x1330
encl_map.ret = 0x142a
we have __cap_relocs, it is a purecap binary
create cap: 0x440003530 Base: 0x2a5 Length: 15 Perms: 4000000000000000 Unk = 0
create cap: 0x440003540 Base: 0x3580 Length: 43962 Perms: 0 Unk = 0
ACHTUNG: RISCV USES OUTDATED ABI
create cap: 0x440003550 Base: 0x1352 Length: 4 Perms: 8000000000000000 Unk = 0
[cVM STACKs] = [0x47e000000 -- 480000000]
Convrting free memory into cVM Heap: 44000f000 -- 47e000000 +3dff1000 ( 991.941406 MB)
cVM doesn't use heap or has a built-in one
SEALED RET FROM MON 0x80e0a350 0x80e0a340
ACHTUNG: 'libsecond.so' has syscall handler 'syscall_handler' at 0x1448
Deploy 17 in 1.333000, SHA-256 Hash: 57afb20bec111549b6b4c98413560d58e97df635b4abde53809fceedc1645b77
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 43fffc000, old TP = 43ffffc00 sp_read = 0x440000000, me->stacl = 0x43ff80000, getSP()=0x43ffff980, me->c_tp = 0x43ffffbf0 43ffffbe0
[1] '/app/sc_main'
&env0 = 0x43fffc040, &env2=0x43fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 00008117 type 0000000000000000
    base 0000000400000000 length 0000000040000000 ofset 00000000000013b4
ca1: sealed COMP DDC
tag 1 s 1 perms 0000817d type 0000000000000000
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 0000817d type ffffffffffffffff
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 00068117 type 0000000000000000
    base 0000000000000000 length 0000800000000000 ofset 00000000000482cc
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0007817d type 0000000000000000
    base 0000000000000000 length 0000800000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 00068117 type 0000000000000000
    base 0000000000000000 length 0000800000000000 ofset 00000000000482a4
ca6: sealed ret from mon
tag 1 s 1 perms 00008117 type 0000000000000000
    base 0000000400000000 length 0000000040000000 ofset 0000000000001468
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 0000817d type ffffffffffffffff
    base 000000043ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 43ffffa60
tag 1 s 0 perms 0000817d type ffffffffffffffff
    base 000000043ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x43fffc000, tp = 0x43ffffa10, &cinv_args = 0x43ffffa90
TP_ARGS: 43e001000, 10, 43ff81000
-----------------------------------------------
hello first(syscall-handler) 
target SP = 47fffc000, old TP = 47ffffc00 sp_read = 0x480000000, me->stacl = 0x47ff80000, getSP()=0x47ffff980, me->c_tp = 0x47ffffbf0 47ffffbe0
[1] '/app/sc_main'
&env0 = 0x47fffc040, &env2=0x47fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 00008117 type 0000000000000000
    base 0000000440000000 length 0000000040000000 ofset 0000000000001330
ca1: sealed COMP DDC
tag 1 s 1 perms 0000817d type 0000000000000000
    base 0000000440000000 length 0000000040000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 0000817d type ffffffffffffffff
    base 0000000440000000 length 0000000040000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 00008117 type 0000000000000000
    base 0000000400000000 length 0000000040000000 ofset 0000000000001486
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0000817d type 0000000000000000
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 0 s 0 perms 00000000 type ffffffffffffffff
    base 0000000000000000 length ffffffffffffffff ofset 0000000000002470
ca6: sealed ret from mon
tag 1 s 1 perms 00008117 type 0000000000000000
    base 0000000440000000 length 0000000040000000 ofset 000000000000142a
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 0000817d type ffffffffffffffff
    base 000000047ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 47ffffa60
tag 1 s 0 perms 0000817d type ffffffffffffffff
    base 000000047ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x47fffc000, tp = 0x47ffffa10, &cinv_args = 0x47ffffa90
TP_ARGS: 47e001000, 11, 47ff81000
-----------------------------------------------
hello second 
```
