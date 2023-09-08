# Partitioned SQLite

This is a toy example that enables the estimation of the overhead of partitioning. It consists of several components executing inside separate pure-cap cVMs: ramfs, vfs, sqlite, speedtest1, and libC. Each component is pure-cap and passes arguments as capabilities to other components, thus preserving the jump-and-return semantics of calls. In the past, this code was also ORC-enabled but hasn't been tested for a while.

Warning: The example is very 'research-oriented' and consists of multiple hardcoded values, unnecessary code, and, in general, has a bad design. Do not use it as a design reference.

## Partitioning scheme

```

        ┌──────────────────────────────────┐
        │                                  │
      ┌─►      libC                        │◄─┐
      │ │                                  │  │
      │ └─────────▲─────────────▲──────────┘  │      ┌───────┐
      │           │             │             │      │   i   │
   ┌──┴───┐    ┌──┴───┐      ┌──┴──┐     ┌────┴──┐   │   n   |
   │      │    │      │      │     │     │       │   │   t   │
   │speed │    │sqlite│      │ vfs │     │ ramfs │   │   r   │
   │test1 │    │      │      │     │     │       │   │   a   │
   │      ├───►│      ├─────►│     ├────►│       │──►│   v   │
   └──────┘    └──────┘      └──▲──┘     └────┬──┘   │   i   │
                                │             │      │   s   │
                                └◄────────────┘      │   o   │
                                                     │   r   │
                                                     └───────┘


```


## Expected output:

