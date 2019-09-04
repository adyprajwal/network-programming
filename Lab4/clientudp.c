//Implement Concurrent Echo Server using UDP


#include<stdio.h>
#include<sys/un.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
 
int main(){
	int sockfd, len;
	struct sockaddr_in serveraddr, cliaddr;
	
	char buffer[1024];
	
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	//serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(6767);
	inet_pton(AF_INET, "192.168.100.8",&serveraddr.sin_addr);	
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
//	if (sockfd == -1) 
//        perror("ERROR opening socket");	
//        exit(0);
//	}
		
	size_t n;
	len = sizeof(serveraddr);
	
	while(1){
		//char *buffer=malloc(100*sizeof(char));
//		n= recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in));
//		
//		if(n<0){
//			perror("receive error");
//			close(sockfd);
//        	exit(1);
//		}
//		printf("DATA RECEIVED = %s\n", buffer);

		bzero(buffer, sizeof(buffer));
		
		n = sendto(sockfd, "Client msg.\n", 12, 0, (struct sockaddr *)&serveraddr, len);
		
		if(n<0){
			perror("sending error");
			close(sockfd);
        	exit(1);
		}
		else{
			printf("DATA SENT, %ld bytes\n",n);
		}		
		
		n= recvfrom(sockfd, buffer, 18, 0, (struct sockaddr *)&serveraddr, &len);
		
		if(n<0){
			perror("receive error");
			close(sockfd);
        	exit(1);
		}
		
		else{
			printf("DATA RECEIVED = %s\n", buffer);
		}
		
		exit(0);
	}
	
	return 0;
}
