# Speedtest1 SQLite

Speedtest1 benchmark for SQLite

# Expected output: 

```
root@cheribsd-riscv64-hybrid:/intravisor # ls -la 
total 78796
drwxr-xr-x   2 root  wheel        512 Feb  4 23:00 .
drwxr-xr-x  21 root  wheel        512 Feb  4 22:55 ..
-rwxr-xr-x   1 root  wheel  104857600 Feb  4 22:57 disk_sqlite.img
-rwxr-xr-x   1 root  wheel   71222888 Feb  4 23:00 libmusl-lkl.so
-rwxr-xr-x   1 root  wheel    1002232 Feb  4 22:58 monitor
-rwxr-xr-x   1 root  wheel        222 Feb  4 22:55 musl-lkl-sqlite.yaml
root@cheribsd-riscv64-hybrid:/intravisor # ./monitor -y musl-lkl-sqlite.yaml
Using yaml.cfg = musl-lkl-sqlite.yaml
MON: sc_cbs[0]: monitor, 0x3fffdff880, 0x3fffdff870, 0x48b86
***************** Deploy 'sqlite' ***************
BUILDING cvm: name=sqlite, disk=disk_sqlite.img, runtime=libmusl-lkl.so, net=(null), args='/ld.so /app/speedtest :memory: --size 50', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = '(null)', cb_out = '(null)' wait = 0s
Mapped 0x0, segment = 0x20000000, map_aaadr = 0x20000000, map_len = ce78000
Mapped 0x129284, segment = 0x20129000, map_aaadr = 0x20129000, map_len = 358000
Mapped 0x481a00, segment = 0x20481000, map_aaadr = 0x20481000, map_len = 19000
Mapped 0x49a1e0, segment = 0x2049a000, map_aaadr = 0x2049a000, map_len = c9de000
SHARED MAPPING 0x205d9000--0x2ce78000
ELF BASE = 0x20000000, MAP SIZE = ce77550, ENTRY = 0x201757a4
encl_map.entry = 0x201757a4
encl_map.ret = 0x4680b0
[cVM STACKs] = [0x2e000000 -- 30000000]
callback_out is empty, use default 'monitor'
MON: probe syscall handler for key monitor
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 2fffc000, sp_read = 0x30000000, me->stacl = 0x2ff80000, getSP()=0x2ffffa00, me->c_tp = 0x2ff81000
[1] '/app/speedtest'
sp[i+1] = '/app/speedtest'
[2] ':memory:'
sp[i+1] = ':memory:'
[3] '--size'
sp[i+1] = '--size'
[4] '50'
sp[i+1] = '50'
&env0 = 0x2fffc038, &env1=0x2fffc040
72 sp = 0x2fffc000
ca0: sealed COMP PPC
tag 1 s 1 perms 00000107 type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 00000000001757a4
ca1: sealed COMP DDC
tag 1 s 1 perms 0000011d type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 0000011d type ffffffffffffffff
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 00068117 type 0000000000000000
        base 0000000000000000 length 0000004000000000 ofset 0000000000048b86
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0007817d type 0000000000000000
        base 0000000000000000 length 0000004000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 00068117 type 0000000000000000
        base 0000000000000000 length 0000004000000000 ofset 0000000000048b5e
ca6: sealed ret from mon
tag 1 s 1 perms 00000107 type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 00000000004680b0
HW: sp = 0xfffc000, tp = 0xff81000
-----------------------------------------------
STARTING LKL, lkl_io_in = 0xce77428, disk_io = 0xce77538
TIMER[0]: 0x182c30 0
TODO: CREATE_CARRIE_TIMER
[    0.000000] Linux version 4.17.0 (vsartako@maru26) (clang version 11.0.0 (https://github.com/CTSRD-CHERI/llvm-project 9c51217b7d41f3124b84b190b6631b90db6d1bf4)) #3 Fri Feb 4 22:51:56 UTC 2022
[    0.000000] bootmem address range: 0x5ea000 - 0xcdea000
[    0.000000] Built 1 zonelists, mobility grouping off.  Total pages: 50500
[    0.000000] Kernel command line: mem=30M
[    0.000000] Dentry cache hash table entries: 32768 (order: 6, 262144 bytes)
[    0.000000] Inode-cache hash table entries: 16384 (order: 5, 131072 bytes)
[    0.000000] Memory available: 147028k/204800k RAM
[    0.000000] SLUB: HWalign=32, Order=0-3, MinObjects=0, CPUs=1, Nodes=1
[    0.000000] NR_IRQS: 4096
[    0.000000] lkl: irqs initialized
[    0.000000] clocksource: lkl: mask: 0xffffffffffffffff max_cycles: 0x1cd42e4dffb, max_idle_ns: 881590591483 ns
[    0.000075] lkl: time and timers initialized (irq1)
[    0.000525] pid_max: default: 4096 minimum: 301
[    0.001772] Mount-cache hash table entries: 512 (order: 0, 4096 bytes)
[    0.002094] Mountpoint-cache hash table entries: 512 (order: 0, 4096 bytes)
[    0.046290] devtmpfs: initialized
[    0.246799] console [lkl_console0] enabled
[    0.248423] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.249850] xor: automatically using best checksumming function   8regs     
[    0.254062] random: get_random_u32 called from 0x0000000000302982 with crng_init=0
[    0.256872] NET: Registered protocol family 16
[    0.287557] cryptd: max_cpu_qlen set to 1000
[    0.304087] clocksource: Switched to clocksource lkl
[    0.317855] NET: Registered protocol family 2
[    0.326356] tcp_listen_portaddr_hash hash table entries: 256 (order: 0, 4096 bytes)
[    0.327578] TCP established hash table entries: 2048 (order: 2, 16384 bytes)
[    0.328969] TCP bind hash table entries: 2048 (order: 2, 16384 bytes)
[    0.330227] TCP: Hash tables configured (established 2048 bind 2048)
[    0.334599] UDP hash table entries: 128 (order: 0, 4096 bytes)
[    0.335629] UDP-Lite hash table entries: 128 (order: 0, 4096 bytes)
[    0.337653] NET: Registered protocol family 1
[    0.349213] workingset: timestamp_bits=62 max_order=16 bucket_order=0
[    0.416240] romfs: ROMFS MTD (C) 2007 Red Hat, Inc.
[    0.594192] NET: Registered protocol family 38
[    0.595373] io scheduler noop registered
[    0.596114] io scheduler deadline registered
[    0.599067] io scheduler cfq registered (default)
[    0.599928] io scheduler mq-deadline registered
[    0.600677] io scheduler kyber registered
CAP_FILE INIT 43 4004e201
CAP_STREAM_HOST INIT 45 4004e401
[    1.185423] device-mapper: ioctl: 4.39.0-ioctl (2018-04-03) initialised: dm-devel@redhat.com
[    1.208876] Warning: unable to open an initial console.
[    1.209912] This architecture does not have kernel memory protection.
ignore destructor in tls_alloc
host0 allocated (task=0xcc95500/host0) pid=51
------ LKL INIT DONE, starting mount  ------- 
------ TEST1 ------- 
------ TEST 1 DONE ------- 
ADD disk
[    1.227113] virtio-mmio virtio-mmio.0.auto: Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.
[    1.234512] virtio_blk virtio0: [vda] 204800 512-byte logical blocks (105 MB/100 MiB)
disk id = 0
------ ADD disk DONE ------- 
[    1.286025] EXT4-fs (vda): recovery complete
[    1.287656] EXT4-fs (vda): mounted filesystem with ordered data mode. Opts: 
loader.c        311
------ CHROOT DONE ------- 
creating /cap/cf1 1
creating /cap/cf2 2
creating /cap/ch1 1
creating /cap/ch2 2
creating /cap/ch3 3
creating /cap/ch4 4
------ MOUNTS DONE ------- 
[lost+found]
[proc]
[.]
[sys]
[..]
[cap]
[app]
[dev]
[run]
------
?--ch4
?--ch3
?--ch2
?--ch1
?--cf2
?--cf1
st.st_mode = 41ed
st.st_nlink = 5
stat2.st_mode = 41ed
stat2.st_nlink = 5
stat2.st_uid = 0
stat2.st_gid = 0
[    1.335406] host1 (52): drop_caches: 3
MOUNT DONE
td = 0x5dbb10, p = 0x5dbb10, td->robust_list.head = 0x5dbba0 0xfffbcb8 0x5dbba0
PRESTART NETWORK BEFORE LKL 
[    1.664205] virtio-mmio virtio-mmio.1.auto: Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.
------ NETWORK ----- 
setting LO
...done
setting eth0
...done
post start done
LOAD: /app/speedtest
app.base = 0xca00000
ready to start the app: 0xcaccbe0
envp = 0xfffc038, me->argv[0] = 0xfffd000, m->argv[0]=/app/speedtest
---------------------------------
-- Speedtest1 for SQLite 3.35.0 2021-02-01 12:39:50 5d54d9fd406381383afdf10612bfd5
 100 - 25000 INSERTs into table with no index......................        1.248
 110 - 25000 ordered INSERTS with one index/PK.....................        1.826
 120 - 25000 unordered INSERTS with one index/PK...................        2.114
 130 - 25 SELECTS, numeric BETWEEN, unindexed......................        1.113
 140 - 10 SELECTS, LIKE, unindexed.................................        2.471
 142 - 10 SELECTS w/ORDER BY, unindexed............................        3.164
 145 - 10 SELECTS w/ORDER BY and LIMIT, unindexed..................        2.015
 150 - CREATE INDEX five times.....................................        2.387
 160 - 5000 SELECTS, numeric BETWEEN, indexed......................        0.970
 161 - 5000 SELECTS, numeric BETWEEN, PK...........................        0.963
 170 - 5000 SELECTS, text BETWEEN, indexed.........................        1.587
 180 - 25000 INSERTS with three indexes............................        2.446
 190 - DELETE and REFILL one table.................................        2.345
 210 - ALTER TABLE ADD COLUMN, and query...........................        0.060
 230 - 5000 UPDATES, numeric BETWEEN, indexed......................        1.063
 240 - 25000 UPDATES of individual rows............................        1.249
 250 - One big UPDATE of the whole 25000-row table.................        0.344
 260 - Query added column after filling............................        0.053
 270 - 5000 DELETEs, numeric BETWEEN, indexed......................        1.962
 280 - 25000 DELETEs of individual rows............................        1.342
 290 - Refill two 25000-row tables using REPLACE...................        5.344
 300 - Refill a 25000-row table using (b&1)==(a&1).................        2.614
 310 - 5000 four-ways joins........................................        2.664
 320 - subquery in result set......................................        5.483
 400 - 35000 REPLACE ops on an IPK.................................        2.337
 410 - 35000 SELECTS on an IPK.....................................        1.372
 500 - 35000 REPLACE on TEXT PK....................................        2.280
 510 - 35000 SELECTS on a TEXT PK..................................        2.214
 520 - 35000 SELECT DISTINCT.......................................        1.444
 980 - PRAGMA integrity_check......................................        3.201
 990 - ANALYZE.....................................................        0.713
       TOTAL.......................................................   60.388
EXIT IS CALLED
```


