//local store for capabilitites, relative address usualy provided via AUX
unsigned long local_cap_store = 0xe001000;


// hostcalls

int host_write(char *ptr, int size);
int host_cap_prb(char *key, void *location, long *size);
void host_exit();
