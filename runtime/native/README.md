

##

|                 				| ARM-H | RISC-V-H | ARM-P | RISC-V-P | ARM-O | RISC-V-O |
|:---------------:				|:-----:|:--------:|:-----:|:--------:|:-----:|:--------:|
| Intravisor 					|   Y   |    Y     |   Y   |    Y     |   Y   |          |
| [hello world](./hello_world)       		|   Y   |    Y     |       |          |       |          |
| [Two Pure](./two-pure)       			|       |          |   Y   |    Y     |       |          |
| [ORC hello](./orc-hello)       		|       |          |   O   |    O     |   O   |     O    |

#### Legend
Y: supported and tested

N: cannot be supported by design

P: partially supported (or supported but pointless)

O: outdated and needs an update

ARM-H: Arm hybrid/native

RISC-V-H: RISC-V64 hybrid/native

ARM-P: Arm pure-cap

RISC-V-P: RISC-V64 pure-cap

ARM-O: Arm pure-cap with ORC support

RISC-V-O: RISC-V64 pure-cap with ORC support
