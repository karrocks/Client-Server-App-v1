#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
	int serverSocketFd, clientSocketFd;
	struct sockaddr_in serverAddress, clientAddress;
	int clientAddressLength;

	serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocketFd == -1)
	{
		printf("failed socket");
		exit(1);
	}

	printf("Socket created\n");

	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl (INADDR_ANY);
	serverAddress.sin_port = htons(9818);

	if(bind(serverSocketFd, (struct sockaddr*)&serverAddress, sizeof(serverAddress))!= 0){
		printf("Failed bind\n");
		exit(1);
	}

	printf("Binded\n");

	if(listen(serverSocketFd, 1)!=0){
		printf("Failed to listen\n");
		exit(1);
	}

	printf("Listening...\n");

	bzero(&clientAddress, sizeof(clientAddress));

	clientSocketFd = accept(serverSocketFd, (struct sockaddr*)&clientAddress, &clientAddressLength);

	if(clientSocketFd == -1){
		printf("Failed to accept\n");
		exit(1);
	}

	printf("Accepted\n");

	char* msg = "Yeahhhhhhhh";
	write(clientSocketFd, msg, strlen(msg));

	printf("sent : \"%s\"\n", msg);

	close(clientSocketFd);
	close(serverSocketFd);
	printf("socket closed");
	return 0;
}