# GGML with gpt-2

NB: requires huge cVM: must be configured properly in .config for both Intravisor and musl-lkl

```
  - base:  0x400000000
    size:  0x080000000
    begin: 0x400000000
    end:   0x480000000
```

# expected output

```
Using yaml.cfg = /intravisor/cvm.yaml
***************** [8] Deploy 'ggml' ***************
BUILDING cvm: name=ggml, disk=disk_docker_ggml.img, runtime=libmusl-lkl.so, net=(null), args='/ld.so /ggml/build/bin/gpt-2 -m /ggml/build/models/gpt-2-117M/ggml-model.bin -t 1 -s 0 -p once', base=0x400000000, size=0x80000000, begin=0x400000000, end=0x480000000, cb_in = '(null)', cb_out = '(null)' wait = 0s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (80000000)
[1]: 898a8000 400000000 f218c f218c 898a8000 f218c
[2]: 8999a190 400102190 26ea3c 26ea3c 8999a190 26ea3c
end of RO: 400380be0
[3]: 89c08be0 400380be0 fe78 fe78 89c08be0 fe78
[4]: 89c18c00 4003a0c00 12c688 1c3fe0 89c18c00 12c688
ELF BASE = 0x400000000, MAP SIZE = 564be0, ENTRY = 0x14fb6c
encl_map.entry = 0x14fb6c
encl_map.ret = 0x361fd0
[cVM STACKs] = [0x47e000000 -- 480000000]
Convrting free memory into cVM Heap: 400565000 -- 47e000000 +7da9b000 ( 2010.605469 MB)
cVM has cvm_heap_begin (4bd490) and cvm_heap_size (4bd498)
callback_out is empty, use default 'monitor'
SEALED RET FROM MON 0x8047e440 0x8047e430
ACHTUNG: 'libmusl-lkl.so' has syscall handler 'syscall_handler' at 0x362008
Deploy 8 in 6.686000, SHA-256 Hash: e548962a068c12e338e6ddfcbd6719d78f54f81beed50a5d701a99b966d62cdc
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 47fffc000, old TP = 47ffffbe0 sp_read = 0x480000000, me->stacl = 0x47ff80000, getSP()=0x47ffff990, me->c_tp = 0x47ffffbd0 47ffffbc0
[1] '/ggml/build/bin/gpt-2'
sp[i+1] = '/ggml/build/bin/gpt-2'
[2] '-m'
sp[i+1] = '-m'
[3] '/ggml/build/models/gpt-2-117M/ggml-model.bin'
sp[i+1] = '/ggml/build/models/gpt-2-117M/ggml-model.bin'
[4] '-t'
sp[i+1] = '-t'
[5] '1'
sp[i+1] = '1'
[6] '-s'
sp[i+1] = '-s'
[7] '0'
sp[i+1] = '0'
[8] '-p'
sp[i+1] = '-p'
[9] 'once'
sp[i+1] = 'once'
&env0 = 0x47fffc060, &env1=0x47fffc068
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000080000000 ofset 000000000014fb6c
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000400000000 length 0000000080000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
    base 0000000400000000 length 0000000080000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 000000000024c1a0
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0003717d type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 000000000024c21c
ca6: sealed ret from mon
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000080000000 ofset 0000000000361fd0
HW: sp = 0x7fffc000, tp = 0x47ffffa10, &cinv_args = 0x47ffffa90
TP_ARGS: 47e001000, 8, 400000000
-----------------------------------------------
STARTING LKL, lkl_io_in = 0x563d70, disk_io = 0x563e90, heap (565000, +7da9b000)
TIMER[0]: 0x15a698 0
TODO: CREATE_CARRIE_TIMER
[    0.000000] Linux version 4.17.0 (cheri@runner-_aJ2xR8B-project-191-concurrent-2) (clang version 13.0.0 (https://git.morello-project.org/morello/llvm-project.git b4f4d8095b90b87ba65a692dfa98de2968996db4)) #1 Sun Feb 11 01:08:38 UTC 2024
[    0.000000] bootmem address range: 0x565000 - 0x7e000000
[    0.000000] Built 1 zonelists, mobility grouping off.  Total pages: 507677
[    0.000000] Kernel command line: 
[    0.000000] Dentry cache hash table entries: 262144 (order: 9, 2097152 bytes)
[    0.000000] Inode-cache hash table entries: 131072 (order: 8, 1048576 bytes)
[    0.000000] Memory available: 1998400k/2058860k RAM
[    0.000000] SLUB: HWalign=32, Order=0-3, MinObjects=0, CPUs=1, Nodes=1
[    0.000000] NR_IRQS: 4096
[    0.000000] lkl: irqs initialized
[    0.000000] clocksource: lkl: mask: 0xffffffffffffffff max_cycles: 0x1cd42e4dffb, max_idle_ns: 881590591483 ns
[    0.000126] lkl: time and timers initialized (irq1)
[    0.001293] pid_max: default: 4096 minimum: 301
[    0.003691] Mount-cache hash table entries: 4096 (order: 3, 32768 bytes)
[    0.004822] Mountpoint-cache hash table entries: 4096 (order: 3, 32768 bytes)
[    0.091365] devtmpfs: initialized
[    0.298801] console [lkl_console0] enabled
[    0.302731] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.306717] xor: automatically using best checksumming function   8regs     
[    0.340072] cryptd: max_cpu_qlen set to 1000
[    0.357923] clocksource: Switched to clocksource lkl
[    0.396713] workingset: timestamp_bits=62 max_order=19 bucket_order=0
[    0.460816] romfs: ROMFS MTD (C) 2007 Red Hat, Inc.
[    0.632835] io scheduler noop registered
[    0.634382] io scheduler deadline registered
[    0.638202] io scheduler cfq registered (default)
[    0.639504] io scheduler mq-deadline registered
[    0.640771] io scheduler kyber registered
CAP_FILE INIT 43 4004e201
CAP_STREAM_HOST INIT 45 4004e401
[    1.180482] device-mapper: ioctl: 4.39.0-ioctl (2018-04-03) initialised: dm-devel@redhat.com
[    1.191422] random: get_random_bytes called from 0x000000000015e5d0 with crng_init=0
[    1.204314] Warning: unable to open an initial console.
[    1.207081] This architecture does not have kernel memory protection.
INT: ignore destructor 15ab5c in tls_alloc
------ LKL INIT DONE, starting mount  ------- 
ADD disk
[    1.266853] virtio_blk virtio0: [vda] 819200 512-byte logical blocks (419 MB/400 MiB)
disk id = 0
------ ADD disk DONE ------- 
[    1.710514] EXT4-fs (vda): mounted filesystem with ordered data mode. Opts: 
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
[opt]
[lost+found]
[..]
[arch.patch]
[.dockerenv]
[sys]
[tmp]
[media]
[proc]
[lib]
[root]
[.]
[sbin]
[run]
[dev]
[bin]
[usr]
[ggml]
[etc]
[cap]
[mnt]
[home]
[var]
[srv]
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
[    1.955914] random: crng init done
MOUNT DONE
td = 0x4cfe08, p = 0x4cfe08, td->robust_list.head = 0x4cfe98 0x7fffbce0 0x4cfe98
NO NETWORK 
LOAD: /ggml/build/bin/gpt-2
app.base = 0x4600000
LOAD: 0x7fffbc80: libstdc++.so.6 at 0x4800000
LOAD: 0x7fffbc80: libgcc_s.so.1 at 0x4c00000
ready to start the app: 0x4615ac8
envp = 0x7fffc060, me->argv[0] = 0x7fffd000, m->argv[0]=/ggml/build/bin/gpt-2
---------------------------------
main: seed = 0
gpt2_model_load: loading model from '/ggml/build/models/gpt-2-117M/ggml-model.bin'
gpt2_model_load: n_vocab = 50257
gpt2_model_load: n_ctx   = 1024
gpt2_model_load: n_embd  = 768
gpt2_model_load: n_head  = 12
gpt2_model_load: n_layer = 12
gpt2_model_load: ftype   = 1
gpt2_model_load: qntvr   = 0
gpt2_model_load: ggml tensor size = 304 bytes
gpt2_model_load: ggml ctx size = 384.77 MB
gpt2_model_load: memory size =    72.00 MB, n_mem = 12288
gpt2_model_load: model size  =   239.08 MB
extract_tests_from_file : No test file found.
test_gpt_tokenizer : 0 tests failed out of 0 tests.
[   56.500246] ------------[ cut here ]------------
[   56.501640] WARNING: CPU: 0 PID: 52 at mm/page_alloc.c:4058 0x00000000001aef1c
[   56.503056] Modules linked in:
[   56.504314] Call Trace:
[   56.505534] 000000001ba77e7f:  [<001aef1c>] 0x00000000001aef1c
[   56.506812] 0000000060d4d025:  [<001aef1c>] 0x00000000001aef1c
[   56.508337] 00000000a753180e:  [<0015e94c>] 0x000000000015e94c
[   56.509612] 0000000097cd0b44:  [<001aef1c>] 0x00000000001aef1c
[   56.510857] 00000000b1031144:  [<001aef1c>] 0x00000000001aef1c
[   56.512370] 0000000082e00063:  [<0035f7bc>] 0x000000000035f7bc
[   56.513681] 000000008593fa4a:  [<001b133c>] 0x00000000001b133c
[   56.514803] 00000000b617e775:  [<001c6838>] 0x00000000001c6838
[   56.515960] 
[   56.516941] ---[ end trace 57c44fcf1c49b645 ]---
[   56.518576] nommu: Allocation of length 137438953472 from process 52 (host1) failed
[   56.520377] active_anon:0 inactive_anon:0 isolated_anon:0
[   56.520377]  active_file:110 inactive_file:62152 isolated_file:0
[   56.520377]  unevictable:4 dirty:1 writeback:0 unstable:0
[   56.520377]  slab_reclaimable:361 slab_unreclaimable:833
[   56.520377]  mapped:0 shmem:0 pagetables:0 bounce:0
[   56.520377]  free:333478 free_pcp:0 free_cma:0
[   56.524773] Node 0 active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:248608kB unevictable:16kB isolated(anon):0kB isolated(file):0kB mapped:0kB dirty:4kB writeback:0kB shmem:0kB writeback_tmp:0kB unstable:0kB all_unreclaimable? no
[   56.528993] Normal free:1333912kB min:5652kB low:7648kB high:9644kB active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:248608kB unevictable:16kB writepending:4kB present:2058860kB managed:1998400kB mlocked:0kB kernel_stack:88kB pagetables:0kB bounce:0kB free_pcp:0kB local_pcp:0kB free_cma:0kB
[   56.532804] lowmem_reserve[]: 0 0
[   56.534710] Normal: 0*4kB 1*8kB (U) 1*16kB (U) 0*32kB 0*64kB 1*128kB (U) 0*256kB 1*512kB (U) 0*1024kB 1*2048kB (U) 1*4096kB (U) 0*8192kB 1*16384kB (U) 0*32768kB 0*65536kB 2*131072kB (U) 2*262144kB (U) 1*524288kB (U) 0*1048576kB 0*2097152kB 0*4194304kB = 1333912kB
[   56.542012] 62276 total pagecache pages
[   56.544030] nommu: Allocation of length 68719476736 from process 52 (host1) failed
[   56.545425] active_anon:0 inactive_anon:0 isolated_anon:0
[   56.545425]  active_file:110 inactive_file:62152 isolated_file:0
[   56.545425]  unevictable:4 dirty:1 writeback:0 unstable:0
[   56.545425]  slab_reclaimable:361 slab_unreclaimable:833
[   56.545425]  mapped:0 shmem:0 pagetables:0 bounce:0
[   56.545425]  free:333478 free_pcp:0 free_cma:0
[   56.548737] Node 0 active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:248608kB unevictable:16kB isolated(anon):0kB isolated(file):0kB mapped:0kB dirty:4kB writeback:0kB shmem:0kB writeback_tmp:0kB unstable:0kB all_unreclaimable? no
[   56.551320] Normal free:1333912kB min:5652kB low:7648kB high:9644kB active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:248608kB unevictable:16kB writepending:4kB present:2058860kB managed:1998400kB mlocked:0kB kernel_stack:88kB pagetables:0kB bounce:0kB free_pcp:0kB local_pcp:0kB free_cma:0kB
[   56.554237] lowmem_reserve[]: 0 0
[   56.555445] Normal: 0*4kB 1*8kB (U) 1*16kB (U) 0*32kB 0*64kB 1*128kB (U) 0*256kB 1*512kB (U) 0*1024kB 1*2048kB (U) 1*4096kB (U) 0*8192kB 1*16384kB (U) 0*32768kB 0*65536kB 2*131072kB (U) 2*262144kB (U) 1*524288kB (U) 0*1048576kB 0*2097152kB 0*4194304kB = 1333912kB
[   56.558529] 62276 total pagecache pages
[   56.559881] nommu: Allocation of length 34359738368 from process 52 (host1) failed
[   56.561287] active_anon:0 inactive_anon:0 isolated_anon:0
[   56.561287]  active_file:110 inactive_file:62152 isolated_file:0
[   56.561287]  unevictable:4 dirty:1 writeback:0 unstable:0
[   56.561287]  slab_reclaimable:361 slab_unreclaimable:833
[   56.561287]  mapped:0 shmem:0 pagetables:0 bounce:0
[   56.561287]  free:333478 free_pcp:0 free_cma:0
[   56.565085] Node 0 active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:248608kB unevictable:16kB isolated(anon):0kB isolated(file):0kB mapped:0kB dirty:4kB writeback:0kB shmem:0kB writeback_tmp:0kB unstable:0kB all_unreclaimable? no
[   56.568736] Normal free:1333912kB min:5652kB low:7648kB high:9644kB active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:248608kB unevictable:16kB writepending:4kB present:2058860kB managed:1998400kB mlocked:0kB kernel_stack:88kB pagetables:0kB bounce:0kB free_pcp:0kB local_pcp:0kB free_cma:0kB
[   56.572572] lowmem_reserve[]: 0 0
[   56.574349] Normal: 0*4kB 1*8kB (U) 1*16kB (U) 0*32kB 0*64kB 1*128kB (U) 0*256kB 1*512kB (U) 0*1024kB 1*2048kB (U) 1*4096kB (U) 0*8192kB 1*16384kB (U) 0*32768kB 0*65536kB 2*131072kB (U) 2*262144kB (U) 1*524288kB (U) 0*1048576kB 0*2097152kB 0*4194304kB = 1333912kB
[   56.579312] 62276 total pagecache pages
[   56.581227] nommu: Allocation of length 17179869184 from process 52 (host1) failed
[   56.583404] active_anon:0 inactive_anon:0 isolated_anon:0
[   56.583404]  active_file:110 inactive_file:62152 isolated_file:0
[   56.583404]  unevictable:4 dirty:1 writeback:0 unstable:0
[   56.583404]  slab_reclaimable:361 slab_unreclaimable:833
[   56.583404]  mapped:0 shmem:0 pagetables:0 bounce:0
[   56.583404]  free:333478 free_pcp:0 free_cma:0
[   56.587983] Node 0 active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:248608kB unevictable:16kB isolated(anon):0kB isolated(file):0kB mapped:0kB dirty:4kB writeback:0kB shmem:0kB writeback_tmp:0kB unstable:0kB all_unreclaimable? no
[   56.591358] Normal free:1333912kB min:5652kB low:7648kB high:9644kB active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:248608kB unevictable:16kB writepending:4kB present:2058860kB managed:1998400kB mlocked:0kB kernel_stack:88kB pagetables:0kB bounce:0kB free_pcp:0kB local_pcp:0kB free_cma:0kB
[   56.595200] lowmem_reserve[]: 0 0
[   56.596855] Normal: 0*4kB 1*8kB (U) 1*16kB (U) 0*32kB 0*64kB 1*128kB (U) 0*256kB 1*512kB (U) 0*1024kB 1*2048kB (U) 1*4096kB (U) 0*8192kB 1*16384kB (U) 0*32768kB 0*65536kB 2*131072kB (U) 2*262144kB (U) 1*524288kB (U) 0*1048576kB 0*2097152kB 0*4194304kB = 1333912kB
[   56.603354] 62276 total pagecache pages
[   56.605244] nommu: Allocation of length 8589934592 from process 52 (host1) failed
[   56.607436] active_anon:0 inactive_anon:0 isolated_anon:0
[   56.607436]  active_file:110 inactive_file:62152 isolated_file:0
[   56.607436]  unevictable:4 dirty:1 writeback:0 unstable:0
[   56.607436]  slab_reclaimable:361 slab_unreclaimable:833
[   56.607436]  mapped:0 shmem:0 pagetables:0 bounce:0
[   56.607436]  free:333478 free_pcp:0 free_cma:0
[   56.611086] Node 0 active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:248608kB unevictable:16kB isolated(anon):0kB isolated(file):0kB mapped:0kB dirty:4kB writeback:0kB shmem:0kB writeback_tmp:0kB unstable:0kB all_unreclaimable? no
[   56.613536] Normal free:1333912kB min:5652kB low:7648kB high:9644kB active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:248608kB unevictable:16kB writepending:4kB present:2058860kB managed:1998400kB mlocked:0kB kernel_stack:88kB pagetables:0kB bounce:0kB free_pcp:0kB local_pcp:0kB free_cma:0kB
[   56.616478] lowmem_reserve[]: 0 0
[   56.617661] Normal: 0*4kB 1*8kB (U) 1*16kB (U) 0*32kB 0*64kB 1*128kB (U) 0*256kB 1*512kB (U) 0*1024kB 1*2048kB (U) 1*4096kB (U) 0*8192kB 1*16384kB (U) 0*32768kB 0*65536kB 2*131072kB (U) 2*262144kB (U) 1*524288kB (U) 0*1048576kB 0*2097152kB 0*4194304kB = 1333912kB
[   56.620878] 62276 total pagecache pages
[   57.635057] host1: page allocation failure: order:20, mode:0x14000c0(GFP_KERNEL), nodemask=(null)
[   57.636915] Call Trace:
[   57.638466] 00000000b1031144:  [<001af9ac>] 0x00000000001af9ac
[   57.639822] 0000000082e00063:  [<0035f7bc>] 0x000000000035f7bc
[   57.641045] 000000008593fa4a:  [<001b133c>] 0x00000000001b133c
[   57.642272] 00000000b617e775:  [<001c6838>] 0x00000000001c6838
[   57.643466] 
[   57.644621] Mem-Info:
[   57.645742] active_anon:0 inactive_anon:0 isolated_anon:0
[   57.645742]  active_file:110 inactive_file:1638 isolated_file:0
[   57.645742]  unevictable:4 dirty:1 writeback:0 unstable:0
[   57.645742]  slab_reclaimable:217 slab_unreclaimable:833
[   57.645742]  mapped:0 shmem:0 pagetables:0 bounce:0
[   57.645742]  free:394146 free_pcp:0 free_cma:0
[   57.648867] Node 0 active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:6552kB unevictable:16kB isolated(anon):0kB isolated(file):0kB mapped:0kB dirty:4kB writeback:0kB shmem:0kB writeback_tmp:0kB unstable:0kB all_unreclaimable? no
[   57.651059] Normal free:1576584kB min:5652kB low:7648kB high:9644kB active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:6552kB unevictable:16kB writepending:4kB present:2058860kB managed:1998400kB mlocked:0kB kernel_stack:88kB pagetables:0kB bounce:0kB free_pcp:0kB local_pcp:0kB free_cma:0kB
[   57.654512] lowmem_reserve[]: 0 0
[   57.655764] Normal: 62*4kB (U) 62*8kB (U) 60*16kB (U) 63*32kB (U) 58*64kB (U) 59*128kB (U) 58*256kB (U) 55*512kB (U) 17*1024kB (U) 5*2048kB (U) 6*4096kB (U) 1*8192kB (U) 3*16384kB (U) 3*32768kB (U) 0*65536kB 2*131072kB (U) 2*262144kB (U) 1*524288kB (U) 0*1048576kB 0*2097152kB 0*4194304kB = 1576584kB
[   57.659209] 1752 total pagecache pages
[   57.660327] 514715 pages RAM
[   57.661292] 0 pages HighMem/MovableOnly
[   57.662413] 15115 pages reserved
[   57.663517] nommu: Allocation of length 4294967296 from process 52 (host1) failed
[   57.664918] active_anon:0 inactive_anon:0 isolated_anon:0
[   57.664918]  active_file:110 inactive_file:1638 isolated_file:0
[   57.664918]  unevictable:4 dirty:1 writeback:0 unstable:0
[   57.664918]  slab_reclaimable:217 slab_unreclaimable:833
[   57.664918]  mapped:0 shmem:0 pagetables:0 bounce:0
[   57.664918]  free:394146 free_pcp:0 free_cma:0
[   57.668121] Node 0 active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:6552kB unevictable:16kB isolated(anon):0kB isolated(file):0kB mapped:0kB dirty:4kB writeback:0kB shmem:0kB writeback_tmp:0kB unstable:0kB all_unreclaimable? no
[   57.670765] Normal free:1576584kB min:5652kB low:7648kB high:9644kB active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:6552kB unevictable:16kB writepending:4kB present:2058860kB managed:1998400kB mlocked:0kB kernel_stack:88kB pagetables:0kB bounce:0kB free_pcp:0kB local_pcp:0kB free_cma:0kB
[   57.673113] lowmem_reserve[]: 0 0
[   57.674143] Normal: 62*4kB (U) 62*8kB (U) 60*16kB (U) 63*32kB (U) 58*64kB (U) 59*128kB (U) 58*256kB (U) 55*512kB (U) 17*1024kB (U) 5*2048kB (U) 6*4096kB (U) 1*8192kB (U) 3*16384kB (U) 3*32768kB (U) 0*65536kB 2*131072kB (U) 2*262144kB (U) 1*524288kB (U) 0*1048576kB 0*2097152kB 0*4194304kB = 1576584kB
[   57.678100] 1752 total pagecache pages
[   57.681902] host1: page allocation failure: order:19, mode:0x14000c0(GFP_KERNEL), nodemask=(null)
[   57.683568] Call Trace:
[   57.684577] 00000000b1031144:  [<001af9ac>] 0x00000000001af9ac
[   57.685969] 0000000082e00063:  [<0035f7bc>] 0x000000000035f7bc
[   57.687370] 000000008593fa4a:  [<001b133c>] 0x00000000001b133c
[   57.688666] 00000000b617e775:  [<001c6838>] 0x00000000001c6838
[   57.689933] 
[   57.690891] nommu: Allocation of length 2147483648 from process 52 (host1) failed
[   57.692452] active_anon:0 inactive_anon:0 isolated_anon:0
[   57.692452]  active_file:110 inactive_file:1591 isolated_file:0
[   57.692452]  unevictable:4 dirty:1 writeback:0 unstable:0
[   57.692452]  slab_reclaimable:217 slab_unreclaimable:833
[   57.692452]  mapped:0 shmem:0 pagetables:0 bounce:0
[   57.692452]  free:394193 free_pcp:0 free_cma:0
[   57.695446] Node 0 active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:6364kB unevictable:16kB isolated(anon):0kB isolated(file):0kB mapped:0kB dirty:4kB writeback:0kB shmem:0kB writeback_tmp:0kB unstable:0kB all_unreclaimable? no
[   57.704780] Normal free:1576772kB min:5652kB low:7648kB high:9644kB active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:6364kB unevictable:16kB writepending:4kB present:2058860kB managed:1998400kB mlocked:0kB kernel_stack:88kB pagetables:0kB bounce:0kB free_pcp:0kB local_pcp:0kB free_cma:0kB
[   57.707921] lowmem_reserve[]: 0 0
[   57.709158] Normal: 63*4kB (U) 63*8kB (U) 61*16kB (U) 64*32kB (U) 60*64kB (U) 59*128kB (U) 58*256kB (U) 55*512kB (U) 17*1024kB (U) 5*2048kB (U) 6*4096kB (U) 1*8192kB (U) 3*16384kB (U) 3*32768kB (U) 0*65536kB 2*131072kB (U) 2*262144kB (U) 1*524288kB (U) 0*1048576kB 0*2097152kB 0*4194304kB = 1576772kB
[   57.712712] 1705 total pagecache pages
[   57.742586] host1: page allocation failure: order:18, mode:0x14000c0(GFP_KERNEL), nodemask=(null)
[   57.744238] Call Trace:
[   57.745287] 00000000b1031144:  [<001af9ac>] 0x00000000001af9ac
[   57.746558] 0000000082e00063:  [<0035f7bc>] 0x000000000035f7bc
[   57.747910] 000000008593fa4a:  [<001b133c>] 0x00000000001b133c
[   57.749277] 00000000b617e775:  [<001c6838>] 0x00000000001c6838
[   57.750484] 
[   57.751365] nommu: Allocation of length 1073741824 from process 52 (host1) failed
[   57.752749] active_anon:0 inactive_anon:0 isolated_anon:0
[   57.752749]  active_file:110 inactive_file:409 isolated_file:0
[   57.752749]  unevictable:4 dirty:1 writeback:0 unstable:0
[   57.752749]  slab_reclaimable:182 slab_unreclaimable:833
[   57.752749]  mapped:0 shmem:0 pagetables:0 bounce:0
[   57.752749]  free:395410 free_pcp:0 free_cma:0
[   57.756051] Node 0 active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:1636kB unevictable:16kB isolated(anon):0kB isolated(file):0kB mapped:0kB dirty:4kB writeback:0kB shmem:0kB writeback_tmp:0kB unstable:0kB all_unreclaimable? no
[   57.758409] Normal free:1581640kB min:5652kB low:7648kB high:9644kB active_anon:0kB inactive_anon:0kB active_file:440kB inactive_file:1636kB unevictable:16kB writepending:4kB present:2058860kB managed:1998400kB mlocked:0kB kernel_stack:88kB pagetables:0kB bounce:0kB free_pcp:0kB local_pcp:0kB free_cma:0kB
[   57.761271] lowmem_reserve[]: 0 0
[   57.762469] Normal: 34*4kB (U) 34*8kB (U) 31*16kB (U) 34*32kB (U) 30*64kB (U) 30*128kB (U) 28*256kB (U) 26*512kB (U) 9*1024kB (U) 6*2048kB (U) 4*4096kB (U) 1*8192kB (U) 2*16384kB (U) 3*32768kB (U) 1*65536kB (U) 2*131072kB (U) 2*262144kB (U) 1*524288kB (U) 0*1048576kB 0*2097152kB 0*4194304kB = 1581640kB
[   57.766153] 523 total pagecache pages
main: compute buffer size: 3.59 MB
main: prompt: 'once'
main: number of tokens in prompt = 1, first 8 tokens: 27078 
once to take up my new job. I was going to move back to Toronto and have a house in Mississauga, so I would probably move back home to Canada. But I was thinking about going to Europe, and when I got here I was like, "I'm not even sure if that's a good idea." So I took an opportunity to try out something in France. I was thinking maybe I could take up that job. So I ended up making a few trips in France.
Q: What's your plan going forward?
A: I'll tell you one thing, this is what I do. I take my wife to the doctor and she says, "I don't think that's a good idea." So I had to do something. The doctor says, "Well, I think it would be a good idea to give it to you." So that's what I did. I think this is what I'm going to do. I want to move to Toronto
main:     load time = 53559.66 ms
main:   sample time =  3471.63 ms
main:  predict time = 518942.53 ms / 2594.71 ms per token
main:    total time = 599046.12 ms
Warning: _Exit is replaced by wrap_thread_exit()
```
