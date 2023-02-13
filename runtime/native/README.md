



### 

|                 				| ARM | ARM SIM | ARM HYB | ARM ORC | RISC-V | RISC-V HYB | RISC-V SIM | RISC-V ORC |
|:---------------:				|:---:|:-------:|:-------:|:-------:|:------:|:----------:|:----------:|:----------:|
| Intravisor 					| Y   |         |         | Y       | Y      |            |            |            |
| [two pure](two-pure/) 			| Y   |         | N       | N       |        |            |            | N          |
| [ffmpeg 1x1](orc-ffmpeg/4.ffmpeg_x1)       	| Y   |         |         |         |        |            |            |            |
| [ffmpeg 2x1-4](orc-ffmpeg/5.ffmpeg_x2)       	| Y   |         |         | Y       |        |            |            |            |
| [SCO/ORC example](orc-hello/)		       	| P   |         |         | Y       |        |            |            |            |
| SQLite 1x-5x               			|     |         |         |         |        |            |            |            |
| [SQLite RISC-V](sqlite_riscv/)               	|     |         |         |         | Y      |            |            |            |
| [Redis](redis/4.redis_x1)         		| Y   |         |         |         |        |            |            |            |
| [micro ROS](uros2/4.uros2_x1/uros2)           | Y   |         |         |         |        |            |            |            |
|                 				|     |         |         |         |        |            |            |            |
|                 				|     |         |         |         |        |            |            |            |
|                 				|     |         |         |         |        |            |            |            |

#### Legend
Y: supported and tested

N: cannot be supported by design

P: partially supported (or supported but pointless)

ARM: Arm pure-cap

RISC-V: RISC-V64 pure-cap