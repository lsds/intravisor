# Redis

Redis is taken from Docker container. The container is pre-compiled and stored on the hub.

## Additional configuration is required
```
ifconfig tap0 create

ifconfig tap0 inet 10.11.11.1/24
```

## Expected output: 

Starting the Redis server
```
root@cheribsd-riscv64-hybrid:/e # ./monitor -y musl-lkl-docker.yaml
Using yaml.cfg = musl-lkl-docker.yaml
MON: sc_cbs[0]: monitor, 0x3fffdff7e0, 0x3fffdff7d0, 0x49f5a
***************** Deploy 'hello' ***************
BUILDING cvm: name=hello, disk=disk_docker.img, runtime=libmusl-lkl.so, net=(null), args='/ld.so /usr/bin/redis-server /redis.conf', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = '(null)', cb_out = '(null)' wait = 0s
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
[1] '/usr/bin/redis-server'
sp[i+1] = '/usr/bin/redis-server'
[2] '/redis.conf'
sp[i+1] = '/redis.conf'
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
[    0.000078] lkl: time and timers initialized (irq1)
[    0.000448] pid_max: default: 4096 minimum: 301
[    0.001789] Mount-cache hash table entries: 512 (order: 0, 4096 bytes)
[    0.002158] Mountpoint-cache hash table entries: 512 (order: 0, 4096 bytes)
[    0.044914] devtmpfs: initialized
[    0.269475] console [lkl_console0] enabled
[    0.271095] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.272369] xor: automatically using best checksumming function   8regs     
[    0.276874] random: get_random_u32 called from 0x0000000000305b12 with crng_init=0
[    0.279974] NET: Registered protocol family 16
[    0.313716] cryptd: max_cpu_qlen set to 1000
[    0.331582] clocksource: Switched to clocksource lkl
[    0.346286] NET: Registered protocol family 2
[    0.355051] tcp_listen_portaddr_hash hash table entries: 256 (order: 0, 4096 bytes)
[    0.356221] TCP established hash table entries: 2048 (order: 2, 16384 bytes)
[    0.357663] TCP bind hash table entries: 2048 (order: 2, 16384 bytes)
[    0.359074] TCP: Hash tables configured (established 2048 bind 2048)
[    0.363789] UDP hash table entries: 128 (order: 0, 4096 bytes)
[    0.364778] UDP-Lite hash table entries: 128 (order: 0, 4096 bytes)
[    0.366819] NET: Registered protocol family 1
[    0.378227] workingset: timestamp_bits=62 max_order=16 bucket_order=0
[    0.453101] romfs: ROMFS MTD (C) 2007 Red Hat, Inc.
[    0.622341] NET: Registered protocol family 38
[    0.623421] io scheduler noop registered
[    0.624092] io scheduler deadline registered
[    0.627245] io scheduler cfq registered (default)
[    0.627951] io scheduler mq-deadline registered
[    0.628706] io scheduler kyber registered
CAP_FILE INIT 43 4004e201
CAP_STREAM_HOST INIT 45 4004e401
[    1.274722] device-mapper: ioctl: 4.39.0-ioctl (2018-04-03) initialised: dm-devel@redhat.com
[    1.302132] Warning: unable to open an initial console.
[    1.303116] This architecture does not have kernel memory protection.
ignore destructor in tls_alloc
host0 allocated (task=0xcc95500/host0) pid=51
------ LKL INIT DONE, starting mount  ------- 
------ TEST1 ------- 
------ TEST 1 DONE ------- 
ADD disk
[    1.320285] virtio-mmio virtio-mmio.0.auto: Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.
[    1.328134] virtio_blk virtio0: [vda] 40960 512-byte logical blocks (21.0 MB/20.0 MiB)
disk id = 0
------ ADD disk DONE ------- 
[    1.386729] EXT4-fs (vda): recovery complete
[    1.388125] EXT4-fs (vda): mounted filesystem with ordered data mode. Opts: 
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
[run]
[var]
[lost+found]
[site]
[redis.conf]
[sys]
[home]
[mnt]
[tmp]
[usr]
[sbin]
[opt]
[lib]
[etc]
[srv]
[media]
[root]
[bin]
[.dockerenv]
[..]
[.]
[cap]
[nginx.conf]
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
[    1.459176] host1 (52): drop_caches: 3
MOUNT DONE
td = 0x5deef0, p = 0x5deef0, td->robust_list.head = 0x5def80 0xfffbcb8 0x5def80
PRESTART NETWORK BEFORE LKL 
[    1.690635] virtio-mmio virtio-mmio.1.auto: Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.
------ NETWORK ----- 
setting LO
...done
setting eth0
...done
post start done
LOAD: /usr/bin/redis-server
app.base = 0xca00000
ready to start the app: 0xca3529e
envp = 0xfffc028, me->argv[0] = 0xfffd000, m->argv[0]=/usr/bin/redis-server
---------------------------------
[    2.215087] random: host1: uninitialized urandom read (63 bytes read)
[    2.216015] random: host1: uninitialized urandom read (1024 bytes read)
51:C 04 Feb 2022 23:59:27.866 # oO0OoO0OoO0Oo Redis is starting oO0OoO0OoO0Oo
51:C 04 Feb 2022 23:59:27.868 # Redis version=6.2.6, bits=64, commit=cc849923, modified=0, pid=51, just started
51:C 04 Feb 2022 23:59:27.869 # Configuration loaded
51:M 04 Feb 2022 23:59:27.895 * Increased maximum number of open files to 10032 (it was originally set to 1024).
51:M 04 Feb 2022 23:59:27.897 * monotonic clock: POSIX clock_gettime
51
51:M 04 Feb 2022 23:59:27.962 * Running mode=standalone, port=6379.
51:M 04 Feb 2022 23:59:27.964 # WARNING: The TCP backlog setting of 511 cannot be enforced because /proc/sys/net/core/somaxconn is set to the lower value of 128.
51:M 04 Feb 2022 23:59:27.966 # Server initialized
51:M 04 Feb 2022 23:59:27.968 # WARNING overcommit_memory is set to 0! Background save may fail under low memory condition. To fix this issue add 'vm.overcommit_memory = 1' to /etc/sysctl.conf and then reboot or run the command 'sysctl vm.overcommit_memory=1' for this to take effect.
tsd = 0x8402c00, libc.tls_size = f8, stack = 0x8402b08
new = 0x8402b08
start = 0x171912, args = 0x8402ae8, ts = 0x8402ad0
new thread = 56
tsd = 0x8c02c00, libc.tls_size = f8, stack = 0x8c02b08
new = 0x8c02b08
start = 0x171912, args = 0x8c02ae8, ts = 0x8c02ad0
new thread = 58
tsd = 0x9402c00, libc.tls_size = f8, stack = 0x9402b08
new = 0x9402b08
start = 0x171912, args = 0x9402ae8, ts = 0x9402ad0
new thread = 60
51:M 04 Feb 2022 23:59:28.692 * Ready to accept connections

```

Connecting to the server via telnet and test. Later, this will be replaced by redis-benchmark

```
root@cheribsd-riscv64-hybrid:~ # telnet 10.11.11.2 6379
Trying 10.11.11.2...
Connected to 10.11.11.2.
Escape character is '^]'.
set $a 123
+OK
get $a
$3
123
get $b
$-1
set $b 456
+OK
```

