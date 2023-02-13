


## Install Docker: 

```
sudo apt  install docker.io
```

## Run ros node:


```
sudo docker run -it --net=host microros/micro-ros-agent:humble tcp4 --port 8888
```


## Run CHERI-enabled uROS2 instance: 

```
./intravisor -y sc-uros2-1x1.yaml
```

## expected output: 

Node: 
```
capvm@capvm:~$ sudo docker run -it --net=host microros/micro-ros-agent:humble tcp4 --port 8888
[1675339984.335161] info     | TCPv4AgentLinux.cpp | init                     | running...             | port: 8888
[1675339984.335462] info     | Root.cpp           | set_verbose_level        | logger setup           | verbose_level: 4
[1675340069.370854] info     | Root.cpp           | create_client            | create                 | client_key: 0x00000015, session_id: 0x81
[1675340069.371702] info     | SessionManager.hpp | establish_session        | session established    | client_key: 0x00000015, address: 192.168.159.19:23201
[1675340069.426563] info     | ProxyClient.cpp    | create_participant       | participant created    | client_key: 0x00000015, participant_id: 0x000(1)
```

CHERI:
```
root@cheribsd-morello-hybrid:/e # ./intravisor -y sc-uros2-1x1.yaml
Using yaml.cfg = sc-uros2-1x1.yaml
state = 0x441460
state->clist = 0x0
***************** [2] Deploy 'uros2' ***************
BUILDING cvm: name=uros2, disk=(null), runtime=libsco_uros2.so, net=(null), args='/ld.so /app/sc_main', base=0x20000000, size=0x10000000, begin=0x20000000, end=0x30000000, cb_in = '(null)', cb_out = 'monitor' wait = -1s
comp->base = 0x20000000
[2]: 8679e000 20000000 3b76c 3b76c 8679e000 3b76c
[3]: 867d976c 2004b76c 6f77c 6f77c 867d976c 6f77c
end of RO: 200caef0
[4]: 86848ef0 200caef0 5a10 5a10 86848ef0 5a10
[5]: 8684e900 200e0900 32460 c871041 8684e900 32460
ELF BASE = 0x20000000, MAP SIZE = c951941, ENTRY = 0x4b9ad
encl_map.entry = 0x4b9ad
encl_map.ret = 0x4baac
we have rela_dyn, it is an ARM (might be purecap) binary
[cVM STACKs] = [0x2e000000 -- 30000000]
SEALED RET FROM MON 0x811b90d0 0x811b90c0
***************** Link Inner<-->Outer ***************
***************** ALL cVMs loaded ***************
target SP = 2fffc000, old TP = 2ffffbe0 sp_read = 0x30000000, me->stacl = 0x2ff80000, getSP()=0x2ffff970, me->c_tp = 0x2ffffbd0 2ffffbc0
[1] '/app/sc_main'
&env0 = 0x2fffc040, &env2=0x2fffc050
ca0: sealed COMP PPC
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 000000000004b9ad
ca1: sealed COMP DDC
tag 1 s 1 perms 00037141 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca2: COMP DDC
tag 1 s 0 perms 00037141 type 0000000000000000
        base 0000000020000000 length 0000000010000000 ofset 0000000000000000
ca3: sealed HC PCC
tag 1 s 1 perms 0002c177 type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 00000000002486e0
ca4: sealed HC DDC (mon.DDC)
tag 1 s 1 perms 0003717d type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 0000000000000000
ca5: sealed OCALL PCC 
tag 1 s 1 perms 0002c177 type 0000000000000004
        base 0000000000000000 length 0001000000000000 ofset 0000000000248740
ca6: sealed ret from mon
tag 1 s 1 perms 0002c143 type 0000000000000004
        base 0000000020000000 length 0000000010000000 ofset 000000000004baad
ca7: SP cap for purecap cVMs
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000002ff80000 length 0000000000080000 ofset 000000000007c000
ca8: TP cap for purecap cVMs, me->c_tp = 2ffffa40
tag 1 s 0 perms 00037141 type 0000000000000000
        base 000000002ff81000 length 0000000000001000 ofset 0000000000000000
HW: sp = 0x2fffc000, tp = 0x2ffff9f0, &cinv_args = 0x2ffffa70
TP_ARGS: 2e001000, 2, 2ff81000
-----------------------------------------------
hello LibOS 
prepare nolibos initptr = 0x20140080, 20140080
422
424
Mount ramfs to /...
VFS: mounting ramfs at /
426
Mount devfs to /dev...VFS: mounting devfs at /dev
428
Register 'null' to devfs
Register 'zero' to devfs
430
Register 'urandom' and 'random' to devfs
432
Initialize random number generator...fd = 0
wrote 12 
fd = 4
read 12 from file = hello world
....testing /dev/zero/dev/zero fd = 5
read 128 bytes from /dev/zero
....testing /dev/random/dev/zero fd = 6
2       0x2fffbec8 8
read 8 bytes from /dev/random, rd=dd524cf8c761657c
./sound.wav, 200e097c (size 88244)
open /./sound.wav
ret = 7
writing file '/./sound.wav', ret = 88244
./redis.conf, 200f62ac (size 106526)
open /./redis.conf
ret = 8
writing file '/./redis.conf', ret = 106526
./hello_world_file.txt, 20110354 (size 10)
open /./hello_world_file.txt
ret = 9
writing file '/./hello_world_file.txt', ret = 10
./22.txt, 201103d8 (size 8)
open /./22.txt
ret = 10
writing file '/./22.txt', ret = 8
., 20110450 (size 0)
ready to start uros2 not implemented srand
not implemented rand
Forced TCP: 192.168.159.19 8888, fd=4 2
not implemented freeaddrinfo
uros2/rclc/rclc/src/rclc/timer.c 35 1 0x200773d5
uros2/rcl/rcl/src/rcl/timer.c 178 1 0x200773d5 1 0x200773d5
tag = 1
RCLC 2fffbe10 1
265 200773d5 1
297 2fffbe10 1 200773d5 1
Timer callback executed. Last time 1002279000
RCLC 2fffbe10 1
265 200773d5 1
297 2fffbe10 1 200773d5 1
Timer callback executed. Last time 999028000
RCLC 2fffbe10 1
265 200773d5 1
297 2fffbe10 1 200773d5 1
Timer callback executed. Last time 1000038000
RCLC 2fffbe10 1
265 200773d5 1
297 2fffbe10 1 200773d5 1
Timer callback executed. Last time 1001442000
RCLC 2fffbe10 1
265 200773d5 1
297 2fffbe10 1 200773d5 1
Timer callback executed. Last time 1001179000
RCLC 2fffbe10 1
265 200773d5 1
297 2fffbe10 1 200773d5 1
Timer callback executed. Last time 997252000
RCLC 2fffbe10 1
265 200773d5 1
297 2fffbe10 1 200773d5 1
Timer callback executed. Last time 1000189000
```

## Known Issues 

uROS has hardcoded address of the node: 

```
./uros2/micro_ros_intravisor/libmicroros/include/rmw_microxrcedds_c/config.h:    #define RMW_UXRCE_DEFAULT_IP "192.168.159.19"
./uros2/micro_ros_intravisor/libmicroros/include/rmw_microxrcedds_c/config.h:    #define RMW_UXRCE_DEFAULT_IP "192.168.159.19"
```

The address should be changed 