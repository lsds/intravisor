FROM alpine:3.8

RUN apk --update upgrade && \
    apk add libgcc && \
    apk add --no-cache --virtual=temporary git build-base automake autoconf libtool bash  pkgconf --update && \
    git clone https://github.com/akopytov/sysbench.git && \
    cd sysbench && \
    git checkout 1.0.15 && \
    ./autogen.sh && \
    ./configure --without-mysql && \
    make -j$(nproc) && \
    make install && \
    apk del temporary && \
    cd .. && \
    rm -rf sysbench

# Use "CFLAGS='-g -O0' ./configure --without-mysql" to build sysbench with debug symbols.
