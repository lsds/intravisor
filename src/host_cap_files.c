#include "monitor.h"

#define CF_NAME_LEN		10
#define MAX_CF_FILES	10

struct cap_files_store_s {
	void *ptr;
	void *loc;
	char name[CF_NAME_LEN];
	int size;
};

static struct cap_files_store_s cap_files[MAX_CF_FILES];
static pthread_mutex_t cf_store_lock;


void init_cap_files_store() {
	memset(cap_files, 0, MAX_CF_FILES*sizeof(struct cap_files_store_s));

	if (pthread_mutex_init(&cf_store_lock, NULL) != 0) {
		printf("\n mutex init failed\n");
		while(1);
	}

}

/**
\brief Hostcall function to 'advertise' a shared buffer. Intravisor creates a record inside a cap_file_store about published buffer: key, address, size
\param[in] ptr beginning of the advertised buffer
\param[in] size size of the buffer
\param[in] key identifier of the buffer
\param[out] ret: index in the table. not used anymore
*/
int host_cap_file_adv(void *ptr, long size, char *key) {
#ifdef CF_DEBUG
	printf("CF_ADV: %p, %ld, %s\n", ptr, size, key);
#endif
	pthread_mutex_lock(&cf_store_lock);
	int i = 0;
	for(i = 0; i < MAX_CF_FILES; i++) {
		if(cap_files[i].ptr == 0)
			break;
	}
	
	if(i == MAX_CF_FILES) {
		printf("need more cap streams/files, die\n");
		while(1);
	}

	cap_files[i].ptr = ptr;
	cap_files[i].size = size;
	snprintf(cap_files[i].name, CF_NAME_LEN, "%s", key);

	pthread_mutex_unlock(&cf_store_lock);

#ifdef CF_DEBUG
	printf("MON: CF[%d] %p %s %d\n", i, cap_files[i].ptr, cap_files[i].name, cap_files[i].size);
#endif
	return i;
}

/**
\brief Hostcall function to 'probe' a shared buffer. Intravisor retrives a shared buffer, creates a capability, and stores it at location
\param[in] key Indentifier of the shared buffer
\param[in] location address inside cVM where to store the capability
\param[in] size address inside cVM where to store the size of the buffer
\param[out] ret: always 0
*/
int host_cap_file_prb(char *key, void *location, long *size) {
//todo: We should check that location and size are located inside the cVM that issued host_cap_file_prb 
#ifdef CF_DEBUG
	printf("MON: CF: probe for key %s, store at %p\n", key, location);
#endif
	pthread_mutex_lock(&cf_store_lock);
	int i;
	for(i = 0; i < MAX_CF_FILES; i++) {
		if(strncmp(cap_files[i].name, key, CF_NAME_LEN) == NULL)
			break;
	}
	
	if(i == MAX_CF_FILES) {
		printf("wrong cap key %s ", key); while(1);
		
	}

	host_reg_cap(cap_files[i].ptr, cap_files[i].size, location);
	if(size) 
		*size = cap_files[i].size;
	cap_files[i].loc = location;

	pthread_mutex_unlock(&cf_store_lock);
	return 0;
}

/**
\brief Hostcall function to destroy a shared buffer (capfile)
\param[in] key Indentifier
\param[out] ret: always 0
*/
int host_cap_file_revoke(char *key) {
#ifdef CF_DEBUG
	printf("MON: CF: revoke cap file with key %s\n", key);
#endif
	pthread_mutex_lock(&cf_store_lock);
	int i;
	for(i = 0; i < MAX_CF_FILES; i++) {
		if(strncmp(cap_files[i].name, key, CF_NAME_LEN) == NULL)
			break;
	}
	
	if(i == MAX_CF_FILES) {
		printf("wrong cap key %s ", key); while(1);
	}

	host_purge_cap(cap_files[i].loc);

	memset(cap_files[i].name, 0, CF_NAME_LEN);
	cap_files[i].size = 0;
	cap_files[i].loc = 0;
	cap_files[i].ptr = 0;

	pthread_mutex_unlock(&cf_store_lock);

//todo: remove the original cap from the CPU contextes of threads inside cVM
	return 0;
}

