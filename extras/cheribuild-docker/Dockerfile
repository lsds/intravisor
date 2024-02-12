FROM debian:latest
SHELL ["/bin/bash", "-c"]

RUN useradd -u 8877 cheri



RUN apt update && apt install -y autoconf automake libtool pkg-config clang bison cmake mercurial ninja-build samba flex texinfo time libglib2.0-dev libpixman-1-dev libarchive-dev libarchive-tools libbz2-dev libattr1-dev libcap-ng-dev libexpat1-dev libgmp-dev git bzip2 xz-utils kconfig-frontends gcc-aarch64-linux-gnu binutils-aarch64-linux-gnu bc python3 python-is-python3 gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu sudo wget curl
RUN rm -rf /var/lib/apt/lists/*
RUN apt clean

RUN mkdir -p /home/cheri && chown -R cheri:cheri /home/cheri

RUN cp /etc/os-release /tmp/
#there is a broken test inside CheriBSD that is skipped for Ubuntu but not for Debian but anyway doesn't work. patches are welcome 
RUN echo "NAME=\"Ubuntu\"" > /etc/os-release

USER cheri


RUN cd ~/  && git clone https://github.com/CTSRD-CHERI/cheribuild.git
RUN cd ~/cheribuild && ./cheribuild.py qemu --enable-hybrid-targets

#riscv
RUN cd ~/cheribuild && ./cheribuild.py llvm-native --enable-hybrid-targets
RUN cd ~/cheribuild && ./cheribuild.py cheribsd-riscv64-hybrid --enable-hybrid-targets
RUN cd ~/cheribuild && ./cheribuild.py gmp-riscv64-hybrid --enable-hybrid-targets
RUN cd ~/cheribuild && ./cheribuild.py gdb-riscv64-hybrid --enable-hybrid-targets
RUN cd ~/cheribuild && ./cheribuild.py bbl-baremetal-riscv64-purecap --enable-hybrid-targets
RUN cd ~/cheribuild && ./cheribuild.py disk-image-riscv64-hybrid --enable-hybrid-targets

#morello
RUN cd ~/cheribuild && ./cheribuild.py morello-llvm-native --enable-hybrid-targets
RUN cd ~/cheribuild && ./cheribuild.py cheribsd-morello-hybrid --enable-hybrid-targets --configure-only
COPY cheribsd.patch /
RUN cd ~/cheri/cheribsd/ && patch -p1 < /cheribsd.patch 
RUN cd ~/cheribuild && ./cheribuild.py cheribsd-morello-hybrid --enable-hybrid-targets
RUN cd ~/cheribuild && ./cheribuild.py gmp-morello-hybrid --enable-hybrid-targets
RUN cd ~/cheribuild && ./cheribuild.py gdb-morello-hybrid --enable-hybrid-targets
RUN cd ~/cheribuild && ./cheribuild.py disk-image-morello-hybrid --enable-hybrid-targets

#freertos rv64
RUN cd ~/cheribuild && ./cheribuild.py newlib-baremetal-riscv64 -d
RUN cd ~/cheribuild && ./cheribuild.py compiler-rt-builtins-baremetal-newlib-riscv64 -d

USER root
RUN cp /tmp/os-release /etc/

RUN adduser cheri sudo
RUN apt update && apt install -y libssl-dev rsync docker.io cpio
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
RUN git clone https://github.com/pyenv/pyenv.git ~/.pyenv && /root/.pyenv/plugins/python-build/bin/python-build 3.9.1 /usr/local/

