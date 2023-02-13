make
/Users/sartakov/cheri/output/morello-sdk/bin/strip --strip-debug libsco_redis.so 
cp ./libsco_redis.so /Users/sartakov/cheri/output/e/
cp ./*.yaml /Users/sartakov/cheri/output/e/
echo "starting objdump"
/Users/sartakov/cheri/output/morello-sdk/bin/objdump -DS libsco_redis.so > 1.txt
