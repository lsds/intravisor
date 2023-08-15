



```
root@cheribsd-morello-hybrid:/e # ./intravisor -y musl-lkl-docker-hello.yaml
Using yaml.cfg = musl-lkl-docker-hello.yaml
***************** [16] Deploy 'hello' ***************
BUILDING cvm: name=hello, disk=disk_docker_hello.img, runtime=libmusl-lkl.so, net=(null), args='/ld.so /a.out', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = '(null)' wait = 0s clean_room = 0
[1]: 89dd0000 400000000 fb56c fb56c 89dd0000 fb56c
[2]: 89ecb570 40010b570 4eddb4 4eddb4 89ecb570 4eddb4
end of RO: 400609340
[3]: 8a3b9340 400609340 1fbe0 1fbe0 8a3b9340 1fbe0
[4]: 8a408f20 400638f20 257ca0 3888df78 8a408f20 257ca0
ELF BASE = 0x400000000, MAP SIZE = 38ec6e98, ENTRY = 0x15c0e4
encl_map.entry = 0x15c0e4
encl_map.ret = 0x5f7c74
[cVM STACKs] = [0x43e000000 -- 440000000]
callback_out is empty, use default 'monitor'
SEALED RET FROM MON 0x80eceb30 0x80eceb20
ACHTUNG: 'libmusl-lkl.so' has syscall handler 'syscall_handler' at 0x5f7ca8
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 43fffc000, old TP = 43ffffbe0 sp_read = 0x440000000, me->stacl = 0x43ff80000, getSP()=0x43ffff990, me->c_tp = 0x43ffffbd0 43ffffbc0
[1] '/a.out'
sp[i+1] = '/a.out'
&env0 = 0x43fffc020, &env1=0x43fffc028
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
        base 0000000400000000 length 0000000040000000 ofset 000000000015c0e4
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
        base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
        base 0000000400000000 length 0000000040000000 ofset 0000000000000000
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
        base 0000000400000000 length 0000000040000000 ofset 00000000005f7c74
HW: sp = 0x3fffc000, tp = 0x43ffffa10, &cinv_args = 0x43ffffa90
TP_ARGS: 43e001000, 10, 400000000
-----------------------------------------------
STARTING LKL, lkl_io_in = 0x38ec6d40, disk_io = 0x38ec6e80
TIMER[0]: 0x185008 0
TODO: CREATE_CARRIE_TIMER
[    0.000000] Linux version 6.1.0 (capvm@capvm) (clang version 13.0.0 (https://git.morello-project.org/morello/llvm-project.git b6885c2a94bfca0eabb7eea8ae1788bdea4430e0), GNU ld (GNU Binutils for Ubuntu) 2.34) #15 Fri Aug 11 23:18:35 UTC 2023
[    0.000000] memblock address range: 0xa80000 - 0x38e80000
[    0.000000] Zone ranges:
[    0.000000]   Normal   [mem 0x0000000000a80000-0x0000000038e7ffff]
[    0.000000] Movable zone start for each node
[    0.000000] Early memory node ranges
[    0.000000]   node   0: [mem 0x0000000000a80000-0x0000000038e7ffff]
[    0.000000] Initmem setup node 0 [mem 0x0000000000a80000-0x0000000038e7ffff]
[    0.000000] Built 1 zonelists, mobility grouping off.  Total pages: 227250
[    0.000000] Kernel command line:  mem=30M
[    0.000000] Dentry cache hash table entries: 131072 (order: 8, 1048576 bytes, linear)
[    0.000000] Inode-cache hash table entries: 65536 (order: 7, 524288 bytes, linear)
[    0.000000] mem auto-init: stack:off, heap alloc:off, heap free:off
[    0.000000] Memory: 862680K/921600K available (4556K kernel code, 1608K rwdata, 396K rodata, 593K init, 922530K bss, 58920K reserved, 0K cma-reserved)
[    0.000000] SLUB: HWalign=32, Order=0-3, MinObjects=0, CPUs=1, Nodes=1
[    0.000000] NR_IRQS: 4096
[    0.000000] lkl: irqs initialized
[    0.000000] clocksource: lkl: mask: 0xffffffffffffffff max_cycles: 0x1cd42e4dffb, max_idle_ns: 881590591483 ns
[    0.000066] lkl: time and timers initialized (irq1)
[    0.001314] pid_max: default: 4096 minimum: 301
[    0.009907] Mount-cache hash table entries: 2048 (order: 2, 16384 bytes, linear)
[    0.010083] Mountpoint-cache hash table entries: 2048 (order: 2, 16384 bytes, linear)
[    0.149635] devtmpfs: initialized
[    0.348269] printk: console [lkl_console0] enabled
[    0.352286] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.366654] NET: Registered PF_NETLINK/PF_ROUTE protocol family
[    0.381555] lkl_pci: probe of lkl_pci failed with error -1
[    0.441288] cryptd: max_cpu_qlen set to 1000
[    0.492293] vgaarb: loaded
[    0.496775] clocksource: Switched to clocksource lkl
[    0.549697] NET: Registered PF_INET protocol family
[    0.556151] IP idents hash table entries: 16384 (order: 5, 131072 bytes, linear)
[    0.569912] tcp_listen_portaddr_hash hash table entries: 512 (order: 0, 4096 bytes, linear)
[    0.573545] Table-perturb hash table entries: 65536 (order: 6, 262144 bytes, linear)
[    0.577071] TCP established hash table entries: 8192 (order: 4, 65536 bytes, linear)
[    0.580326] TCP bind hash table entries: 8192 (order: 5, 131072 bytes, linear)
[    0.583096] TCP: Hash tables configured (established 8192 bind 8192)
[    0.591988] UDP hash table entries: 512 (order: 2, 16384 bytes, linear)
[    0.594215] UDP-Lite hash table entries: 512 (order: 2, 16384 bytes, linear)
[    0.602801] NET: Registered PF_UNIX/PF_LOCAL protocol family
[    0.605885] PCI: CLS 0 bytes, default 32
[    0.624276] workingset: timestamp_bits=62 max_order=18 bucket_order=0
[    0.707061] romfs: ROMFS MTD (C) 2007 Red Hat, Inc.
[    0.710543] NET: Registered PF_ALG protocol family
[    0.712974] xor: automatically using best checksumming function   8regs     
[    0.717223] io scheduler mq-deadline registered
[    0.722915] io scheduler kyber registered
[    2.116924] wireguard: WireGuard 1.0.0 loaded. See www.wireguard.com for information.
[    2.120335] wireguard: Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
[    2.163616] device-mapper: ioctl: 4.47.0-ioctl (2022-07-28) initialised: dm-devel@redhat.com
[    2.196431] NET: Registered PF_INET6 protocol family
[    2.231126] Segment Routing with IPv6
[    2.237763] In-situ OAM (IOAM) with IPv6
[    2.242257] sit: IPv6, IPv4 and MPLS over IPv4 tunneling driver
[    2.466110] Warning: unable to open an initial console.
[    2.471051] This architecture does not have kernel memory protection.
[    2.476770] Run /init as init process
ignore destructor in tls_alloc
------ LKL INIT DONE, starting mount  ------- 
179
181
ADD disk
[    2.548313] virtio_blk virtio0: 1/0/0 default/read/poll queues
[    2.577464] virtio_blk virtio0: [vda] 61440 512-byte logical blocks (31.5 MB/30.0 MiB)
disk id = 0
------ ADD disk DONE ------- 
[    2.802994] EXT4-fs (vda): mounted filesystem with ordered data mode. Quota mode: disabled.
[    2.811628] ext4 filesystem being mounted at /mnt/123 supports timestamps until 2038 (0x7fffffff)
179
181
loader.c        295
------ CHROOT DONE ------- 
179
181
179
181
179
181
------ MOUNTS DONE ------- 
pad Descriptor Table: 0 ((null))
null: No error information
pad Descriptor Table: 1 ((null))
null: No error information
pad Descriptor Table: 2 ((null))
null: No error information
[a.out]
[media]
[dev]
[lib]
[root]
[usr]
[etc]
[tmp]
[sys]
[opt]
[bin]
[srv]
[.]
[proc]
[hello_world.c]
[..]
[.dockerenv]
[home]
[sbin]
[var]
[mnt]
[lost+found]
[run]
------
st_lkl.st_mode = 21a4
st_lkl.st_nlink = 1
st_musl.st_mode = 21a4
st_musl.st_nlink = 1
st_musl.st_uid = 0
st_musl.st_gid = 0
Size of musl stat: 128
Offset of st_mode:      16, Size: 4
Offset of st_nlink:     20, Size: 4
Offset of st_uid:       24, Size: 4
Offset of st_gid:       28, Size: 4
Size of lkl stat: 128
Offset of st_mode:      16, Size: 4
Offset of st_nlink:     20, Size: 4
Offset of st_uid:       24, Size: 4
Offset of st_gid:       28, Size: 4
S_IFMT = f000, S_IFDIR = 4000
O_DIRECTORY = 0x4000
is_dir(/dev/stdin): 0 (LKL) 0 (musl)
wrote 512 to urandom
urandom_read_iter 1353
urandom_read_iter 1363
[    2.962674] random: host1: uninitialized urandom read (8 bytes read)
urandom_read_iter 1373
get_random_bytes_user 404
get_random_bytes_user 408
get_random_bytes_user 417
get_random_bytes_user 419
get_random_bytes_user 425
get_random_bytes_user 427
 rret = 8 rnd_val = 505313378
MOUNT DONE
td = 0x9c37c0, p = 0x9c37c0, td->robust_list.head = 0x9c3850 0x3fffbce0 0x9c3850
NO NETWORK 
LOAD: /a.out
app.base = 0xf40000
ready to start the app: 0xf40800
envp = 0x3fffc020, me->argv[0] = 0x3fffd000, m->argv[0]=/a.out
---------------------------------
hello world
stat2.st_mode = 21a4
stat2.st_nlink = 1
stat2.st_uid = 0
stat2.st_gid = 0
Size of stat: 128
Offset of st_mode:      16, Size: 4
Offset of st_nlink:     20, Size: 4
Offset of st_uid:       24, Size: 4
Offset of st_gid:       28, Size: 4
EXIT IS CALLED
```