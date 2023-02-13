make
$HOME/cheri/output/morello-sdk/bin/strip --strip-debug libu_second.so 
cp ./libu_second.so $HOME/cheri/output/e/
echo "starting objdump"
$HOME/cheri/output/morello-sdk/bin/objdump -DS libu_second.so > 1.txt
