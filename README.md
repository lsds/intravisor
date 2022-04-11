# Intravisor  0.0.2



## In the nutshell

Intravisor deployes programs, runtimes, LibOSs into its address space and uses CHERI capabilitites for isolation and sharing.
[More information about motivation and design](https://fosdem.org/2022/schedule/event/tee_intravisor/), [Pre-print on arxiv](https://arxiv.org/abs/2202.05732)

## Building

CHERI toolchains and QEMU (tested on Ubuntu 18.04.6)

```
sudo apt install autoconf automake libtool pkg-config clang bison cmake ninja-build samba flex texinfo libglib2.0-dev libpixman-1-dev libarchive-dev libarchive-tools libbz2-dev libattr1-dev libcap-ng-dev gcc-7-riscv64-linux-gnu-base binutils-riscv64-linux-gnu
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

### MUSL-LKL

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
cp src/build/monitor ~/cheri/output/intravisor/
cp runtime/baremetal/hello_world/libhello.so runtime/baremetal/hello_world/hello.yaml  ~/cheri/output/intravisor/
```

Copy from nfs into CHERI (otherwise it works very slow)

```
root@cheribsd-riscv64-hybrid:~ # cp -r /outputroot/intravisor /
root@cheribsd-riscv64-hybrid:~ # cd /intravisor/
root@cheribsd-riscv64-hybrid:/intravisor # ./monitor -y hello.yaml 
```

Expected output: 
```
Using yaml.cfg = hello.yaml
MON: sc_cbs[0]: monitor, 0x3fffdff900, 0x3fffdff8f0, 0x4dd50
MON: CAP[0] 0x45169140 test1 32
MON: CAP[1] 0x45160000 test2 4096
***************** Deploy 'hello' ***************
BUILDING cvm: name=hello, disk=(null), runtime=libhello.so, net=(null), args='(null)', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = '(null)', cb_out = 'monitor' wait = 0s
Mapped 0x0, segment = 0x20000000, map_aaadr = 0x20000000, map_len = 4000
Mapped 0x12c4, segment = 0x20001000, map_aaadr = 0x20001000, map_len = 1000
Mapped 0x2498, segment = 0x20002000, map_aaadr = 0x20002000, map_len = 1000
Mapped 0x3518, segment = 0x20003000, map_aaadr = 0x20003000, map_len = 1000
ELF BASE = 0x20000000, MAP SIZE = 3520, ENTRY = 0x200012c4
encl_map.entry = 0x200012c4
encl_map.ret = 0x1390
[cVM STACKs] = [0x2e000000 -- 30000000]
MON: probe syscall handler for key monitor
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 2fffc000, sp_read = 0x30000000, me->stacl = 0x2ff80000, getSP()=0x2ffffaf0, me->c_tp = 0x2ff81000
&env0 = 0x2fffc018, &env1=0x2fffc020
72 sp = 0x2fffc000
ca0: sealed COMP PPC
tag 1 s 1 perms 00000107 type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 00000000000012c4
ca1: sealed COMP DDC
tag 1 s 1 perms 0000011d type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 0000011d type ffffffffffffffff
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 00068117 type 0000000000000000
        base 0000000000000000 length 0000004000000000 ofset 00000000000486c2
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0007817d type 0000000000000000
        base 0000000000000000 length 0000004000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 00068117 type 0000000000000000
        base 0000000000000000 length 0000004000000000 ofset 000000000004869a
ca6: sealed ret from mon
tag 1 s 1 perms 00000107 type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 0000000000001390
HW: sp = 0xfffc000, tp = 0xff81000
-----------------------------------------------
hello world, let's read cap 'test1' 
MON: probe for key test1, store at 0x2fffbfc0
Hello world
```

### Run and build for FPGA 

Please use the following [instruction](https://github.com/sartakov/CHERI/blob/main/FETT_AWS_F1.md).

## IPC 

Intravisor features fast IPC primitives based on capabilitites. See [examples](runtime/musl-lkl/apps). 


# Acknowledgements

This work was partially funded by the UK Government’s Industrial Strategy Challenge Fund (ISCF) under the Digital Security by Design (DSbD) Programme.

# Paper 

Accepted to OSDI'22

Sartakov, V. A., Vilanova, L., Eyers, D., Shinagawa, T., & Pietzuch, P. (2022). CAP-VMs: Capability-Based Isolation and Sharing for Microservices. 15th USENIX Symposium on Operating Systems Design and Implementation (OSDI'22).


