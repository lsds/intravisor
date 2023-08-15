# Python

Python compiled from sources. Just a simple 'hello world' written in Python. Requires python3.9 for build.

# Expected output: 

```
root@cheribsd-riscv64-hybrid:/e # ./intravisor -y musl-lkl-libhello.yaml
Using yaml.cfg = musl-lkl-libhello.yaml
***************** [16] Deploy 'python' ***************
BUILDING cvm: name=python, disk=disk_python.img, runtime=libmusl-lkl.so, net=(null), args='/ld.so /usr/bin/python3 /app/libtest.py', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = '(null)' wait = 0s clean_room = 0
[1]: 868dd000 400000000 f4104 f4104 868dd000 f4104
[2]: 869d1104 4000f5104 243300 243300 869d1104 243300
end of RO: 400339420
[3]: 86c14420 400339420 fd60 fd60 86c14420 fd60
[4]: 86c24180 40034a180 12c2a8 38693930 86c24180 12c2a8
ELF BASE = 0x400000000, MAP SIZE = 389ddab0, ENTRY = 0x13e6c4
encl_map.entry = 0x13e6c4
encl_map.ret = 0x328ae4
[cVM STACKs] = [0x43e000000 -- 440000000]
callback_out is empty, use default 'monitor'
SEALED RET FROM MON 0x80abbc30 0x80abbc20
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 43fffc000, old TP = 43ffffc00 sp_read = 0x440000000, me->stacl = 0x43ff80000, getSP()=0x43ffff990, me->c_tp = 0x43ffffbf0 43ffffbe0
[1] '/usr/bin/python3'
sp[i+1] = '/usr/bin/python3'
[2] '/app/libtest.py'
sp[i+1] = '/app/libtest.py'
&env0 = 0x43fffc028, &env1=0x43fffc030
ca0: sealed COMP PCC
tag 1 s 1 perms 00008117 type 0000000000000000
        base 0000000400000000 length 0000000040000000 ofset 000000000013e6c4
ca1: sealed COMP DDC
tag 1 s 1 perms 0000817d type 0000000000000000
        base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 0000817d type ffffffffffffffff
        base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 00068117 type 0000000000000000
        base 0000000000000000 length 0000800000000000 ofset 0000000000049c52
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0007817d type 0000000000000000
        base 0000000000000000 length 0000800000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 00068117 type 0000000000000000
        base 0000000000000000 length 0000800000000000 ofset 0000000000049c2a
ca6: sealed ret from mon
tag 1 s 1 perms 00008117 type 0000000000000000
        base 0000000400000000 length 0000000040000000 ofset 0000000000328ae4
HW: sp = 0x3fffc000, tp = 0x43ffffa30, &cinv_args = 0x43ffffab0
TP_ARGS: 43e001000, 10, 43ff81000
-----------------------------------------------
STARTING LKL, lkl_io_in = 0x389dcc88, disk_io = 0x389dcd98
TIMER[0]: 0x1486a2 0
TODO: CREATE_CARRIE_TIMER
[    0.000000] Linux version 4.17.0 (capvm@capvm) (clang version 14.0.0 (https://github.com/CTSRD-CHERI/llvm-project.git ed9d9964fb200af225739a89bfb988cbe8d8f69e)) #67 Wed Aug 2 12:41:55 UTC 2023
[    0.000000] bootmem address range: 0x589000 - 0x38989000
[    0.000000] Built 1 zonelists, mobility grouping off.  Total pages: 227250
[    0.000000] Kernel command line: mem=30M
[    0.000000] Dentry cache hash table entries: 131072 (order: 8, 1048576 bytes)
[    0.000000] Inode-cache hash table entries: 65536 (order: 7, 524288 bytes)
[    0.000000] Memory available: 862676k/921600k RAM
[    0.000000] SLUB: HWalign=32, Order=0-3, MinObjects=0, CPUs=1, Nodes=1
[    0.000000] NR_IRQS: 4096
[    0.000000] lkl: irqs initialized
[    0.000000] clocksource: lkl: mask: 0xffffffffffffffff max_cycles: 0x1cd42e4dffb, max_idle_ns: 881590591483 ns
[    0.000138] lkl: time and timers initialized (irq1)
[    0.002844] pid_max: default: 4096 minimum: 301
[    0.008837] Mount-cache hash table entries: 2048 (order: 2, 16384 bytes)
[    0.009407] Mountpoint-cache hash table entries: 2048 (order: 2, 16384 bytes)
[    0.101301] devtmpfs: initialized
[    0.324611] console [lkl_console0] enabled
[    0.331778] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.335544] xor: automatically using best checksumming function   8regs     
[    0.381336] cryptd: max_cpu_qlen set to 1000
[    0.401375] clocksource: Switched to clocksource lkl
[    0.446986] workingset: timestamp_bits=62 max_order=18 bucket_order=0
[    0.512824] romfs: ROMFS MTD (C) 2007 Red Hat, Inc.
[    0.820529] io scheduler noop registered
[    0.822202] io scheduler deadline registered
[    0.826645] io scheduler cfq registered (default)
[    0.828076] io scheduler mq-deadline registered
[    0.829389] io scheduler kyber registered
CAP_GADGET INIT 50 4004e201
[    1.694897] device-mapper: ioctl: 4.39.0-ioctl (2018-04-03) initialised: dm-devel@redhat.com
[    1.705751] random: get_random_bytes called from 0x000000000014bbc8 with crng_init=0
[    1.719048] Warning: unable to open an initial console.
[    1.720933] This architecture does not have kernel memory protection.
ignore destructor in tls_alloc
host0 allocated (task=0x38874540/host0) pid=51
------ LKL INIT DONE, starting mount  ------- 
------ TEST1 ------- 
------ TEST 1 DONE ------- 
ADD disk
[    1.753568] virtio-mmio virtio-mmio.0.auto: Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.
[    1.768716] virtio_blk virtio0: [vda] 409600 512-byte logical blocks (210 MB/200 MiB)
disk id = 0
------ ADD disk DONE ------- 
[    1.890723] EXT4-fs (vda): recovery complete
[    1.893076] EXT4-fs (vda): mounted filesystem with ordered data mode. Opts: 
loader.c        326
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
[proc]
[dev]
[run]
[.]
[sys]
[lost+found]
[app]
[..]
[usr]
[cap]
------
?--cg4
?--cg3
?--cg2
?--cg1
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
[    2.028392] host1 (52): drop_caches: 3
MOUNT DONE
td = 0x57a7b8, p = 0x57a7b8, td->robust_list.head = 0x57a848 0x3fffbcb8 0x57a848
NO NETWORK 
LOAD: /usr/bin/python3
app.base = 0x38400000
ready to start the app: 0x38461c14
envp = 0x3fffc028, me->argv[0] = 0x3fffd000, m->argv[0]=/usr/bin/python3
---------------------------------
[    2.245688] random: host1: uninitialized urandom read (24 bytes read)
LOAD: /usr/lib/python3.9/lib-dynload/_ctypes.cpython-39-riscv64-linux-gnu.so at 0x4620000
LOAD: libffi.so.8 at 0x4670000
LOAD: /usr/lib/python3.9/lib-dynload/_struct.cpython-39-riscv64-linux-gnu.so at 0x4680000
LOAD: /app/libtest.so at 0x46a0000
hello world from lib
```


# problems 

Be careful with stat.h. stat in LKL, in old headers, and in musl should be the same

Makefile may require additional improvements

Python has two changes compared to the original version: 

* `setup.py` is changed: 

```
    def configure_compiler(self):
        # Ensure that /usr/local is always used, but the local build
        # directories (i.e. '.' and 'Include') must be first.  See issue
        # 10520.
#        if not CROSS_COMPILING:
#            add_dir_to_list(self.compiler.library_dirs, '/usr/local/lib')
#            add_dir_to_list(self.compiler.include_dirs, '/usr/local/include')
        # only change this for cross builds for 3.3, issues on Mageia
#        if CROSS_COMPILING:
#            self.add_cross_compiling_paths()
#        self.add_multiarch_paths()
        self.add_ldflags_cppflags()
        print("nothing");
```
We use gcc from musl-lkl. It uses REALGCC compiler with replaced flags. Python takes library pathes from REALGCC and add them during linking. As a result Python is linked against wrong libc.

* Makefile.pre.inc has hardcoded `LIBFFI_INCLUDEDIR=	../dest/usr/include`. It ignores LIBFFI_INCLUDEDIR for an unknown reasons. 

Patches are welcome 