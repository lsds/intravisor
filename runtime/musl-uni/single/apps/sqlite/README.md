# SQLite speedtest1 benchmark 

## known limitatations 

Port seems incomplete

## expected output 

```
Using yaml.cfg = /intravisor/cvm.yaml
***************** [16] Deploy 'sqlite' ***************
BUILDING cvm: name=sqlite, disk=(null), runtime=libsqlite.so, net=(null), args='/ld.so /app/sc_main', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
[2]: 8adbb000 400000000 2cd8c 2cd8c 8adbb000 2cd8c
[3]: 8ade7d90 40003cd90 c4114 c4114 8ade7d90 c4114
end of RO: 400110eb0
[4]: 8aeabeb0 400110eb0 7350 7350 8aeabeb0 7350
[5]: 8aeb3200 400128200 2ec0 1c0d8 8aeb3200 2ec0
ELF BASE = 0x400000000, MAP SIZE = 1442d8, ENTRY = 0xf100d
encl_map.entry = 0xf100d
encl_map.ret = 0xf0f1c
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x43e000000 -- 440000000]
Convrting free memory into cVM Heap: 400145000 -- 43e000000 +3debb000 ( 990.730469 MB)
cVM has cvm_heap_begin (13a3a0) and cvm_heap_size (13a380)
SEALED RET FROM MON 0x809ff490 0x809ff480
ACHTUNG: 'libsqlite.so' has syscall handler 'syscall_handler' at 0xf0f55
Deploy 16 in 2.160000, SHA-256 Hash: 6db2a9696aae7d1e53cbe95eb45fbf9ebbb7fe79867d51a1aa905d11d66bbe07
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 43fffc000, old TP = 43ffffbe0 sp_read = 0x440000000, me->stacl = 0x43ff80000, getSP()=0x43ffff970, me->c_tp = 0x43ffffbd0 43ffffbc0
[1] '/app/sc_main'
&env0 = 0x43fffc040, &env2=0x43fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 00000000000f100d
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 0000000000249668
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0003717d type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 00000000002496d0
ca6: sealed ret from mon
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 00000000000f0f1d
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000043ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 43ffffa40
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000043ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x43fffc000, tp = 0x43ffff9f0, &cinv_args = 0x43ffffa70
TP_ARGS: 43e001000, 10, 43ff81000
-----------------------------------------------
hello musl-uni 
prepare nolibos initcVM Heap: 400145000 -- 7decf5000 +3debb000 ( 990.730469 MB)
ptr = 0x400145040, 145040
424
426
Mount ramfs to /...
VFS: mounting ramfs at /
428
Mount devfs to /dev...VFS: mounting devfs at /dev
430
Register 'null' to devfs
Register 'zero' to devfs
432
Register 'urandom' and 'random' to devfs
434
Initialize random number generator...fd = 0
wrote 12 
fd = 3
read 12 from file = hello world
....testing /dev/zero/dev/zero fd = 3
read 128 bytes from /dev/zero
....testing /dev/random/dev/zero fd = 3
read 8 bytes from /dev/random, rd=a7135e24912251f8
--------- LibOS is ok,  ------- 
-- Speedtest1 for SQLite 3.22.0 2020-06-25 14:32:53 8ea3f6477e70eb9136629248abd86d625bc612705c0ad0d940b46998f1a7alt2
lstat /abc.db
100 - 500 INSERTs into table with no index 	0.186
110 - 500 ordered INSERTS with one index/PK 	0.136
120 - 500 unordered INSERTS with one index/PK 	0.120
130 - 25 SELECTS, numeric BETWEEN, unindexed 	0.132
140 - 10 SELECTS, LIKE, unindexed 	0.148
142 - 10 SELECTS w/ORDER BY, unindexed 	0.191
145 - 10 SELECTS w/ORDER BY and LIMIT, unindexed 	0.225
150 - CREATE INDEX five times 	0.236
160 - 100 SELECTS, numeric BETWEEN, indexed 	0.64
161 - 100 SELECTS, numeric BETWEEN, PK 	0.58
170 - 100 SELECTS, text BETWEEN, indexed 	0.81
180 - 500 INSERTS with three indexes 	0.158
190 - DELETE and REFILL one table 	0.104
210 - ALTER TABLE ADD COLUMN, and query 	0.22
230 - 100 UPDATES, numeric BETWEEN, indexed 	0.66
240 - 500 UPDATES of individual rows 	0.98
250 - One big UPDATE of the whole 500-row table 	0.23
260 - Query added column after filling 	0.6
270 - 100 DELETEs, numeric BETWEEN, indexed 	0.105
280 - 500 DELETEs of individual rows 	0.120
290 - Refill two 500-row tables using REPLACE 	0.240
300 - Refill a 500-row table using (b&1)==(a&1) 	0.123
310 - 100 four-ways joins 	0.200
320 - subquery in result set 	0.6
400 - 700 REPLACE ops on an IPK 	0.104
410 - 700 SELECTS on an IPK 	0.156
500 - 700 REPLACE on TEXT PK 	0.99
510 - 700 SELECTS on a TEXT PK 	0.189
520 - 700 SELECT DISTINCT 	0.38
980 - PRAGMA integrity_check 	0.210
990 - ANALYZE 	0.79
       TOTAL 3.723
```
