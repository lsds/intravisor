# Intravisor  0.1.0


## tl;dr

Intravisor deployes programs, runtimes, LibOSs into its address space and uses CHERI capabilitites for isolation and sharing.
[More information about motivation and design](https://fosdem.org/2022/schedule/event/tee_intravisor/)

## Building SDK for RISC-V

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
git checkout 9e758e60d8ba600bc35c27eb42c08c73ad7c1a9f
./cheribuild.py --enable-hybrid-targets disk-image-riscv64-hybrid -d
```

Compile QEMU and run it
```
./cheribuild.py run-riscv64-hybrid --enable-hybrid-targets -d

login:root 

root@cheribsd-riscv64-hybrid:~ # qemu-mount-rootfs.sh
```

## Building SDK for Morello

Compile SDK:

```
git clone https://github.com/CTSRD-CHERI/cheribuild.git
cd cheribuild/
git checkout 9e758e60d8ba600bc35c27eb42c08c73ad7c1a9f
./cheribuild.py disk-image-morello-hybrid --enable-hybrid-targets --cheribsd/git-revision=release/22.05p1 -d
```
Run in QEMU:

```
./cheribuild.py run-morello-hybrid --enable-hybrid-targets --cheribsd/git-revision=release/22.05p1
```


## Building Intravisor

Intravisor
```
git clone https://github.com/lsds/intravisor
cd intravisor
make -C src 
```

You can enable certain features in src/Makefile:
* Single-Copy Objects: `CFLAGS += -DSCO`

## Building and running cVMs

```
make -C runtime/native/two-pure/first/
make -C runtime/native/two-pure/second/
#copy libfirst.so, libsecond.so, intravisor, and two-pure.yaml to the Morello (QEMU or board)
./intravisor -y two-pure.yaml
```

[Expected Output](runtime/native/)


## Runtimes

### native

All supported targets can be hound [here](runtime/native)


### MUSL-LKL

The musl-lkl runtime is deprecated due to the lack of resources. You can use the [v.0.0.2](https://github.com/lsds/intravisor/tree/v0.0.2) branch to play with it.


# Acknowledgements

This work was partially funded by the UK Government’s Industrial Strategy Challenge Fund (ISCF) under the Digital Security by Design (DSbD) Programme.

# Paper 

Vasily A. Sartakov, Lluís Vilanova, David Eyers, Takahiro Shinagawa, and Peter Pietzuch. CAP-VMs: Capability-Based isolation and sharing in the cloud. In 16th USENIX Symposium on Operating Systems Design and Implementation (OSDI 22), pages 597–612, Carls- bad, CA, July 2022. USENIX Association.