```
root@cheribsd-morello-hybrid:/e # ./intravisor  -y musl-uni-sqlite-mp-5x1.yaml
Using yaml.cfg = musl-uni-sqlite-mp-5x1.yaml
***************** [6] Deploy 'ramfs' ***************
BUILDING cvm: name=ramfs, disk=(null), runtime=libsco_ramfs.so, net=(null), args='/ld.so /app/sc_main', base=0x60000000, size=0x10000000, begin=0x60000000, end=0x70000000, cb_in = 'libsco_vfs.so', cb_out = 'monitor' wait = -1s clean_room = 0
[2]: 889f5000 60000000 12cc 12cc 889f5000 12cc
[3]: 889f62d0 600112d0 21a8 21a8 889f62d0 21a8
end of RO: 60023480
[4]: 889f8480 60023480 180 180 889f8480 180
[5]: 889f8600 60033600 188 bd50 889f8600 188
ELF BASE = 0x60000000, MAP SIZE = 3f350, ENTRY = 0x115bd
encl_map.entry = 0x115bd
encl_map.ret = 0x11878
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x6e000000 -- 70000000]
Convrting free memory into cVM Heap: 60040000 -- 6e000000 +dfc0000 ( 223.750000 MB)
cVM doesn't use heap or has a built-in one
SEALED RET FROM MON 0x80506160 0x80506150
ACHTUNG: 'libsco_ramfs.so' has syscall handler 'syscall_handler' at 0x118b1
***************** [2] Deploy 'vfs' ***************
BUILDING cvm: name=vfs, disk=(null), runtime=libsco_vfs.so, net=(null), args='/ld.so /app/sc_main', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = 'libsco_sqlite.so', cb_out = 'libsco_ramfs.so' wait = -1s clean_room = 0
[2]: 8837e000 20000000 2adc 2adc 8837e000 2adc
[3]: 88380ae0 20012ae0 487c 487c 88380ae0 487c
end of RO: 20027360
[4]: 88385360 20027360 320 320 88385360 320
[5]: 88385680 20037680 230 114b0 88385680 230
ELF BASE = 0x20000000, MAP SIZE = 48b30, ENTRY = 0x12e51
encl_map.entry = 0x12e51
encl_map.ret = 0x13028
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x2e000000 -- 30000000]
Convrting free memory into cVM Heap: 20049000 -- 2e000000 +dfb7000 ( 223.714844 MB)
cVM doesn't use heap or has a built-in one
SEALED RET FROM MON 0x80506160 0x80506150
ACHTUNG: 'libsco_vfs.so' has syscall handler 'syscall_handler' at 0x13061
***************** [5] Deploy 'scolibc' ***************
BUILDING cvm: name=scolibc, disk=(null), runtime=libsco_libc.so, net=(null), args='/ld.so /app/sc_main', base=0x50000000, size=0x10000000, begin=0x50000000, end=0x60000000, cb_in = '(null)', cb_out = 'libsco_vfs.so' wait = -1s clean_room = 0
[2]: 88e61000 50000000 14a4 14a4 88e61000 14a4
[3]: 88e624a8 500114a8 4ae8 4ae8 88e624a8 4ae8
end of RO: 50025f90
[4]: 88e66f90 50025f90 230 230 88e66f90 230
[5]: 88e671c0 500361c0 8 c82a608 88e671c0 8
ELF BASE = 0x50000000, MAP SIZE = c8607c8, ENTRY = 0x117e1
encl_map.entry = 0x117e1
encl_map.ret = 0x11a28
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x5e000000 -- 60000000]
Convrting free memory into cVM Heap: 5c861000 -- 5e000000 +179f000 ( 23.621094 MB)
cVM doesn't use heap or has a built-in one
SEALED RET FROM MON 0x80506160 0x80506150
ACHTUNG: 'libsco_libc.so' has syscall handler 'syscall_handler' at 0x11a61
***************** [1] Deploy 'sqlite' ***************
BUILDING cvm: name=sqlite, disk=(null), runtime=libsco_sqlite.so, net=(null), args='/ld.so /app/sc_main', base=0x10000000, size=0x10000000, begin=0x10000000, end=0x20000000, cb_in = 'libsco_speedtest1.so', cb_out = 'libsco_vfs.so' wait = -1s clean_room = 0
[2]: 88212000 10000000 1fa6c 1fa6c 88212000 1fa6c
[3]: 88231a70 1002fa70 b15a8 b15a8 88231a70 b15a8
end of RO: 100f1020
[4]: 882e3020 100f1020 57e0 57e0 882e3020 57e0
[5]: 882e8800 10106800 2880 eaf0 882e8800 2880
ELF BASE = 0x10000000, MAP SIZE = 1152f0, ENTRY = 0x2fd39
encl_map.entry = 0x2fd39
encl_map.ret = 0x2ff10
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x1e000000 -- 20000000]
Convrting free memory into cVM Heap: 10116000 -- 1e000000 +deea000 ( 222.914062 MB)
cVM doesn't use heap or has a built-in one
SEALED RET FROM MON 0x80506160 0x80506150
ACHTUNG: 'libsco_sqlite.so' has syscall handler 'syscall_handler' at 0x2ff49
***************** [3] Deploy 'speedtest1' ***************
BUILDING cvm: name=speedtest1, disk=(null), runtime=libsco_speedtest1.so, net=(null), args='/ld.so /app/sc_main', base=0x30000000, size=0x10000000, begin=0x30000000, end=0x40000000, cb_in = '(null)', cb_out = 'libsco_sqlite.so' wait = -1s clean_room = 0
[2]: 88e60000 30000000 481c 481c 88e60000 481c
[3]: 88e64820 30014820 583c 583c 88e64820 583c
end of RO: 3002a060
[4]: 88e6a060 3002a060 1120 1120 88e6a060 1120
[5]: 88e6b180 3003b180 8 c840 88e6b180 8
ELF BASE = 0x30000000, MAP SIZE = 479c0, ENTRY = 0x14a35
encl_map.entry = 0x14a35
encl_map.ret = 0x14c88
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x3e000000 -- 40000000]
Convrting free memory into cVM Heap: 30048000 -- 3e000000 +dfb8000 ( 223.718750 MB)
cVM doesn't use heap or has a built-in one
SEALED RET FROM MON 0x80506160 0x80506150
ACHTUNG: 'libsco_speedtest1.so' has syscall handler 'syscall_handler' at 0x14cc1
***************** Link Inner<-->Outer ***************
libsco_vfs.so[2] is inner for libsco_ramfs.so[6]
libsco_sqlite.so[1] is inner for libsco_vfs.so[2]
libsco_speedtest1.so[3] is inner for libsco_sqlite.so[1]
***************** ALL cVMs loaded ***************
target SP = 6fffc000, old TP = 6ffffbe0 sp_read = 0x70000000, me->stacl = 0x6ff80000, getSP()=0x6ffff970, me->c_tp = 0x6ffffbd0 6ffffbc0
[1] '/app/sc_main'
&env0 = 0x6fffc040, &env2=0x6fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000060000000 length 0000000010000000 ofset 00000000000115bd
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000060000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
    base 0000000060000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 0000000000248914
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0003717d type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 0000000000248974
ca6: sealed ret from mon
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000060000000 length 0000000010000000 ofset 0000000000011879
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000006ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 6ffffa40
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000006ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x6fffc000, tp = 0x6ffff9f0, &cinv_args = 0x6ffffa70
TP_ARGS: 6e001000, 6, 6ff81000
-----------------------------------------------
BOOT: SCO RAMFS 
target SP = 2fffc000, old TP = 2ffffbe0 sp_read = 0x30000000, me->stacl = 0x2ff80000, getSP()=0x2ffff970, me->c_tp = 0x2ffffbd0 2ffffbc0
[1] '/app/sc_main'
&env0 = 0x2fffc040, &env2=0x2fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000020000000 length 0000000010000000 ofset 0000000000012e51
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
    base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000060000000 length 0000000010000000 ofset 00000000000118b1
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000060000000 length 0000000010000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 0 s 0 perms 00000000 type 0000000000000000
    base 0000000000000000 length ffffffffffffffff ofset 0000000000202cc0
ca6: sealed ret from mon
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000020000000 length 0000000010000000 ofset 0000000000013029
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000002ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 2ffffa40
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000002ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x2fffc000, tp = 0x2ffff9f0, &cinv_args = 0x2ffffa70
TP_ARGS: 2e001000, 2, 2ff81000
-----------------------------------------------
BOOT: SCO VFS 
target SP = 5fffc000, old TP = 5ffffbe0 sp_read = 0x60000000, me->stacl = 0x5ff80000, getSP()=0x5ffff970, me->c_tp = 0x5ffffbd0 5ffffbc0
[1] '/app/sc_main'
&env0 = 0x5fffc040, &env2=0x5fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000050000000 length 0000000010000000 ofset 00000000000117e1
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000050000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
    base 0000000050000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000020000000 length 0000000010000000 ofset 0000000000013061
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 0 s 0 perms 00000000 type 0000000000000000
    base 0000000000000000 length ffffffffffffffff ofset 0000000000202cc0
ca6: sealed ret from mon
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000050000000 length 0000000010000000 ofset 0000000000011a29
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000005ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 5ffffa40
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000005ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x5fffc000, tp = 0x5ffff9f0, &cinv_args = 0x5ffffa70
TP_ARGS: 5e001000, 5, 5ff81000
-----------------------------------------------
BOOT: SCO LIBC 
target SP = 1fffc000, old TP = 1ffffbe0 sp_read = 0x20000000, me->stacl = 0x1ff80000, getSP()=0x1ffff970, me->c_tp = 0x1ffffbd0 1ffffbc0
[1] '/app/sc_main'
&env0 = 0x1fffc040, &env2=0x1fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000010000000 length 0000000010000000 ofset 000000000002fd39
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000010000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
    base 0000000010000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000020000000 length 0000000010000000 ofset 0000000000013061
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 0 s 0 perms 00000000 type 0000000000000000
    base 0000000000000000 length ffffffffffffffff ofset 0000000000202cc0
ca6: sealed ret from mon
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000010000000 length 0000000010000000 ofset 000000000002ff11
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000001ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 1ffffa40
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000001ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x1fffc000, tp = 0x1ffff9f0, &cinv_args = 0x1ffffa70
TP_ARGS: 1e001000, 1, 1ff81000
-----------------------------------------------
BOOT: SQLite 
target SP = 3fffc000, old TP = 3ffffbe0 sp_read = 0x40000000, me->stacl = 0x3ff80000, getSP()=0x3ffff970, me->c_tp = 0x3ffffbd0 3ffffbc0
[1] '/app/sc_main'
&env0 = 0x3fffc040, &env2=0x3fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000030000000 length 0000000010000000 ofset 0000000000014a35
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000030000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
    base 0000000030000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000010000000 length 0000000010000000 ofset 000000000002ff49
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000010000000 length 0000000010000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 0 s 0 perms 00000000 type 0000000000000000
    base 0000000000000000 length ffffffffffffffff ofset 0000000000202cc0
ca6: sealed ret from mon
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000030000000 length 0000000010000000 ofset 0000000000014c89
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000003ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 3ffffa40
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000003ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x3fffc000, tp = 0x3ffff9f0, &cinv_args = 0x3ffffa70
TP_ARGS: 3e001000, 3, 3ff81000
-----------------------------------------------
BOOT: SCO Speedtest1 
prepare nolibos init37
39
Mount ramfs to /...
VFS: mounting ramfs at /
fd = 0
fd = 3
read from file = hello world
-- Speedtest1 for SQLite 3.22.0 2020-06-25 14:32:53 8ea3f6477e70eb9136629248abd86d625bc612705c0ad0d940b46998f1a7alt2
100 - 20000 INSERTs into table with no index 	101
110 - 20000 ordered INSERTS with one index/PK 	221
120 - 20000 unordered INSERTS with one index/PK 	334
130 - 25 SELECTS, numeric BETWEEN, unindexed 	47
140 - 10 SELECTS, LIKE, unindexed 	146
142 - 10 SELECTS w/ORDER BY, unindexed 	233
145 - 10 SELECTS w/ORDER BY and LIMIT, unindexed 	169
150 - CREATE INDEX five times 	1198
160 - 4000 SELECTS, numeric BETWEEN, indexed 	37
161 - 4000 SELECTS, numeric BETWEEN, PK 	37
170 - 4000 SELECTS, text BETWEEN, indexed 	87
180 - 20000 INSERTS with three indexes 	978
190 - DELETE and REFILL one table 	242
210 - ALTER TABLE ADD COLUMN, and query 	2
230 - 4000 UPDATES, numeric BETWEEN, indexed 	208
240 - 20000 UPDATES of individual rows 	95
250 - One big UPDATE of the whole 20000-row table 	72
260 - Query added column after filling 	2
270 - 4000 DELETEs, numeric BETWEEN, indexed 	340
280 - 20000 DELETEs of individual rows 	204
290 - Refill two 20000-row tables using REPLACE 	553
300 - Refill a 20000-row table using (b&1)==(a&1) 	193
310 - 4000 four-ways joins 	189
320 - subquery in result set 	178
400 - 28000 REPLACE ops on an IPK 	631
410 - 28000 SELECTS on an IPK 	163
500 - 28000 REPLACE on TEXT PK 	693
510 - 28000 SELECTS on a TEXT PK 	257
520 - 28000 SELECT DISTINCT 	105
980 - PRAGMA integrity_check 	224
990 - ANALYZE 	50
       TOTAL 7989
```
