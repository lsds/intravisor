make
$HOME/cheri/output/morello-sdk/bin/strip --strip-debug libfirst.so
mkdir -p $HOME/cheri/output/e/
cp ./libfirst.so $HOME/cheri/output/e/
cp ./*.yaml $HOME/cheri/output/e/
echo "starting objdump"
$HOME/cheri/output/morello-sdk/bin/objdump -DS libfirst.so > 1.txt
