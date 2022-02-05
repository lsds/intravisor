#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <poll.h>
#include <assert.h>

#define IOCTL_CF_SET_CAP	0x4004e200
#define IOCTL_CF_SET_SIZE	0x4004e201
#define IOCTL_CF_ADV		0x4004e202
#define IOCTL_CF_PRB		0x4004e203
#define IOCTL_CF_SET_MODE	0x4004e204


#define IOCTL_CS_SET_CAP	0x4004e400
#define IOCTL_CS_SET_SIZE	0x4004e401
#define IOCTL_CS_ADV		0x4004e402
#define IOCTL_CS_PRB		0x4004e403
#define IOCTL_CS_SET_MODE	0x4004e404
#define IOCTL_CS_REG_BUF	0x4004e405
#define IOCTL_CS_WAIT		0x4004e406
#define IOCTL_CS_SPIN_READ	0x4004e407

//#define FAST

#define MAX_SIZE (4*1024*1024)
int size = MAX_SIZE;

__attribute__((aligned(4096))) char ptr[MAX_SIZE];
__attribute__((aligned(4096))) char dnull[MAX_SIZE];

void *s_send(void *args) {
		int err;
		int ret;
		printf("Testing CF_STREAMs SEND thread, ptr = %p, dnull = %p\n", ptr, dnull);

		int fd_out = open("/cap/ch2", O_RDWR);
		if(!fd_out) {
			printf("cannot open /cap/s2\n"); while(1);
		} else
			printf("fd_out = %d\n", fd_out);

		char key2[10]="key1";
		err = ioctl(fd_out, IOCTL_CS_PRB, key2);
		if (err != 0) {
			printf( "Error: ioctl %d  %s\n", __LINE__, strerror(err));
			while(1);
		}

		int i = 0;
		while(1) {
			int ts = snprintf(dnull, size, "send %d", i++);
			write(fd_out, dnull, (ts/16+1)*16);
		}
}

void *s_recv(void *args) {
		struct timeval t_end, *t_start, t_start2;

		int fd;
		int err;
		int ret;
		printf("Testing CF_STREAMs RECV thread, ptr = %p, dnull = %p\n", ptr, dnull);

//register recv buffer 
		int fd_in = open("/cap/ch1", O_RDWR);
		if(!fd_in) {
			 printf("cannot open /cap/ch1\n"); while(1);
		} else
			printf("fd_in = %d\n",fd_in);

		err = ioctl(fd_in, IOCTL_CS_SET_SIZE, size);
		if (err != 0) {
			printf( "Error: ioctl %d  %s\n", __LINE__, strerror(err));
			while(1);
		}

		err = ioctl(fd_in, IOCTL_CS_REG_BUF, ptr);
		if (err != 0) {
			printf( "Error: ioctl %d  %s\n", __LINE__, strerror(err));
			while(1);
		}

		char key[10]="key1";
		err = ioctl(fd_in, IOCTL_CS_ADV, key);
		if (err != 0) {
			printf( "Error: ioctl %d  %s\n", __LINE__, strerror(err));
			while(1);
		}

		int i = 0;
		while(1) {
			err = ioctl(fd_in, IOCTL_CS_WAIT, ptr);
			if (err != 0) {
				printf( "Error: ioctl %d  %s\n", __LINE__, strerror(err));
				while(1);
			}

			printf("%d:\trecv = '%s'\n", i++, ptr);

			memset(ptr, 0, size);
			err = ioctl(fd_in, IOCTL_CS_REG_BUF, ptr);
			if (err != 0) {
				printf( "Error: ioctl %d  %s\n", __LINE__, strerror(err));
				while(1);
			}
		}
}


int main (int argc, char *argv[]) {
	pthread_attr_t attr;
	int rc, ret, err;
	long t;
	void *status;
	struct timeval t_start, t_end;

//	void *ptr = malloc(size);
//	void *dnull = malloc(size);

	int test = 0;
	if(argc > 1)
		test = argv[1][0] - '0';
	else {
		printf("1 -- CF_Stream,	single\n");
		printf("2 -- CF_Stream, 2 thread\n");
		printf("3 -- CF_Stream, 1 recv thread\n");
		printf("4 -- CF_Stream, 1 send thread\n");
		exit(0);
	}

	if(test == 1) {
		printf("Testing CF_STREAMs, single thread\n");

//register recv buffer 
		int fd1 = open("/cap/ch1", O_RDWR);
		if(!fd1) {
			 printf("cannot open /cap/ch1\n"); while(1);
		}

		err = ioctl(fd1, IOCTL_CS_SET_SIZE, size);
		if (err != 0) {
			printf( "Error: ioctl %d  %s\n", __LINE__, strerror(err));
			while(1);
		}

		memset(ptr, 0, size);
		err = ioctl(fd1, IOCTL_CS_REG_BUF, ptr);
		if (err != 0) {
			printf( "Error: ioctl %d  %s\n", __LINE__, strerror(err));
			while(1);
		}

		char key[10]="key1";
		err = ioctl(fd1, IOCTL_CS_ADV, key);
		if (err != 0) {
			printf( "Error: ioctl %d  %s\n", __LINE__, strerror(err));
			while(1);
		}

		printf("RECV:\tclear ('%s') and publish ptr(%p) with key '%s' via /cap/ch1 \n", ptr, ptr, key);

		close(fd1);

//sender side
		int fd2 = open("/cap/ch2", O_RDWR);
		if(!fd2) {
			printf("cannot open /cap/ch2\n"); while(1);
		}

		char key2[10]="key1";
		err = ioctl(fd2, IOCTL_CS_PRB, key2);
		if (err != 0) {
			printf( "Error: ioctl %d  %s\n", __LINE__, strerror(err));
			while(1);
		}

		#define MSG	"text for ptr"
		int ssize = snprintf(dnull, size, MSG);
		printf("SEND:\tsending ptr (%p) with '%s' via /cap/ch2 (%d)\n", dnull, dnull, fd2);
		write(fd2, dnull, (ssize/16+1)*16); //capcopy is doubleword, so the size should be aligned

		close(fd2);

		fd1 = open("/cap/ch1", O_RDWR);
		if(!fd1) {
			  printf("cannot open /cap/ch1\n"); while(1);
		}

		err = ioctl(fd1, IOCTL_CS_WAIT, 0); //here could be *size as arg
		if (err != 0) {
			printf( "Error: ioctl %d  %s\n", __LINE__, strerror(err));
			while(1);
		}

		printf("RECV:\tCheck ptr (%p) after wait: '%s'\n", ptr, ptr);
	}

	if(test == 2 ) {

		pthread_t thread_recv;
		rc = pthread_create(&thread_recv, NULL, s_recv, NULL);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			perror("pthread_create");
			exit(-1);
		}

		pthread_t thread_send;
		rc = pthread_create(&thread_send, NULL, s_send, NULL);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			perror("pthread_create");
			exit(-1);
		}

		pthread_join(thread_recv, NULL);
	}


	if(test == 3 ) {

		pthread_t thread_recv;
		rc = pthread_create(&thread_recv, NULL, s_recv, NULL);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			perror("pthread_create");
			exit(-1);
		}
//		pthread_join(thread_recv, NULL);
		exit(0);
	}

	if(test == 4) {
		pthread_t thread_send;
		rc = pthread_create(&thread_send, NULL, s_send, NULL);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			perror("pthread_create");
			exit(-1);
		}

		pthread_join(thread_send, NULL);
	}
}
