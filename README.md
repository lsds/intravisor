# Intravisor  0.3.1

Intravisor is the type-3 hypervisor that utilises hardware memory capabilities as the foundation for virtualisation.
It hosts capability-based virtual machines called CAP-VMs (or cVMs for short).
A cVM is a binary constrained by capabilities and also uses them for communication with other cVMs.

Intravisor requires CHERI hardware and supports both hybrid and pure-cap ABIs.
In the case of the hybrid ABI, it supports execution of native binaries (docker-based) in a constrained form.
An LKL libOS provides a Linux interface and takes only a few base mechanisms from the host kernel: threads, locks, I/O, time.

In the case of the pure-cap ABI, Intravisor provides a pure-cap environment based on Unikraft/CubicleOS.
It enables fine-grained partitioning at scale without the use of messages or microkernels.

[More information about motivation and design](https://fosdem.org/2022/schedule/event/tee_intravisor/)

Key Features
* Pure-cap and hybrid cVMs
* Compatability with Linux in musl-lkl runtime (hybrid only)
* Minimalistic pure-cap runtime based on musl and unikraft
* Architectures: RISCV-64 and AArch64 (Morello board)


## Hybrid cVMs and LKL

musl-lkl runtime provides Linux-comptatible environment to run code in a contrained form using capabilities.
musl-lkl instances have their own name space and kernel functionality provided by the LKL.
Binaries inside musl-lkl programs can use native code thus can be generated using Docker on ordinary systems.
musl-lkl support RISCV-64 and Aarch64 architectures.

## Pur-cap cVMs
Pure-cap cVMs are also suported by Intravisor.
Lightweigh runtime based on musl and Unikraft/CubicleOS provides minimalistic environment to run pure-cap code.
Pure-cap cVMs can be effectively partitioned and extremaly low performance costs.

## Object Reuse with Capabilities

Object Reuse with Capabilities (ORC) is a system that allows reusing binaries across isolated capability-based virtual machines.
In ORC, duplicating components in co-located software systems can be removed and replaced by single, shared versions.
Components are shared and isolated using hardware memory capabilities (CHERI), while their state is decoupled after merging due to the use of a special capability-based relocation of state variables.
The latter requires to use a special LLVM pass during the compiling of capability-aware binaries. 


## Prepare SDK

You can download pre-build VMWare image with Morello and RISCV64 SDK: `https://disk.yandex.com/d/Kr6eHel7fE3oow`. Login:  capvm/capvm

You can use [dockerfile](extras/cheribuild-docker/) to build your own SDK or use ready-to-use container (`docker push intravisor/cheri-sdk:2405`).

[Manual build](build.md)

## Building Intravisor, runtime, programs

Intravisor
```
mkdir -p ~/cheri/output/intravisor
git clone https://github.com/lsds/intravisor
cd intravisor
kconfig-mconf Kconfig
make -C src/
cp src/intravisor ~/cheri/output/intravisor
```

musl-lkl programs:
```
mkdir -p ~/cheri/output/intravisor
make -C runtime/musl-lkl
sudo cp runtime/musl-lkl/build/*.so ~/cheri/output/intravisor/
source runtime/musl-lkl/apps/SOURCE_ME.aarch64 #or SOURCE_ME.rv64
make -C runtime/musl-lkl/apps/ all
make -C runtime/musl-lkl/apps/ install INSTALL_PATH=~/cheri/output/intravisor/
```

musl-uni programs:
```
mkdir -p ~/cheri/output/intravisor
make -C runtime/musl-uni/single/
make -C runtime/musl-uni/single/apps/ -j 8
make -C runtime/musl-uni/single/apps/ install INSTALL_PATH=~/cheri/output/intravisor/
```

native programs:
```
mkdir -p ~/cheri/output/intravisor
make -C runtime/native/two-pure/first/
make -C runtime/native/two-pure/second/
cp runtime/native/two-pure/first/libfirst.so runtime/native/two-pure/second/libsecond.so runtime/native/two-pure/first/two-pure.yaml ~/cheri/output/intravisor/
```

For new Arm-only musl-uni runtime, please follow this [instruction](runtime/musl3-uni2)


## Run in QEMU/Morello


Copy from nfs into CHERI-enabled system

```
root@cheribsd-riscv64-hybrid:~ # cp -r /outputroot/intravisor /
root@cheribsd-riscv64-hybrid:~ # cd /intravisor/
root@cheribsd-riscv64-hybrid:/intravisor # ./intravisor -y two-pure.yaml 
```

Expected [output](runtime/native/two-pure).

# IPC 

Intravisor features fast IPC primitives based on capabilitites. See [examples](runtime/musl-lkl/apps/cap_file/). 


# Acknowledgements

This work was funded by the Technology Innovation Institute (TII) through its Secure Systems Research Center (SSRC),
and the UK Government’s Industrial Strategy Challenge Fund (ISCF) under the Digital Security by Design (DSbD) Programme (UKRI grant EP/V000365 “CloudCAP”).
This work was also supported by JSPS KAKENHI grant number 18KK0310 and JST CREST grant number JPMJCR22M3, Japan.

# Paper 

Vasily A. Sartakov, Lluís Vilanova, Munir Geden, David Eyers, Takahiro Shinagawa, Peter Pietzuch. "ORC: Increasing Cloud Memory Density via Object Reuse with Capabilities". In 17th USENIX Symposium on Operating Systems Design and Implementation (OSDI 23) (pp. 573-587). USENIX Association.

Vasily A. Sartakov, Lluís Vilanova, David Eyers, Takahiro Shinagawa, and Peter Pietzuch. "CAP-VMs: Capability-Based Isolation and Sharing in the Cloud". In 16th USENIX Symposium on Operating Systems Design and Implementation (OSDI 22), pages 597–612, Carlsbad, CA, USA, July 2022. USENIX Association.

# Support 

We are open for joint works, collaborations, and commercial support. Contact: `v.sartakov@imperial.ac.uk`