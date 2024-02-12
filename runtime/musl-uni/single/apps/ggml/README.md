# ggml 

Known limitations:
* libcxx is not actually ported, but compiled. iostream causes CHERI segfault -- this code is replaced by open/read/ in GGML
* CXX runtime support does not exist, thus, no deployment contstructors

## expected output

```
Using yaml.cfg = /intravisor/cvm.yaml
***************** [16] Deploy 'ggml' ***************
BUILDING cvm: name=ggml, disk=(null), runtime=libggml.so, net=(null), args='/ld.so /dead/beef', base=0x400000000, size=0x40000000, begin=0x400000000, end=0x440000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s clean_room = 0, libvirt = 0
requested cVM size matches CVM_MAX_SIZE (40000000)
[2]: 89003000 400000000 5d68c 5d68c 89003000 5d68c
[3]: 89060690 40006d690 1d1e7c 1d1e7c 89060690 1d1e7c
end of RO: 40024f510
[4]: 89232510 40024f510 22af0 22af0 89232510 22af0
[5]: 89255000 400282000 cb0 a2ba8 89255000 cb0
ELF BASE = 0x400000000, MAP SIZE = 324ba8, ENTRY = 0x2245cd
encl_map.entry = 0x2245cd
encl_map.ret = 0x2244dc
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x43e000000 -- 440000000]
Convrting free memory into cVM Heap: 400325000 -- 43e000000 +3dcdb000 ( 988.855469 MB)
cVM has cvm_heap_begin (31a440) and cvm_heap_size (31a420)
SEALED RET FROM MON 0x804ff6a0 0x804ff690
ACHTUNG: 'libggml.so' has syscall handler 'syscall_handler' at 0x224515
Deploy 16 in 2.845000, SHA-256 Hash: 2162d83c1db36b4dc8acab176cb4ba221d5c06d3c28be9dcb5afda386b71c2e2
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 43fffc000, old TP = 43ffffbe0 sp_read = 0x440000000, me->stacl = 0x43ff80000, getSP()=0x43ffff970, me->c_tp = 0x43ffffbd0 43ffffbc0
[1] '/dead/beef'
&env0 = 0x43fffc040, &env2=0x43fffc050
ca0: sealed COMP PCC
tag 1 s 1 perms 0002c147 type 0000000000000004
    base 0000000400000000 length 0000000040000000 ofset 00000000002245cd
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
    base 0000000400000000 length 0000000040000000 ofset 00000000002244dd
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
prepare nolibos initcVM Heap: 400325000 -- 7dd0d5000 +3dcdb000 ( 988.855469 MB)
ptr = 0x400325040, 325040
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
app mainWARNING: get_file_size is unsafe and doesnt filename (root_ggml.cpio) when it loads
WARNING: copy_file_into_cvm is unsafe and doesnt check where (0x401330000/251223040) and what (root_ggml.cpio) it loads
size2 = 251223040, size = 251223040
test.txt, 1330078 (size 1)
writing file '/test.txt', ret = 1
ggml-model.bin, 13300fc (size 251222425)
writing file '/ggml-model.bin', ret = 251222425
., 102c5b08 (size 0)
main: seed = 0
gpt2_model_load: loading model from '/ggml-model.bin'
fd = 3
magic is okgpt2_model_load: n_vocab = 50257
gpt2_model_load: n_ctx   = 1024
gpt2_model_load: n_embd  = 768
gpt2_model_load: n_head  = 12
gpt2_model_load: n_layer = 12
gpt2_model_load: ftype   = 1
gpt2_model_load: qntvr   = 0
gpt2_model_load: ggml tensor size = 416 bytes
gpt2_model_load: ggml ctx size = 384.77 MB
gpt2_model_load: memory size =    72.00 MB, n_mem = 12288
  model/h0/attn/c_attn/b - [ 2304,     1], type =    f32,   0.01 MB,      9216 bytes
  model/h0/attn/c_attn/w - [  768,  2304], type =    f16,   3.38 MB,   3538944 bytes
  model/h0/attn/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
  model/h0/attn/c_proj/w - [  768,   768], type =    f16,   1.12 MB,   1179648 bytes
         model/h0/ln_1/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h0/ln_1/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h0/ln_2/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h0/ln_2/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
     model/h0/mlp/c_fc/b - [ 3072,     1], type =    f32,   0.01 MB,     12288 bytes
     model/h0/mlp/c_fc/w - [  768,  3072], type =    f16,   4.50 MB,   4718592 bytes
   model/h0/mlp/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
   model/h0/mlp/c_proj/w - [ 3072,   768], type =    f16,   4.50 MB,   4718592 bytes
  model/h1/attn/c_attn/b - [ 2304,     1], type =    f32,   0.01 MB,      9216 bytes
  model/h1/attn/c_attn/w - [  768,  2304], type =    f16,   3.38 MB,   3538944 bytes
  model/h1/attn/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
  model/h1/attn/c_proj/w - [  768,   768], type =    f16,   1.12 MB,   1179648 bytes
         model/h1/ln_1/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h1/ln_1/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h1/ln_2/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h1/ln_2/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
     model/h1/mlp/c_fc/b - [ 3072,     1], type =    f32,   0.01 MB,     12288 bytes
     model/h1/mlp/c_fc/w - [  768,  3072], type =    f16,   4.50 MB,   4718592 bytes
   model/h1/mlp/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
   model/h1/mlp/c_proj/w - [ 3072,   768], type =    f16,   4.50 MB,   4718592 bytes
 model/h10/attn/c_attn/b - [ 2304,     1], type =    f32,   0.01 MB,      9216 bytes
 model/h10/attn/c_attn/w - [  768,  2304], type =    f16,   3.38 MB,   3538944 bytes
 model/h10/attn/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
 model/h10/attn/c_proj/w - [  768,   768], type =    f16,   1.12 MB,   1179648 bytes
        model/h10/ln_1/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
        model/h10/ln_1/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
        model/h10/ln_2/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
        model/h10/ln_2/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
    model/h10/mlp/c_fc/b - [ 3072,     1], type =    f32,   0.01 MB,     12288 bytes
    model/h10/mlp/c_fc/w - [  768,  3072], type =    f16,   4.50 MB,   4718592 bytes
  model/h10/mlp/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
  model/h10/mlp/c_proj/w - [ 3072,   768], type =    f16,   4.50 MB,   4718592 bytes
 model/h11/attn/c_attn/b - [ 2304,     1], type =    f32,   0.01 MB,      9216 bytes
 model/h11/attn/c_attn/w - [  768,  2304], type =    f16,   3.38 MB,   3538944 bytes
 model/h11/attn/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
 model/h11/attn/c_proj/w - [  768,   768], type =    f16,   1.12 MB,   1179648 bytes
        model/h11/ln_1/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
        model/h11/ln_1/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
        model/h11/ln_2/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
        model/h11/ln_2/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
    model/h11/mlp/c_fc/b - [ 3072,     1], type =    f32,   0.01 MB,     12288 bytes
    model/h11/mlp/c_fc/w - [  768,  3072], type =    f16,   4.50 MB,   4718592 bytes
  model/h11/mlp/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
  model/h11/mlp/c_proj/w - [ 3072,   768], type =    f16,   4.50 MB,   4718592 bytes
  model/h2/attn/c_attn/b - [ 2304,     1], type =    f32,   0.01 MB,      9216 bytes
  model/h2/attn/c_attn/w - [  768,  2304], type =    f16,   3.38 MB,   3538944 bytes
  model/h2/attn/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
  model/h2/attn/c_proj/w - [  768,   768], type =    f16,   1.12 MB,   1179648 bytes
         model/h2/ln_1/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h2/ln_1/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h2/ln_2/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h2/ln_2/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
     model/h2/mlp/c_fc/b - [ 3072,     1], type =    f32,   0.01 MB,     12288 bytes
     model/h2/mlp/c_fc/w - [  768,  3072], type =    f16,   4.50 MB,   4718592 bytes
   model/h2/mlp/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
   model/h2/mlp/c_proj/w - [ 3072,   768], type =    f16,   4.50 MB,   4718592 bytes
  model/h3/attn/c_attn/b - [ 2304,     1], type =    f32,   0.01 MB,      9216 bytes
  model/h3/attn/c_attn/w - [  768,  2304], type =    f16,   3.38 MB,   3538944 bytes
  model/h3/attn/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
  model/h3/attn/c_proj/w - [  768,   768], type =    f16,   1.12 MB,   1179648 bytes
         model/h3/ln_1/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h3/ln_1/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h3/ln_2/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h3/ln_2/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
     model/h3/mlp/c_fc/b - [ 3072,     1], type =    f32,   0.01 MB,     12288 bytes
     model/h3/mlp/c_fc/w - [  768,  3072], type =    f16,   4.50 MB,   4718592 bytes
   model/h3/mlp/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
   model/h3/mlp/c_proj/w - [ 3072,   768], type =    f16,   4.50 MB,   4718592 bytes
  model/h4/attn/c_attn/b - [ 2304,     1], type =    f32,   0.01 MB,      9216 bytes
  model/h4/attn/c_attn/w - [  768,  2304], type =    f16,   3.38 MB,   3538944 bytes
  model/h4/attn/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
  model/h4/attn/c_proj/w - [  768,   768], type =    f16,   1.12 MB,   1179648 bytes
         model/h4/ln_1/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h4/ln_1/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h4/ln_2/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h4/ln_2/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
     model/h4/mlp/c_fc/b - [ 3072,     1], type =    f32,   0.01 MB,     12288 bytes
     model/h4/mlp/c_fc/w - [  768,  3072], type =    f16,   4.50 MB,   4718592 bytes
   model/h4/mlp/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
   model/h4/mlp/c_proj/w - [ 3072,   768], type =    f16,   4.50 MB,   4718592 bytes
  model/h5/attn/c_attn/b - [ 2304,     1], type =    f32,   0.01 MB,      9216 bytes
  model/h5/attn/c_attn/w - [  768,  2304], type =    f16,   3.38 MB,   3538944 bytes
  model/h5/attn/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
  model/h5/attn/c_proj/w - [  768,   768], type =    f16,   1.12 MB,   1179648 bytes
         model/h5/ln_1/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h5/ln_1/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h5/ln_2/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h5/ln_2/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
     model/h5/mlp/c_fc/b - [ 3072,     1], type =    f32,   0.01 MB,     12288 bytes
     model/h5/mlp/c_fc/w - [  768,  3072], type =    f16,   4.50 MB,   4718592 bytes
   model/h5/mlp/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
   model/h5/mlp/c_proj/w - [ 3072,   768], type =    f16,   4.50 MB,   4718592 bytes
  model/h6/attn/c_attn/b - [ 2304,     1], type =    f32,   0.01 MB,      9216 bytes
  model/h6/attn/c_attn/w - [  768,  2304], type =    f16,   3.38 MB,   3538944 bytes
  model/h6/attn/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
  model/h6/attn/c_proj/w - [  768,   768], type =    f16,   1.12 MB,   1179648 bytes
         model/h6/ln_1/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h6/ln_1/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h6/ln_2/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h6/ln_2/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
     model/h6/mlp/c_fc/b - [ 3072,     1], type =    f32,   0.01 MB,     12288 bytes
     model/h6/mlp/c_fc/w - [  768,  3072], type =    f16,   4.50 MB,   4718592 bytes
   model/h6/mlp/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
   model/h6/mlp/c_proj/w - [ 3072,   768], type =    f16,   4.50 MB,   4718592 bytes
  model/h7/attn/c_attn/b - [ 2304,     1], type =    f32,   0.01 MB,      9216 bytes
  model/h7/attn/c_attn/w - [  768,  2304], type =    f16,   3.38 MB,   3538944 bytes
  model/h7/attn/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
  model/h7/attn/c_proj/w - [  768,   768], type =    f16,   1.12 MB,   1179648 bytes
         model/h7/ln_1/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h7/ln_1/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h7/ln_2/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h7/ln_2/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
     model/h7/mlp/c_fc/b - [ 3072,     1], type =    f32,   0.01 MB,     12288 bytes
     model/h7/mlp/c_fc/w - [  768,  3072], type =    f16,   4.50 MB,   4718592 bytes
   model/h7/mlp/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
   model/h7/mlp/c_proj/w - [ 3072,   768], type =    f16,   4.50 MB,   4718592 bytes
  model/h8/attn/c_attn/b - [ 2304,     1], type =    f32,   0.01 MB,      9216 bytes
  model/h8/attn/c_attn/w - [  768,  2304], type =    f16,   3.38 MB,   3538944 bytes
  model/h8/attn/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
  model/h8/attn/c_proj/w - [  768,   768], type =    f16,   1.12 MB,   1179648 bytes
         model/h8/ln_1/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h8/ln_1/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h8/ln_2/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h8/ln_2/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
     model/h8/mlp/c_fc/b - [ 3072,     1], type =    f32,   0.01 MB,     12288 bytes
     model/h8/mlp/c_fc/w - [  768,  3072], type =    f16,   4.50 MB,   4718592 bytes
   model/h8/mlp/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
   model/h8/mlp/c_proj/w - [ 3072,   768], type =    f16,   4.50 MB,   4718592 bytes
  model/h9/attn/c_attn/b - [ 2304,     1], type =    f32,   0.01 MB,      9216 bytes
  model/h9/attn/c_attn/w - [  768,  2304], type =    f16,   3.38 MB,   3538944 bytes
  model/h9/attn/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
  model/h9/attn/c_proj/w - [  768,   768], type =    f16,   1.12 MB,   1179648 bytes
         model/h9/ln_1/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h9/ln_1/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h9/ln_2/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
         model/h9/ln_2/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
     model/h9/mlp/c_fc/b - [ 3072,     1], type =    f32,   0.01 MB,     12288 bytes
     model/h9/mlp/c_fc/w - [  768,  3072], type =    f16,   4.50 MB,   4718592 bytes
   model/h9/mlp/c_proj/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
   model/h9/mlp/c_proj/w - [ 3072,   768], type =    f16,   4.50 MB,   4718592 bytes
            model/ln_f/b - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
            model/ln_f/g - [  768,     1], type =    f32,   0.00 MB,      3072 bytes
               model/wpe - [  768,  1024], type =    f32,   3.00 MB,   3145728 bytes
               model/wte - [  768, 50257], type =    f16,  73.62 MB,  77194752 bytes
gpt2_model_load: model size  =   239.08 MB
extract_tests_from_file : No test file found.
test_gpt_tokenizer : 0 tests failed out of 0 tests.
main: compute buffer size: 3.59 MB
main: prompt: 'Once upon a time'
main: number of tokens in prompt = 4, first 8 tokens: 7454 2402 257 640 
Once upon a time, this country is at war with itself. The enemy has not stopped, but the allies have already begun. We will never let the Americans take our country for granted. We will not let it be our fate to do what they say.
We have our allies in a new war, one that is not the traditional American one.
America has been the world's foremost leader in international disarmament. It is now an even greater leader in a new world war. We have our allies
main:     load time = 24622.37 ms
main:   sample time =  1182.69 ms
main:  predict time = 2928464.50 ms / 28431.69 ms per token
main:    total time = 2956360.00 ms
```