#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // for close
#include <string.h>

int main()
{
	int c;
	struct sockaddr_in serverAd;
	char receivedMsg[256];
	char sentMsg[256];
	int error = 100;


	c = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serverAd, sizeof(serverAd));

	serverAd.sin_family = AF_INET;
	serverAd.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAd.sin_port = htons(9818);

	error = connect(c, (struct sockaddr*)&serverAd, sizeof(serverAd));

	if (error == -1)
    {
        printf("There was an error making a connection to the remote socket\n\n");
    }

	while(1)
	{
        printf("Client: ");
        fgets(sentMsg, sizeof(sentMsg), stdin);

        send(c, sentMsg, sizeof(sentMsg), 0);


		recv(c, receivedMsg, sizeof(receivedMsg), 0);
        
        printf("Server: %s", receivedMsg);



        if (strncmp(sentMsg, "bye", 3) == 0)
        {
            break;
        }

	}
}