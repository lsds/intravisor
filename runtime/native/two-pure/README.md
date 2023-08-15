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
Using yaml.cfg = two-pure.yaml
***************** [16] Deploy 'first' ***************
BUILDING cvm: name=first, disk=(null), runtime=libfirst.so, net=(null), args='/ld.so /app/sc_main', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s clean_room = 0
[2]: 885ea000 400000000 3fc 3fc 885ea000 3fc
[3]: 885ea400 400010400 200 200 885ea400 200
end of RO: 400020600
[4]: 885ea600 400020600 e0 e0 885ea600 e0
[5]: 885ea6e0 4000306e0 0 abc0 885ea6e0 0
ELF BASE = 0x400000000, MAP SIZE = 3b2a0, ENTRY = 0x10449
encl_map.entry = 0x10449
encl_map.ret = 0x1051c
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x43e000000 -- 440000000]
SEALED RET FROM MON 0x8049d040 0x8049d030
ACHTUNG: 'libfirst.so' has syscall handler 'syscall_handler' at 0x10551
***************** [17] Deploy 'second' ***************
BUILDING cvm: name=second, disk=(null), runtime=libsecond.so, net=(null), args='/ld.so /app/sc_main', base=0x440000000, size=0x40000000, begin=0x440000000, end=0x480000000, cb_in = '(null)', cb_out = 'libfirst.so' wait = -1s clean_room = 0
[2]: 87d28000 440000000 39c 39c 87d28000 39c
[3]: 87d2839c 44001039c 144 144 87d2839c 144
end of RO: 4400204e0
[4]: 87d284e0 4400204e0 d0 d0 87d284e0 d0
[5]: 87d285b0 4400305b0 0 abc0 87d285b0 0
ELF BASE = 0x440000000, MAP SIZE = 3b170, ENTRY = 0x1039d
encl_map.entry = 0x1039d
encl_map.ret = 0x104a8
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x47e000000 -- 480000000]
SEALED RET FROM MON 0x8049d040 0x8049d030
ACHTUNG: 'libsecond.so' has syscall handler 'syscall_handler' at 0x104dd
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 43fffc000, old TP = 43ffffbe0 sp_read = 0x440000000, me->stacl = 0x43ff80000, getSP()=0x43ffff970, me->c_tp = 0x43ffffbd0 43ffffbc0
[1] '/app/sc_main'
&env0 = 0x43fffc040, &env2=0x43fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000010449
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 000000000024861c
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0003717d type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 000000000024867c
ca6: sealed ret from mon
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 000000000001051d
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000043ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 43ffffa40
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000043ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x43fffc000, tp = 0x43ffff9f0, &cinv_args = 0x43ffffa70
TP_ARGS: 43e001000, 10, 43ff81000
-----------------------------------------------
hello first(syscall-handler) 
target SP = 47fffc000, old TP = 47ffffbe0 sp_read = 0x480000000, me->stacl = 0x47ff80000, getSP()=0x47ffff970, me->c_tp = 0x47ffffbd0 47ffffbc0
[1] '/app/sc_main'
&env0 = 0x47fffc040, &env2=0x47fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000440000000 length 0000000040000000 ofset 000000000001039d
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000440000000 length 0000000040000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
    base 0000000440000000 length 0000000040000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000010551
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 0 s 0 perms 00000000 type 0000000000000000
    base 0000000000000000 length ffffffffffffffff ofset 0000000000202c60
ca6: sealed ret from mon
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000440000000 length 0000000040000000 ofset 00000000000104a9
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000047ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 47ffffa40
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000047ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x47fffc000, tp = 0x47ffff9f0, &cinv_args = 0x47ffffa70
TP_ARGS: 47e001000, 11, 47ff81000
-----------------------------------------------
hello second 
```
