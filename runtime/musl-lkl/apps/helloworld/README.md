# hello world


A very basic example. Read a file stored on disk.img. 

Expected output: 

```
root@cheribsd-riscv64-hybrid:/intravisor # ls -la 
total 70740
drwxr-xr-x   2 root  wheel       512 Feb  4 23:32 .
drwxr-xr-x  21 root  wheel       512 Feb  4 22:55 ..
-rwxr-xr-x   1 root  wheel    204800 Feb  4 23:31 disk.img
-rwxr-xr-x   1 root  wheel  71222888 Feb  4 23:00 libmusl-lkl.so
-rwxr-xr-x   1 root  wheel    922000 Feb  4 23:07 monitor
-rwxr-xr-x   1 root  wheel       220 Feb  4 23:31 musl-lkl-hello.yaml
root@cheribsd-riscv64-hybrid:/intravisor # ./monitor -y musl-lkl-hello.yaml
Using yaml.cfg = musl-lkl-hello.yaml
MON: sc_cbs[0]: monitor, 0x3fffdff880, 0x3fffdff870, 0x48b86
***************** Deploy 'hello' ***************
BUILDING cvm: name=hello, disk=disk.img, runtime=libmusl-lkl.so, net=(null), args='/ld.so /app/helloworld', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = '(null)', cb_out = 'monitor' wait = 0s
Mapped 0x0, segment = 0x20000000, map_aaadr = 0x20000000, map_len = ce78000
Mapped 0x129284, segment = 0x20129000, map_aaadr = 0x20129000, map_len = 358000
Mapped 0x481a00, segment = 0x20481000, map_aaadr = 0x20481000, map_len = 19000
Mapped 0x49a1e0, segment = 0x2049a000, map_aaadr = 0x2049a000, map_len = c9de000
SHARED MAPPING 0x205d9000--0x2ce78000
ELF BASE = 0x20000000, MAP SIZE = ce77550, ENTRY = 0x201757a4
encl_map.entry = 0x201757a4
encl_map.ret = 0x4680b0
[cVM STACKs] = [0x2e000000 -- 30000000]
MON: probe syscall handler for key monitor
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 2fffc000, sp_read = 0x30000000, me->stacl = 0x2ff80000, getSP()=0x2ffffa00, me->c_tp = 0x2ff81000
[1] '/app/helloworld'
sp[i+1] = '/app/helloworld'
&env0 = 0x2fffc020, &env1=0x2fffc028
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
[    0.000074] lkl: time and timers initialized (irq1)
[    0.000596] pid_max: default: 4096 minimum: 301
[    0.001769] Mount-cache hash table entries: 512 (order: 0, 4096 bytes)
[    0.002108] Mountpoint-cache hash table entries: 512 (order: 0, 4096 bytes)
[    0.045439] devtmpfs: initialized
[    0.242586] console [lkl_console0] enabled
[    0.244182] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.245527] xor: automatically using best checksumming function   8regs     
[    0.249662] random: get_random_u32 called from 0x0000000000302982 with crng_init=0
[    0.252542] NET: Registered protocol family 16
[    0.283264] cryptd: max_cpu_qlen set to 1000
[    0.299627] clocksource: Switched to clocksource lkl
[    0.312747] NET: Registered protocol family 2
[    0.320741] tcp_listen_portaddr_hash hash table entries: 256 (order: 0, 4096 bytes)
[    0.322043] TCP established hash table entries: 2048 (order: 2, 16384 bytes)
[    0.323568] TCP bind hash table entries: 2048 (order: 2, 16384 bytes)
[    0.324946] TCP: Hash tables configured (established 2048 bind 2048)
[    0.329585] UDP hash table entries: 128 (order: 0, 4096 bytes)
[    0.330606] UDP-Lite hash table entries: 128 (order: 0, 4096 bytes)
[    0.332695] NET: Registered protocol family 1
[    0.343540] workingset: timestamp_bits=62 max_order=16 bucket_order=0
[    0.409456] romfs: ROMFS MTD (C) 2007 Red Hat, Inc.
[    0.585687] NET: Registered protocol family 38
[    0.586843] io scheduler noop registered
[    0.587555] io scheduler deadline registered
[    0.590595] io scheduler cfq registered (default)
[    0.591395] io scheduler mq-deadline registered
[    0.592074] io scheduler kyber registered
CAP_FILE INIT 43 4004e201
CAP_STREAM_HOST INIT 45 4004e401
[    1.165765] device-mapper: ioctl: 4.39.0-ioctl (2018-04-03) initialised: dm-devel@redhat.com
[    1.187544] Warning: unable to open an initial console.
[    1.188748] This architecture does not have kernel memory protection.
ignore destructor in tls_alloc
host0 allocated (task=0xcc95500/host0) pid=51
------ LKL INIT DONE, starting mount  ------- 
------ TEST1 ------- 
------ TEST 1 DONE ------- 
ADD disk
[    1.205186] virtio-mmio virtio-mmio.0.auto: Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.
[    1.212357] virtio_blk virtio0: [vda] 400 512-byte logical blocks (205 kB/200 KiB)
disk id = 0
------ ADD disk DONE ------- 
[    1.243561] EXT4-fs (vda): warning: mounting unchecked fs, running e2fsck is recommended
[    1.249045] EXT4-fs (vda): mounted filesystem without journal. Opts: 
loader.c        311
------ CHROOT DONE ------- 
creating /cap/cf1 1
creating /cap/cf2 2
creating /cap/ch1 1
creating /cap/ch2 2
creating /cap/ch3 3
creating /cap/ch4 4
------ MOUNTS DONE ------- 
[proc]
[.]
[lost+found]
[app]
[dev]
[run]
[..]
[sys]
[cap]
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
[    1.294487] host1 (52): drop_caches: 3
MOUNT DONE
td = 0x5dbb10, p = 0x5dbb10, td->robust_list.head = 0x5dbba0 0xfffbcb8 0x5dbba0
PRESTART NETWORK BEFORE LKL 
[    1.592841] virtio-mmio virtio-mmio.1.auto: Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.
------ NETWORK ----- 
setting LO
...done
setting eth0
...done
post start done
LOAD: /app/helloworld
app.base = 0xc908000
ready to start the app: 0xc90979c
envp = 0xfffc020, me->argv[0] = 0xfffd000, m->argv[0]=/app/helloworld
---------------------------------
getSP = 0xc909782
Hello World!
EXIT IS CALLED
```
