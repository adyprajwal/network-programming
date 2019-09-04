#include <sys/types.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <pthread.h>

int main()
{
	struct  sockaddr_in sa;
	int server_fd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(server_fd==-1)
	{
		return 1;
	}	
	memset(&sa,0,sizeof(struct sockaddr_in));
	sa.sin_family = PF_INET;
	sa.sin_port = htons(6767);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(server_fd, (struct sockaddr *)&sa, sizeof(struct sockaddr_in))==-1)
	{
		perror("bind failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	if(listen(server_fd,10)==-1)
	{
		perror("listen failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	pid_t pid;
	
	while(1)
	{
		struct sockaddr_in ca;
		memset(&ca,0,sizeof(struct sockaddr_in));
		socklen_t ca_len;

		int client_fd = accept(server_fd,NULL,NULL);
	
		if(client_fd<0)
		{
			perror("accept failed");
			close(server_fd);
			exit(EXIT_FAILURE);
		}	
		else
		{
			
	      	pid= fork();
	      	if(pid==-1)
	      	{
	      	perror("cannot fork");
			// exit(EXIT_FAILURE);
	      	}
	      	else
	      	{
	      		printf("%u\n",getpid() );
	      		char *buffer=malloc(100*sizeof(char));

				memset(buffer,0,100*sizeof(char));
				int readbytes=read(client_fd,buffer,100*sizeof(char));

				if(readbytes==-1)
				{
					perror("read failed");
				}
				else
				{
					for(int i=0;i<readbytes;i++)
					{
						printf("%c",*(buffer+i));
					}
					printf("\n");
					if(write(client_fd,buffer,readbytes)==-1)
					{
						perror("write failed");
					
					}	
				}
	      	}

		}
	}
	
	
	

}
