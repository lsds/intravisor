make
$HOME/cheri/output/morello-sdk/bin/strip --strip-debug libu_first.so 
cp ./libu_first.so $HOME/cheri/output/e/
echo "starting objdump"
$HOME/cheri/output/morello-sdk/bin/objdump -DS libu_first.so > 1.txt
