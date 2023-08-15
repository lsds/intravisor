# HelloWorld with CAP_File

Similarly to the baremetal example, we access shared data via capabilitites.
However, this time, the interaction with capabilitites are hiden by a CAP_File. 
It provides POSIX read/write/llseek API and internally uses cap-aware instructions. 

In the example, we read and write data allocated by Intravisor (following the deployment scenario) via CAP_File.


## Expected output

```
<... lkl boot ...>
---------------------------------
device is open: CAPFILE
fd = 3
MON: probe for key test1, store at 0x2ce18e20
read 32 bytes ('Hello world
') from cap_file with key 'test1'
let's write 'cap filler
' into cap_file and read result back
wrote 12 bytes
read 32 bytes ('cap filler
') from cap_file with key 'test1'
EXIT IS CALLED
```