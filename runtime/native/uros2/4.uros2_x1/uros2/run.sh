make
$HOME/cheri/output/morello-sdk/bin/strip --strip-debug libsco_uros2.so 
cp ./libsco_uros2.so $HOME/cheri/output/e/
cp ./*.yaml $HOME/cheri/output/e/
echo "starting objdump"
$HOME/cheri/output/morello-sdk/bin/objdump -DS libsco_uros2.so > 1.txt
#scp -r $HOME/cheri/output/e root@192.168.159.22:/