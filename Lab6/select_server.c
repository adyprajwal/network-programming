// WAP to demonstrate use of select function
#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
	int i;
	char buff[200];
	int client_fd[3];	
	int max_fd = 0;
	fd_set set;
	// FD_ZERO (&set);
	int select_value;
	
	struct sockaddr_in sa;
	
	int server_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_fd == -1){
		perror("can not create socket");
		exit(EXIT_FAILURE);
	}
	printf(" Creating Socket\n");

	memset(&sa, 0, sizeof(struct sockaddr_in));
	sa.sin_family = PF_INET;
	sa.sin_port = htons(8000);
	(sa.sin_addr).s_addr = htonl(INADDR_ANY);
	
	if(bind(server_fd, (struct sockaddr *)&sa, sizeof(struct sockaddr_in))){
		perror("Error binding\n");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("Bind Successful \n");
	if(listen(server_fd, 1) < 0 ){
		perror("Listen Failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("Listening \n");
	
//	struct sockaddr_in ca;
//	int* ca_len;
	
	

	for(i=0; i<3; i++)
	{
    	client_fd[i] = accept(server_fd, NULL, NULL);

    	 if(client_fd[i]<0){
            perror("accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
    	if (client_fd[i]> max_fd){
    		max_fd = client_fd[i];
    	}
    	printf("Accept Request\n");
    }
    int c;
	while(1){
		for(i=0; i<3; i++)
		{
			FD_SET(client_fd[i], &set);
		}

		int selected = select(max_fd+1,&set,NULL,NULL,NULL);		//check for arrived incoming message 
		if(selected == -1)
		{
			perror("Error in select");
		}
		else
		{
			for(i=0; i<3; i++){
				if(FD_ISSET(client_fd[i], &set)){		
					if(read(client_fd[i], buff, sizeof(buff)) == -1){
						perror("read failed");
					}
					else{
						printf("Messsage is: %s \n", buff );
					}
					
						
				}			
				
			}
		}
	break;
		
	}
return 0;
}


	
