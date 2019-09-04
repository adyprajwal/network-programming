//Implement a TCP echo server
#include <sys/types.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int client_fd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	struct sockaddr_in sa;

	if(client_fd<0)
	{
		perror("socket creation failed");
		close(client_fd);
		exit(EXIT_FAILURE);
	}

	

	memset(&sa,0,sizeof(struct sockaddr_in));
	sa.sin_family = PF_INET;
	sa.sin_port = htons(8000);
	
	char* ip_addr =" 192.168.100.8";
	int a=inet_pton(PF_INET,ip_addr,&sa.sin_addr);

	if(a==-1)
	{
		perror("ip address conversion failed");
		close(client_fd);
		exit(EXIT_FAILURE);
	}
	
	int res = connect(client_fd,(struct sockaddr *)&sa,sizeof(struct sockaddr_in));
	if(res==-1)
	{
		perror("connect failed");
		close(client_fd);
		exit(EXIT_FAILURE);
	}
	
	char* buffer="Hello";
	char* readbuffer=malloc(100*sizeof(char));
	int readbytes=0;

	if(write(client_fd,buffer,5*sizeof(char))==-1)
	{
		perror("write failed");
		
	}
	else
	{
		readbytes= read(client_fd,readbuffer,100*sizeof(char));
		if(readbytes==-1)
		{
			perror("read failed");
		}
		else
		{
			for(int i=0;i<readbytes;i++)
			{
				printf("%c",*(readbuffer+i));
			}
			printf("\n");
		}
		}

}