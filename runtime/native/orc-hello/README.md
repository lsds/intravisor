ORC/SCO example, requires ORC/SCO support in Intravisor

NB: due to the experimental nature of ORC, please use pre-defined cVM sizes and etc.

# hello

The example demonstrates the basic ideas of ORC: It deploys two unique cVMs that share the third one. The latter is an ORC cVM.

In case of the GitHub version, to enable ORC support, you should comment out "NO_ACTION" flag in `1.shared/LocPass/Loc.cpp`.
Intravisor also should support ORC.

The example consists of three components. 

```
├── 1.shared						# the ORC Component. it receives incomming jump-and-return calls from unique components
│   ├── arch						# arch-specific code
│   ├── BRKGEPPass				# Pass that breaks long LLVM instructions into small ones
│   ├── hostcalls.c				# this file consists of routines for incomming calls
│   ├── hostcalls.h
│   ├── LocPass					# ORC pass, replaces accesses to gloval variables by cap-relative ones
│   ├── main.c					# main code
│   ├── sco-orc-2x1.yaml		# configuration for a single unique component
│   └── sco-orc-2x2.yaml		# configuration for two unique components
├── 2.unique1						# unique component. makes a call into the shared one and returns back.
│   ├── arch
│   ├── hostcalls.c				# the caller side of cross-component calls
│   ├── hostcalls.h
│   ├── main.c					# start funcion
├── 3.unique2						# the same as above
│   ├── arch
│   ├── hostcalls.c
│   ├── hostcalls.h
│   ├── main.c
```

The first component -- `shared` is a shared as ORC library. it has a state variable `tgv` with a default value `5`. 
This component exposes a public function that increments this variable. The routine to the increment is 'syscall --> case 1000' in `1.shared/main.c`. 
The unique components -- the second and the third cVMs -- can invoke this routine via hostcalls. In the example, we first start the shared component, then the unique components.
Both unique components invoke the increment 5 times.

Expected Output: 

```
root@cheribsd-morello-hybrid:/orc/1.orc-hello # ./intravisor -y sco-orc-2x2.yaml 
Using yaml.cfg = sco-orc-2x2.yaml
state = 0x440a60
state->clist = 0x0
***************** [2] Deploy 'shared' ***************
BUILDING cvm: name=shared, disk=(null), runtime=libshared.sco, net=(null), args='/ld.so /app/sc_main', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s
comp->base = 0x20000000
[2]: 855f8000 20000000 41c 41c 855f8000 41c
[3]: 855f8420 20010420 410 410 855f8420 410
end of RO: 20020830
[4]: 855f8830 20020830 110 110 855f8830 110
[5]: 855f8940 20030940 8 abd0 855f8940 8
***************** [1] Deploy 'unique1' ***************
BUILDING cvm: name=unique1, disk=(null), runtime=libu_first.so, net=(null), args='/ld.so /app/sc_main', base=0x10000000, size=0x10000000, begin=0x10000000, end=0x20000000, cb_in = '(null)', cb_out = 'libshared.sco' wait = 0s
comp->base = 0x10000000
[2]: 855ee000 10000000 424 424 855ee000 424
[3]: 855ee424 10010424 27c 27c 855ee424 27c
end of RO: 100206a0
[4]: 855ee6a0 100206a0 e0 e0 855ee6a0 e0
[5]: 855ee780 10030780 0 abc0 855ee780 0
***************** [3] Deploy 'unique2' ***************
BUILDING cvm: name=unique2, disk=(null), runtime=libu_second.so, net=(null), args='/ld.so /app/sc_main', base=0x30000000, size=0x10000000, begin=0x30000000, end=0x40000000, cb_in = '(null)', cb_out = 'libshared.sco' wait = -1s
comp->base = 0x30000000
[2]: 85204000 30000000 424 424 85204000 424
[3]: 85204424 30010424 27c 27c 85204424 27c
end of RO: 300206a0
[4]: 852046a0 300206a0 e0 e0 852046a0 e0
[5]: 85204780 30030780 0 abc0 85204780 0
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 2fffc000, old TP = 2ffffbe0 sp_read = 0x30000000, me->stacl = 0x2ff80000, getSP()=0x2ffff9b0, me->c_tp = 0x2ffffbd0 2ffffbc0
[1] '/app/sc_main'
-----------------------------------------------
target SP = 1fffc000, old TP = 1ffffbe0 sp_read = 0x20000000, me->stacl = 0x1ff80000, getSP()=0x1ffff9b0, me->c_tp = 0x1ffffbd0 1ffffbc0
target SP = 3fffc000, old TP = 3ffffbe0 sp_read = 0x40000000, me->stacl = 0x3ff80000, getSP()=0x3ffff9b0, me->c_tp = 0x3ffffbd0 3ffffbc0
[1] '/app/sc_main'
-----------------------------------------------
hello U2
[1] '/app/sc_main'
-----------------------------------------------
hello U1
GET SCO CAPS: 1 2 0x1ff81040
GET SCO CAPS: 1 2 0x3ff81040
clonned 0x20000000--0x2003b510 to 0x88042000--0x8807d510, first 20830 unmapped = 0 , payload 0 unmapped = -1
5:In buffer U2
6:In buffer U2
7:In buffer U2
8:In buffer U2
9:In buffer U2
clonned 0x20000000--0x2003b510 to 0x8797b000--0x879b6510, first 20830 unmapped = 0 , payload 0 unmapped = -1
5:In buffer U1
6:In buffer U1
7:In buffer U1
8:In buffer U1
9:In buffer U1
```

Each time when the shared component is asked to increment the `tgv` variable, it prints the current value. Therefore, we see 5 increments from U2 and 5 increments from U1.
However, the increments have the same values: from 5 to 9. This is because the decoupling of the state, which is indirectly can be seen in the `clonned` message.
The non-decoupled state would increment the `tgv` for 10 times, which lead to the output like: 

```
5:In buffer U2
6:In buffer U2
7:In buffer U2
8:In buffer U2
9:In buffer U2

::In buffer U1
;:In buffer U1
<:In buffer U1
=:In buffer U1
>:In buffer U1
```
