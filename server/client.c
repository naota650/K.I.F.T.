#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 8080

int main()
{
	int client_fd;
	int new_socket;
	struct sockaddr_in address;
	struct sockaddr_in cli;

	//create socket fd
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	else
		printf("socket created\n");

	bzero(&address, sizeof(address));

	//asign IP, Port
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(PORT);

	//connect the cli socket to server socket
	if(connect(client_fd, (struct sockaddr*)&address, (socklen_t)sizeof(address)) != 0)
	{
		perror("Connection with server failed\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("Connected to the server\n");

	close(client_fd);
}
