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
	// int error_check;
	char receivedMsg[256];
	char sentMsg[256];
	int error = 100;

	s = socket(AF_INET, SOCK_STREAM, 0);

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

	error = listen(s, 1);

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

	while(1)
	{
        recv(c, receivedMsg, sizeof(receivedMsg), 0);

        printf("Client: %s", receivedMsg);
        printf("Server: ");

        fgets(sentMsg, sizeof(sentMsg), stdin);


        if (strncmp(sentMsg, "bye", 3) == 0)
        {
            break;
        }

		send(c, sentMsg, sizeof(sentMsg), 0);
        // write(c, sentMsg, strlen(sentMsg));
       
	}


}