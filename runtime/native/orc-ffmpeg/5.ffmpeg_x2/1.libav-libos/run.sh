make
$HOME/cheri/output/morello-sdk/bin/strip --strip-debug libsco_av-os.so
cp ./libsco_av-os.so $HOME/cheri/output/e/
cp ./*.yaml $HOME/cheri/output/e/
echo "starting objdump"
$HOME/cheri/output/morello-sdk/bin/objdump -DS libsco_av-os.so > 1.txt
