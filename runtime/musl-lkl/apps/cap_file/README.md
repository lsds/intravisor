# HelloWorld with CAP_File

Similarly to the baremetal example, we access shared data via capabilitites.
However, this time, the interaction with capabilitites are hiden by a CAP_File. 
It provides POSIX read/write/llseek API and internally uses cap-aware instructions. 

In the example, we read and write data allocated by Intravisor (following the deployment scenario) via CAP_File.


## Expected output

```
Using yaml.cfg = /intravisor/cvm.yaml
CF_ADV: 0x85b6d000, 32, test1
MON: CF[0] 0x85b6d000 test1 32
***************** [16] Deploy 'cap_file_test' ***************
BUILDING cvm: name=cap_file_test, disk=disk_cap_file.img, runtime=libmusl-lkl.so, net=(null), args='/ld.so /app/cap_file', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = 'monitor' wait = 0s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
[1]: 87e2c000 400000000 f29d4 f29d4 87e2c000 f29d4
[2]: 87f1e9d4 4000f39d4 2413c6 2413c6 87f1e9d4 2413c6
end of RO: 400335da0
[3]: 8815fda0 400335da0 fe80 fe80 8815fda0 fe80
[4]: 8816fc20 400346c20 12c2a8 1c3b40 8816fc20 12c2a8
ELF BASE = 0x400000000, MAP SIZE = 50a760, ENTRY = 0x13a050
encl_map.entry = 0x13a050
encl_map.ret = 0x326a5a
[cVM STACKs] = [0x43e000000 -- 440000000]
Convrting free memory into cVM Heap: 40050b000 -- 43e000000 +3daf5000 ( 986.957031 MB)
cVM has cvm_heap_begin (4630d0) and cvm_heap_size (4630d8)
SEALED RET FROM MON 0x80d72210 0x80d72200
Deploy 16 in 16.134000, SHA-256 Hash: fb3433f10e74a7662300dc3551bb25ed04d7674ad207695523d2f47b04711501
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 43fffc000, old TP = 43ffffc00 sp_read = 0x440000000, me->stacl = 0x43ff80000, getSP()=0x43ffff990, me->c_tp = 0x43ffffbf0 43ffffbe0
[1] '/app/cap_file'
sp[i+1] = '/app/cap_file'
&env0 = 0x43fffc020, &env1=0x43fffc028
ca0: sealed COMP PCC
tag 1 s 1 perms 00008117 type 0000000000000000
    base 0000000400000000 length 0000000040000000 ofset 000000000013a050
ca1: sealed COMP DDC
tag 1 s 1 perms 0000817d type 0000000000000000
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 0000817d type ffffffffffffffff
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 00068117 type 0000000000000000
    base 0000000000000000 length 0000800000000000 ofset 000000000004acb4
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0007817d type 0000000000000000
    base 0000000000000000 length 0000800000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 00068117 type 0000000000000000
    base 0000000000000000 length 0000800000000000 ofset 000000000004ac8c
ca6: sealed ret from mon
tag 1 s 1 perms 00008117 type 0000000000000000
    base 0000000400000000 length 0000000040000000 ofset 0000000000326a5a
HW: sp = 0x3fffc000, tp = 0x43ffffa30, &cinv_args = 0x43ffffab0
TP_ARGS: 43e001000, 10, 43ff81000
-----------------------------------------------
STARTING LKL, lkl_io_in = 0x5098f0, disk_io = 0x509a10, heap (50b000, +3daf5000)
TIMER[0]: 0x144156 0
TODO: CREATE_CARRIE_TIMER
[    0.000000] Linux version 4.17.0 (cheri@runner-_aJ2xR8B-project-191-concurrent-2) (clang version 14.0.0 (https://github.com/CTSRD-CHERI/llvm-project.git ed9d9964fb200af225739a89bfb988cbe8d8f69e)) #1 Sun Feb 11 01:16:00 UTC 2024
[    0.000000] bootmem address range: 0x50b000 - 0x3e000000
[    0.000000] Built 1 zonelists, mobility grouping off.  Total pages: 249206
[    0.000000] Kernel command line: 
[    0.000000] Dentry cache hash table entries: 131072 (order: 8, 1048576 bytes)
[    0.000000] Inode-cache hash table entries: 65536 (order: 7, 524288 bytes)
[    0.000000] Memory available: 951720k/1010644k RAM
[    0.000000] SLUB: HWalign=32, Order=0-3, MinObjects=0, CPUs=1, Nodes=1
[    0.000000] NR_IRQS: 4096
[    0.000000] lkl: irqs initialized
[    0.000000] clocksource: lkl: mask: 0xffffffffffffffff max_cycles: 0x1cd42e4dffb, max_idle_ns: 881590591483 ns
[    0.000169] lkl: time and timers initialized (irq1)
[    0.003221] pid_max: default: 4096 minimum: 301
[    0.008505] Mount-cache hash table entries: 2048 (order: 2, 16384 bytes)
[    0.011539] Mountpoint-cache hash table entries: 2048 (order: 2, 16384 bytes)
[    0.138862] devtmpfs: initialized
[    0.450324] console [lkl_console0] enabled
[    0.454153] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.457640] xor: automatically using best checksumming function   8regs     
[    0.501346] cryptd: max_cpu_qlen set to 1000
[    0.526216] clocksource: Switched to clocksource lkl
[    0.567530] workingset: timestamp_bits=62 max_order=18 bucket_order=0
[    0.653527] romfs: ROMFS MTD (C) 2007 Red Hat, Inc.
[    0.939798] io scheduler noop registered
[    0.941044] io scheduler deadline registered
[    0.945820] io scheduler cfq registered (default)
[    0.947382] io scheduler mq-deadline registered
[    0.948681] io scheduler kyber registered
CAP_FILE INIT 43 4004e201
CAP_STREAM_HOST INIT 45 4004e401
[    1.861995] device-mapper: ioctl: 4.39.0-ioctl (2018-04-03) initialised: dm-devel@redhat.com
[    1.875398] random: get_random_bytes called from 0x0000000000147d84 with crng_init=0
[    1.891091] Warning: unable to open an initial console.
[    1.893745] This architecture does not have kernel memory protection.
INT: ignore destructor 144622 in tls_alloc
------ LKL INIT DONE, starting mount  ------- 
ADD disk
[    1.947532] virtio_blk virtio0: [vda] 1000 512-byte logical blocks (512 kB/500 KiB)
disk id = 0
------ ADD disk DONE ------- 
[    2.070288] EXT4-fs (vda): mounted filesystem without journal. Opts: 
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
[cap]
[run]
[sys]
[dev]
[.]
[lost+found]
[..]
[proc]
[app]
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
O_DIRECTORY = 0x10000
is_dir(/dev/stdin): 0 (LKL) 0 (musl)
Adding entropy to entropy pool
[    2.211554] random: crng init done
MOUNT DONE
td = 0x475a20, p = 0x475a20, td->robust_list.head = 0x475ab0 0x3fffbcb8 0x475ab0
NO NETWORK 
LOAD: /app/cap_file
app.base = 0x3c27c000
ready to start the app: 0x3c27d820
envp = 0x3fffc020, me->argv[0] = 0x3fffd000, m->argv[0]=/app/cap_file
---------------------------------
device is open: CAPFILE
fd = 4
MON: CF: probe for key test1, store at 0x4004b0a30
read 0 bytes ('@WG') from cap_file with key 'test1'
let's write 'cap filler
' into cap_file and read result back
wrote 12 bytes
read 12 bytes ('cap filler
') from cap_file with key 'test1'
Warning: _Exit is replaced by wrap_thread_exit()
```