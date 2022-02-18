#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // for close
#include <string.h>

int main()
{
	int s, c;
	struct sockaddr_in serverAd, clientAd;
	int clientLen;

	s = socket(AF_INET, SOCK_STREAM, 0);

	if(s == -1){
		printf("socket creation failed\n");
		exit(1);
	}

	printf("Socket Created\n");
 
	int error;

	bzero(&serverAd, sizeof(serverAd));
	serverAd.sin_family = AF_INET;
	serverAd.sin_addr.s_addr = htonl (INADDR_ANY);
	serverAd.sin_port = htons(9818);


	error = bind(s, (const struct sockaddr*)&serverAd, sizeof(serverAd));

	if(error == -1)
	{
		printf("Failed to bind\n");
		exit(1);
	}

	printf("Bounded\n");

	error = listen(s, 2);

	if(error == -1)
	{
		printf("Failed to listen\n");
		exit(1);
	}

	printf("Listening...\n");

	bzero(&clientAd, sizeof(clientAd));

	c = accept(s, (struct sockaddr*)&clientAd, &clientLen);

	if(c == -1){
		printf("Failed to accept");
		exit(1);
	}

	printf("Accepted\n");

	char *msg = "Bro! it worked";

	write(c, msg, strlen(msg));

	printf("Sent\n");

	close(s);
	close(c);


}