# Pandas

Uses a workbook from Kaggle.

Arm only

## expected output 

```
Using yaml.cfg = /intravisor/cvm.yaml
***************** [16] Deploy 'hello' ***************
BUILDING cvm: name=hello, disk=disk_docker_pandas.img, runtime=libmusl-lkl.so, net=(null), args='/ld.so /usr/bin/python3 -u /2.py', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = '(null)' wait = 0s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
[1]: 898b4000 400000000 f218c f218c 898b4000 f218c
[2]: 899a6190 400102190 26ea3c 26ea3c 899a6190 26ea3c
end of RO: 400380be0
[3]: 89c14be0 400380be0 fe78 fe78 89c14be0 fe78
[4]: 89c24c00 4003a0c00 12c688 1c3fe0 89c24c00 12c688
ELF BASE = 0x400000000, MAP SIZE = 564be0, ENTRY = 0x14fb6c
encl_map.entry = 0x14fb6c
encl_map.ret = 0x361fd0
[cVM STACKs] = [0x43e000000 -- 440000000]
Convrting free memory into cVM Heap: 400565000 -- 43e000000 +3da9b000 ( 986.605469 MB)
cVM has cvm_heap_begin (4bd490) and cvm_heap_size (4bd498)
callback_out is empty, use default 'monitor'
SEALED RET FROM MON 0x80d9d6e0 0x80d9d6d0
ACHTUNG: 'libmusl-lkl.so' has syscall handler 'syscall_handler' at 0x362008
Deploy 16 in 6.803000, SHA-256 Hash: 71524d537b961f77e23fc1fb5462120c6ec8a2d1e5955da6d00a37c6f95b09df
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 43fffc000, old TP = 43ffffbe0 sp_read = 0x440000000, me->stacl = 0x43ff80000, getSP()=0x43ffff990, me->c_tp = 0x43ffffbd0 43ffffbc0
[1] '/usr/bin/python3'
sp[i+1] = '/usr/bin/python3'
[2] '-u'
sp[i+1] = '-u'
[3] '/2.py'
sp[i+1] = '/2.py'
&env0 = 0x43fffc030, &env1=0x43fffc038
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 000000000014fb6c
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 000000000024c1a4
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0003717d type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 000000000024c220
ca6: sealed ret from mon
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000361fd0
HW: sp = 0x3fffc000, tp = 0x43ffffa10, &cinv_args = 0x43ffffa90
TP_ARGS: 43e001000, 10, 400000000
-----------------------------------------------
STARTING LKL, lkl_io_in = 0x563d70, disk_io = 0x563e90, heap (565000, +3da9b000)
TIMER[0]: 0x15a698 0
TODO: CREATE_CARRIE_TIMER
[    0.000000] Linux version 4.17.0 (cheri@runner-_aJ2xR8B-project-191-concurrent-0) (clang version 13.0.0 (https://git.morello-project.org/morello/llvm-project.git b4f4d8095b90b87ba65a692dfa98de2968996db4)) #1 Sun Feb 11 01:08:40 UTC 2024
[    0.000000] bootmem address range: 0x565000 - 0x3e000000
[    0.000000] Built 1 zonelists, mobility grouping off.  Total pages: 249117
[    0.000000] Kernel command line: 
[    0.000000] Dentry cache hash table entries: 131072 (order: 8, 1048576 bytes)
[    0.000000] Inode-cache hash table entries: 65536 (order: 7, 524288 bytes)
[    0.000000] Memory available: 951360k/1010284k RAM
[    0.000000] SLUB: HWalign=32, Order=0-3, MinObjects=0, CPUs=1, Nodes=1
[    0.000000] NR_IRQS: 4096
[    0.000000] lkl: irqs initialized
[    0.000000] clocksource: lkl: mask: 0xffffffffffffffff max_cycles: 0x1cd42e4dffb, max_idle_ns: 881590591483 ns
[    0.000149] lkl: time and timers initialized (irq1)
[    0.001333] pid_max: default: 4096 minimum: 301
[    0.004452] Mount-cache hash table entries: 2048 (order: 2, 16384 bytes)
[    0.005240] Mountpoint-cache hash table entries: 2048 (order: 2, 16384 bytes)
[    0.101472] devtmpfs: initialized
[    0.310808] console [lkl_console0] enabled
[    0.314073] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.317517] xor: automatically using best checksumming function   8regs     
[    0.351165] cryptd: max_cpu_qlen set to 1000
[    0.369950] clocksource: Switched to clocksource lkl
[    0.402454] workingset: timestamp_bits=62 max_order=18 bucket_order=0
[    0.461319] romfs: ROMFS MTD (C) 2007 Red Hat, Inc.
[    0.642831] io scheduler noop registered
[    0.644518] io scheduler deadline registered
[    0.648142] io scheduler cfq registered (default)
[    0.649701] io scheduler mq-deadline registered
[    0.651060] io scheduler kyber registered
CAP_FILE INIT 43 4004e201
CAP_STREAM_HOST INIT 45 4004e401
[    1.213879] device-mapper: ioctl: 4.39.0-ioctl (2018-04-03) initialised: dm-devel@redhat.com
[    1.224245] random: get_random_bytes called from 0x000000000015e5d0 with crng_init=0
[    1.237547] Warning: unable to open an initial console.
[    1.240665] This architecture does not have kernel memory protection.
INT: ignore destructor 15ab5c in tls_alloc
------ LKL INIT DONE, starting mount  ------- 
ADD disk
[    1.292998] virtio_blk virtio0: [vda] 1228800 512-byte logical blocks (629 MB/600 MiB)
disk id = 0
------ ADD disk DONE ------- 
[    1.451758] EXT4-fs (vda): mounted filesystem with ordered data mode. Opts: 
loader.c	355
------ CHROOT DONE ------- 
creating /cap/cf1 1
creating /cap/cf2 2
creating /cap/ch1 1
creating /cap/ch2 2
creating /cap/ch3 3
creating /cap/ch4 4
creating /cap/cg1 1
creating /cap/cg2 2
creating /cap/cg3 3
creating /cap/cg4 4
------ MOUNTS DONE ------- 
pad Descriptor Table: 0 ((null))
pad Descriptor Table: 1 ((null))
pad Descriptor Table: 2 ((null))
[..]
[run]
[.dockerenv]
[full_data.csv]
[proc]
[dev]
[sys]
[lib]
[tmp]
[srv]
[var]
[.]
[2.py]
[mnt]
[usr]
[opt]
[etc]
[lost+found]
[home]
[sbin]
[root]
[media]
[1.py]
[bin]
[cap]
------
�--cg4
�--cg3
�--cg2
�--cg1
�--ch4
�--ch3
�--ch2
�--ch1
�--cf2
�--cf1
st_lkl.st_mode = 21a4
st_lkl.st_nlink = 1
st_musl.st_mode = 21a4
st_musl.st_nlink = 1
st_musl.st_uid = 0
st_musl.st_gid = 0
Size of musl stat: 128
Offset of st_mode:	16, Size: 4
Offset of st_nlink:	20, Size: 4
Offset of st_uid:	24, Size: 4
Offset of st_gid:	28, Size: 4
Size of lkl stat: 128
Offset of st_mode:	16, Size: 4
Offset of st_nlink:	20, Size: 4
Offset of st_uid:	24, Size: 4
Offset of st_gid:	28, Size: 4
S_IFMT = f000, S_IFDIR = 4000
O_DIRECTORY = 0x4000
is_dir(/dev/stdin): 0 (LKL) 0 (musl)
Adding entropy to entropy pool
[    1.683245] random: crng init done
MOUNT DONE
td = 0x4cfe08, p = 0x4cfe08, td->robust_list.head = 0x4cfe98 0x3fffbce0 0x4cfe98
NO NETWORK 
LOAD: /usr/bin/python3
app.base = 0x3c380000
LOAD: 0x3fffbc80: libpython3.11.so.1.0 at 0x3c800000
ready to start the app: 0x3c3807b0
envp = 0x3fffc030, me->argv[0] = 0x3fffd000, m->argv[0]=/usr/bin/python3
---------------------------------
LOAD: 0x3fff6930: /usr/lib/python3.11/lib-dynload/_json.cpython-311-aarch64-linux-musl.so at 0x3d540000
LOAD: 0x3fff7a50: /usr/lib/python3.11/site-packages/numpy/core/_multiarray_umath.cpython-311-aarch64-linux-musl.so at 0x3d800000
LOAD: 0x3fff7a00: libopenblas.so.3 at 0x4000000
LOAD: 0x3fff7a00: libgfortran.so.5 at 0x5200000
LOAD: 0x3fff7a00: libgcc_s.so.1 at 0x5400000
LOAD: 0x3fff6950: /usr/lib/python3.11/lib-dynload/math.cpython-311-aarch64-linux-musl.so at 0x5480000
LOAD: 0x3fff6950: /usr/lib/python3.11/lib-dynload/_datetime.cpython-311-aarch64-linux-musl.so at 0x54c0000
LOAD: 0x3fff5230: /usr/lib/python3.11/lib-dynload/_struct.cpython-311-aarch64-linux-musl.so at 0x5700000
LOAD: 0x3fff59a0: /usr/lib/python3.11/lib-dynload/_pickle.cpython-311-aarch64-linux-musl.so at 0x5740000
LOAD: 0x3fff5230: /usr/lib/python3.11/lib-dynload/_contextvars.cpython-311-aarch64-linux-musl.so at 0x5880000
LOAD: 0x3fff8660: /usr/lib/python3.11/site-packages/numpy/core/_multiarray_tests.cpython-311-aarch64-linux-musl.so at 0x5bc0000
LOAD: 0x3fff7f80: /usr/lib/python3.11/lib-dynload/_ctypes.cpython-311-aarch64-linux-musl.so at 0x5c40000
LOAD: 0x3fff7f30: libffi.so.8 at 0x5cc0000
LOAD: 0x3fff59a0: /usr/lib/python3.11/site-packages/numpy/linalg/_umath_linalg.cpython-311-aarch64-linux-musl.so at 0x5f00000
LOAD: 0x3fff86f0: /usr/lib/python3.11/site-packages/numpy/random/mtrand.cpython-311-aarch64-linux-musl.so at 0x6600000
LOAD: 0x3fff7d80: /usr/lib/python3.11/site-packages/numpy/random/bit_generator.cpython-311-aarch64-linux-musl.so at 0x6700000
LOAD: 0x3fff7400: /usr/lib/python3.11/site-packages/numpy/random/_common.cpython-311-aarch64-linux-musl.so at 0x6780000
LOAD: 0x3fff67e0: /usr/lib/python3.11/lib-dynload/binascii.cpython-311-aarch64-linux-musl.so at 0x6800000
LOAD: 0x3fff6790: libz.so.1 at 0x6840000
LOAD: 0x3fff67e0: /usr/lib/python3.11/lib-dynload/_hashlib.cpython-311-aarch64-linux-musl.so at 0x6880000
LOAD: 0x3fff6790: libcrypto.so.3 at 0x6c00000
LOAD: 0x3fff6070: /usr/lib/python3.11/lib-dynload/_blake2.cpython-311-aarch64-linux-musl.so at 0x7100000
LOAD: 0x3fff6070: /usr/lib/python3.11/lib-dynload/_bisect.cpython-311-aarch64-linux-musl.so at 0x7140000
LOAD: 0x3fff67e0: /usr/lib/python3.11/lib-dynload/_random.cpython-311-aarch64-linux-musl.so at 0x7180000
LOAD: 0x3fff67e0: /usr/lib/python3.11/lib-dynload/_sha512.cpython-311-aarch64-linux-musl.so at 0x71c0000
LOAD: 0x3fff7db0: /usr/lib/python3.11/site-packages/numpy/random/_bounded_integers.cpython-311-aarch64-linux-musl.so at 0x7200000
LOAD: 0x3fff8070: /usr/lib/python3.11/site-packages/numpy/random/_mt19937.cpython-311-aarch64-linux-musl.so at 0x7280000
LOAD: 0x3fff86f0: /usr/lib/python3.11/site-packages/numpy/random/_philox.cpython-311-aarch64-linux-musl.so at 0x72c0000
LOAD: 0x3fff86f0: /usr/lib/python3.11/site-packages/numpy/random/_pcg64.cpython-311-aarch64-linux-musl.so at 0x7300000
LOAD: 0x3fff86f0: /usr/lib/python3.11/site-packages/numpy/random/_sfc64.cpython-311-aarch64-linux-musl.so at 0x7340000
LOAD: 0x3fff86f0: /usr/lib/python3.11/site-packages/numpy/random/_generator.cpython-311-aarch64-linux-musl.so at 0x7400000
LOAD: 0x3fff70a0: /usr/lib/python3.11/lib-dynload/_opcode.cpython-311-aarch64-linux-musl.so at 0x75c0000
LOAD: 0x3fff99c0: /usr/lib/python3.11/lib-dynload/_typing.cpython-311-aarch64-linux-musl.so at 0x78c0000
LOAD: 0x3fff7910: /usr/lib/python3.11/site-packages/pandas/_libs/interval.cpython-311-aarch64-linux-musl.so at 0x7a00000
LOAD: 0x3fff6fc0: /usr/lib/python3.11/site-packages/pandas/_libs/hashtable.cpython-311-aarch64-linux-musl.so at 0x7c00000
LOAD: 0x3fff59c0: /usr/lib/python3.11/site-packages/pandas/_libs/missing.cpython-311-aarch64-linux-musl.so at 0x7d40000
LOAD: 0x3fff3e80: /usr/lib/python3.11/site-packages/pandas/_libs/tslibs/dtypes.cpython-311-aarch64-linux-musl.so at 0x7dc0000
LOAD: 0x3fff3510: /usr/lib/python3.11/site-packages/pandas/_libs/tslibs/np_datetime.cpython-311-aarch64-linux-musl.so at 0x7e00000
LOAD: 0x3fff43b0: /usr/lib/python3.11/site-packages/pandas/_libs/tslibs/conversion.cpython-311-aarch64-linux-musl.so at 0x7e80000
LOAD: 0x3fff3a40: /usr/lib/python3.11/site-packages/pandas/_libs/tslibs/base.cpython-311-aarch64-linux-musl.so at 0x7e40000
LOAD: 0x3fff3a40: /usr/lib/python3.11/site-packages/pandas/_libs/tslibs/nattype.cpython-311-aarch64-linux-musl.so at 0x7f00000
LOAD: 0x3fff3a40: /usr/lib/python3.11/site-packages/pandas/_libs/tslibs/tzconversion.cpython-311-aarch64-linux-musl.so at 0x7f80000
LOAD: 0x3fff2f10: /usr/lib/python3.11/site-packages/pandas/_libs/tslibs/timezones.cpython-311-aarch64-linux-musl.so at 0x38000000
LOAD: 0x3fff2100: /usr/lib/python3.11/lib-dynload/_zoneinfo.cpython-311-aarch64-linux-musl.so at 0x380c0000
LOAD: 0x3fff3d00: /usr/lib/python3.11/site-packages/pandas/_libs/tslibs/parsing.cpython-311-aarch64-linux-musl.so at 0x38280000
LOAD: 0x3fff33a0: /usr/lib/python3.11/site-packages/pandas/_libs/tslibs/offsets.cpython-311-aarch64-linux-musl.so at 0x38400000
LOAD: 0x3fff2a40: /usr/lib/python3.11/site-packages/pandas/_libs/tslibs/timedeltas.cpython-311-aarch64-linux-musl.so at 0x38380000
LOAD: 0x3fff23a0: /usr/lib/python3.11/site-packages/pandas/_libs/tslibs/fields.cpython-311-aarch64-linux-musl.so at 0x38580000
LOAD: 0x3fff1a50: /usr/lib/python3.11/site-packages/pandas/_libs/tslibs/ccalendar.cpython-311-aarch64-linux-musl.so at 0x38540000
LOAD: 0x3fff0e30: /usr/lib/python3.11/lib-dynload/fcntl.cpython-311-aarch64-linux-musl.so at 0x38680000
LOAD: 0x3fff0e30: /usr/lib/python3.11/lib-dynload/_posixsubprocess.cpython-311-aarch64-linux-musl.so at 0x386c0000
LOAD: 0x3fff0e30: /usr/lib/python3.11/lib-dynload/select.cpython-311-aarch64-linux-musl.so at 0x38700000
LOAD: 0x3fff2a40: /usr/lib/python3.11/site-packages/pandas/_libs/tslibs/timestamps.cpython-311-aarch64-linux-musl.so at 0x38780000
LOAD: 0x3fff2d40: /usr/lib/python3.11/site-packages/pandas/_libs/properties.cpython-311-aarch64-linux-musl.so at 0x38840000
LOAD: 0x3fff2010: /usr/lib/python3.11/lib-dynload/_decimal.cpython-311-aarch64-linux-musl.so at 0x38880000
LOAD: 0x3fff1fc0: libmpdec.so.3 at 0x38c00000
LOAD: 0x3fff43b0: /usr/lib/python3.11/site-packages/pandas/_libs/tslibs/period.cpython-311-aarch64-linux-musl.so at 0x38c80000
LOAD: 0x3fff43b0: /usr/lib/python3.11/site-packages/pandas/_libs/tslibs/vectorized.cpython-311-aarch64-linux-musl.so at 0x38d40000
LOAD: 0x3fff5340: /usr/lib/python3.11/site-packages/pandas/_libs/ops_dispatch.cpython-311-aarch64-linux-musl.so at 0x38d80000
LOAD: 0x3fff72b0: /usr/lib/python3.11/site-packages/pandas/_libs/algos.cpython-311-aarch64-linux-musl.so at 0x38e00000
LOAD: 0x3fff8080: /usr/lib/python3.11/site-packages/pandas/_libs/lib.cpython-311-aarch64-linux-musl.so at 0x39000000
LOAD: 0x3fff79a0: /usr/lib/python3.11/site-packages/pandas/_libs/tslib.cpython-311-aarch64-linux-musl.so at 0x39100000
LOAD: 0x3fff85b0: /usr/lib/python3.11/site-packages/pandas/_libs/hashing.cpython-311-aarch64-linux-musl.so at 0x39180000
LOAD: 0x3fff6a30: /usr/lib/python3.11/site-packages/pandas/_libs/ops.cpython-311-aarch64-linux-musl.so at 0x39440000
LOAD: 0x3fff8ae0: /usr/lib/python3.11/lib-dynload/_csv.cpython-311-aarch64-linux-musl.so at 0x39580000
LOAD: 0x3fff8ae0: /usr/lib/python3.11/lib-dynload/zlib.cpython-311-aarch64-linux-musl.so at 0x39700000
LOAD: 0x3fff8370: /usr/lib/python3.11/lib-dynload/_bz2.cpython-311-aarch64-linux-musl.so at 0x39740000
LOAD: 0x3fff8320: libbz2.so.1 at 0x39780000
LOAD: 0x3fff8370: /usr/lib/python3.11/lib-dynload/_lzma.cpython-311-aarch64-linux-musl.so at 0x397c0000
LOAD: 0x3fff8320: liblzma.so.5 at 0x39800000
LOAD: 0x3fff9250: /usr/lib/python3.11/site-packages/pandas/_libs/arrays.cpython-311-aarch64-linux-musl.so at 0x39880000
LOAD: 0x3fff8ae0: /usr/lib/python3.11/lib-dynload/unicodedata.cpython-311-aarch64-linux-musl.so at 0x39a00000
LOAD: 0x3fff85b0: /usr/lib/python3.11/site-packages/pandas/_libs/index.cpython-311-aarch64-linux-musl.so at 0x39e80000
LOAD: 0x3fff8ae0: /usr/lib/python3.11/site-packages/pandas/_libs/join.cpython-311-aarch64-linux-musl.so at 0x3a000000
LOAD: 0x3fff7490: /usr/lib/python3.11/site-packages/pandas/_libs/sparse.cpython-311-aarch64-linux-musl.so at 0x39f00000
LOAD: 0x3fff8d20: /usr/lib/python3.11/site-packages/pandas/_libs/reduction.cpython-311-aarch64-linux-musl.so at 0x3a380000
LOAD: 0x3fff76d0: /usr/lib/python3.11/site-packages/pandas/_libs/indexing.cpython-311-aarch64-linux-musl.so at 0x3a980000
LOAD: 0x3fff65b0: /usr/lib/python3.11/site-packages/pandas/_libs/internals.cpython-311-aarch64-linux-musl.so at 0x3ac00000
LOAD: 0x3fff5910: /usr/lib/python3.11/site-packages/pandas/_libs/writers.cpython-311-aarch64-linux-musl.so at 0x7680000
LOAD: 0x3fff6d20: /usr/lib/python3.11/lib-dynload/mmap.cpython-311-aarch64-linux-musl.so at 0x3af40000
LOAD: 0x3fff65b0: /usr/lib/python3.11/lib-dynload/grp.cpython-311-aarch64-linux-musl.so at 0x3afc0000
LOAD: 0x3fff7490: /usr/lib/python3.11/site-packages/pandas/_libs/window/aggregations.cpython-311-aarch64-linux-musl.so at 0x3b180000
LOAD: 0x3fff7440: libstdc++.so.6 at 0x3b400000
LOAD: 0x3fff6d20: /usr/lib/python3.11/site-packages/pandas/_libs/window/indexers.cpython-311-aarch64-linux-musl.so at 0x3b280000
LOAD: 0x3fff7e40: /usr/lib/python3.11/site-packages/pandas/_libs/reshape.cpython-311-aarch64-linux-musl.so at 0x3b800000
LOAD: 0x3fff7c00: /usr/lib/python3.11/site-packages/pandas/_libs/tslibs/strptime.cpython-311-aarch64-linux-musl.so at 0x3b880000
LOAD: 0x3fff8ae0: /usr/lib/python3.11/site-packages/pandas/_libs/groupby.cpython-311-aarch64-linux-musl.so at 0x3bb00000
LOAD: 0x3fff85b0: /usr/lib/python3.11/lib-dynload/_socket.cpython-311-aarch64-linux-musl.so at 0x3bec0000
LOAD: 0x3fff85b0: /usr/lib/python3.11/lib-dynload/array.cpython-311-aarch64-linux-musl.so at 0x3bf40000
LOAD: 0x3fff8d20: /usr/lib/python3.11/site-packages/pandas/_libs/testing.cpython-311-aarch64-linux-musl.so at 0x3bf80000
LOAD: 0x3fff86a0: /usr/lib/python3.11/lib-dynload/cmath.cpython-311-aarch64-linux-musl.so at 0x3bfc0000
LOAD: 0x3fff9250: /usr/lib/python3.11/site-packages/pandas/_libs/parsers.cpython-311-aarch64-linux-musl.so at 0x8080000
LOAD: 0x3fff9250: /usr/lib/python3.11/site-packages/pandas/_libs/json.cpython-311-aarch64-linux-musl.so at 0x8180000
LOAD: 0x3fff96d0: /usr/lib/python3.11/site-packages/sklearn/__check_build/_check_build.cpython-311-aarch64-linux-musl.so at 0x89c0000
LOAD: 0x3fff7b50: /usr/lib/python3.11/site-packages/scipy/_lib/_ccallback_c.cpython-311-aarch64-linux-musl.so at 0x8ac0000
LOAD: 0x3fff85b0: /usr/lib/python3.11/site-packages/scipy/sparse/_sparsetools.cpython-311-aarch64-linux-musl.so at 0x9000000
LOAD: 0x3fff8080: /usr/lib/python3.11/site-packages/scipy/sparse/_csparsetools.cpython-311-aarch64-linux-musl.so at 0x8d00000
LOAD: 0x3fff5d90: /usr/lib/python3.11/site-packages/scipy/sparse/linalg/_isolve/_iterative.cpython-311-aarch64-linux-musl.so at 0x8e80000
LOAD: 0x3fff4740: /usr/lib/python3.11/site-packages/scipy/linalg/_fblas.cpython-311-aarch64-linux-musl.so at 0x9400000
LOAD: 0x3fff4740: /usr/lib/python3.11/site-packages/scipy/linalg/_flapack.cpython-311-aarch64-linux-musl.so at 0x9600000
LOAD: 0x3fff5b50: /usr/lib/python3.11/site-packages/scipy/linalg/_cythonized_array_utils.cpython-311-aarch64-linux-musl.so at 0x9900000
LOAD: 0x3fff4740: /usr/lib/python3.11/site-packages/scipy/linalg/_flinalg.cpython-311-aarch64-linux-musl.so at 0x99c0000
LOAD: 0x3fff53e0: /usr/lib/python3.11/site-packages/scipy/linalg/_solve_toeplitz.cpython-311-aarch64-linux-musl.so at 0x9a80000
LOAD: 0x3fff4c70: /usr/lib/python3.11/site-packages/scipy/linalg/_matfuncs_sqrtm_triu.cpython-311-aarch64-linux-musl.so at 0x9b00000
LOAD: 0x3fff53e0: /usr/lib/python3.11/site-packages/scipy/linalg/_matfuncs_expm.cpython-311-aarch64-linux-musl.so at 0x9b80000
LOAD: 0x3fff49f0: /usr/lib/python3.11/site-packages/scipy/linalg/cython_lapack.cpython-311-aarch64-linux-musl.so at 0x9d00000
LOAD: 0x3fff49f0: /usr/lib/python3.11/site-packages/scipy/linalg/cython_blas.cpython-311-aarch64-linux-musl.so at 0x9c80000
LOAD: 0x3fff5b50: /usr/lib/python3.11/site-packages/scipy/linalg/_decomp_update.cpython-311-aarch64-linux-musl.so at 0x9e00000
LOAD: 0x3fff5d90: /usr/lib/python3.11/site-packages/scipy/sparse/linalg/_dsolve/_superlu.cpython-311-aarch64-linux-musl.so at 0xa000000
LOAD: 0x3fff5620: /usr/lib/python3.11/site-packages/scipy/sparse/linalg/_eigen/arpack/_arpack.cpython-311-aarch64-linux-musl.so at 0xa100000
LOAD: 0x3fff8080: /usr/lib/python3.11/site-packages/scipy/sparse/csgraph/_shortest_path.cpython-311-aarch64-linux-musl.so at 0xa200000
LOAD: 0x3fff7220: /usr/lib/python3.11/site-packages/scipy/sparse/csgraph/_tools.cpython-311-aarch64-linux-musl.so at 0xa2c0000
LOAD: 0x3fff8080: /usr/lib/python3.11/site-packages/scipy/sparse/csgraph/_traversal.cpython-311-aarch64-linux-musl.so at 0xa340000
LOAD: 0x3fff8080: /usr/lib/python3.11/site-packages/scipy/sparse/csgraph/_min_spanning_tree.cpython-311-aarch64-linux-musl.so at 0xa380000
LOAD: 0x3fff8080: /usr/lib/python3.11/site-packages/scipy/sparse/csgraph/_flow.cpython-311-aarch64-linux-musl.so at 0xa400000
LOAD: 0x3fff8080: /usr/lib/python3.11/site-packages/scipy/sparse/csgraph/_matching.cpython-311-aarch64-linux-musl.so at 0xa480000
LOAD: 0x3fff8080: /usr/lib/python3.11/site-packages/scipy/sparse/csgraph/_reordering.cpython-311-aarch64-linux-musl.so at 0xa500000
LOAD: 0x3fff9490: /usr/lib/python3.11/site-packages/sklearn/utils/murmurhash.cpython-311-aarch64-linux-musl.so at 0xa600000
LOAD: 0x3fff6a30: /usr/lib/python3.11/lib-dynload/_heapq.cpython-311-aarch64-linux-musl.so at 0xa880000
LOAD: 0x3fff71a0: /usr/lib/python3.11/lib-dynload/_queue.cpython-311-aarch64-linux-musl.so at 0xa8c0000
LOAD: 0x3fff71a0: /usr/lib/python3.11/lib-dynload/_multiprocessing.cpython-311-aarch64-linux-musl.so at 0xa900000
LOAD: 0x3fff6f60: /usr/lib/python3.11/site-packages/numpy/linalg/lapack_lite.cpython-311-aarch64-linux-musl.so at 0xac40000
LOAD: 0x3fff6a30: /usr/lib/python3.11/site-packages/scipy/spatial/_ckdtree.cpython-311-aarch64-linux-musl.so at 0xad00000
LOAD: 0x3fff71a0: /usr/lib/python3.11/site-packages/scipy/spatial/_qhull.cpython-311-aarch64-linux-musl.so at 0xae00000
LOAD: 0x3fff6840: /usr/lib/python3.11/site-packages/scipy/_lib/messagestream.cpython-311-aarch64-linux-musl.so at 0xaf80000
LOAD: 0x3fff5d90: /usr/lib/python3.11/site-packages/scipy/spatial/_distance_wrap.cpython-311-aarch64-linux-musl.so at 0xb800000
LOAD: 0x3fff5d90: /usr/lib/python3.11/site-packages/scipy/spatial/_hausdorff.cpython-311-aarch64-linux-musl.so at 0xb880000
LOAD: 0x3fff5620: /usr/lib/python3.11/site-packages/scipy/special/_ufuncs.cpython-311-aarch64-linux-musl.so at 0xba00000
LOAD: 0x3fff4c80: /usr/lib/python3.11/site-packages/scipy/special/_ufuncs_cxx.cpython-311-aarch64-linux-musl.so at 0xb980000
LOAD: 0x3fff4980: /usr/lib/python3.11/site-packages/scipy/special/_specfun.cpython-311-aarch64-linux-musl.so at 0xbd80000
LOAD: 0x3fff4eb0: /usr/lib/python3.11/site-packages/scipy/special/_comb.cpython-311-aarch64-linux-musl.so at 0xbe00000
LOAD: 0x3fff53e0: /usr/lib/python3.11/site-packages/scipy/special/_ellip_harm_2.cpython-311-aarch64-linux-musl.so at 0xbe80000
LOAD: 0x3fff5d90: /usr/lib/python3.11/site-packages/scipy/spatial/_distance_pybind.cpython-311-aarch64-linux-musl.so at 0xc080000
LOAD: 0x3fff6500: /usr/lib/python3.11/site-packages/scipy/spatial/transform/_rotation.cpython-311-aarch64-linux-musl.so at 0xc100000
LOAD: 0x3fff6a30: /usr/lib/python3.11/site-packages/scipy/ndimage/_nd_image.cpython-311-aarch64-linux-musl.so at 0xc300000
LOAD: 0x3fff6a30: /usr/lib/python3.11/site-packages/scipy/ndimage/_ni_label.cpython-311-aarch64-linux-musl.so at 0xc380000
LOAD: 0x3fff4c50: /usr/lib/python3.11/site-packages/scipy/optimize/_minpack2.cpython-311-aarch64-linux-musl.so at 0xc500000
LOAD: 0x3fff5180: /usr/lib/python3.11/site-packages/scipy/optimize/_group_columns.cpython-311-aarch64-linux-musl.so at 0xc540000
LOAD: 0x3fff4a10: /usr/lib/python3.11/site-packages/scipy/optimize/_trlib/_trlib.cpython-311-aarch64-linux-musl.so at 0xc600000
LOAD: 0x3fff4c50: /usr/lib/python3.11/site-packages/scipy/optimize/_lbfgsb.cpython-311-aarch64-linux-musl.so at 0xc6c0000
LOAD: 0x3fff4c50: /usr/lib/python3.11/site-packages/scipy/optimize/_moduleTNC.cpython-311-aarch64-linux-musl.so at 0xc740000
LOAD: 0x3fff4c50: /usr/lib/python3.11/site-packages/scipy/optimize/_cobyla.cpython-311-aarch64-linux-musl.so at 0xc780000
LOAD: 0x3fff5180: /usr/lib/python3.11/site-packages/scipy/optimize/_slsqp.cpython-311-aarch64-linux-musl.so at 0xc7c0000
LOAD: 0x3fff4c50: /usr/lib/python3.11/site-packages/scipy/optimize/_minpack.cpython-311-aarch64-linux-musl.so at 0xc800000
LOAD: 0x3fff3b30: /usr/lib/python3.11/site-packages/scipy/optimize/_lsq/givens_elimination.cpython-311-aarch64-linux-musl.so at 0xc880000
LOAD: 0x3fff4720: /usr/lib/python3.11/site-packages/scipy/optimize/_zeros.cpython-311-aarch64-linux-musl.so at 0xca40000
LOAD: 0x3fff53c0: /usr/lib/python3.11/site-packages/scipy/optimize/__nnls.cpython-311-aarch64-linux-musl.so at 0xca80000
LOAD: 0x3fff5180: /usr/lib/python3.11/site-packages/scipy/optimize/_highs/_highs_wrapper.cpython-311-aarch64-linux-musl.so at 0xcc00000
LOAD: 0x3fff5180: /usr/lib/python3.11/site-packages/scipy/optimize/_highs/_highs_constants.cpython-311-aarch64-linux-musl.so at 0xcb00000
LOAD: 0x3fff33c0: /usr/lib/python3.11/site-packages/scipy/linalg/_interpolative.cpython-311-aarch64-linux-musl.so at 0xcb80000
LOAD: 0x3fff5180: /usr/lib/python3.11/site-packages/scipy/optimize/_bglu_dense.cpython-311-aarch64-linux-musl.so at 0xd080000
LOAD: 0x3fff6060: /usr/lib/python3.11/site-packages/scipy/optimize/_lsap.cpython-311-aarch64-linux-musl.so at 0xd140000
LOAD: 0x3fff58f0: /usr/lib/python3.11/site-packages/scipy/optimize/_direct.cpython-311-aarch64-linux-musl.so at 0xd200000
LOAD: 0x3fff53c0: /usr/lib/python3.11/site-packages/scipy/integrate/_odepack.cpython-311-aarch64-linux-musl.so at 0xd280000
LOAD: 0x3fff53c0: /usr/lib/python3.11/site-packages/scipy/integrate/_quadpack.cpython-311-aarch64-linux-musl.so at 0xd2c0000
LOAD: 0x3fff53c0: /usr/lib/python3.11/site-packages/scipy/integrate/_vode.cpython-311-aarch64-linux-musl.so at 0xd340000
LOAD: 0x3fff53c0: /usr/lib/python3.11/site-packages/scipy/integrate/_dop.cpython-311-aarch64-linux-musl.so at 0xd380000
LOAD: 0x3fff53c0: /usr/lib/python3.11/site-packages/scipy/integrate/_lsoda.cpython-311-aarch64-linux-musl.so at 0xd3c0000
LOAD: 0x3fff5fd0: /usr/lib/python3.11/site-packages/scipy/stats/_stats.cpython-311-aarch64-linux-musl.so at 0xd900000
LOAD: 0x3fff5670: /usr/lib/python3.11/site-packages/scipy/special/cython_special.cpython-311-aarch64-linux-musl.so at 0xda00000
LOAD: 0x3fff5d90: /usr/lib/python3.11/site-packages/scipy/stats/_boost/beta_ufunc.cpython-311-aarch64-linux-musl.so at 0xdc00000
LOAD: 0x3fff5d90: /usr/lib/python3.11/site-packages/scipy/stats/_boost/binom_ufunc.cpython-311-aarch64-linux-musl.so at 0xdd00000
LOAD: 0x3fff5d90: /usr/lib/python3.11/site-packages/scipy/stats/_boost/nbinom_ufunc.cpython-311-aarch64-linux-musl.so at 0xdd80000
LOAD: 0x3fff5d90: /usr/lib/python3.11/site-packages/scipy/stats/_boost/hypergeom_ufunc.cpython-311-aarch64-linux-musl.so at 0xde00000
LOAD: 0x3fff5d90: /usr/lib/python3.11/site-packages/scipy/stats/_boost/ncf_ufunc.cpython-311-aarch64-linux-musl.so at 0xde80000
LOAD: 0x3fff5d90: /usr/lib/python3.11/site-packages/scipy/stats/_boost/ncx2_ufunc.cpython-311-aarch64-linux-musl.so at 0xdf00000
LOAD: 0x3fff5d90: /usr/lib/python3.11/site-packages/scipy/stats/_boost/nct_ufunc.cpython-311-aarch64-linux-musl.so at 0xdf80000
LOAD: 0x3fff5d90: /usr/lib/python3.11/site-packages/scipy/stats/_boost/skewnorm_ufunc.cpython-311-aarch64-linux-musl.so at 0xe080000
LOAD: 0x3fff5d90: /usr/lib/python3.11/site-packages/scipy/stats/_boost/invgauss_ufunc.cpython-311-aarch64-linux-musl.so at 0xe100000
LOAD: 0x3fff3ce0: /usr/lib/python3.11/site-packages/scipy/interpolate/_fitpack.cpython-311-aarch64-linux-musl.so at 0xe1c0000
LOAD: 0x3fff3ce0: /usr/lib/python3.11/site-packages/scipy/interpolate/dfitpack.cpython-311-aarch64-linux-musl.so at 0xe300000
LOAD: 0x3fff3ce0: /usr/lib/python3.11/site-packages/scipy/interpolate/_bspl.cpython-311-aarch64-linux-musl.so at 0xe400000
LOAD: 0x3fff50f0: /usr/lib/python3.11/site-packages/scipy/interpolate/_ppoly.cpython-311-aarch64-linux-musl.so at 0xe480000
LOAD: 0x3fff5620: /usr/lib/python3.11/site-packages/scipy/interpolate/interpnd.cpython-311-aarch64-linux-musl.so at 0xe580000
LOAD: 0x3fff5620: /usr/lib/python3.11/site-packages/scipy/interpolate/_rbfinterp_pythran.cpython-311-aarch64-linux-musl.so at 0xe600000
LOAD: 0x3fff5620: /usr/lib/python3.11/site-packages/scipy/interpolate/_rgi_cython.cpython-311-aarch64-linux-musl.so at 0xe680000
LOAD: 0x3fff6500: /usr/lib/python3.11/site-packages/scipy/stats/_biasedurn.cpython-311-aarch64-linux-musl.so at 0xe740000
LOAD: 0x3fff6a30: /usr/lib/python3.11/site-packages/scipy/stats/_levy_stable/levyst.cpython-311-aarch64-linux-musl.so at 0xe780000
LOAD: 0x3fff6a30: /usr/lib/python3.11/site-packages/scipy/stats/_stats_pythran.cpython-311-aarch64-linux-musl.so at 0xe840000
LOAD: 0x3fff7910: /usr/lib/python3.11/site-packages/scipy/stats/_statlib.cpython-311-aarch64-linux-musl.so at 0xea40000
LOAD: 0x3fff7910: /usr/lib/python3.11/site-packages/scipy/stats/_mvn.cpython-311-aarch64-linux-musl.so at 0xec00000
LOAD: 0x3fff71a0: /usr/lib/python3.11/site-packages/scipy/stats/_sobol.cpython-311-aarch64-linux-musl.so at 0xed80000
LOAD: 0x3fff71a0: /usr/lib/python3.11/site-packages/scipy/stats/_qmc_cy.cpython-311-aarch64-linux-musl.so at 0xeb00000
LOAD: 0x3fff71a0: /usr/lib/python3.11/site-packages/scipy/stats/_rcont/rcont.cpython-311-aarch64-linux-musl.so at 0xef00000
LOAD: 0x3fff8d20: /usr/lib/python3.11/site-packages/sklearn/utils/_isfinite.cpython-311-aarch64-linux-musl.so at 0xf180000
LOAD: 0x3fff9c00: /usr/lib/python3.11/site-packages/sklearn/utils/_openmp_helpers.cpython-311-aarch64-linux-musl.so at 0xf140000
LOAD: 0x3fff9bb0: libgomp.so.1 at 0xf200000
LOAD: 0x3fff99c0: /usr/lib/python3.11/site-packages/sklearn/utils/_logistic_sigmoid.cpython-311-aarch64-linux-musl.so at 0x3ad80000
LOAD: 0x3fff99c0: /usr/lib/python3.11/site-packages/sklearn/utils/sparsefuncs_fast.cpython-311-aarch64-linux-musl.so at 0xf600000
LOAD: 0x3fffa130: /usr/lib/python3.11/site-packages/sklearn/preprocessing/_csr_polynomial_expansion.cpython-311-aarch64-linux-musl.so at 0xf700000
hello world
0    4733
1     248
Name: stroke, dtype: int64
LOAD: 0x3fff8ae0: /usr/lib/python3.11/lib-dynload/_ssl.cpython-311-aarch64-linux-musl.so at 0x30100000
LOAD: 0x3fff8a90: libssl.so.3 at 0x30200000
LOAD: 0x3fff8d20: /usr/lib/python3.11/site-packages/sklearn/feature_extraction/_hashing_fast.cpython-311-aarch64-linux-musl.so at 0x30400000
LOAD: 0x3fff8360: /usr/lib/python3.11/site-packages/sklearn/utils/_vector_sentinel.cpython-311-aarch64-linux-musl.so at 0x30440000
LOAD: 0x3fff99c0: /usr/lib/python3.11/site-packages/sklearn/utils/_random.cpython-311-aarch64-linux-musl.so at 0x30540000
LOAD: 0x3fffa130: /usr/lib/python3.11/site-packages/sklearn/datasets/_svmlight_format_fast.cpython-311-aarch64-linux-musl.so at 0x30580000
LOAD: 0x3fff8370: /usr/lib/python3.11/site-packages/scipy/io/matlab/_mio_utils.cpython-311-aarch64-linux-musl.so at 0x306c0000
LOAD: 0x3fff8370: /usr/lib/python3.11/site-packages/scipy/io/matlab/_mio5_utils.cpython-311-aarch64-linux-musl.so at 0x30700000
LOAD: 0x3fff7a00: /usr/lib/python3.11/site-packages/scipy/io/matlab/_streams.cpython-311-aarch64-linux-musl.so at 0x30780000
LOAD: 0x3fff71a0: /usr/lib/python3.11/site-packages/sklearn/neighbors/_ball_tree.cpython-311-aarch64-linux-musl.so at 0x30a00000
LOAD: 0x3fff5b90: /usr/lib/python3.11/site-packages/sklearn/metrics/_dist_metrics.cpython-311-aarch64-linux-musl.so at 0x30b00000
LOAD: 0x3fff5520: /usr/lib/python3.11/site-packages/sklearn/utils/_typedefs.cpython-311-aarch64-linux-musl.so at 0x30c40000
LOAD: 0x3fff5520: /usr/lib/python3.11/site-packages/sklearn/utils/_readonly_array_wrapper.cpython-311-aarch64-linux-musl.so at 0x30c80000
LOAD: 0x3fff4780: /usr/lib/python3.11/site-packages/sklearn/metrics/cluster/_expected_mutual_info_fast.cpython-311-aarch64-linux-musl.so at 0x30d00000
LOAD: 0x3fff3130: /usr/lib/python3.11/site-packages/sklearn/metrics/_pairwise_distances_reduction/_base.cpython-311-aarch64-linux-musl.so at 0x30f00000
LOAD: 0x3fff27e0: /usr/lib/python3.11/site-packages/sklearn/metrics/_pairwise_distances_reduction/_datasets_pair.cpython-311-aarch64-linux-musl.so at 0x30f80000
LOAD: 0x3fff27e0: /usr/lib/python3.11/site-packages/sklearn/utils/_cython_blas.cpython-311-aarch64-linux-musl.so at 0x31000000
LOAD: 0x3fff3130: /usr/lib/python3.11/site-packages/sklearn/metrics/_pairwise_distances_reduction/_argkmin.cpython-311-aarch64-linux-musl.so at 0x31100000
LOAD: 0x3fff27f0: /usr/lib/python3.11/site-packages/sklearn/metrics/_pairwise_distances_reduction/_middle_term_computer.cpython-311-aarch64-linux-musl.so at 0x31180000
LOAD: 0x3fff27f0: /usr/lib/python3.11/site-packages/sklearn/utils/_heap.cpython-311-aarch64-linux-musl.so at 0x31240000
LOAD: 0x3fff27f0: /usr/lib/python3.11/site-packages/sklearn/utils/_sorting.cpython-311-aarch64-linux-musl.so at 0x31280000
LOAD: 0x3fff3130: /usr/lib/python3.11/site-packages/sklearn/metrics/_pairwise_distances_reduction/_radius_neighbors.cpython-311-aarch64-linux-musl.so at 0x31300000
LOAD: 0x3fff4010: /usr/lib/python3.11/site-packages/sklearn/metrics/_pairwise_fast.cpython-311-aarch64-linux-musl.so at 0x31380000
LOAD: 0x3fff6830: /usr/lib/python3.11/site-packages/sklearn/neighbors/_partition_nodes.cpython-311-aarch64-linux-musl.so at 0x31440000
LOAD: 0x3fff71a0: /usr/lib/python3.11/site-packages/sklearn/neighbors/_kd_tree.cpython-311-aarch64-linux-musl.so at 0x31480000
LOAD: 0x3fff5b50: /usr/lib/python3.11/site-packages/sklearn/decomposition/_cdnmf_fast.cpython-311-aarch64-linux-musl.so at 0x31600000
LOAD: 0x3fff4c70: /usr/lib/python3.11/site-packages/sklearn/utils/_seq_dataset.cpython-311-aarch64-linux-musl.so at 0x316c0000
LOAD: 0x3fff4740: /usr/lib/python3.11/site-packages/sklearn/utils/arrayfuncs.cpython-311-aarch64-linux-musl.so at 0x31780000
LOAD: 0x3fff4740: /usr/lib/python3.11/site-packages/sklearn/linear_model/_cd_fast.cpython-311-aarch64-linux-musl.so at 0x31980000
LOAD: 0x3fff2980: /usr/lib/python3.11/site-packages/sklearn/_loss/_loss.cpython-311-aarch64-linux-musl.so at 0x31c00000
LOAD: 0x3fff53e0: /usr/lib/python3.11/site-packages/sklearn/linear_model/_sgd_fast.cpython-311-aarch64-linux-musl.so at 0x31e00000
LOAD: 0x3fff48e0: /usr/lib/python3.11/site-packages/sklearn/utils/_weight_vector.cpython-311-aarch64-linux-musl.so at 0x31e80000
LOAD: 0x3fff4500: /usr/lib/python3.11/site-packages/sklearn/linear_model/_sag_fast.cpython-311-aarch64-linux-musl.so at 0x32040000
LOAD: 0x3fff2bc0: /usr/lib/python3.11/site-packages/sklearn/svm/_libsvm.cpython-311-aarch64-linux-musl.so at 0x32100000
LOAD: 0x3fff2bc0: /usr/lib/python3.11/site-packages/sklearn/svm/_liblinear.cpython-311-aarch64-linux-musl.so at 0x321c0000
LOAD: 0x3fff2bc0: /usr/lib/python3.11/site-packages/sklearn/svm/_libsvm_sparse.cpython-311-aarch64-linux-musl.so at 0x32280000
LOAD: 0x3fff5b50: /usr/lib/python3.11/site-packages/sklearn/decomposition/_online_lda_fast.cpython-311-aarch64-linux-musl.so at 0x32400000
LOAD: 0x3fff53e0: /usr/lib/python3.11/site-packages/sklearn/_isotonic.cpython-311-aarch64-linux-musl.so at 0x32500000
LOAD: 0x3fff5620: /usr/lib/python3.11/site-packages/sklearn/manifold/_utils.cpython-311-aarch64-linux-musl.so at 0x325c0000
LOAD: 0x3fff5620: /usr/lib/python3.11/site-packages/sklearn/manifold/_barnes_hut_tsne.cpython-311-aarch64-linux-musl.so at 0x32600000
LOAD: 0x3fff4c80: /usr/lib/python3.11/site-packages/sklearn/neighbors/_quad_tree.cpython-311-aarch64-linux-musl.so at 0x32680000
LOAD: 0x3fff2ef0: /usr/lib/python3.11/site-packages/sklearn/tree/_criterion.cpython-311-aarch64-linux-musl.so at 0x32780000
LOAD: 0x3fff2580: /usr/lib/python3.11/site-packages/sklearn/tree/_splitter.cpython-311-aarch64-linux-musl.so at 0x32800000
LOAD: 0x3fff1c10: /usr/lib/python3.11/site-packages/sklearn/tree/_tree.cpython-311-aarch64-linux-musl.so at 0x32880000
LOAD: 0x3fff12e0: /usr/lib/python3.11/site-packages/sklearn/tree/_utils.cpython-311-aarch64-linux-musl.so at 0x32980000
LOAD: 0x3fff62c0: /usr/lib/python3.11/site-packages/sklearn/cluster/_k_means_common.cpython-311-aarch64-linux-musl.so at 0x32a80000
LOAD: 0x3fff62c0: /usr/lib/python3.11/site-packages/sklearn/cluster/_k_means_minibatch.cpython-311-aarch64-linux-musl.so at 0x32b00000
LOAD: 0x3fff62c0: /usr/lib/python3.11/site-packages/sklearn/cluster/_k_means_lloyd.cpython-311-aarch64-linux-musl.so at 0x32b80000
LOAD: 0x3fff62c0: /usr/lib/python3.11/site-packages/sklearn/cluster/_k_means_elkan.cpython-311-aarch64-linux-musl.so at 0x32c00000
LOAD: 0x3fff6a30: /usr/lib/python3.11/site-packages/sklearn/utils/_fast_dict.cpython-311-aarch64-linux-musl.so at 0x32d00000
LOAD: 0x3fff6500: /usr/lib/python3.11/site-packages/sklearn/cluster/_hierarchical_fast.cpython-311-aarch64-linux-musl.so at 0x32e00000
LOAD: 0x3fff6a30: /usr/lib/python3.11/site-packages/sklearn/cluster/_dbscan_inner.cpython-311-aarch64-linux-musl.so at 0x32e80000
LOAD: 0x3fff6a30: /usr/lib/python3.11/site-packages/sklearn/ensemble/_gradient_boosting.cpython-311-aarch64-linux-musl.so at 0x33100000
LOAD: 0x3fff6a30: /usr/lib/python3.11/site-packages/sklearn/ensemble/_hist_gradient_boosting/_gradient_boosting.cpython-311-aarch64-linux-musl.so at 0x331c0000
LOAD: 0x3fff63d0: /usr/lib/python3.11/site-packages/sklearn/ensemble/_hist_gradient_boosting/common.cpython-311-aarch64-linux-musl.so at 0x33240000
LOAD: 0x3fff62c0: /usr/lib/python3.11/site-packages/sklearn/ensemble/_hist_gradient_boosting/_binning.cpython-311-aarch64-linux-musl.so at 0x332c0000
LOAD: 0x3fff62c0: /usr/lib/python3.11/site-packages/sklearn/ensemble/_hist_gradient_boosting/_bitset.cpython-311-aarch64-linux-musl.so at 0x33300000
LOAD: 0x3fff62c0: /usr/lib/python3.11/site-packages/sklearn/ensemble/_hist_gradient_boosting/splitting.cpython-311-aarch64-linux-musl.so at 0x33380000
LOAD: 0x3fff62c0: /usr/lib/python3.11/site-packages/sklearn/ensemble/_hist_gradient_boosting/histogram.cpython-311-aarch64-linux-musl.so at 0x33480000
LOAD: 0x3fff5b50: /usr/lib/python3.11/site-packages/sklearn/ensemble/_hist_gradient_boosting/_predictor.cpython-311-aarch64-linux-musl.so at 0x33500000
LOAD: 0x3fff62c0: /usr/lib/python3.11/site-packages/sklearn/ensemble/_hist_gradient_boosting/utils.cpython-311-aarch64-linux-musl.so at 0x33580000
1    4733
0    4733
Name: stroke, dtype: int64
            age  ...  smoking_status_smokes
492   52.000000  ...                      0
5529  77.985506  ...                      0
4879  10.000000  ...                      0
3036  79.000000  ...                      0
8396  70.975621  ...                      0
...         ...  ...                    ...
102   80.000000  ...                      1
4421  45.000000  ...                      0
2574  80.000000  ...                      0
5985  82.000000  ...                      0
2819  20.000000  ...                      0
[7572 rows x 19 columns]
TRAINING ACCURACY: 1.0
VALIDATION ACCURACY 0.9714889123548046
Warning: _Exit is replaced by wrap_thread_exit()
```