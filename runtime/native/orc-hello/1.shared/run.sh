make
$HOME/cheri/output/morello-sdk/bin/strip --strip-debug libshared.sco
mkdir -p $HOME/cheri/output/e/
cp ./libshared.sco $HOME/cheri/output/e/
cp ./*.yaml $HOME/cheri/output/e/
echo "starting objdump"
$HOME/cheri/output/morello-sdk/bin/objdump -DS libshared.sco > 1.txt
