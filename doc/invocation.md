


```

	                   Intravisor         cVM


                              │
                              │
                              │
                              │
                      cinv()  │
                              └───────────┐ outer_c:
                                          │
                                          │
                                          │
                                          │ host_write("HELLO\n", sizeof("HELLO\n"));
                                          │
                                          │
          hostcall_asm:       ┌───────────┘ c_out_3(1, ptr, size, 0);
                              │
                              │
                              │
 hostcall(1, ptr, size, ...)  │
                              │
     wrap_write(0, ptr, size) │
                              │
                              │
                              └───────────┐   ret_from_monitor:
                                          │
                                          │
                                          │
                                          ▼


```

Intravisor invokes cVM via `cinv(tp_args[0], &cinv_args)`. This function has two arguments. The first argument is the address of the location of capabilities (pointers) used for communication between Intravisor and the cVM. In Arm, the TP register points to the same location. However, RISC-V hybrid has an old ABI where this address is passed explicitly. The cVM must know this address; otherwise, it cannot use the hostcall interface. The address is computed as the bottom of memory reserved for stacks of threads plus 0x1000. Inside cVM, in pure-cap Arm and RISC-V, this address is provided via TP. In the hybrid MUSL-LKL, it is passed via the AUX structure or computed at compilation time. It may also be generated and loaded at runtime using Intravisor.

The second argument is a structure with caps (pointers) that must be stored by the `cinv()` function prior to switching into the cVM. Without these caps, the cVM cannot use the hostcall interface. The structure has 10 elements, although not all of them are actually used in a particular architecture. The `cinv()` function takes these pointers and stores them at specific offsets of the first argument. Later, the hostcall interface inside cVM loads these caps from known locations and uses them.

In essence, the arg structure contains:
0. Sealed PCC capability to the entrance function of a cVM (outer_c)
1. Sealed DDC of the cVM
2. Unsealed DDC
3. Sealed PCC capability to the Intravisor hostcall routine (tp_write)
4. Sealed DCC of Intravisor
5. Currently ignored
6. cVM's PCC that points to ret_from_mon
7. Stack pointer

The latter is very important: some architectures require explicit use of SP as a capability or SP as an offset to DDC. The `cinv()` function loads the SP prior to switching into the cVM. All other parts should handle SP properly during hostcalls/return procedures.

The `cinv` code reads arguments from the structure and puts them at predefined offsets. The offsets and capabilities (pointers), essentially, should not differ from those in `arm_sim` or `risc-v_sim`. In fact, Intravisor generates all `cinv()` arguments, and all that one needs is to put them properly at the proper offsets. 

On the other side, the `c_out()` routine loads capabilities (pointers) used for to perform a hostcall from the `local_cap_store` variable, which points precisely to the address used as the first argument of `cinv()`. 



