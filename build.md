# Manual build

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

CheriBSD need to be [patched](extras/cheribuild-docker/cheribsd.patch) to support Arm-hybrid musl-lkl instances. Once patched, KERNEL_CONFIGURED_DDC_RELATIVE must be always enabled in the configuration even for pure-cap code.


