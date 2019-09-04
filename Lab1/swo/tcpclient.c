//Implement connection oriented service using TCP socket
#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	//address of socket where we want to connect. Specify an address for the socket
	struct sockaddr_in sa;

	//create socket
	//integer to hold socket descriptor
	int client_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (client_fd == -1){
		perror("can not create socket");
		exit(EXIT_FAILURE);
	}
	//fill memory with a constant byte
	memset(&sa, 0, sizeof(struct sockaddr_in));
	 
	sa.sin_family = AF_INET;
	sa.sin_port = htons(8000); 								    //host byte order to network byte order short
	//sa.sin_addr.s_addr = htonl(INADDR_ANY);					//sin_addr is struct itself that holding the address itself

	inet_pton(AF_INET, "192.168.1.65",&(sa.sin_addr));			//convert IPv4 and IPv6 addresses from text to binary form


	//connect - initiate a connection on a socket
	int connection_status = connect(client_fd, (struct sockaddr *)&sa, sizeof(struct sockaddr_in));			//need to pass a pointer and size of sa
	if(connection_status == -1){
		perror("Connection to server failed");
		close(client_fd);
		exit(EXIT_FAILURE);
	}
	close(client_fd);
	return 0;
}