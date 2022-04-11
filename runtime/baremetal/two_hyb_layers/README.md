# Two nested isolation layers

This example deploys two nested isolation layers with programs, libouter_h.so (O) and libinner_h.so (I) 
The inner layer begines from 0x10000000 and ends at 0x20000000, the outer layer begines from 0x10000000 and ends at 0x30000000.
In other words, the outer has access to the memory of the inner one, while the inner has access only to its own memory.
Both inner and outer layers have the same base -- this allows to pass pointers from Inner to Outer without their translation.

The Outer layer works as syscall handler for the Inner layer. 
Introvisor (M), in turn, in a syscall (hostcall) handler for the Outer layer.
In the example, firstly, Intravisor deploys programs and builds host- and sys- calls interfaces.
Then it starts the Outer layer, which prints a 'hello' message. Then it starts the inner layer.
The latter passes a pointer to a message to the outer layer, and the outer layer uses its hostcall interface to pass the pointer to Intravisor.

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
 |     | 0x20000000     |         |
 |     -----------------|         |
 |     |                |  / \    |
 |     |                |   |     |
 |     |                |   |     |
 |     |                |   | (I) |
 |     |                |   |     |
 |     |                |   |     |
 |     | 0x10000000     |  \ /   \ /
 |     ------------------
 |                       
\ /        0x000000000   
       ------------------

```

The programs can be deployed in another configuration when layers are not nested.
In this case, the inner layer cannot pass a pointer to a message to the outer layer, because layers are not intersecting and thus programs can communicate 
only by capabilitites. 

### Expected output 

```
# ./monitor -y two_layers.yaml
Using yaml.cfg = two_layers.yaml
***************** Deploy 'outer' ***************
BUILDING cvm: name=outer, disk=(null), runtime=libouter_h.so, net=(null), args='(null)', base=0x20000000, size=0x10000000, begin=0x10000000, end=0x30000000, cb_in = 'libinner_h.so', cb_out = 'monitor' wait = -1s
mapped at 0x40088000
Mapped 0x0, segment = 0x20000000, map_aaadr = 0x20000000, map_len = 4000
Mapped 0x12b8, segment = 0x20001000, map_aaadr = 0x20001000, map_len = 1000
Mapped 0x2598, segment = 0x20002000, map_aaadr = 0x20002000, map_len = 1000
Mapped 0x3618, segment = 0x20003000, map_aaadr = 0x20003000, map_len = 1000
ELF BASE = 0x20000000, MAP SIZE = 3620, ENTRY = 0x12b8
encl_map.entry = 0x12b8
encl_map.ret = 0x1408
[cVM STACKs] = [0x2e000000 -- 30000000]
ACHTUNG: 'libouter_h.so' has syscall handler 'syscall_handler' at 0x1432
***************** Deploy 'inner' ***************
BUILDING cvm: name=inner, disk=(null), runtime=libinner_h.so, net=(null), args='(null)', base=0x10000000, size=0x10000000, begin=0x10000000, end=0x20000000, cb_in = '(null)', cb_out = 'libouter_h.so' wait = 0s
mapped at 0x40088000
Mapped 0x0, segment = 0x10000000, map_aaadr = 0x10000000, map_len = 4000
Mapped 0x12b0, segment = 0x10001000, map_aaadr = 0x10001000, map_len = 1000
Mapped 0x2430, segment = 0x10002000, map_aaadr = 0x10002000, map_len = 1000
Mapped 0x34b0, segment = 0x10003000, map_aaadr = 0x10003000, map_len = 1000
ELF BASE = 0x10000000, MAP SIZE = 34b8, ENTRY = 0x12b0
encl_map.entry = 0x12b0
encl_map.ret = 0x1334
[cVM STACKs] = [0x1e000000 -- 20000000]
***************** Link Inner<-->Outer ***************
libinner_h.so[1] is inner for libouter_h.so[2]
***************** ALL cVMs loaded ***************
target SP = 2fffc000, old TP = 40083020 sp_read = 0x30000000, me->stacl = 0x2ff80000, getSP()=0x2ffff950, me->c_tp = 0x2ff81000
&env0 = 0x2fffc018, &env1=0x2fffc020
72 sp = 0x2fffc000
ca0: sealed COMP PPC
tag 1 s 1 perms 00000107 type 0000000000000000
        base 0000000010000000 length 0000000020000000 ofset 00000000100012b8
ca1: sealed COMP DDC
tag 1 s 1 perms 0000017d type 0000000000000000
        base 0000000010000000 length 0000000020000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 0000017d type ffffffffffffffff
        base 0000000010000000 length 0000000020000000 ofset 0000000000000000
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
tag 1 s 1 perms 00000107 type 0000000000000000
        base 0000000010000000 length 0000000020000000 ofset 0000000010001408
HW: sp = 0x1fffc000, tp = 0x1ff81000
-----------------------------------------------
hello outer layer 
target SP = 1fffc000, old TP = 40085020 sp_read = 0x20000000, me->stacl = 0x1ff80000, getSP()=0x1ffff950, me->c_tp = 0x1ff81000
&env0 = 0x1fffc018, &env1=0x1fffc020
72 sp = 0x1fffc000
ca0: sealed COMP PPC
tag 1 s 1 perms 00000107 type 0000000000000000
        base 0000000010000000 length 0000000010000000 ofset 00000000000012b0
ca1: sealed COMP DDC
tag 1 s 1 perms 0000017d type 0000000000000000
        base 0000000010000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 0000017d type ffffffffffffffff
        base 0000000010000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 00000107 type 0000000000000000
        base 0000000010000000 length 0000000020000000 ofset 0000000010001432
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0000017d type 0000000000000000
        base 0000000010000000 length 0000000020000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 0 s 0 perms 00000000 type ffffffffffffffff
        base 0000000000000000 length ffffffffffffffff ofset 0000000000055720
ca6: sealed ret from mon
tag 1 s 1 perms 00000107 type 0000000000000000
        base 0000000010000000 length 0000000010000000 ofset 0000000000001334
HW: sp = 0xfffc000, tp = 0xff81000
-----------------------------------------------
hello world from inner 
```
