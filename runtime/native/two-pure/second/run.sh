make
$HOME/cheri/output/morello-sdk/bin/strip --strip-debug libsecond.so 
cp ./libsecond.so $HOME/cheri/output/e/
cp ./*.yaml $HOME/cheri/output/e/
echo "starting objdump"
$HOME/cheri/output/morello-sdk/bin/objdump -DS libsecond.so > 1.txt
