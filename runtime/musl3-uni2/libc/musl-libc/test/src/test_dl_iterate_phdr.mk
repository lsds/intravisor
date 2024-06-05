src/test_dl_iterate_phdr-dynamic.exe: LDLIBS += -lstt-tls-symbol-lib -Lsrc/lib '-Wl,-rpath=$$ORIGIN/lib'
