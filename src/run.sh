make

$HOME/cheri/output/morello-sdk/bin/objdump -DS intravisor > 1.txt
$HOME/cheri/output/morello-sdk/bin/strip --strip-debug intravisor
cp intravisor $HOME/cheri/output/e/
#scp -r $HOME/cheri/output/e/* root@192.168.159.10:/e/