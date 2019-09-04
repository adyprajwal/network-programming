//Implement Concurrent echo server using TCP client
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){

	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, 0, sizeof(struct sockaddr_in));
	serverAddr.sin_family = PF_INET;
	serverAddr.sin_port = htons(6767);
	//serverAddr.sin_addr.s_addr = inet_addr("192.168.49.1");
	
	inet_pton(PF_INET, "192.168.100.8",&(serverAddr.sin_addr));

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");
	
	int r,w;

	while(1){
		printf("Client: \t");
		scanf("%s", &buffer[0]);
		//send(clientSocket, buffer, strlen(buffer), 0);
		w= write(clientSocket, buffer, strlen(buffer));

		if(strcmp(buffer, ":exit") == 0){
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}

		r= read(clientSocket, buffer, 1024);
		if(r < 0){
			printf("[-]Error in receiving data.\n");
		}else{
			printf("Server: \t%s\n", buffer);
		}
		bzero(buffer, sizeof(buffer));
	}

	return 0;
}
