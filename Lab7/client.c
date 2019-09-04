#include <sys/types.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


int main(int argc, char const *argv[])
{
	struct sockaddr_in sa;

	const char *servIP = "192.168.100.8";
	char *buffer = "Welcome";


	
	struct in_addr* addrptr = malloc(sizeof(struct in_addr));
	int a = inet_aton(servIP, addrptr);

 	int client_fd= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 	if(client_fd==-1){
 		printf("failed to connect socket");
 		 exit(EXIT_FAILURE);
 	}

 	memset(&sa,0,sizeof(struct sockaddr_in)); // set zero
	sa.sin_family= AF_INET;
	sa.sin_port = htons(6767);
	/*sa.sin_addr.s_addr=htonl(INADDR_ANY);*/
	inet_pton(AF_INET, servIP,&sa.sin_addr);

	printf("success creating \n");
	if(connect(client_fd, (struct sockaddr *)&sa, sizeof(struct sockaddr_in)) == -1 ){
		perror("Accept Request failed");
		close(client_fd);
		exit(EXIT_FAILURE);
	}
	else{
		int write_operation = write(client_fd, buffer, sizeof(buffer));
		if(write_operation==-1)
		{
			printf("Couldnot write the message");
		}
		else
		{
		printf("Writed the message succesfully\n");	
		close(client_fd);
//		exit(0);
		}	
	}

	//while(1){}
	
	// if(wr == 100){
	// 	printf("write success\n");
	// }

	// if(wr == -1){
	// 	printf("failed\n");
	// }
return 0;
}
