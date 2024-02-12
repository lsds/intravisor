Relies on Python and darknet. 


```
Using yaml.cfg = /intravisor/cvm.yaml
***************** [16] Deploy 'darknet' ***************
BUILDING cvm: name=darknet, disk=disk_darknet_python.img, runtime=libmusl-lkl.so, net=(null), args='/ld.so /usr/bin/python3.9 /darknet.py', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = 'monitor' wait = 0s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
[1]: 8abc1000 400000000 f218c f218c 8abc1000 f218c
[2]: 8acb3190 400102190 26ea3c 26ea3c 8acb3190 26ea3c
end of RO: 400380be0
[3]: 8af21be0 400380be0 fe78 fe78 8af21be0 fe78
[4]: 8af31c00 4003a0c00 12c688 1c3fe0 8af31c00 12c688
ELF BASE = 0x400000000, MAP SIZE = 564be0, ENTRY = 0x14fb6c
encl_map.entry = 0x14fb6c
encl_map.ret = 0x361fd0
[cVM STACKs] = [0x43e000000 -- 440000000]
Convrting free memory into cVM Heap: 400565000 -- 43e000000 +3da9b000 ( 986.605469 MB)
cVM has cvm_heap_begin (4bd490) and cvm_heap_size (4bd498)
SEALED RET FROM MON 0x81005140 0x81005130
ACHTUNG: 'libmusl-lkl.so' has syscall handler 'syscall_handler' at 0x362008
Deploy 16 in 6.578000, SHA-256 Hash: 71524d537b961f77e23fc1fb5462120c6ec8a2d1e5955da6d00a37c6f95b09df
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 43fffc000, old TP = 43ffffbe0 sp_read = 0x440000000, me->stacl = 0x43ff80000, getSP()=0x43ffff990, me->c_tp = 0x43ffffbd0 43ffffbc0
[1] '/usr/bin/python3.9'
sp[i+1] = '/usr/bin/python3.9'
[2] '/darknet.py'
sp[i+1] = '/darknet.py'
&env0 = 0x43fffc028, &env1=0x43fffc030
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
[    0.000115] lkl: time and timers initialized (irq1)
[    0.001293] pid_max: default: 4096 minimum: 301
[    0.006656] Mount-cache hash table entries: 2048 (order: 2, 16384 bytes)
[    0.007340] Mountpoint-cache hash table entries: 2048 (order: 2, 16384 bytes)
[    0.096404] devtmpfs: initialized
[    0.302028] console [lkl_console0] enabled
[    0.305697] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.308840] xor: automatically using best checksumming function   8regs     
[    0.344704] cryptd: max_cpu_qlen set to 1000
[    0.360889] clocksource: Switched to clocksource lkl
[    0.393602] workingset: timestamp_bits=62 max_order=18 bucket_order=0
[    0.454985] romfs: ROMFS MTD (C) 2007 Red Hat, Inc.
[    0.635040] io scheduler noop registered
[    0.637054] io scheduler deadline registered
[    0.641401] io scheduler cfq registered (default)
[    0.642876] io scheduler mq-deadline registered
[    0.644420] io scheduler kyber registered
CAP_FILE INIT 43 4004e201
CAP_STREAM_HOST INIT 45 4004e401
[    1.191470] device-mapper: ioctl: 4.39.0-ioctl (2018-04-03) initialised: dm-devel@redhat.com
[    1.201728] random: get_random_bytes called from 0x000000000015e5d0 with crng_init=0
[    1.215870] Warning: unable to open an initial console.
[    1.218555] This architecture does not have kernel memory protection.
INT: ignore destructor 15ab5c in tls_alloc
------ LKL INIT DONE, starting mount  ------- 
ADD disk
[    1.270503] virtio_blk virtio0: [vda] 800000 512-byte logical blocks (410 MB/391 MiB)
disk id = 0
------ ADD disk DONE ------- 
[    1.425215] EXT4-fs (vda): mounted filesystem with ordered data mode. Opts: 
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
[.]
[darknet.py]
[dev]
[..]
[proc]
[run]
[alexnet.weights]
[data]
[lost+found]
[app]
[usr]
[cap]
[cfg]
[libdarknet.so]
[sys]
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
[    1.605329] random: crng init done
MOUNT DONE
td = 0x4cfe08, p = 0x4cfe08, td->robust_list.head = 0x4cfe98 0x3fffbce0 0x4cfe98
NO NETWORK 
LOAD: /usr/bin/python3.9
app.base = 0x3c400000
ready to start the app: 0x3c462708
envp = 0x3fffc028, me->argv[0] = 0x3fffd000, m->argv[0]=/usr/bin/python3.9
---------------------------------
LOAD: 0x3fff9dd0: /usr/lib/python3.9/lib-dynload/_ctypes.cpython-39-aarch64-linux-gnu.so at 0x3d1c0000
LOAD: 0x3fff9d80: libffi.so.8 at 0x3d240000
LOAD: 0x3fff91d0: /usr/lib/python3.9/lib-dynload/_struct.cpython-39-aarch64-linux-gnu.so at 0x3d2c0000
LOAD: 0x3fffa9d0: /usr/lib/python3.9/lib-dynload/math.cpython-39-aarch64-linux-gnu.so at 0x3d300000
LOAD: 0x3fff91d0: /usr/lib/python3.9/lib-dynload/_bisect.cpython-39-aarch64-linux-gnu.so at 0x3d380000
LOAD: 0x3fff9dd0: /usr/lib/python3.9/lib-dynload/_random.cpython-39-aarch64-linux-gnu.so at 0x3d3c0000
LOAD: 0x3fff9dd0: /usr/lib/python3.9/lib-dynload/_sha512.cpython-39-aarch64-linux-gnu.so at 0x3d400000
LOAD: 0x3fffb3e0: ./libdarknet.so at 0x3d500000
layer     filters    size              input                output
    0 conv     96 11 x11 / 4   227 x 227 x   3   ->    55 x  55 x  96  0.211 BFLOPs
    1 max          3 x 3 / 2    55 x  55 x  96   ->    27 x  27 x  96
    2 conv    256  5 x 5 / 1    27 x  27 x  96   ->    27 x  27 x 256  0.896 BFLOPs
    3 max          3 x 3 / 2    27 x  27 x 256   ->    13 x  13 x 256
    4 conv    384  3 x 3 / 1    13 x  13 x 256   ->    13 x  13 x 384  0.299 BFLOPs
    5 conv    384  3 x 3 / 1    13 x  13 x 384   ->    13 x  13 x 384  0.449 BFLOPs
    6 conv    256  3 x 3 / 1    13 x  13 x 384   ->    13 x  13 x 256  0.299 BFLOPs
    7 max          3 x 3 / 2    13 x  13 x 256   ->     6 x   6 x 256
    8 connected                            9216  ->  4096
    9 dropout       p = 0.50               4096  ->  4096
   10 connected                            4096  ->  4096
   11 dropout       p = 0.50               4096  ->  4096
   12 connected                            4096  ->  1000
   13 softmax                                        1000
Loading weights from alexnet.weights...Done!
[(b'golfcart', 0.19030287861824036), (b'Siberian husky', 0.1809222549200058), (b'malamute', 0.070033960044384), (b'tricycle', 0.06294385343790054), (b'Eskimo dog', 0.04174640774726868)]
Warning: _Exit is replaced by wrap_thread_exit()
```