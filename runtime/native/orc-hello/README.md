ORC/SCO example, requires ORC/SCO support in Intravisor


## extected out for sco-orc-2x1.yaml

```
root@cheribsd-morello-hybrid:/e # ./intravisor -y sco-orc-2x1.yaml
Using yaml.cfg = sco-orc-2x1.yaml
state = 0x441460
state->clist = 0x0
***************** [2] Deploy 'shared' ***************
BUILDING cvm: name=shared, disk=(null), runtime=libshared.sco, net=(null), args='/ld.so /app/sc_main', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s
comp->base = 0x20000000
[2]: 877df000 20000000 42c 42c 877df000 42c
[3]: 877df430 20010430 410 410 877df430 410
end of RO: 20020840
[4]: 877df840 20020840 100 100 877df840 100
[5]: 877df940 20030940 8 abd0 877df940 8
ELF BASE = 0x20000000, MAP SIZE = 3b510, ENTRY = 0x1068d
encl_map.entry = 0x1068d
encl_map.ret = 0x10744
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x2e000000 -- 30000000]
SEALED RET FROM MON 0x809d3cb0 0x809d3ca0
ACHTUNG: 'libshared.sco' has syscall handler 'syscall_handler' at 0x10779
***************** [1] Deploy 'unique1' ***************
BUILDING cvm: name=unique1, disk=(null), runtime=libu_first.so, net=(null), args='/ld.so /app/sc_main', base=0x10000000, size=0x10000000, begin=0x10000000, end=0x20000000, cb_in = '(null)', cb_out = 'libshared.sco' wait = -1s
comp->base = 0x10000000
[2]: 87a57000 10000000 434 434 87a57000 434
[3]: 87a57434 10010434 26c 26c 87a57434 26c
end of RO: 100206a0
[4]: 87a576a0 100206a0 f0 f0 87a576a0 f0
[5]: 87a57790 10030790 0 abc0 87a57790 0
ELF BASE = 0x10000000, MAP SIZE = 3b350, ENTRY = 0x10435
encl_map.entry = 0x10435
encl_map.ret = 0x105bc
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x1e000000 -- 20000000]
SEALED RET FROM MON 0x809d3cb0 0x809d3ca0
ACHTUNG: 'libu_first.so' has syscall handler 'syscall_handler' at 0x105f1
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 2fffc000, old TP = 2ffffbe0 sp_read = 0x30000000, me->stacl = 0x2ff80000, getSP()=0x2ffff970, me->c_tp = 0x2ffffbd0 2ffffbc0
[1] '/app/sc_main'
&env0 = 0x2fffc040, &env2=0x2fffc050
ca0: sealed COMP PPC
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 000000000001068d
ca1: sealed COMP DDC
tag 1 s 1 perms 00037141 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037141 type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c177 type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 0000000000248658
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0003717d type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 0002c177 type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 00000000002486b8
ca6: sealed ret from mon
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000010745
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000002ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 2ffffa40
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000002ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x2fffc000, tp = 0x2ffff9f0, &cinv_args = 0x2ffffa70
TP_ARGS: 2e001000, 2, 2ff81000
-----------------------------------------------
target SP = 1fffc000, old TP = 1ffffbe0 sp_read = 0x20000000, me->stacl = 0x1ff80000, getSP()=0x1ffff970, me->c_tp = 0x1ffffbd0 1ffffbc0
[1] '/app/sc_main'
&env0 = 0x1fffc040, &env2=0x1fffc050
ca0: sealed COMP PPC
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000010000000 length 0000000010000000 ofset 0000000000010435
ca1: sealed COMP DDC
tag 1 s 1 perms 00037141 type 0000000000000004
        base 0000000010000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037141 type 0000000000000000
        base 0000000010000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000010779
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 00037141 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 0 s 0 perms 00000000 type 0000000000000000
        base 0000000000000000 length ffffffffffffffff ofset 0000000000202ae0
ca6: sealed ret from mon
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000010000000 length 0000000010000000 ofset 00000000000105bd
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000001ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 1ffffa40
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000001ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x1fffc000, tp = 0x1ffff9f0, &cinv_args = 0x1ffffa70
TP_ARGS: 1e001000, 1, 1ff81000
-----------------------------------------------
hello U1
GET SCO CAPS: 1 2 0x1ff81040
clonned 0x20000000--0x2003b510 to 0x88692000--0x886cd510, first 20840 unmapped = 0 , payload 0 unmapped = -1
5:In buffer U1
6:In buffer U1
7:In buffer U1
8:In buffer U1
9:In buffer U1
```

## expected output for sco-orc-2x2.yaml


