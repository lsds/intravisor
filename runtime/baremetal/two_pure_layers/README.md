# Two pure-cap isolated cVMs

This example deploys two cVMs with programs, libouter_p.so (O) and libinner_p.so (I) 
The inner layer begines from 0x10000000 and ends at 0x20000000, the outer layer begines from 0x20000000 and ends at 0x30000000.
In other words, cVMs can access memory of each other only via capabilities 

The Outer cVM works as syscall handler for the Inner cVM. 
Introvisor (M), in turn, in a syscall (hostcall) handler for the Outer cVM.
In the example, firstly, Intravisor deploys programs and builds host- and sys- calls interfaces.
Then it starts the Outer cVM, which prints a 'hello' message. Then it starts the inner cVM.
The latter passes a pointer to a message to the outer cVM. The Outer cVM copies data from the inner cVM 
and uses its own hostcall interface to pass the pointer to Intravisor.

```
     ------------------
/ \      0xfffffffff      
 |                       
 | (M)                   
 |                       
 |     	0x30000000      
 |     |----------------+
 |     |                |        / \
 |     |                |         |
 |     |                |         |
 |     |                |     (O) |
 |     |                |         |
 |     | 0x20000000     |        \ /
 |     -----------------|         
 |     |                |  / \
 |     |                |   |
 |     |                |   |
 |     |                |   | (I)
 |     |                |   |
 |     |                |   |
 |     | 0x10000000     |  \ /
 |     ------------------
 |                       
\ /        0x000000000   
       ------------------

```


### Expected output 

