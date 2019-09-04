//Implement connection oriented service using TCP socket
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	struct sockaddr_in sa;
	//create server socket
	int server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_fd == -1)
	{
		perror("can not create socket");
		exit(EXIT_FAILURE);
	}
	printf("socket create success\n");


	//server address
	
	memset(&sa, 0, sizeof(struct sockaddr_in));
	sa.sin_family = AF_INET;		//address family
	sa.sin_port = htons(8000);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);	

	//bind a name to a socket. bind() assigns the address specified by addr to the socket referred to by the file descriptor sockfd.
	if(bind(server_fd, (struct sockaddr *)&sa, sizeof(struct sockaddr_in))== -1)
	{
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}
	printf("Success binding\n");
	
	// listen - for connections on a socket
	if(listen(server_fd,5)==-1)				//5 is the backlog which is no of connection can be waiting for particular socket at one point of time
	{
		perror("Listen failed");
		exit(EXIT_FAILURE);
	}
	printf("Success listening\n");

	//accept- when we accept the connection we get back the client socket that we are writing to
	while(1){
		//int client = accept(server_fd,(struct sockaddr *)&sa, sizeof(sockaddr_in));

		int client_fd = accept(server_fd, NULL, NULL);
		
		if(client_fd <0)
		{
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        printf("Success Accept\n");
     
       //read and write
	}
	close(server_fd);
	return 0;
}	
