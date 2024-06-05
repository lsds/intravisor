make -C ../../
rm -rf ./*.so
make

$HOME/cheri/output/morello-sdk/bin/strip --strip-debug *.so 


cp *.so $HOME/cheri/output/e/
cp *.yaml $HOME/cheri/output/e/

echo copied

$HOME/cheri/output/morello-sdk/bin/objdump -DS *.so > 1.txt
#scp -r $HOME/cheri/output/e/* root@192.168.159.13:/e/


