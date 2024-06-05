#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	struct sockaddr_in saddr = {.sin_family = AF_INET, .sin_port = 12121};
	struct sockaddr * psaddr = (struct sockaddr *)&saddr;
	socklen_t addr_len = sizeof(saddr);
	int status, sockfd, clientfd, serverfd;
	const char * inband = "inband";
	const char * ooband = "out";
	const char * inbrec = "inbandou";
	const char * oobrec = "t";
	char buffer[25];

	pid_t pid;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return 1;

	if(bind(sockfd, (struct sockaddr *)&saddr, addr_len) == -1)
		return 2;

	if(listen(sockfd, 5) == -1)
		return 3;

	pid = fork();
	if (pid == 0){
		// Client
		if((clientfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
			exit(4);
		if(connect(clientfd, psaddr, addr_len) == -1)
			exit(5);

		send(clientfd, inband, strlen(inband), 0);
		send(clientfd, ooband, strlen(ooband), MSG_OOB);

		close(clientfd);
		exit(0);
	} else {
		// Server
		serverfd = accept(sockfd, psaddr, &addr_len);
		if(serverfd == -1)
			return 6;
		sleep(5);

		memset(buffer, 0, sizeof(buffer));
		if(sockatmark(serverfd) != 0)
			return 7;
		recv(serverfd, &buffer, sizeof(buffer), 0);
		if (memcmp(inbrec, buffer, strlen(inbrec)))
			return 8;

		memset(buffer,0,sizeof(buffer));
		if(sockatmark(serverfd) != 1)
			return 9;
		recv(serverfd, &buffer, sizeof(buffer), MSG_OOB);
		if (memcmp(oobrec, buffer, 1))
			return 10;

		close(serverfd);
		close(sockfd);
	}
	if (waitpid(pid, &status, 0) == -1)
		return -1;
	if (WIFEXITED(status))
		return WEXITSTATUS(status);
	return -2;
}
