Build Morello LLVM with Musl
============================

This document provides details about how to use the `build-morello.sh <tools/build-morello.sh>`_
script to build LLVM toolchain with Musl C library for purecap target. The script also supports
building everything for AArch64 target that you may use as a baseline.

The script provides endpoints to run different steps each of which has its own parameters. These
steps should be executed in order to successfully build the toolchain, however some steps (e.g.
those that run tests) may be optional and are not covered here.

The overall sequence of the steps to build the complete toolchain looks like this:

* ``clang``
* ``musl-headers``
* ``crt``
* ``compiler-rt``
* ``musl``

At this point you will have Clang with C library and runtimes that are enough to compile and
build C programs and libraries.

* ``libunwind``
* ``libcxxabi``
* ``libcxx``

These additional steps are required to build C++ LLVM libraries that will allow building and
running C++ applications. These steps are currently experimental and incomplete.

All these steps can be done for two targets:

* ``aarch64-unknown-linux-musl_purecap`` (Morello Purecap)
* ``aarch64-unknown-linux-gnu`` (AArch64)

and will work on both AArch64 and x86 hosts.

Some of the steps can be affected by certain environment variables that are described along with
each step's parameters. This script does not require any root privileges and shouldn't be run as
root.

Note, that all paths must be absolute.

Sources can be checked out from:

* https://git.morello-project.org/morello/llvm-project for LLVM.
* https://git.morello-project.org/morello/musl-libc for Musl.

After building all the steps, the resulting toolchain will reside in the directory denoted below
as ``${MORELLO}`` (the toolchain) and another directory ``${SYSROOT}`` (the sysroot) where C library
(binaries and headers) and some other libraries will be installed. Note that sysroot should be
different for each target and that it may reside inside the ``${MORELLO}`` folder.

Note that each step will remove and overwrite build directories and will run ``make clean`` or
equivalent in the corresponding source root.

Prerequisites
-------------

* ``make`` (4.2 or newer)
* ``cmake`` (3.13.x or newer)
* ``python`` (3.6+)
* ``bash`` (5.x+)
* ``llvm`` and ``lld`` host version (11.0+).
* ``git`` to clone sources (not used by the script but will be needed to get the sources).
* ``wget`` to download kernel headers and licence files.

Steps
-----

Build Clang
^^^^^^^^^^^

.. code-block::

   LLVM_TARGETS="<targets>" \
   bash build-morello.sh clang ${LLVM_SRC} ${HOST_CLANG} ${MORELLO} ${CLANG_BUILD}

Note that the ``LLVM_TARGETS`` environment variable will be different depending on
what host you are working on:

* ``LLVM_TARGETS=X86;AArch64`` for x86 hosts
* ``LLVM_TARGETS=AArch64`` for AArch64 hosts

Parameters:

* ``LLVM_SRC=/path/to/llvm-project`` is path to LLVM sources checked out from Git.
* ``HOST_CLANG=/path/to/host/llvm`` is path to host Clang (you can install it using package manager).
* ``MORELLO=/path/to/toolchain`` is path where resulting toolchain will be installed.
* ``CLANG_BUILD=/path/to/build-clang`` is path to any empty folder used for intermediate build files.

Install C library headers
^^^^^^^^^^^^^^^^^^^^^^^^^

The standard headers are required to compile objects for the target. We install headers before building
C library itself.

.. code-block::

   CC=${MORELLO}/bin/clang \
   bash build-morello.sh musl-headers ${MUSL_SRC} ${SYSROOT} ${TRIPLE}

It is important that at this stage ``CC`` environment variable contains path to ``clang`` from the
newly built Morello Clang.

Parameters:

* ``MUSL_SRC=/path/to/musl-sources`` path to Musl sources checkout from Git.
* ``SYSROOT=/path/to/sysroot/for/target`` path where Musl headers will be installed for the target (Purecap or AArch64).
* ``TRIPLE=aarch64-unknown-linux-musl_purecap`` for Morello Purecap.
* ``TRIPLE=aarch64-unknown-linux-gnu`` for AArch64.

Build Compiler Runtime
^^^^^^^^^^^^^^^^^^^^^^

This includes compilation of files ``libclang_rt.builtins.a`` (Compiler RT), and ``clang_rt.crtbegin.o``
and ``clang_rt.crtend.o`` (CRT objects) that should be provided by a compiler and are required to#
successfully link a binary for your target platform.

The following command builds CRT objects.

