# FFmpeg 

Partially ported ffmpeg.

## Expected output

```
Using yaml.cfg = /intravisor/cvm.yaml
***************** [16] Deploy 'ffmpeg' ***************
BUILDING cvm: name=ffmpeg, disk=(null), runtime=libffmpeg.so, net=(null), args='/ld.so /app/sc_main', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
[2]: 8a9fb000 400000000 1c61bc 1c61bc 8a9fb000 1c61bc
[3]: 8abc11c0 4001d61c0 51f16c 51f16c 8abc11c0 51f16c
end of RO: 400705330
[4]: 8b0e0330 400705330 e94d0 e94d0 8b0e0330 e94d0
[5]: 8b1c9800 4007fe800 3520 2ca0d8 8b1c9800 3520
ELF BASE = 0x400000000, MAP SIZE = ac88d8, ENTRY = 0x6d83ad
encl_map.entry = 0x6d83ad
encl_map.ret = 0x6d82bc
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x43e000000 -- 440000000]
Convrting free memory into cVM Heap: 400ac9000 -- 43e000000 +3d537000 ( 981.214844 MB)
cVM has cvm_heap_begin (abe530) and cvm_heap_size (abe510)
SEALED RET FROM MON 0x80e97d50 0x80e97d40
ACHTUNG: 'libffmpeg.so' has syscall handler 'syscall_handler' at 0x6d82f5
Deploy 16 in 13.149000, SHA-256 Hash: e100a9c87aa915c25579e951e8b8374281d9d6bb797148fa89168c7075abf75a
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 43fffc000, old TP = 43ffffbe0 sp_read = 0x440000000, me->stacl = 0x43ff80000, getSP()=0x43ffff970, me->c_tp = 0x43ffffbd0 43ffffbc0
[1] '/app/sc_main'
&env0 = 0x43fffc040, &env2=0x43fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 00000000006d83ad
ca1: sealed COMP DDC
tag 1 s 1 perms 00037145 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037145 type 0000000000000000
    base 0000000400000000 length 0000000040000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 0000000000249668
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0003717d type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 0002c177 type 0000000000000004
    base 0000000000000000 length 0001000000000000 ofset 00000000002496d0
ca6: sealed ret from mon
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 00000000006d82bd
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000043ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 43ffffa40
tag 1 s 0 perms 00037145 type 0000000000000000
    base 000000043ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x43fffc000, tp = 0x43ffff9f0, &cinv_args = 0x43ffffa70
TP_ARGS: 43e001000, 10, 43ff81000
-----------------------------------------------
hello musl-uni 
prepare nolibos initcVM Heap: 400ac9000 -- 7d5e39000 +3d537000 ( 981.214844 MB)
ptr = 0x400ac9040, ac9040
424
426
Mount ramfs to /...
VFS: mounting ramfs at /
428
Mount devfs to /dev...VFS: mounting devfs at /dev
430
Register 'null' to devfs
Register 'zero' to devfs
432
Register 'urandom' and 'random' to devfs
434
Initialize random number generator...fd = 0
wrote 12 
fd = 3
read 12 from file = hello world
....testing /dev/zero/dev/zero fd = 3
read 128 bytes from /dev/zero
....testing /dev/random/dev/zero fd = 3
read 8 bytes from /dev/random, rd=a7135e24912251f8
--------- LibOS is ok,  ------- 
app mainffmpeg version 3.4.11 Copyright (c) 2000-2022 the FFmpeg developers
  built with Apple clang version 14.0.0 (clang-1400.0.29.102)
  configuration: --disable-fast-unaligned --disable-pthreads --disable-w32threads --disable-os2threads --disable-debug --disable-stripping --disable-safe-bitstream-reader --disable-all --disable-ffmpeg --enable-avcodec --enable-avformat --enable-avfilter --disable-filters --disable-swresample --disable-swscale --disable-network --disable-d3d11va --disable-dxva2 --disable-vaapi --disable-vdpau --enable-protocol=file --disable-bzlib --disable-iconv --disable-libxcb --disable-lzma --disable-sdl2 --disable-securetransport --disable-xlib --disable-zlib --disable-hwaccels --disable-videotoolbox --disable-audiotoolbox
  libavutil      57. 39.100 / 57. 39.100
  libavcodec     59. 50.100 / 59. 50.100
  libavformat    59. 34.101 / 59. 34.101
  libavfilter     8. 49.101 /  8. 49.101
  libswscale      6.  8.112 /  6.  8.112
  libswresample   4.  9.100 /  4.  9.100
not implemented sigfillset
Input #0, rawvideo, from '/dev/urandom':
  Duration: N/A, start: 0.000000, bitrate: 4423 kb/s
  Stream #0:0: Video: rawvideo (I420 / 0x30323449), yuv420p, 128x96, 4423 kb/s, 30 tbr, 30 tbn
Guessed Channel Layout for Input Stream #1.0 : stereo
Input #1, s16le, from '/dev/urandom':
  Duration: N/A, bitrate: N/A
  Stream #1:0: Audio: pcm_s16le, 48000 Hz, stereo, 1536 kb/s
Stream mapping:
  Stream #0:0 -> #0:0 (rawvideo (native) -> h263 (native))
  Stream #1:0 -> #0:1 (copy)
Press [q] to stop, [?] for help
Output #0, avi, to '/dev/null':
  Metadata:
    ISFT            : Lavf59.34.101
  Stream #0:0: Video: h263 (H263 / 0x33363248), yuv420p(progressive), 128x96, q=2-31, 200 kb/s, 30 fps, 30 tbn
    Metadata:
      encoder         : Lavc59.50.100 h263
    Side data:
      cpb: bitrate max/min/avg: 0/0/200000 buffer size: 0 vbv_delay: N/A
  Stream #0:1: Audio: pcm_s16le ([1][0][0][0] / 0x0001), 48000 Hz, stereo, 1536 kb/s
frame=    1 fps=0.0 q=4.3 size=      10kB time=00:00:00.03 bitrate=2377.5kbits/s speed=  77x    
frame=    6 fps=0.0 q=9.3 size=     134kB time=00:00:00.20 bitrate=5499.8kbits/s speed=0.385x    
frame=   30 fps= 29 q=24.8 size=     256kB time=00:00:01.00 bitrate=2097.2kbits/s speed=0.97x    
frame=   53 fps= 35 q=24.8 size=     512kB time=00:00:01.76 bitrate=2374.1kbits/s speed=1.15x    
frame=   75 fps= 37 q=24.8 size=     768kB time=00:00:02.50 bitrate=2516.6kbits/s speed=1.23x    
frame=  101 fps= 40 q=24.8 size=    1024kB time=00:00:03.36 bitrate=2491.7kbits/s speed=1.32x    
frame=  127 fps= 42 q=24.8 size=    1280kB time=00:00:04.23 bitrate=2477.0kbits/s speed=1.39x    
frame=  152 fps= 43 q=24.8 size=    1536kB time=00:00:05.06 bitrate=2483.5kbits/s speed=1.42x    
frame=  178 fps= 44 q=24.8 size=    1792kB time=00:00:05.93 bitrate=2474.2kbits/s speed=1.46x    
frame=  205 fps= 45 q=24.8 size=    2048kB time=00:00:06.83 bitrate=2455.2kbits/s speed=1.49x    
frame=  230 fps= 45 q=24.8 size=    2304kB time=00:00:07.66 bitrate=2461.9kbits/s speed=1.51x    
frame=  258 fps= 46 q=24.8 size=    2560kB time=00:00:08.60 bitrate=2438.5kbits/s speed=1.54x    
frame=  285 fps= 47 q=24.8 size=    2816kB time=00:00:09.50 bitrate=2428.3kbits/s speed=1.56x    
frame=  300 fps= 47 q=24.8 Lsize=    3218kB time=00:00:10.00 bitrate=2634.4kbits/s speed=1.56x    
video:1314kB audio:1876kB subtitle:0kB other streams:0kB global headers:0kB muxing overhead: 0.873842%
bench: utime=0.000s stime=0.000s rtime=6.431s
bench: maxrss=0kB
Exited successfully
```
