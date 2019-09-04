#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <netdb.h>
#include <string.h>

int main(){

	struct sockaddr_in sa;
	int i;
	int client_fd;
	char buff[100];
	

	int server_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	fcntl(server_fd,F_SETFL, O_NONBLOCK);

	//socklen_t len;

	if (server_fd==-1){
		perror("Cannot create socket ");
		exit(EXIT_FAILURE);
	}
	printf("Socket creation success\n");

	memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(6000);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_fd,(struct sockaddr *)&sa, sizeof sa) == -1) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    } 
    printf("bind success\n");
    

    if(listen(server_fd, 10) == -1) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("listen success\n");

    while(1){

    	//clientfd is lastfd
    	client_fd = accept(server_fd, NULL, NULL);

    	if(client_fd==-1){
            // perror("accept failed");
            // exit(EXIT_FAILURE);
        }
        else
        {
        	//printf("%d\n",client_fd );
        	fcntl(client_fd, F_GETFL, O_NONBLOCK);
        }

		// printf("Accept success\n");
		
		
    	for(i = server_fd+1; i<=client_fd; i++){
    		if(read(i,buff,100)!=-1)
    		{
    			printf("%s\n",buff );
    		}
    	}
    }
   
    close(server_fd);


}