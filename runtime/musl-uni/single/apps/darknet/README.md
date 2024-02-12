Weights: 

wget https://pjreddie.com/media/files/tiny.weights
wget https://pjreddie.com/media/files/yolov3.weights
wget https://pjreddie.com/media/files/alexnet.weights
wget https://pjreddie.com/media/files/darknet.weights
wget https://pjreddie.com/media/files/vgg-16.weights
wget https://pjreddie.com/media/files/extraction.weights
wget https://pjreddie.com/media/files/darknet19.weights
wget https://pjreddie.com/media/files/darknet19_448.weights
wget https://pjreddie.com/media/files/resnet18.weights
wget https://pjreddie.com/media/files/resnet34.weights
wget https://pjreddie.com/media/files/resnet50.weights
wget https://pjreddie.com/media/files/resnet101.weights
wget https://pjreddie.com/media/files/resnet152.weights
wget https://pjreddie.com/media/files/resnext50.weights
wget https://pjreddie.com/media/files/resnext101-32x4d.weights
wget https://pjreddie.com/media/files/resnext152-32x4d.weights
wget https://pjreddie.com/media/files/densenet201.weights
wget https://pjreddie.com/media/files/darknet53.weights
wget https://pjreddie.com/media/files/darknet53_448.weights


## Expected output

