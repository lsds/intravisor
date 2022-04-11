# Runtimes

Intravisor provides two runtime environments: 

* [baremetal](runtime/baremetal) (native) doesn't have a libraryOS. baremetal cVMs directly use the hostcall interface to communicate with the Intravisor and other cVMs. Mostly, baremetal cVMs are used for developments, experiments, and testing of new features. 
* [MUSL-LKL](runtime/musl-lkl) runtime has a full-fledged library operating system inside and provides a Linux-compatible environment for programs.  
