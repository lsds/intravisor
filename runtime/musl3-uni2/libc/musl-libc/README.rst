Musl libc for Morello
=====================

Musl C library ported to Morello
--------------------------------

Disclaimer
^^^^^^^^^^

This repository contains *work-in-progress* port of Musl libc to `Morello`_ targeting
purecap ABI. It is intended for experimental use.

.. _Morello: https://www.arm.com/architecture/cpu/morello

Using this library
------------------

To build Morello Musl libc, use Morello toolchain, for example, Morello LLVM (see below).
This toolchain will cross-compile Musl libc. This works in the same way on both AArch64
and x86 hosts.

Building consists of two stages: configure and build.

To configure for purecap target, run

.. code-block::

   CC=${MORELLO}/bin/clang ./configure --enable-morello --prefix=${PREFIX} \
        --target=aarch64-linux-musl_purecap

Here, ``${MORELLO}`` is directory where Morello LLVM is installed and ``${PREFIX}`` is
where Musl will be installed. You may use this folder as sysroot for compiling and
linking purecap Morello applications based on Musl.

To build and install, just run

.. code-block::

   make
   make install

The following example demonstrates how to build a purecap Morello application and link
it to this C library. We presume the code of the application is in the ``hello.c`` file.

Compile and link application:

.. code-block::

   ${MORELLO_HOME}/bin/clang \
        -march=morello --target=aarch64-linux-musl_purecap \
        --sysroot ${PREFIX} hello.c -o hello -static

Running unit tests
------------------

TBD

Morello LLVM toolchain
----------------------

See this document for details about how to build Morello LLVM toolchain from source:
`build-morello-clang.rst <build-morello-clang.rst>`_. It explains how to use the
`tools/build-morello.sh <tools/build-morello.sh>`_ script.

Original README
---------------

Original Musl `README <README>`_ file.