```
root@cheribsd-morello-hybrid:/e # ./intravisor -y sco-orc-2x2.yaml
Using yaml.cfg = sco-orc-2x2.yaml
state = 0x441460
state->clist = 0x0
***************** [2] Deploy 'shared' ***************
BUILDING cvm: name=shared, disk=(null), runtime=libshared.sco, net=(null), args='/ld.so /app/sc_main', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s
comp->base = 0x20000000
[2]: 85d86000 20000000 42c 42c 85d86000 42c
[3]: 85d86430 20010430 410 410 85d86430 410
end of RO: 20020840
[4]: 85d86840 20020840 100 100 85d86840 100
[5]: 85d86940 20030940 8 abd0 85d86940 8
ELF BASE = 0x20000000, MAP SIZE = 3b510, ENTRY = 0x1068d
encl_map.entry = 0x1068d
encl_map.ret = 0x10744
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x2e000000 -- 30000000]
SEALED RET FROM MON 0x809603c0 0x809603b0
ACHTUNG: 'libshared.sco' has syscall handler 'syscall_handler' at 0x10779
***************** [1] Deploy 'unique1' ***************
BUILDING cvm: name=unique1, disk=(null), runtime=libu_first.so, net=(null), args='/ld.so /app/sc_main', base=0x10000000, size=0x10000000, begin=0x10000000, end=0x20000000, cb_in = '(null)', cb_out = 'libshared.sco' wait = 0s
comp->base = 0x10000000
[2]: 86502000 10000000 434 434 86502000 434
[3]: 86502434 10010434 26c 26c 86502434 26c
end of RO: 100206a0
[4]: 865026a0 100206a0 f0 f0 865026a0 f0
[5]: 86502790 10030790 0 abc0 86502790 0
ELF BASE = 0x10000000, MAP SIZE = 3b350, ENTRY = 0x10435
encl_map.entry = 0x10435
encl_map.ret = 0x105bc
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x1e000000 -- 20000000]
SEALED RET FROM MON 0x809603c0 0x809603b0
ACHTUNG: 'libu_first.so' has syscall handler 'syscall_handler' at 0x105f1
***************** [3] Deploy 'unique2' ***************
BUILDING cvm: name=unique2, disk=(null), runtime=libu_second.so, net=(null), args='/ld.so /app/sc_main', base=0x30000000, size=0x10000000, begin=0x30000000, end=0x40000000, cb_in = '(null)', cb_out = 'libshared.sco' wait = -1s
comp->base = 0x30000000
[2]: 860a5000 30000000 434 434 860a5000 434
[3]: 860a5434 30010434 26c 26c 860a5434 26c
end of RO: 300206a0
[4]: 860a56a0 300206a0 f0 f0 860a56a0 f0
[5]: 860a5790 30030790 0 abc0 860a5790 0
ELF BASE = 0x30000000, MAP SIZE = 3b350, ENTRY = 0x10435
encl_map.entry = 0x10435
encl_map.ret = 0x105bc
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x3e000000 -- 40000000]
SEALED RET FROM MON 0x809603c0 0x809603b0
ACHTUNG: 'libu_second.so' has syscall handler 'syscall_handler' at 0x105f1
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 2fffc000, old TP = 2ffffbe0 sp_read = 0x30000000, me->stacl = 0x2ff80000, getSP()=0x2ffff970, me->c_tp = 0x2ffffbd0 2ffffbc0
[1] '/app/sc_main'
&env0 = 0x2fffc040, &env2=0x2fffc050
ca0: sealed COMP PPC
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 000000000001068d
ca1: sealed COMP DDC
tag 1 s 1 perms 00037141 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037141 type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c177 type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 0000000000248658
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0003717d type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 0002c177 type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 00000000002486b8
ca6: sealed ret from mon
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000010745
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000002ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 2ffffa40
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000002ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x2fffc000, tp = 0x2ffff9f0, &cinv_args = 0x2ffffa70
TP_ARGS: 2e001000, 2, 2ff81000
-----------------------------------------------
target SP = 1fffc000, old TP = 1ffffbe0 sp_read = 0x20000000, me->stacl = 0x1ff80000, getSP()=0x1ffff970, me->c_tp = 0x1ffffbd0 1ffffbc0
target SP = 3fffc000, old TP = 3ffffbe0 sp_read = 0x40000000, me->stacl = 0x3ff80000, getSP()=0x3ffff970, me->c_tp = 0x3ffffbd0 3ffffbc0
[1] '/app/sc_main'
&env0 = 0x3fffc040, &env2=0x3fffc050
ca0: sealed COMP PPC
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000030000000 length 0000000010000000 ofset 0000000000010435
ca1: sealed COMP DDC
tag 1 s 1 perms 00037141 type 0000000000000004
        base 0000000030000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037141 type 0000000000000000
        base 0000000030000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000010779
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 00037141 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 0 s 0 perms 00000000 type 0000000000000000
        base 0000000000000000 length ffffffffffffffff ofset 0000000000202ae0
ca6: sealed ret from mon
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000030000000 length 0000000010000000 ofset 00000000000105bd
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000003ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 3ffffa40
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000003ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x3fffc000, tp = 0x3ffff9f0, &cinv_args = 0x3ffffa70
TP_ARGS: 3e001000, 3, 3ff81000
-----------------------------------------------
hello U2
GET SCO CAPS: 1 2 0x3ff81040
clonned 0x20000000--0x2003b510 to 0x8741f000--0x8745a510, first 20840 unmapped = 0 , payload 0 unmapped = -1
5:In buffer U2
6:In buffer U2
7:In buffer U2
8:In buffer U2
9:In buffer U2
[1] '/app/sc_main'
&env0 = 0x1fffc040, &env2=0x1fffc050
ca0: sealed COMP PPC
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000010000000 length 0000000010000000 ofset 0000000000010435
ca1: sealed COMP DDC
tag 1 s 1 perms 00037141 type 0000000000000004
        base 0000000010000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037141 type 0000000000000000
        base 0000000010000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000010779
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 00037141 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 0 s 0 perms 00000000 type 0000000000000000
        base 0000000000000000 length ffffffffffffffff ofset 0000000000202ae0
ca6: sealed ret from mon
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000010000000 length 0000000010000000 ofset 00000000000105bd
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000001ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 1ffffa40
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000001ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x1fffc000, tp = 0x1ffff9f0, &cinv_args = 0x1ffffa70
TP_ARGS: 1e001000, 1, 1ff81000
-----------------------------------------------
hello U1
GET SCO CAPS: 1 2 0x1ff81040
clonned 0x20000000--0x2003b510 to 0x882ce000--0x88309510, first 20840 unmapped = 0 , payload 0 unmapped = -1
5:In buffer U1
6:In buffer U1
7:In buffer U1
8:In buffer U1
9:In buffer U1
^C
root@cheribsd-morello-hybrid:/e # 

```