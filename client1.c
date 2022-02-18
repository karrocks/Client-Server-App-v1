#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // for close
#include <string.h>
#include <arpa/inet.h>



int main()
{
	int c;
	struct sockaddr_in serverAd;

	c = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serverAd, sizeof(serverAd));
	serverAd.sin_family = AF_INET;
	serverAd.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAd.sin_port = htons(9818);

	if(connect(c, (struct sockaddr*)&serverAd, sizeof(serverAd))!=0)
	{
		printf("Connection failed\n");
		exit(1);
	}

	char buf[128];
	
	read(c, buf, 128);
	
	printf("%s", buf);
	

	close(c);

}