```
./monitor -y two_pure.yaml 
Using yaml.cfg = two_pure.yaml
***************** Deploy 'outer' ***************
BUILDING cvm: name=outer, disk=(null), runtime=libouter_p.so, net=(null), args='(null)', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = 'libinner_p.so', cb_out = 'monitor' wait = -1s
mapped at 0x404b3000
Mapped 0x0, segment = 0x20000000, map_aaadr = 0x20000000, map_len = f000
Mapped 0x1418, segment = 0x20001000, map_aaadr = 0x20001000, map_len = 1000
Mapped 0x26f0, segment = 0x20002000, map_aaadr = 0x20002000, map_len = 1000
Mapped 0x3790, segment = 0x20003000, map_aaadr = 0x20003000, map_len = c000
SHARED MAPPING 0x20004000--0x2000f000
ELF BASE = 0x20000000, MAP SIZE = e400, ENTRY = 0x154e
encl_map.entry = 0x154e
encl_map.ret = 0x15e6
we have __cap_relocs, it is a purecap binary
TODO: create cap: 0x20003790 Base: 0x295 Length: 30 Perms: 4000000000000000 Unk = 0
store REL_CAP
tag 1 s 0 perms 0000017d type ffffffffffffffff
        base 0000000020000295 length 000000000000001e ofset 0000000000000000
TODO: create cap: 0x200037a0 Base: 0x1654 Length: 42 Perms: 8000000000000000 Unk = 0
store REL_CAP
tag 1 s 0 perms 00000117 type ffffffffffffffff
        base 0000000020000000 length 0000000010000000 ofset 0000000000001654
TODO: create cap: 0x200037b0 Base: 0x167e Length: 18 Perms: 8000000000000000 Unk = 0
store REL_CAP
tag 1 s 0 perms 00000117 type ffffffffffffffff
        base 0000000020000000 length 0000000010000000 ofset 000000000000167e
TODO: create cap: 0x200037c0 Base: 0x2c7 Length: 12 Perms: 4000000000000000 Unk = 0
store REL_CAP
tag 1 s 0 perms 0000017d type ffffffffffffffff
        base 00000000200002c7 length 000000000000000c ofset 0000000000000000
TODO: create cap: 0x200037d0 Base: 0x2b3 Length: 20 Perms: 4000000000000000 Unk = 0
store REL_CAP
tag 1 s 0 perms 0000017d type ffffffffffffffff
        base 00000000200002b3 length 0000000000000014 ofset 0000000000000000
TODO: create cap: 0x200037e0 Base: 0x3840 Length: 43962 Perms: 0 Unk = 0
replace cap for caps
store REL_CAP
tag 1 s 0 perms 0000017d type ffffffffffffffff
        base 000000002e001000 length 0000000000001000 ofset 0000000000000000
TODO: create cap: 0x200037f0 Base: 0x16c0 Length: 44 Perms: 8000000000000000 Unk = 0
store REL_CAP
tag 1 s 0 perms 00000117 type ffffffffffffffff
        base 0000000020000000 length 0000000010000000 ofset 00000000000016c0
TODO: create cap: 0x20003800 Base: 0x1598 Length: 340 Perms: 8000000000000000 Unk = 0
store REL_CAP
tag 1 s 0 perms 00000117 type ffffffffffffffff
        base 0000000020000000 length 0000000010000000 ofset 0000000000001598
[cVM STACKs] = [0x2e000000 -- 30000000]
ACHTUNG: 'libouter_p.so' has syscall handler 'syscall_handler' at 0x160a
***************** Deploy 'inner' ***************
BUILDING cvm: name=inner, disk=(null), runtime=libinner_p.so, net=(null), args='(null)', base=0x10000000, size=0x10000000, begin=0x10000000, end=0x20000000, cb_in = '(null)', cb_out = 'libouter_p.so' wait = 0s
mapped at 0x40088000
Mapped 0x0, segment = 0x10000000, map_aaadr = 0x10000000, map_len = f000
Mapped 0x1378, segment = 0x10001000, map_aaadr = 0x10001000, map_len = 1000
Mapped 0x24f0, segment = 0x10002000, map_aaadr = 0x10002000, map_len = 1000
Mapped 0x3590, segment = 0x10003000, map_aaadr = 0x10003000, map_len = c000
SHARED MAPPING 0x10004000--0x1000f000
ELF BASE = 0x10000000, MAP SIZE = e1c0, ENTRY = 0x1378
encl_map.entry = 0x1378
encl_map.ret = 0x141a
we have __cap_relocs, it is a purecap binary
TODO: create cap: 0x10003590 Base: 0x295 Length: 25 Perms: 4000000000000000 Unk = 0
store REL_CAP
tag 1 s 0 perms 0000017d type ffffffffffffffff
        base 0000000010000295 length 0000000000000019 ofset 0000000000000000
TODO: create cap: 0x100035a0 Base: 0x1440 Length: 108 Perms: 8000000000000000 Unk = 0
store REL_CAP
tag 1 s 0 perms 00000117 type ffffffffffffffff
        base 0000000010000000 length 0000000010000000 ofset 0000000000001440
TODO: create cap: 0x100035b0 Base: 0x14ac Length: 64 Perms: 8000000000000000 Unk = 0
store REL_CAP
tag 1 s 0 perms 00000117 type ffffffffffffffff
        base 0000000010000000 length 0000000010000000 ofset 00000000000014ac
TODO: create cap: 0x100035c0 Base: 0x3600 Length: 43962 Perms: 0 Unk = 0
replace cap for caps
store REL_CAP
tag 1 s 0 perms 0000017d type ffffffffffffffff
        base 000000001e001000 length 0000000000001000 ofset 0000000000000000
TODO: create cap: 0x100035d0 Base: 0x13c8 Length: 292 Perms: 8000000000000000 Unk = 0
store REL_CAP
tag 1 s 0 perms 00000117 type ffffffffffffffff
        base 0000000010000000 length 0000000010000000 ofset 00000000000013c8
[cVM STACKs] = [0x1e000000 -- 20000000]
***************** Link Inner<-->Outer ***************
libinner_p.so[1] is inner for libouter_p.so[2]
***************** ALL cVMs loaded ***************
target SP = 2fffc000, old TP = 40083020 sp_read = 0x30000000, me->stacl = 0x2ff80000, getSP()=0x2ffff950, me->c_tp = 0x2ff81000
&env0 = 0x2fffc018, &env1=0x2fffc020
72 sp = 0x2fffc000
ca0: sealed COMP PPC
tag 1 s 1 perms 00000117 type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 000000000000154e
ca1: sealed COMP DDC
tag 1 s 1 perms 0000017d type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 0000017d type ffffffffffffffff
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 00068117 type 0000000000000000
        base 0000000000000000 length 0000004000000000 ofset 000000000004a658
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0007817d type 0000000000000000
        base 0000000000000000 length 0000004000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 00068117 type 0000000000000000
        base 0000000000000000 length 0000004000000000 ofset 000000000004a630
ca6: sealed ret from mon
tag 1 s 1 perms 00000117 type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 00000000000015e6
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 0000017d type ffffffffffffffff
        base 000000002ff80000 length 000000000007c000 ofset 000000000007c000
HW: sp = 0x2fffc000, tp = 0x2ff81000
-----------------------------------------------
hello outer layer 
target SP = 1fffc000, old TP = 40085020 sp_read = 0x20000000, me->stacl = 0x1ff80000, getSP()=0x1ffff950, me->c_tp = 0x1ff81000
&env0 = 0x1fffc018, &env1=0x1fffc020
72 sp = 0x1fffc000
ca0: sealed COMP PPC
tag 1 s 1 perms 00000117 type 0000000000000000
        base 0000000010000000 length 0000000010000000 ofset 0000000000001378
ca1: sealed COMP DDC
tag 1 s 1 perms 0000017d type 0000000000000000
        base 0000000010000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 0000017d type ffffffffffffffff
        base 0000000010000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 00000117 type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 000000000000160a
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0000017d type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 0 s 0 perms 00000000 type ffffffffffffffff
        base 0000000000000000 length ffffffffffffffff ofset 0000000000055720
ca6: sealed ret from mon
tag 1 s 1 perms 00000117 type 0000000000000000
        base 0000000010000000 length 0000000010000000 ofset 000000000000141a
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 0000017d type ffffffffffffffff
        base 000000001ff80000 length 000000000007c000 ofset 000000000007c000
HW: sp = 0x1fffc000, tp = 0x1ff81000
-----------------------------------------------
Outer: intercepting message 'hello world from inner 
```
