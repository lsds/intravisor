# CAP_Stream 

This example demonstrates a new capability-based interface for communication between cVMs. 
The interface is stream: one side pre-registers incomming buffer(s), the other side will select the buffer on delivery.
The interface itself is based on two mechanisms: CAP_Files -- asyncronous data access at byte granularity, and CAP_Calls -- invocation of functions in different cVMs. 

## One thread, one cVM. (musl-lkl-cap_stream-single.yaml)

We deploy a cVM and it uses cap devices for communication. 

Expected output

```
<...>
---------------------------------
Testing CF_STREAMs, single thread
MON: STREAM_CAP[0] 0x2031ecbe key1 0xce3cdd8
RECV:   clear ('') and publish ptr(0x8005000) with key 'key1' via /cap/ch1 
SEND:   sending ptr (0x8405000) with 'text for ptr' via /cap/ch2 (3)
me->func = 0x2031ecbe, addr=0x0, sp = 0x2f5ffeb0
RECV:   Check ptr (0x8005000) after wait: 'text for ptr'
```


## Two cVMs (musl-lkl-cap_stream-dual.yaml)

Now we spawn two cVMs, one with sender and one with receiver. In a loop, receiver registers an input buffer and waits for incomming message while the sender
infinitely sends incremental messages. 

Expected output: 

