#Two pure-cap cVMs


## expected output


```
root@cheribsd-morello-hybrid:/e # ./intravisor -y two-pure.yaml 
Using yaml.cfg = two-pure.yaml
state = 0x441260
state->clist = 0x0
***************** [2] Deploy 'first' ***************
BUILDING cvm: name=first, disk=(null), runtime=libfirst.so, net=(null), args='/ld.so /app/sc_main', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s
comp->base = 0x20000000
[2]: 887d6000 20000000 40c 40c 887d6000 40c
[3]: 887d6410 20010410 1f0 1f0 887d6410 1f0
end of RO: 20020600
[4]: 887d6600 20020600 f0 f0 887d6600 f0
[5]: 887d66f0 200306f0 0 abc0 887d66f0 0
ELF BASE = 0x20000000, MAP SIZE = 3b2b0, ENTRY = 0x10459
encl_map.entry = 0x10459
encl_map.ret = 0x1052c
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x2e000000 -- 30000000]
SEALED RET FROM MON 0x80e1c450 0x80e1c440
ACHTUNG: 'libfirst.so' has syscall handler 'syscall_handler' at 0x10561
***************** [1] Deploy 'second' ***************
BUILDING cvm: name=second, disk=(null), runtime=libsecond.so, net=(null), args='/ld.so /app/sc_main', base=0x10000000, size=0x10000000, begin=0x10000000, end=0x20000000, cb_in = '(null)', cb_out = 'libfirst.so' wait = -1s
comp->base = 0x10000000
[2]: 88fe4000 10000000 3ac 3ac 88fe4000 3ac
[3]: 88fe43ac 100103ac 154 154 88fe43ac 154
end of RO: 10020500
[4]: 88fe4500 10020500 e0 e0 88fe4500 e0
[5]: 88fe45e0 100305e0 0 abc0 88fe45e0 0
ELF BASE = 0x10000000, MAP SIZE = 3b1a0, ENTRY = 0x103ad
encl_map.entry = 0x103ad
encl_map.ret = 0x104b8
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x1e000000 -- 20000000]
SEALED RET FROM MON 0x80e1c450 0x80e1c440
ACHTUNG: 'libsecond.so' has syscall handler 'syscall_handler' at 0x104ed
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 2fffc000, old TP = 2ffffbe0 sp_read = 0x30000000, me->stacl = 0x2ff80000, getSP()=0x2ffff970, me->c_tp = 0x2ffffbd0 2ffffbc0
[1] '/app/sc_main'
&env0 = 0x2fffc040, &env2=0x2fffc050
ca0: sealed COMP PPC
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000010459
ca1: sealed COMP DDC
tag 1 s 1 perms 00037141 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037141 type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c177 type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 0000000000248410
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0003717d type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 0002c177 type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 0000000000248470
ca6: sealed ret from mon
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 000000000001052d
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000002ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 2ffffa40
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000002ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x2fffc000, tp = 0x2ffff9f0, &cinv_args = 0x2ffffa70
TP_ARGS: 2e001000, 2, 2ff81000
-----------------------------------------------
hello first(syscall-handler) 
target SP = 1fffc000, old TP = 1ffffbe0 sp_read = 0x20000000, me->stacl = 0x1ff80000, getSP()=0x1ffff970, me->c_tp = 0x1ffffbd0 1ffffbc0
[1] '/app/sc_main'
&env0 = 0x1fffc040, &env2=0x1fffc050
ca0: sealed COMP PPC
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000010000000 length 0000000010000000 ofset 00000000000103ad
ca1: sealed COMP DDC
tag 1 s 1 perms 00037141 type 0000000000000004
        base 0000000010000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037141 type 0000000000000000
        base 0000000010000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000010561
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 00037141 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 0 s 0 perms 00000000 type 0000000000000000
        base 0000000000000000 length ffffffffffffffff ofset 0000000000202aa0
ca6: sealed ret from mon
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000010000000 length 0000000010000000 ofset 00000000000104b9
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000001ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 1ffffa40
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000001ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x1fffc000, tp = 0x1ffff9f0, &cinv_args = 0x1ffffa70
TP_ARGS: 1e001000, 1, 1ff81000
-----------------------------------------------
hello second 
```
