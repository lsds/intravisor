#include <ctype.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

struct shmbuf {
	sem_t sem1;
	sem_t sem2;
	size_t cnt;
	char buf[128];
};

int shm_test(char * string, char * shmpath, int * pid) {
	int fd, cfd;
	int len = strlen(string);
	struct shmbuf *shmp, *cshmp;
	struct timespec stime;

	clock_gettime(CLOCK_REALTIME, &stime);
	stime.tv_sec += 1;

	// Create shared memory
	fd = shm_open(shmpath, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return 1;
	if (ftruncate(fd, sizeof(struct shmbuf)) == -1)
		return 2;

	shmp = mmap(NULL, sizeof(*shmp), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (shmp == MAP_FAILED)
		return 3;
	if (!__builtin_cheri_tag_get(shmp))
		return 4;
	if (sem_init(&shmp->sem1, 1, 0) == -1 || sem_init(&shmp->sem2, 1, 0) == -1)
		return 5;

	*pid = fork();
	if (*pid == 0) {
		// Forked process, new fd for shared memory
		cfd = shm_open(shmpath, O_RDWR, 0);
		if (cfd == -1)
			exit(11);

		cshmp = mmap(NULL, sizeof(*cshmp), PROT_READ | PROT_WRITE, MAP_SHARED, cfd, 0);
		if (cshmp == MAP_FAILED)
			exit(12);
		if (!__builtin_cheri_tag_get(shmp))
			exit(13);
		cshmp->cnt = len;
		memcpy(&cshmp->buf, string, len);

		if (sem_post(&cshmp->sem1) == -1)
			exit(14);
		if (sem_timedwait(&cshmp->sem2, &stime) == -1)
			exit(15);

		write(STDOUT_FILENO, &cshmp->buf, len);
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	} else {
		// Main process
		if (sem_timedwait(&shmp->sem1, &stime) == -1)
			return -1;
		for (int j=0;j< shmp->cnt;j++)
			shmp->buf[j] = toupper(shmp->buf[j]);
		if(sem_post(&shmp->sem2) == -1)
			return -1;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	int ret, pid = 0;
	char *shmpath = "sharemem";
	if (argc < 2)
		return -1;
	ret = shm_test(argv[1], shmpath, &pid);
	if (shm_unlink(shmpath))
		return 8;
	if (ret > 0)
		return ret;

	// Check status of forked process
	if (waitpid(pid, &ret, 0) == -1)
		return 9;
	if (WIFEXITED(ret))
		return WEXITSTATUS(ret);
	return -2;
}
