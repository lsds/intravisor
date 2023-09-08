# 0.2.1 gitlab-ci
* Kconfig
* Now Intravisor uses gitlab-ci for authomated builds
* Dockerfile to compile SDK or run Intravisor
* musl-lkl is back:
  - Linux kernel version 4.17.0
  - supports both arm and risc-v architectures
  - compatible with docker images (proper stat.h for both architectures)
  - patch for CheriBSD to enable PCC-relative hybrid compartments
  - proper pthreads behaviour (threads, locks, keys)
  - c++ ctors in musl are back
* musl-uni:
  - centralised build system for arm and riscv for single cVM applications
* native: minimalistic demos
  - ORC hello
  - Hybrid hello_world with CF_FILE
  - Two pure-cap cVMs, one is the syscall handler for anothe one
* overall clean up: old bugs removed, new added

# 0.1.0 ORC
* ARM support
* ORC support 
* New services: pure-cap FFMpeg, uros2, redis, sqlite
* pure-cap LibOS based on Unikraft, CubicleOS, musl-libc
* LKL is deprecated

# 0.0.2 Pure-cap support 

* Intravisor supports hybrid and pure-cap cVMs at the same time
* new native example: two_pure_layers (non-nested pure-cap cVMs)
* code cleanup
 
# 0.0.1 Initial 

* Basic support for musl-lkl cVMs
* Baremetal (native) eaxmples: hello_world, nested layers
* musl-lkl apps: cap_files, cap_stream, helloworld, python3, sqlite, redis via Docker
* yaml configs 
