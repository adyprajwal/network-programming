//Implement a TCP echo server
#include <sys/types.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(){
	struct sockaddr_in sa;

	int client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(client_fd<0){
		perror("Failed to create socket\n");
		close(client_fd);
		exit(EXIT_FAILURE);
	}

	memset(&sa,0,sizeof(struct sockaddr_in));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(8000);
	int a = inet_pton(AF_INET, "192.168.100.8", &sa.sin_addr);

	printf("Success creating socket \n");
	if(a==-1)
	{
		perror("IP address conversion failed");
		close(client_fd);
		exit(EXIT_FAILURE);
	}

	if(connect(client_fd,(struct sockaddr *)&sa, sizeof(struct sockaddr_in)) == -1){
		perror("connect failed");
		close(client_fd);
		exit(EXIT_FAILURE);
	}
	char* buffer="hello";
	int wr = write(client_fd, buffer, sizeof(buffer));
	return 0;
}