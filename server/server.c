#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
	int server_fd;
	int new_socket;
	int len;
	int opt = 1;
	struct sockaddr_in address;
	struct sockaddr_in cli;

	//creates socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	else
		printf("socked created\n");
	bzero(&address, sizeof(address));
	//assign  IP, PORT


	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);
	
	//binding newly created socket to given iP and verification
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) != 0)
	{
		perror("socket bind has failed\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("socket successfully binded\n");

	//close(server_fd);
	//return 0;

	//Now server is ready to listen and verifcation
	if ((listen(server_fd, 5)) != 0)
	{
		printf("Listen failed\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("Server is listening\n");

	len = sizeof(cli);

	//Accept the data packet from client and verification
	new_socket = accept(server_fd, (struct sockaddr*)&cli, (socklen_t*)&len);
	if (new_socket < 0)
	{
		printf("Server accept failed\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("Server accept the client\n");

	//Closes socket after done
	close(server_fd);

	return 0;
}
