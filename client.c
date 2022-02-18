#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
	int socketFd;
	struct sockaddr_in serverAddress;

	socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFd == -1)
	{
		printf("failed socket");
		exit(1);
	}

	printf("Socket created\n");

	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddress.sin_port = htons(9818);

	if(connect(socketFd, (struct sockaddr*)&serverAddress, sizeof(serverAddress))!=0)
	{
		printf("Failed to connect\n");
		exit(1);
	}

	printf("Connected\n");

	char buf[128];
	read(socketFd, buf, 128);
	printf("recieved : %s\n", buf);

	close(socketFd);
	printf("socket closed");
	return 0;

}