```
root@cheribsd-riscv64-hybrid:/intravisor # ./monitor -y musl-lkl-cap_stream-single.yaml
Using yaml.cfg = musl-lkl-cap_stream-single.yaml
MON: sc_cbs[0]: monitor, 0x3fffdff870, 0x3fffdff860, 0x48b86
***************** Deploy 'cap_stream_test' ***************
BUILDING cvm: name=cap_stream_test, disk=disk.img, runtime=libmusl-lkl.so, net=(null), args='/ld.so /app/cap_stream 1', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = '(null)', cb_out = 'monitor' wait = 0s
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
[1] '/app/cap_stream'
sp[i+1] = '/app/cap_stream'
[2] '1'
sp[i+1] = '1'
&env0 = 0x2fffc028, &env1=0x2fffc030
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
[    0.000072] lkl: time and timers initialized (irq1)
[    0.000515] pid_max: default: 4096 minimum: 301
[    0.001677] Mount-cache hash table entries: 512 (order: 0, 4096 bytes)
[    0.002015] Mountpoint-cache hash table entries: 512 (order: 0, 4096 bytes)
[    0.044628] devtmpfs: initialized
[    0.242614] console [lkl_console0] enabled
[    0.244297] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.245755] xor: automatically using best checksumming function   8regs     
[    0.249735] random: get_random_u32 called from 0x0000000000302982 with crng_init=0
[    0.252960] NET: Registered protocol family 16
[    0.283772] cryptd: max_cpu_qlen set to 1000
[    0.299845] clocksource: Switched to clocksource lkl
[    0.313334] NET: Registered protocol family 2
[    0.321185] tcp_listen_portaddr_hash hash table entries: 256 (order: 0, 4096 bytes)
[    0.322461] TCP established hash table entries: 2048 (order: 2, 16384 bytes)
[    0.324095] TCP bind hash table entries: 2048 (order: 2, 16384 bytes)
[    0.325597] TCP: Hash tables configured (established 2048 bind 2048)
[    0.329720] UDP hash table entries: 128 (order: 0, 4096 bytes)
[    0.330757] UDP-Lite hash table entries: 128 (order: 0, 4096 bytes)
[    0.332945] NET: Registered protocol family 1
[    0.343514] workingset: timestamp_bits=62 max_order=16 bucket_order=0
[    0.409039] romfs: ROMFS MTD (C) 2007 Red Hat, Inc.
[    0.581341] NET: Registered protocol family 38
[    0.582371] io scheduler noop registered
[    0.583145] io scheduler deadline registered
[    0.586174] io scheduler cfq registered (default)
[    0.586973] io scheduler mq-deadline registered
[    0.587767] io scheduler kyber registered
CAP_FILE INIT 43 4004e201
CAP_STREAM_HOST INIT 45 4004e401
[    1.162717] device-mapper: ioctl: 4.39.0-ioctl (2018-04-03) initialised: dm-devel@redhat.com
[    1.189757] Warning: unable to open an initial console.
[    1.190868] This architecture does not have kernel memory protection.
ignore destructor in tls_alloc
host0 allocated (task=0xcc95500/host0) pid=51
------ LKL INIT DONE, starting mount  ------- 
------ TEST1 ------- 
------ TEST 1 DONE ------- 
ADD disk
[    1.211252] virtio-mmio virtio-mmio.0.auto: Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.
[    1.219086] virtio_blk virtio0: [vda] 400 512-byte logical blocks (205 kB/200 KiB)
disk id = 0
------ ADD disk DONE ------- 
[    1.255397] EXT4-fs (vda): mounted filesystem without journal. Opts: 
loader.c        311
------ CHROOT DONE ------- 
creating /cap/cf1 1
creating /cap/cf2 2
creating /cap/ch1 1
creating /cap/ch2 2
creating /cap/ch3 3
creating /cap/ch4 4
------ MOUNTS DONE ------- 
[.]
[sys]
[app]
[cap]
[run]
[proc]
[..]
[lost+found]
[dev]
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
[    1.303639] host1 (52): drop_caches: 3
MOUNT DONE
td = 0x5dbb10, p = 0x5dbb10, td->robust_list.head = 0x5dbba0 0xfffbcb8 0x5dbba0
PRESTART NETWORK BEFORE LKL 
[    1.602440] virtio-mmio virtio-mmio.1.auto: Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.
------ NETWORK ----- 
setting LO
...done
setting eth0
...done
post start done
LOAD: /app/cap_stream
app.base = 0x8000000
ready to start the app: 0x800248c
envp = 0xfffc028, me->argv[0] = 0xfffd000, m->argv[0]=/app/cap_stream
---------------------------------
Testing CF_STREAMs, single thread
MON: STREAM_CAP[0] 0x2031ecbe key1 0xce3cdd8
RECV:   clear ('') and publish ptr(0x8005000) with key 'key1' via /cap/ch1 
SEND:   sending ptr (0x8405000) with 'text for ptr' via /cap/ch2 (3)
me->func = 0x2031ecbe, addr=0x0, sp = 0x2f5ffeb0
RECV:   Check ptr (0x8005000) after wait: 'text for ptr'
EXIT IS CALLED
^CFeb  4 23:43:39 cheribsd-riscv64-hybrid dhclient[1011]: Interface tap0 is down, dhclient exiting
Feb  4 23:43:40 cheribsd-riscv64-hybrid dhclient[1011]: connection closed
Feb  4 23:43:40 cheribsd-riscv64-hybrid dhclient[1011]: exiting.

root@cheribsd-riscv64-hybrid:/intravisor # ./monitor -y musl-lkl-cap_stream-dual.yaml 
Using yaml.cfg = musl-lkl-cap_stream-dual.yaml
MON: sc_cbs[0]: monitor, 0x3fffdff870, 0x3fffdff860, 0x48b86
***************** Deploy 'recv' ***************
BUILDING cvm: name=recv, disk=disk.img, runtime=libmusl-lkl.so, net=(null), args='/ld.so /app/cap_stream 3', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = '(null)', cb_out = 'monitor' wait = 10s
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
***************** Deploy 'send' ***************
BUILDING cvm: name=send, disk=disk.img, runtime=libmusl-lkl.so, net=(null), args='/ld.so /app/cap_stream 4', base=0x10000000, size=0x10000000, begin=0x10000000, end=0x20000000, cb_in = '(null)', cb_out = 'monitor' wait = 0s
Mapped 0x0, segment = 0x10000000, map_aaadr = 0x10000000, map_len = ce78000
Mapped 0x129284, segment = 0x10129000, map_aaadr = 0x10129000, map_len = 358000
Mapped 0x481a00, segment = 0x10481000, map_aaadr = 0x10481000, map_len = 19000
Mapped 0x49a1e0, segment = 0x1049a000, map_aaadr = 0x1049a000, map_len = c9de000
SHARED MAPPING 0x105d9000--0x1ce78000
ELF BASE = 0x10000000, MAP SIZE = ce77550, ENTRY = 0x101757a4
encl_map.entry = 0x101757a4
encl_map.ret = 0x4680b0
[cVM STACKs] = [0x1e000000 -- 20000000]
MON: probe syscall handler for key monitor
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 2fffc000, sp_read = 0x30000000, me->stacl = 0x2ff80000, getSP()=0x2ffffa00, me->c_tp = 0x2ff81000
[1] '/app/cap_stream'
sp[i+1] = '/app/cap_stream'
[2] '3'
sp[i+1] = '3'
&env0 = 0x2fffc028, &env1=0x2fffc030
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
[    0.000138] lkl: time and timers initialized (irq1)
[    0.002359] pid_max: default: 4096 minimum: 301
[    0.006800] Mount-cache hash table entries: 512 (order: 0, 4096 bytes)
[    0.007180] Mountpoint-cache hash table entries: 512 (order: 0, 4096 bytes)
[    0.077369] devtmpfs: initialized
[    0.281014] console [lkl_console0] enabled
[    0.283248] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.285344] xor: automatically using best checksumming function   8regs     
[    0.291494] random: get_random_u32 called from 0x0000000000302982 with crng_init=0
[    0.294966] NET: Registered protocol family 16
[    0.332338] cryptd: max_cpu_qlen set to 1000
[    0.356664] clocksource: Switched to clocksource lkl
[    0.373684] NET: Registered protocol family 2
[    0.388856] tcp_listen_portaddr_hash hash table entries: 256 (order: 0, 4096 bytes)
[    0.390522] TCP established hash table entries: 2048 (order: 2, 16384 bytes)
[    0.392122] TCP bind hash table entries: 2048 (order: 2, 16384 bytes)
[    0.393676] TCP: Hash tables configured (established 2048 bind 2048)
[    0.399497] UDP hash table entries: 128 (order: 0, 4096 bytes)
[    0.400659] UDP-Lite hash table entries: 128 (order: 0, 4096 bytes)
[    0.403766] NET: Registered protocol family 1
[    0.418576] workingset: timestamp_bits=62 max_order=16 bucket_order=0
[    0.488853] romfs: ROMFS MTD (C) 2007 Red Hat, Inc.
[    0.674803] NET: Registered protocol family 38
[    0.676209] io scheduler noop registered
[    0.676994] io scheduler deadline registered
[    0.680378] io scheduler cfq registered (default)
[    0.681299] io scheduler mq-deadline registered
[    0.682082] io scheduler kyber registered
CAP_FILE INIT 43 4004e201
CAP_STREAM_HOST INIT 45 4004e401
[    1.263020] device-mapper: ioctl: 4.39.0-ioctl (2018-04-03) initialised: dm-devel@redhat.com
[    1.295025] Warning: unable to open an initial console.
[    1.296610] This architecture does not have kernel memory protection.
ignore destructor in tls_alloc
host0 allocated (task=0xcc94fc0/host0) pid=51
------ LKL INIT DONE, starting mount  ------- 
------ TEST1 ------- 
------ TEST 1 DONE ------- 
ADD disk
[    1.325321] virtio-mmio virtio-mmio.0.auto: Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.
[    1.340545] virtio_blk virtio0: [vda] 400 512-byte logical blocks (205 kB/200 KiB)
disk id = 0
------ ADD disk DONE ------- 
[    1.395014] EXT4-fs (vda): warning: mounting unchecked fs, running e2fsck is recommended
[    1.402827] EXT4-fs (vda): mounted filesystem without journal. Opts: 
loader.c        311
------ CHROOT DONE ------- 
creating /cap/cf1 1
creating /cap/cf2 2
creating /cap/ch1 1
creating /cap/ch2 2
creating /cap/ch3 3
creating /cap/ch4 4
------ MOUNTS DONE ------- 
[.]
[sys]
[app]
[cap]
[run]
[proc]
[..]
[lost+found]
[dev]
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
[    1.473558] host1 (52): drop_caches: 3
MOUNT DONE
td = 0x5dbb10, p = 0x5dbb10, td->robust_list.head = 0x5dbba0 0xfffbcb8 0x5dbba0
PRESTART NETWORK BEFORE LKL 
[    1.817132] virtio-mmio virtio-mmio.1.auto: Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.
------ NETWORK ----- 
setting LO
...done
setting eth0
...done
post start done
LOAD: /app/cap_stream
app.base = 0x8000000
ready to start the app: 0x800248c
envp = 0xfffc028, me->argv[0] = 0xfffd000, m->argv[0]=/app/cap_stream
---------------------------------
tsd = 0x8862c00, libc.tls_size = f8, stack = 0x8862b08
new = 0x8862b08
start = 0x16e94e, args = 0x8862ae8, ts = 0x8862ad0
new thread = 55
EXIT IS CALLED
Testing CF_STREAMs RECV thread, ptr = 0x8005000, dnull = 0x8405000
fd_in = 3
MON: STREAM_CAP[0] 0x2031ecbe key1 0xce3cdd8
target SP = 1fffc000, sp_read = 0x20000000, me->stacl = 0x1ff80000, getSP()=0x1ffffa00, me->c_tp = 0x1ff81000
[1] '/app/cap_stream'
sp[i+1] = '/app/cap_stream'
[2] '4'
sp[i+1] = '4'
&env0 = 0x1fffc028, &env1=0x1fffc030
72 sp = 0x1fffc000
ca0: sealed COMP PPC
tag 1 s 1 perms 00000107 type 0000000000000000
        base 0000000010000000 length 0000000010000000 ofset 00000000001757a4
ca1: sealed COMP DDC
tag 1 s 1 perms 0000011d type 0000000000000000
        base 0000000010000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 0000011d type ffffffffffffffff
        base 0000000010000000 length 0000000010000000 ofset 0000000000000000
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
        base 0000000010000000 length 0000000010000000 ofset 00000000004680b0
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
[    0.000166] lkl: time and timers initialized (irq1)
[    0.002403] pid_max: default: 4096 minimum: 301
[    0.006835] Mount-cache hash table entries: 512 (order: 0, 4096 bytes)
[    0.007218] Mountpoint-cache hash table entries: 512 (order: 0, 4096 bytes)
[    0.093516] devtmpfs: initialized
[    0.359971] console [lkl_console0] enabled
[    0.364063] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.366223] xor: automatically using best checksumming function   8regs     
[    0.373467] random: get_random_u32 called from 0x0000000000302982 with crng_init=0
[    0.376890] NET: Registered protocol family 16
[    0.440328] cryptd: max_cpu_qlen set to 1000
[    0.467327] clocksource: Switched to clocksource lkl
[    0.560180] NET: Registered protocol family 2
[    0.575286] tcp_listen_portaddr_hash hash table entries: 256 (order: 0, 4096 bytes)
[    0.576718] TCP established hash table entries: 2048 (order: 2, 16384 bytes)
[    0.578152] TCP bind hash table entries: 2048 (order: 2, 16384 bytes)
[    0.579738] TCP: Hash tables configured (established 2048 bind 2048)
[    0.585710] UDP hash table entries: 128 (order: 0, 4096 bytes)
[    0.586943] UDP-Lite hash table entries: 128 (order: 0, 4096 bytes)
[    0.590358] NET: Registered protocol family 1
[    0.606444] workingset: timestamp_bits=62 max_order=16 bucket_order=0
[    0.689945] romfs: ROMFS MTD (C) 2007 Red Hat, Inc.
[    0.916242] NET: Registered protocol family 38
[    0.917691] io scheduler noop registered
[    0.918502] io scheduler deadline registered
[    0.921666] io scheduler cfq registered (default)
[    0.922477] io scheduler mq-deadline registered
[    0.923279] io scheduler kyber registered
CAP_FILE INIT 43 4004e201
CAP_STREAM_HOST INIT 45 4004e401
[    1.795497] device-mapper: ioctl: 4.39.0-ioctl (2018-04-03) initialised: dm-devel@redhat.com
[    1.828888] Warning: unable to open an initial console.
[    1.830415] This architecture does not have kernel memory protection.
ignore destructor in tls_alloc
host0 allocated (task=0xcc95500/host0) pid=51
------ LKL INIT DONE, starting mount  ------- 
------ TEST1 ------- 
------ TEST 1 DONE ------- 
ADD disk
[    1.899549] virtio-mmio virtio-mmio.0.auto: Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.
[    1.916178] virtio_blk virtio0: [vda] 400 512-byte logical blocks (205 kB/200 KiB)
disk id = 0
------ ADD disk DONE ------- 
[    2.036396] EXT4-fs (vda): warning: mounting unchecked fs, running e2fsck is recommended
[    2.044709] EXT4-fs (vda): mounted filesystem without journal. Opts: 
loader.c        311
------ CHROOT DONE ------- 
creating /cap/cf1 1
creating /cap/cf2 2
creating /cap/ch1 1
creating /cap/ch2 2
creating /cap/ch3 3
creating /cap/ch4 4
------ MOUNTS DONE ------- 
[.]
[sys]
[app]
[cap]
[run]
[proc]
[..]
[lost+found]
[dev]
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
[    2.120885] host1 (52): drop_caches: 3
MOUNT DONE
td = 0x5dbb10, p = 0x5dbb10, td->robust_list.head = 0x5dbba0 0xfffbcb8 0x5dbba0
PRESTART NETWORK BEFORE LKL 
[    2.126368] virtio-mmio virtio-mmio.1.auto: Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.
------ NETWORK ----- 
setting LO
...done
setting eth0
virtio net fd read: Bad file descriptor
...done
post start done
LOAD: /app/cap_stream
app.base = 0x8000000
ready to start the app: 0x800248c
envp = 0xfffc028, me->argv[0] = 0xfffd000, m->argv[0]=/app/cap_stream
---------------------------------
tsd = 0x8862c00, libc.tls_size = f8, stack = 0x8862b08
new = 0x8862b08
start = 0x16e94e, args = 0x8862ae8, ts = 0x8862ad0
new thread = 55
Testing CF_STREAMs SEND thread, ptr = 0x8005000, dnull = 0x8405000
fd_out = 3
me->func = 0x2031ecbe, addr=0x0, sp = 0x2f57feb0
0:      recv = 'send 0'
1:      recv = 'send 1'
2:      recv = 'send 2'
3:      recv = 'send 3'
4:      recv = 'send 4'
5:      recv = 'send 5'
6:      recv = 'send 6'
7:      recv = 'send 7'
8:      recv = 'send 8'
9:      recv = 'send 9'
10:     recv = 'send 10'
11:     recv = 'send 11'
12:     recv = 'send 12'
13:     recv = 'send 13'
14:     recv = 'send 14'
15:     recv = 'send 15'
16:     recv = 'send 16'
17:     recv = 'send 17'
18:     recv = 'send 18'
<..>

```
