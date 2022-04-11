# MUSL-LKL runtime


## Content 

```
 ├── apps             # various native applications for LKL-MUSL
 ├── lkl              # LibraryOS (LKL)
 ├── lkl_loader       # init for LKL-MUSL and hostcall interface (cVM side)
 ├── musl-host        # musl for cross-compiling (host system)
 ├── musl-target      # musl for LKL-MUSL cVM
 └── tools            # compiling tools
```

## how to build

```
make
```

After the compilation, copy the runtime binary (`build/libmusl-lkl.so`) together with your application (`apps/any`) to a CHERI-enabled platform
