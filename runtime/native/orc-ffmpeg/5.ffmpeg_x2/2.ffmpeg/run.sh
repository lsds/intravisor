make
$HOME/cheri/output/morello-sdk/bin/strip --strip-debug libu_ffmpeg.so 
cp ./libu_ffmpeg.so $HOME/cheri/output/e/
echo "starting objdump"
$HOME/cheri/output/morello-sdk/bin/objdump -DS libu_ffmpeg.so > 1.txt
