# Hello world 

A simple 'hello world' program. 

After start, it probes the capability with text from the Intravisor, which allocated in filled it at boot following the yaml config.

Then, we read data via the cap and print it using the hostcall interface.

Expected output:
```
root@cheribsd-morello-hybrid:/e # ./intravisor -y native-hello.yaml
Using yaml.cfg = native-hello.yaml
***************** [17] Deploy 'hello' ***************
BUILDING cvm: name=hello, disk=(null), runtime=libnative-hello.so, net=(null), args='/ld.so /app/main', base=0x440000000, size=0x40000000, begin=0x440000000, end=0x480000000, cb_in = '(null)', cb_out = 'monitor' wait = 0s clean_room = 0
[2]: 89911000 440000000 3c4 3c4 89911000 3c4
[3]: 899113c8 4400103c8 238 238 899113c8 238
end of RO: 440020600
[4]: 89911600 440020600 90 90 89911600 90
[5]: 89911690 440030690 8 8 89911690 8
ELF BASE = 0x440000000, MAP SIZE = 30698, ENTRY = 0x103c8
encl_map.entry = 0x103c8
encl_map.ret = 0x104e4
[cVM STACKs] = [0x47e000000 -- 480000000]
SEALED RET FROM MON 0x8062d820 0x8062d810
ACHTUNG: 'libnative-hello.so' has syscall handler 'syscall_handler' at 0x10518
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 47fffc000, old TP = 47ffffbe0 sp_read = 0x480000000, me->stacl = 0x47ff80000, getSP()=0x47ffff990, me->c_tp = 0x47ffffbd0 47ffffbc0
[1] '/app/main'
sp[i+1] = '/app/main'
&env0 = 0x47fffc020, &env1=0x47fffc028
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
        base 0000000440000000 length 0000000040000000 ofset 00000000000103c8
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
        base 0000000440000000 length 0000000040000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
        base 0000000440000000 length 0000000040000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c177 type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 000000000024b42c
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0003717d type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 0002c177 type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 000000000024b4a8
ca6: sealed ret from mon
tag 1 s 1 perms 0002c147 type 0000000000000004
        base 0000000440000000 length 0000000040000000 ofset 00000000000104e4
HW: sp = 0x3fffc000, tp = 0x47ffffa10, &cinv_args = 0x47ffffa90
TP_ARGS: 47e001000, 11, 440000000
-----------------------------------------------
hello world, let's read cap 'test1' 
Hello world
```
