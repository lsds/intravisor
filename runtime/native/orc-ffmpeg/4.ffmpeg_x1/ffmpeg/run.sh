make
$HOME/cheri/output/morello-sdk/bin/strip --strip-debug libsco_ffmpeg.so 
cp ./libsco_ffmpeg.so $HOME/cheri/output/e/
cp ./*.yaml $HOME/cheri/output/e/
echo "starting objdump"
$HOME/cheri/output/morello-sdk/bin/objdump -DS libsco_ffmpeg.so > 1.txt
