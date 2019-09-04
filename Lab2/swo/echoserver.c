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
	char buff[255];

	int server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(server_fd==-1){
		perror("socket creation failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	memset(&sa, 0, sizeof(struct sockaddr_in));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(8000);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(server_fd, (struct sockaddr*)&sa, sizeof(struct sockaddr_in))==-1){
		perror("bind failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	if(listen(server_fd,10)==-1){
		perror("listen failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("Listening to  connections..\n");

	while(1){
		int client_fd = accept(server_fd,NULL,NULL);
		if(client_fd<0){
			printf("Could not accept requests\n");
			exit(EXIT_FAILURE);
		}
		else{
			memset(buff, 0, sizeof(buff));
			//bzero(buff,100);
			int r = read(client_fd,buff,sizeof(buff));
			if(r ==-1){
				printf("Error reading data from client\n");
			}
			printf("Messsage from Client: %s\n", buff );

			int res = close(client_fd);
	        if(res==-1){
	            perror("close failed");
	            exit(EXIT_FAILURE);
			}
		
		}
	}

return 0;
}