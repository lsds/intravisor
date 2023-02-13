# Intravisor  0.1.0


## tl;dr

Intravisor deployes programs, runtimes, LibOSs into its address space and uses CHERI capabilitites for isolation and sharing.
[More information about motivation and design](https://fosdem.org/2022/schedule/event/tee_intravisor/)

## Building for RISC-V

CHERI toolchains and QEMU 

Ubuntu (tested on 18.04.6)
```
sudo apt install autoconf automake libtool pkg-config clang bison cmake ninja-build samba flex texinfo libglib2.0-dev libpixman-1-dev libarchive-dev libarchive-tools libbz2-dev libattr1-dev libcap-ng-dev gcc-7-riscv64-linux-gnu-base binutils-riscv64-linux-gnu
```
macOS
```
brew install cmake ninja libarchive git glib gnu-sed automake autoconf coreutils llvm make wget pixman pkg-config xz samba
```

Then:
```
git clone https://github.com/CTSRD-CHERI/cheribuild.git
cd cheribuild/
./cheribuild.py --enable-hybrid-targets disk-image-riscv64-hybrid -d
```

Compile QEMU and run it
```
./cheribuild.py run-riscv64-hybrid --enable-hybrid-targets -d

login:root 

root@cheribsd-riscv64-hybrid:~ # qemu-mount-rootfs.sh
```

## Building for Morello

Compile SDK:

```
git clone https://github.com/CTSRD-CHERI/cheribuild.git
cd cheribuild/
git checkout 36b95e9325e03e2705bfe0d561311dcd606686a6
./cheribuild.py disk-image-morello-hybrid --enable-hybrid-targets --cheribsd/git-revision=release/22.05p1 -d
```
Run in QEMU:

```
./cheribuild.py run-morello-hybrid --enable-hybrid-targets --cheribsd/git-revision=release/22.05p1
```


### Building Intravisor, runtime, programs

Intravisor
```
git clone https://github.com/lsds/intravisor
cd intravisor
make -C src 
```

Baremetal (no libos) program: 
```
make -C runtime/baremetal/hello_world/
```

### MUSL-LKL (deprecated, use the v.0.0.2 branch)

At the time of writing, the latest version of CHERI-enabled LLVM-13 doesn't compile LKL. We use  LLVM-11 for development and experiments.
To use LLVM-11, you need (assuming fresh build):
```
cd ~/cheribuild/
./cheribuild.py llvm-native --enable-hybrid-targets --configure-only
./cheribuild.py cheribsd-riscv64-hybrid --enable-hybrid-targets --configure-only
cd ~/cheri/llvm-project/
git fetch --unshallow or git fetch --depth=100
git checkout 9c51217b7d41f3124b84b190b6631b90db6d1bf4
cd ~/cheri/cheribsd/
git fetch --unshallow or git fetch --depth=100
git checkout 47aecc899648a1f6fdea1474a967e5e57eb3bcb0
cd ~/cheribuild/
./cheribuild.py disk-image-riscv64-hybrid -d --enable-hybrid-targets
```

### Run in QEMU

Copy binaries into QEMU

```
mkdir ~/cheri/output/intravisor
cp src/intravisor ~/cheri/output/intravisor/
cp runtime/native/two-pure/first/libfirst.so runtime/native/two-pure/second/libsecond.so runtime/native/two-pure/first/two-pure.yaml ~/cheri/output/intravisor/
```

Copy from nfs into CHERI (otherwise it works very slow)

```
root@cheribsd-riscv64-hybrid:~ # cp -r /outputroot/intravisor /
root@cheribsd-riscv64-hybrid:~ # cd /intravisor/
root@cheribsd-riscv64-hybrid:/intravisor # ./intravisor -y two-pure.yaml 
```

Expected output: 
```
Using yaml.cfg = two-pure.yaml
state = 0x441460
state->clist = 0x0
***************** [2] Deploy 'first' ***************
BUILDING cvm: name=first, disk=(null), runtime=libfirst.so, net=(null), args='/ld.so /app/sc_main', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s
comp->base = 0x20000000
[2]: 85163000 20000000 40c 40c 85163000 40c
[3]: 85163410 20010410 1f0 1f0 85163410 1f0
end of RO: 20020600
[4]: 85163600 20020600 f0 f0 85163600 f0
[5]: 851636f0 200306f0 0 abc0 851636f0 0
ELF BASE = 0x20000000, MAP SIZE = 3b2b0, ENTRY = 0x10459
encl_map.entry = 0x10459
encl_map.ret = 0x1052c
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x2e000000 -- 30000000]
SEALED RET FROM MON 0x8071cd60 0x8071cd50
ACHTUNG: 'libfirst.so' has syscall handler 'syscall_handler' at 0x10561
***************** [1] Deploy 'second' ***************
BUILDING cvm: name=second, disk=(null), runtime=libsecond.so, net=(null), args='/ld.so /app/sc_main', base=0x10000000, size=0x10000000, begin=0x10000000, end=0x20000000, cb_in = '(null)', cb_out = 'libfirst.so' wait = -1s
comp->base = 0x10000000
Segmentation fault (core dumped)
root@cheribsd-morello-hybrid:/intravisor # ./intravisor -y two-pure.yaml
Using yaml.cfg = two-pure.yaml
state = 0x441460
state->clist = 0x0
***************** [2] Deploy 'first' ***************
BUILDING cvm: name=first, disk=(null), runtime=libfirst.so, net=(null), args='/ld.so /app/sc_main', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s
comp->base = 0x20000000
[2]: 85c84000 20000000 40c 40c 85c84000 40c
[3]: 85c84410 20010410 1f0 1f0 85c84410 1f0
end of RO: 20020600
[4]: 85c84600 20020600 f0 f0 85c84600 f0
[5]: 85c846f0 200306f0 0 abc0 85c846f0 0
ELF BASE = 0x20000000, MAP SIZE = 3b2b0, ENTRY = 0x10459
encl_map.entry = 0x10459
encl_map.ret = 0x1052c
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x2e000000 -- 30000000]
SEALED RET FROM MON 0x808dc7f0 0x808dc7e0
ACHTUNG: 'libfirst.so' has syscall handler 'syscall_handler' at 0x10561
***************** [1] Deploy 'second' ***************
BUILDING cvm: name=second, disk=(null), runtime=libsecond.so, net=(null), args='/ld.so /app/sc_main', base=0x10000000, size=0x10000000, begin=0x10000000, end=0x20000000, cb_in = '(null)', cb_out = 'libfirst.so' wait = -1s
comp->base = 0x10000000
Segmentation fault (core dumped)
root@cheribsd-morello-hybrid:/intravisor # ls
intravisor      intravisor.core libfirst.so     two-pure.yaml
root@cheribsd-morello-hybrid:/intravisor # ls
intravisor      intravisor.core libfirst.so     two-pure.yaml
root@cheribsd-morello-hybrid:/intravisor # cd ..
root@cheribsd-morello-hybrid:/ # rm -rf intravisor/
root@cheribsd-morello-hybrid:/ # cp -r /outputroot/intravisor /
root@cheribsd-morello-hybrid:/ # cd intravisor/
root@cheribsd-morello-hybrid:/intravisor # ./intravisor -y two-pure.yaml
Using yaml.cfg = two-pure.yaml
state = 0x441460
state->clist = 0x0
***************** [2] Deploy 'first' ***************
BUILDING cvm: name=first, disk=(null), runtime=libfirst.so, net=(null), args='/ld.so /app/sc_main', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s
comp->base = 0x20000000
[2]: 8792e000 20000000 40c 40c 8792e000 40c
[3]: 8792e410 20010410 1f0 1f0 8792e410 1f0
end of RO: 20020600
[4]: 8792e600 20020600 f0 f0 8792e600 f0
[5]: 8792e6f0 200306f0 0 abc0 8792e6f0 0
ELF BASE = 0x20000000, MAP SIZE = 3b2b0, ENTRY = 0x10459
encl_map.entry = 0x10459
encl_map.ret = 0x1052c
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x2e000000 -- 30000000]
SEALED RET FROM MON 0x81085a00 0x810859f0
ACHTUNG: 'libfirst.so' has syscall handler 'syscall_handler' at 0x10561
***************** [1] Deploy 'second' ***************
BUILDING cvm: name=second, disk=(null), runtime=libsecond.so, net=(null), args='/ld.so /app/sc_main', base=0x10000000, size=0x10000000, begin=0x10000000, end=0x20000000, cb_in = '(null)', cb_out = 'libfirst.so' wait = -1s
comp->base = 0x10000000
[2]: 87505000 10000000 3ac 3ac 87505000 3ac
[3]: 875053ac 100103ac 154 154 875053ac 154
end of RO: 10020500
[4]: 87505500 10020500 e0 e0 87505500 e0
[5]: 875055e0 100305e0 0 abc0 875055e0 0
ELF BASE = 0x10000000, MAP SIZE = 3b1a0, ENTRY = 0x103ad
encl_map.entry = 0x103ad
encl_map.ret = 0x104b8
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x1e000000 -- 20000000]
SEALED RET FROM MON 0x81085a00 0x810859f0
ACHTUNG: 'libsecond.so' has syscall handler 'syscall_handler' at 0x104ed
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 2fffc000, old TP = 2ffffbe0 sp_read = 0x30000000, me->stacl = 0x2ff80000, getSP()=0x2ffff970, me->c_tp = 0x2ffffbd0 2ffffbc0
[1] '/app/sc_main'
&env0 = 0x2fffc040, &env2=0x2fffc050
ca0: sealed COMP PPC
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000010459
ca1: sealed COMP DDC
tag 1 s 1 perms 00037141 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037141 type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c177 type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 0000000000248658
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0003717d type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 0002c177 type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 00000000002486b8
ca6: sealed ret from mon
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 000000000001052d
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000002ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 2ffffa40
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000002ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x2fffc000, tp = 0x2ffff9f0, &cinv_args = 0x2ffffa70
TP_ARGS: 2e001000, 2, 2ff81000
-----------------------------------------------
hello first(syscall-handler) 
target SP = 1fffc000, old TP = 1ffffbe0 sp_read = 0x20000000, me->stacl = 0x1ff80000, getSP()=0x1ffff970, me->c_tp = 0x1ffffbd0 1ffffbc0
[1] '/app/sc_main'
&env0 = 0x1fffc040, &env2=0x1fffc050
ca0: sealed COMP PPC
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000010000000 length 0000000010000000 ofset 00000000000103ad
ca1: sealed COMP DDC
tag 1 s 1 perms 00037141 type 0000000000000004
        base 0000000010000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037141 type 0000000000000000
        base 0000000010000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000010561
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 00037141 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 0 s 0 perms 00000000 type 0000000000000000
        base 0000000000000000 length ffffffffffffffff ofset 0000000000202ae0
ca6: sealed ret from mon
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000010000000 length 0000000010000000 ofset 00000000000104b9
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000001ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 1ffffa40
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000001ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x1fffc000, tp = 0x1ffff9f0, &cinv_args = 0x1ffffa70
TP_ARGS: 1e001000, 1, 1ff81000
-----------------------------------------------
hello second 
```

## IPC 

Intravisor features fast IPC primitives based on capabilitites. See [examples](runtime/musl-lkl/apps). 


# Acknowledgements

This work was partially funded by the UK Government’s Industrial Strategy Challenge Fund (ISCF) under the Digital Security by Design (DSbD) Programme.

# Paper 

Vasily A. Sartakov, Lluís Vilanova, David Eyers, Takahiro Shinagawa, and Peter Pietzuch. CAP-VMs: Capability-Based isolation and sharing in the cloud. In 16th USENIX Symposium on Operating Systems Design and Implementation (OSDI 22), pages 597–612, Carls- bad, CA, July 2022. USENIX Association.