```
Using yaml.cfg = /intravisor/cvm.yaml
***************** [16] Deploy 'darknet' ***************
BUILDING cvm: name=darknet, disk=(null), runtime=libdarknet.so, net=(null), args='/ld.so /app/sc_main', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
[2]: 899b5000 400000000 28c94 28c94 899b5000 28c94
[3]: 899ddc98 400038c98 a30b0 a30b0 899ddc98 a30b0
end of RO: 4000ebd50
[4]: 89a80d50 4000ebd50 63b0 63b0 89a80d50 63b0
[5]: 89a87100 400102100 1490 19db8 89a87100 1490
ELF BASE = 0x400000000, MAP SIZE = 11beb8, ENTRY = 0xc3acd
encl_map.entry = 0xc3acd
encl_map.ret = 0xc39dc
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x43e000000 -- 440000000]
Convrting free memory into cVM Heap: 40011c000 -- 43e000000 +3dee4000 ( 990.890625 MB)
cVM has cvm_heap_begin (1117a0) and cvm_heap_size (111780)
SEALED RET FROM MON 0x80ec26f0 0x80ec26e0
ACHTUNG: 'libdarknet.so' has syscall handler 'syscall_handler' at 0xc3a15
Deploy 16 in 2.352000, SHA-256 Hash: 7fa0cbd098ef54e93342c6fac3da5ce4c1f9ab8696cc59be62aa254286de7f81
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 43fffc000, old TP = 43ffffbe0 sp_read = 0x440000000, me->stacl = 0x43ff80000, getSP()=0x43ffff970, me->c_tp = 0x43ffffbd0 43ffffbc0
[1] '/app/sc_main'
&env0 = 0x43fffc040, &env2=0x43fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 00000000000c3acd
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
    base 0000000400000000 length 0000000040000000 ofset 00000000000c39dd
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
prepare nolibos initcVM Heap: 40011c000 -- 7def5c000 +3dee4000 ( 990.890625 MB)
ptr = 0x40011c040, 11c040
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
app mainWARNING: get_file_size is unsafe and doesnt filename (root.cpio) when it loads
WARNING: copy_file_into_cvm is unsafe and doesnt check where (0x401120000/250269184) and what (root.cpio) it loads
size2 = 250269184, size = 250269184
imagenet1k.data, 1120080 (size 208)
writing file '/imagenet1k.data', ret = 208
vgg-16.cfg, 11201cc (size 1442)
writing file '/vgg-16.cfg', ret = 1442
resnext101-32x4d.cfg, 11207f4 (size 10868)
writing file '/resnext101-32x4d.cfg', ret = 10868
dog.jpg, 11232e0 (size 163759)
writing file '/dog.jpg', ret = 163759
resnet101.cfg, 114b30c (size 10335)
writing file '/resnet101.cfg', ret = 10335
extraction.cfg, 114dbec (size 2142)
writing file '/extraction.cfg', ret = 2142
yolov3.cfg, 114e4c8 (size 8342)
writing file '/yolov3.cfg', ret = 8342
resnet34.cfg, 11505dc (size 4150)
writing file '/resnet34.cfg', ret = 4150
resnext50.cfg, 1151690 (size 5437)
writing file '/resnext50.cfg', ret = 5437
alexnet.cfg, 1152c4c (size 910)
writing file '/alexnet.cfg', ret = 910
darknet19_448.cfg, 115305c (size 2004)
writing file '/darknet19_448.cfg', ret = 2004
darknet19.cfg, 11538ac (size 2076)
writing file '/darknet19.cfg', ret = 2076
resnet152.cfg, 1154144 (size 15349)
writing file '/resnet152.cfg', ret = 15349
darknet.cfg, 1157db8 (size 1154)
writing file '/darknet.cfg', ret = 1154
resnet18.cfg, 11582b8 (size 2348)
writing file '/resnet18.cfg', ret = 2348
imagenet.labels.list, 1158c68 (size 218420)
writing file '/imagenet.labels.list', ret = 218420
darknet53_448.cfg, 118e21c (size 5789)
writing file '/darknet53_448.cfg', ret = 5789
darknet53.cfg, 118f938 (size 5815)
writing file '/darknet53.cfg', ret = 5815
tiny.cfg, 1191068 (size 1751)
writing file '/tiny.cfg', ret = 1751
nothing.txt, 11917bc (size 22)
writing file '/nothing.txt', ret = 22
yolov3-tiny.cfg, 1191854 (size 1915)
writing file '/yolov3-tiny.cfg', ret = 1915
imagenet.shortnames.list, 1192058 (size 246356)
writing file '/imagenet.shortnames.list', ret = 246356
resnext152-32x4d.cfg, 11ce330 (size 16206)
writing file '/resnext152-32x4d.cfg', ret = 16206
densenet201.cfg, 11d2300 (size 19747)
writing file '/densenet201.cfg', ret = 19747
resnet50.cfg, 11d70a0 (size 5268)
writing file '/resnet50.cfg', ret = 5268
alexnet.weights, 11d85b4 (size 249513392)
writing file '/alexnet.weights', ret = 249513392
., ffccbd4 (size 0)
744
/alexnet.cfg r
746
749
751
753
755
757
760
762
770
774
776
layer     filters    size              input                output
778
    0 conv     96 11 x11 / 4   227 x 227 x   3   ->    55 x  55 x  96  0.211 BFLOPs
    1 max          3 x 3 / 2    55 x  55 x  96   ->    27 x  27 x  96
    2 conv    256  5 x 5 / 1    27 x  27 x  96   ->    27 x  27 x 256  0.896 BFLOPs
    3 max          3 x 3 / 2    27 x  27 x 256   ->    13 x  13 x 256
    4 conv    384  3 x 3 / 1    13 x  13 x 256   ->    13 x  13 x 384  0.299 BFLOPs
    5 conv    384  3 x 3 / 1    13 x  13 x 384   ->    13 x  13 x 384  0.449 BFLOPs
    6 conv    256  3 x 3 / 1    13 x  13 x 384   ->    13 x  13 x 256  0.299 BFLOPs
    7 max          3 x 3 / 2    13 x  13 x 256   ->     6 x   6 x 256
    8 connected                            9216  ->  4096
    9 dropout       p = 0.50               4096  ->  4096
   10 connected                            4096  ->  4096
   11 dropout       p = 0.50               4096  ->  4096
   12 connected                            4096  ->  1000
   13 softmax                                        1000
Loading weights from /alexnet.weights.../alexnet.weights rb
Done!
/alexnet.weights: Loading in 58.376476 seconds.
/imagenet1k.data r
imagenet.shortnames.list r
/dog.jpg rb
/dog.jpg: Predicted in 45.803047 seconds.
19.03%: golfcart
18.09%: Siberian husky
 7.00%: malamute
 6.29%: tricycle
 4.17%: Eskimo dog
```