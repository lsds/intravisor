make
cp ./libsco_libos.so ${HOME}/cheri/output/e/
cp ./*.yaml ${HOME}/cheri/output/e/
${HOME}/cheri/output/sdk/bin/objdump -DS libsco_libos.so > 1.txt