.. code-block::

   CC=${MORELLO}/bin/clang \
   bash build-morello.sh crt ${LLVM_SRC} ${SYSROOT} ${TRIPLE}

It is important that at this stage ``CC`` environment variable contains path to ``clang`` from the
newly built Morello Clang.

Parameters:

* ``LLVM_SRC=/path/to/llvm-project`` is path to LLVM sources checked out from Git.
* ``SYSROOT=/path/to/sysroot/for/target`` path where Musl headers have been installed for the current target.
* ``TRIPLE=aarch64-unknown-linux-musl_purecap`` for Morello Purecap target.
* ``TRIPLE=aarch64-unknown-linux-gnu`` for AArch64 target.

The value of ``TRIPLE`` should correspond to the value of ``SYSROOT``. At this stage Musl headers
will be used to compile CRT objects.

The following command builds Compiler RT:

.. code-block::

   bash build-morello.sh compiler-rt ${LLVM_SRC} ${MORELLO} ${COMP_RT_BUILD} ${SYSROOT} ${TRIPLE}

Environment variables:

* ``MORELLO_NPROC=4`` number of parallel jobs to build Compiler RT

Parameters:

* ``LLVM_SRC=/path/to/llvm-project`` is path to LLVM sources checked out from Git.
* ``MORELLO=/path/to/toolchain`` is path where resulting toolchain will be installed.
* ``SYSROOT=/path/to/sysroot/for/target`` path where Musl headers have been installed for the current target.
* ``TRIPLE=aarch64-unknown-linux-musl_purecap`` for Morello Purecap target.
* ``TRIPLE=aarch64-unknown-linux-gnu`` for AArch64 target.

The value of ``TRIPLE`` should correspond to the value of ``SYSROOT``. At this stage Musl headers
will be used to build Compiler RT. Also at this point the directory pointed to by the ``MORELLO``
variable should contain installation of Morello Clang.

As a result of these two commands, you should see files ``libclang_rt.builtins.a`` (Compiler RT),
and ``clang_rt.crtbegin.o`` and ``clang_rt.crtend.o`` (CRT objects) in the directory
``${MORELLO}/lib/clang/13.0.0/lib/${TRIPLE}``.

Build Musl
^^^^^^^^^^

The following command builds Musl C library for the specified target.

.. code-block::

   CC=${MORELLO}/bin/clang \
   bash build-morello.sh musl ${MUSL_SRC} ${SYSROOT} ${TRIPLE}

It is important that at this stage ``CC`` environment variable contains path to ``clang`` from the
newly built Morello Clang.

Environment variables:

* ``MORELLO_NPROC=8`` number of parallel jobs to build Compiler RT

Parameters:

* ``MUSL_SRC=/path/to/musl-sources`` path to Musl sources checkout from Git.
* ``SYSROOT=/path/to/sysroot/for/target`` path where Musl binaries will be installed for the current target.
* ``TRIPLE=aarch64-unknown-linux-musl_purecap`` for Morello Purecap target.
* ``TRIPLE=aarch64-unknown-linux-gnu`` for AArch64 target.

The value of ``TRIPLE`` should correspond to the value of ``SYSROOT``.

Build libunwind, libcxxabi and libcxx
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The following command builds LLVM's libunwind, libcxxabi and libcxx for the specified target. 
Note that this is quite experimental.

.. code-block::

   bash build-morello.sh libruntimes ${LLVM_SRC} ${MORELLO} ${RUNTIMES_BUILD} ${SYSROOT} ${TRIPLE}

Environment variables:

* ``MORELLO_NPROC=4`` number of parallel build jobs.

Parameters:

* ``LLVM_SRC=/path/to/llvm-project`` is path to LLVM sources checked out from Git.
* ``MORELLO=/path/to/toolchain`` is path where resulting toolchain will be installed.
* ``RUNTIMES_BUILD=/path/to/build-runtimes`` is path to any empty folder used for intermediate build files.
* ``SYSROOT=/path/to/sysroot/for/target`` path where Musl binaries have been installed for the current target.
* ``TRIPLE=aarch64-unknown-linux-musl_purecap`` for Morello Purecap target.
* ``TRIPLE=aarch64-unknown-linux-gnu`` for AArch64 target.
The value of ``TRIPLE`` should correspond to the value of ``SYSROOT``.

Optional Parameters:

* ``KERNEL_BRANCH=morello/master`` target branch of kernel headers.

The resulting binaries will be placed into the ``${SYSROOT}/lib`` directory.
