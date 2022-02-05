# Python

Python compiled from sources. Just a simple 'hello world' written in Python. Requires python3.9 for build.

# Expected output: 

```
root@cheribsd-riscv64-hybrid:/e # ls -la 
total 148076
drwxr-xr-x   2 root  wheel        512 Feb  4 23:24 .
drwxr-xr-x  21 root  wheel        512 Feb  4 23:18 ..
-rwxr-xr-x   1 root  wheel  104857600 Feb  4 23:24 disk_python.img
-rwxr-xr-x   1 root  wheel   71197448 Feb  4 23:21 libmusl-lkl.so
-rwxr-xr-x   1 root  wheel     484376 Feb  4 23:27 monitor
-rwxr-xr-x   1 root  wheel        224 Feb  4 23:18 musl-lkl-python.yaml
root@cheribsd-riscv64-hybrid:/e # ./monitor -y musl-lkl-python.yaml
Using yaml.cfg = musl-lkl-python.yaml
MON: sc_cbs[0]: monitor, 0x3fffdff7e0, 0x3fffdff7d0, 0x49f5a
***************** Deploy 'python' ***************
BUILDING cvm: name=python, disk=disk_python.img, runtime=libmusl-lkl.so, net=(null), args='/ld.so /usr/bin/python3 /app/helloworld.py', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = '(null)', cb_out = '(null)' wait = 0s
Mapped 0x0, segment = 0x20000000, map_aaadr = 0x20000000, map_len = ce7b000
Mapped 0x129804, segment = 0x20129000, map_aaadr = 0x20129000, map_len = 35b000
Mapped 0x484b80, segment = 0x20484000, map_aaadr = 0x20484000, map_len = 19000
Mapped 0x49d360, segment = 0x2049d000, map_aaadr = 0x2049d000, map_len = c9de000
SHARED MAPPING 0x205dc000--0x2ce7b000
ELF BASE = 0x20000000, MAP SIZE = ce7a550, ENTRY = 0x20178768
encl_map.entry = 0x20178768
encl_map.ret = 0x46b240
[cVM STACKs] = [0x2e000000 -- 30000000]
callback_out is empty, use default 'monitor'
MON: probe syscall handler for key monitor
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 2fffc000, sp_read = 0x30000000, me->stacl = 0x2ff80000, getSP()=0x2ffffa00, me->c_tp = 0x2ff81000
[1] '/usr/bin/python3'
sp[i+1] = '/usr/bin/python3'
[2] '/app/helloworld.py'
sp[i+1] = '/app/helloworld.py'
&env0 = 0x2fffc028, &env1=0x2fffc030
72 sp = 0x2fffc000
ca0: sealed COMP PPC
tag 1 s 1 perms 00000107 type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 0000000000178768
ca1: sealed COMP DDC
tag 1 s 1 perms 0000011d type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 0000011d type ffffffffffffffff
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 00068117 type 0000000000000000
        base 0000000000000000 length 0000004000000000 ofset 0000000000049f5a
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0007817d type 0000000000000000
        base 0000000000000000 length 0000004000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 00068117 type 0000000000000000
        base 0000000000000000 length 0000004000000000 ofset 0000000000049f32
ca6: sealed ret from mon
tag 1 s 1 perms 00000107 type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 000000000046b240
HW: sp = 0xfffc000, tp = 0xff81000
-----------------------------------------------
STARTING LKL, lkl_io_in = 0xce7a428, disk_io = 0xce7a538
TIMER[0]: 0x185dc0 0
TODO: CREATE_CARRIE_TIMER
[    0.000000] Linux version 4.17.0 (vsartako@maru25) (clang version 11.0.0 (https://github.com/CTSRD-CHERI/llvm-project.git 9c51217b7d41f3124b84b190b6631b90db6d1bf4)) #62 Fri Feb 4 23:17:39 UTC 2022
[    0.000000] bootmem address range: 0x5ed000 - 0xcded000
[    0.000000] Built 1 zonelists, mobility grouping off.  Total pages: 50500
[    0.000000] Kernel command line: mem=30M
[    0.000000] Dentry cache hash table entries: 32768 (order: 6, 262144 bytes)
[    0.000000] Inode-cache hash table entries: 16384 (order: 5, 131072 bytes)
[    0.000000] Memory available: 147028k/204800k RAM
[    0.000000] SLUB: HWalign=32, Order=0-3, MinObjects=0, CPUs=1, Nodes=1
[    0.000000] NR_IRQS: 4096
[    0.000000] lkl: irqs initialized
[    0.000000] clocksource: lkl: mask: 0xffffffffffffffff max_cycles: 0x1cd42e4dffb, max_idle_ns: 881590591483 ns
[    0.000098] lkl: time and timers initialized (irq1)
[    0.002312] pid_max: default: 4096 minimum: 301
[    0.006923] Mount-cache hash table entries: 512 (order: 0, 4096 bytes)
[    0.007351] Mountpoint-cache hash table entries: 512 (order: 0, 4096 bytes)
[    0.085735] devtmpfs: initialized
[    0.312733] console [lkl_console0] enabled
[    0.317982] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.320127] xor: automatically using best checksumming function   8regs     
[    0.328209] random: get_random_u32 called from 0x0000000000305b12 with crng_init=0
[    0.332048] NET: Registered protocol family 16
[    0.372329] cryptd: max_cpu_qlen set to 1000
[    0.404935] clocksource: Switched to clocksource lkl
[    0.424916] NET: Registered protocol family 2
[    0.440263] tcp_listen_portaddr_hash hash table entries: 256 (order: 0, 4096 bytes)
[    0.441798] TCP established hash table entries: 2048 (order: 2, 16384 bytes)
[    0.443349] TCP bind hash table entries: 2048 (order: 2, 16384 bytes)
[    0.444893] TCP: Hash tables configured (established 2048 bind 2048)
[    0.452041] UDP hash table entries: 128 (order: 0, 4096 bytes)
[    0.453280] UDP-Lite hash table entries: 128 (order: 0, 4096 bytes)
[    0.456575] NET: Registered protocol family 1
[    0.476851] workingset: timestamp_bits=62 max_order=16 bucket_order=0
[    0.552887] romfs: ROMFS MTD (C) 2007 Red Hat, Inc.
[    0.745915] NET: Registered protocol family 38
[    0.747307] io scheduler noop registered
[    0.748033] io scheduler deadline registered
[    0.751534] io scheduler cfq registered (default)
[    0.752289] io scheduler mq-deadline registered
[    0.752981] io scheduler kyber registered
CAP_FILE INIT 43 4004e201
CAP_STREAM_HOST INIT 45 4004e401
[    1.399433] device-mapper: ioctl: 4.39.0-ioctl (2018-04-03) initialised: dm-devel@redhat.com
[    1.438105] Warning: unable to open an initial console.
[    1.439667] This architecture does not have kernel memory protection.
ignore destructor in tls_alloc
host0 allocated (task=0xcc95500/host0) pid=51
------ LKL INIT DONE, starting mount  ------- 
------ TEST1 ------- 
------ TEST 1 DONE ------- 
ADD disk
[    1.466427] virtio-mmio virtio-mmio.0.auto: Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.
[    1.484559] virtio_blk virtio0: [vda] 204800 512-byte logical blocks (105 MB/100 MiB)
disk id = 0
------ ADD disk DONE ------- 
[    1.598155] EXT4-fs (vda): mounted filesystem with ordered data mode. Opts: 
loader.c        311
------ CHROOT DONE ------- 
creating /cap/cf1 1
creating /cap/cf2 2
creating /cap/ch1 1
creating /cap/ch2 2
creating /cap/ch3 3
creating /cap/ch4 4
------ MOUNTS DONE ------- 
[sys]
[cap]
[lost+found]
[dev]
[app]
[run]
[..]
[usr]
[.]
[proc]
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
[    1.694270] host1 (52): drop_caches: 3
MOUNT DONE
td = 0x5deef0, p = 0x5deef0, td->robust_list.head = 0x5def80 0xfffbcb8 0x5def80
PRESTART NETWORK BEFORE LKL 
[    1.952313] virtio-mmio virtio-mmio.1.auto: Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.
------ NETWORK ----- 
setting LO
...done
setting eth0
...done
post start done
LOAD: /usr/bin/python3
app.base = 0xc000000
ready to start the app: 0xc259870
envp = 0xfffc028, me->argv[0] = 0xfffd000, m->argv[0]=/usr/bin/python3
---------------------------------
[    4.731058] random: host1: uninitialized urandom read (24 bytes read)
[    6.294108] random: fast init done
Hello world from CHERI python

EXIT IS CALLED

```


# problems 

Be careful with stat.h. stat in LKL, in old headers, and in musl should be the same

Makefile may require additional improvements