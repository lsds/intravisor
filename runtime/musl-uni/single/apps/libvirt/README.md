# Libvirtd service 

Was ported to Intravisor as part of the DSbD TAP4. Only minimal functionality is supported: can spawn a new cVM via `virsh`

## Expected output 

This output is for CI -- it exits after 20 seconds since start 

```
Using yaml.cfg = /intravisor/cvm.yaml
***************** [16] Deploy 'libvirt' ***************
BUILDING cvm: name=libvirt, disk=(null), runtime=liblibvirt.so, net=(null), args='/ld.so /app/sc_main', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s clean_room = 0, libvirt = 1
requested cVM size matches CVM_MAX_SIZE (40000000)
[2]: 897ed000 400000000 174654 174654 897ed000 174654
[3]: 89961658 400184658 2a22ac 2a22ac 89961658 2a22ac
end of RO: 400436910
[4]: 89c03910 400436910 5def0 5def0 89c03910 5def0
[5]: 89c61800 4004a4800 13230 3eb88 89c61800 13230
ELF BASE = 0x400000000, MAP SIZE = 4e3388, ENTRY = 0x402275
encl_map.entry = 0x402275
encl_map.ret = 0x402184
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x43e000000 -- 440000000]
Convrting free memory into cVM Heap: 4004e4000 -- 43e000000 +3db1c000 ( 987.109375 MB)
cVM has cvm_heap_begin (4d8be0) and cvm_heap_size (4d8bc0)
SEALED RET FROM MON 0x802991e0 0x802991d0
ACHTUNG: 'liblibvirt.so' has syscall handler 'syscall_handler' at 0x4021bd
Deploy 16 in 3.511000, SHA-256 Hash: cb546088b779bf98a82295f761f25a9bf49bda59a8a4d768977fc813a93f10d8
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 43fffc000, old TP = 43ffffbe0 sp_read = 0x440000000, me->stacl = 0x43ff80000, getSP()=0x43ffff970, me->c_tp = 0x43ffffbd0 43ffffbc0
[1] '/app/sc_main'
&env0 = 0x43fffc040, &env2=0x43fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000402275
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 0000000000249668
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0003717d type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 00000000002496d0
ca6: sealed ret from mon
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000402185
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000043ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 43ffffa40
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000043ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x43fffc000, tp = 0x43ffff9f0, &cinv_args = 0x43ffffa70
TP_ARGS: 43e001000, 10, 43ff81000
-----------------------------------------------
hello musl-uni 
prepare nolibos initcVM Heap: 4004e4000 -- 7db6a4000 +3db1c000 ( 987.109375 MB)
ptr = 0x4004e4040, 4e4040
424
426
Mount ramfs to /...
VFS: mounting ramfs at /
428
Mount devfs to /dev...VFS: mounting devfs at /dev
430
Register 'null' to devfs
Register 'zero' to devfs
432
Register 'urandom' and 'random' to devfs
434
Initialize random number generator...fd = 0
wrote 12 
fd = 3
read 12 from file = hello world
....testing /dev/zero/dev/zero fd = 3
read 128 bytes from /dev/zero
....testing /dev/random/dev/zero fd = 3
read 8 bytes from /dev/random, rd=a7135e24912251f8
--------- LibOS is ok,  ------- 
app mainWARNING: get_file_size is unsafe and doesnt filename (root_libvirt.cpio) when it loads
WARNING: copy_file_into_cvm is unsafe and doesnt check where (0x4004eba00/1024) and what (root_libvirt.cpio) it loads
size2 = 1024, size = 1024
libvirt.conf, 4eba7c (size 647)
writing file '/libvirt.conf', ret = 647
., 4ebd74 (size 0)
--------- LibVirt ------- 2024-02-11 11:48:21.016+0000: 18253592880: info : libvirt version: 4.9.0
2024-02-11 11:48:21.016+0000: 19: info : hostname: localhost
2024-02-11 11:48:21.016+0000: 16: debug : virGlobalInit:240 : register drivers
2024-02-11 11:48:21.035+0000: 22: debug : virConfReadFile:752 : filename=/libvirt.conf
2024-02-11 11:48:21.041+0000: 11: debug : virFileClose:109 : Closed fd 3
2024-02-11 11:48:21.049+0000: 33: debug : virConfAddEntry:223 : Add entry uri_default 0x400502be0
2024-02-11 11:48:21.052+0000: 30: debug : virConfAddEntry:223 : Add entry auth_tcp 0x400502fe0
2024-02-11 11:48:21.056+0000: 32: debug : virConfAddEntry:223 : Add entry listen_tcp 0x400503340
2024-02-11 11:48:21.060+0000: 32: debug : virConfAddEntry:223 : Add entry listen_tls 0x4005036c0
2024-02-11 11:48:21.063+0000: 33: debug : virConfAddEntry:223 : Add entry min_workers 0x400503a40
2024-02-11 11:48:21.066+0000: 33: debug : virConfAddEntry:223 : Add entry max_workers 0x400503dc0
2024-02-11 11:48:21.070+0000: 34: debug : virConfAddEntry:223 : Add entry prio_workers 0x400504140
2024-02-11 11:48:21.074+0000: 28: debug : virConfGetValueBool:1029 : Get value bool 0x400503340 2
2024-02-11 11:48:21.078+0000: 28: debug : virConfGetValueBool:1029 : Get value bool 0x4005036c0 2
2024-02-11 11:48:21.082+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.085+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.088+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.092+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.094+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.097+0000: 30: debug : virConfGetValueString:893 : Get value string 0x400502fe0 3
2024-02-11 11:48:21.104+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.107+0000: 25: debug : virConfGetValueStringList:942 : Get value string list 0 0
2024-02-11 11:48:21.110+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.113+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.116+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.119+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.122+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.125+0000: 18: debug : virConfGetValueBool:1029 : Get value bool 0 0
2024-02-11 11:48:21.128+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.131+0000: 18: debug : virConfGetValueBool:1029 : Get value bool 0 0
2024-02-11 11:48:21.133+0000: 18: debug : virConfGetValueBool:1029 : Get value bool 0 0
2024-02-11 11:48:21.134+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.136+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.138+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.140+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.142+0000: 25: debug : virConfGetValueStringList:942 : Get value string list 0 0
2024-02-11 11:48:21.143+0000: 25: debug : virConfGetValueStringList:942 : Get value string list 0 0
2024-02-11 11:48:21.145+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.148+0000: 28: debug : virConfGetValueUInt:1126 : Get value uint 0x400503a40 2
2024-02-11 11:48:21.150+0000: 28: debug : virConfGetValueUInt:1126 : Get value uint 0x400503dc0 2
2024-02-11 11:48:21.153+0000: 18: debug : virConfGetValueUInt:1126 : Get value uint 0 0
2024-02-11 11:48:21.155+0000: 18: debug : virConfGetValueUInt:1126 : Get value uint 0 0
2024-02-11 11:48:21.157+0000: 18: debug : virConfGetValueUInt:1126 : Get value uint 0 0
2024-02-11 11:48:21.159+0000: 28: debug : virConfGetValueUInt:1126 : Get value uint 0x400504140 2
2024-02-11 11:48:21.161+0000: 18: debug : virConfGetValueUInt:1126 : Get value uint 0 0
2024-02-11 11:48:21.163+0000: 18: debug : virConfGetValueUInt:1126 : Get value uint 0 0
2024-02-11 11:48:21.166+0000: 18: debug : virConfGetValueUInt:1126 : Get value uint 0 0
2024-02-11 11:48:21.168+0000: 18: debug : virConfGetValueUInt:1126 : Get value uint 0 0
2024-02-11 11:48:21.170+0000: 18: debug : virConfGetValueUInt:1126 : Get value uint 0 0
2024-02-11 11:48:21.172+0000: 18: debug : virConfGetValueUInt:1126 : Get value uint 0 0
2024-02-11 11:48:21.174+0000: 18: debug : virConfGetValueUInt:1126 : Get value uint 0 0
2024-02-11 11:48:21.176+0000: 18: debug : virConfGetValueBool:1029 : Get value bool 0 0
2024-02-11 11:48:21.178+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.180+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.182+0000: 18: debug : virConfGetValueUInt:1126 : Get value uint 0 0
2024-02-11 11:48:21.185+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.188+0000: 20: debug : virConfGetValueString:893 : Get value string 0 0
2024-02-11 11:48:21.191+0000: 17: debug : virConfGetValueInt:1077 : Get value int 0 0
2024-02-11 11:48:21.193+0000: 18: debug : virConfGetValueUInt:1126 : Get value uint 0 0
2024-02-11 11:48:21.196+0000: 17: debug : virConfGetValueInt:1077 : Get value int 0 0
2024-02-11 11:48:21.205+0000: 18: debug : virConfGetValueUInt:1126 : Get value uint 0 0
2024-02-11 11:48:21.208+0000: 18: debug : virConfGetValueUInt:1126 : Get value uint 0 0
libvirt_main 1196 disabled
2024-02-11 11:48:21.214+0000: 16: debug : virLogParseOutputs:1765 : outputs=2:stderr
2024-02-11 11:48:21.218+0000: 15: debug : virLogParseOutput:1593 : output=2:stderr
Skip virEventPollInit
2024-02-11 11:48:21.236+0000: 17185152640: info : libvirt version: 4.9.0
2024-02-11 11:48:21.236+0000: 19: info : hostname: localhost
2024-02-11 11:48:21.236+0000: 90: info : virModuleLoad:112 : Module '/usr/local/lib/libvirt/connection-driver/libvirt_driver_network.so' does not exist
2024-02-11 11:48:21.243+0000: 88: info : virModuleLoad:112 : Module '/usr/local/lib/libvirt/connection-driver/libvirt_driver_libxl.so' does not exist
2024-02-11 11:48:21.247+0000: 87: info : virModuleLoad:112 : Module '/usr/local/lib/libvirt/connection-driver/libvirt_driver_qemu.so' does not exist
2024-02-11 11:48:21.253+0000: 86: info : virModuleLoad:112 : Module '/usr/local/lib/libvirt/connection-driver/libvirt_driver_cvm.so' does not exist
skip not implemented 445 libvirt/src/remote/remote_daemon.c
broken virSetSockReuseAddr 19libvirt/src/util/virsocketaddr.c 442 0.0.0.0 
not implemented freeaddrinfo
not implemented 733 libvirt/src/remote/remote_daemon.c
2024-02-11 11:48:21.291+0000: 52: warning : virArchFromHost:179 : Unknown host arch , report to libvir-list@redhat.com
not implemented 556 libvirt/src/cvm/cvm_driver.c
skipping not implemented at 581 libvirt/src/cvm/cvm_driver.c
not implemented 733 libvirt/src/remote/remote_daemon.c
skip not implemented 826 libvirt/src/rpc/virnetdaemon.c
not implemented pthread_cond_destroy
not implemented pthread_cond_destroy
```
