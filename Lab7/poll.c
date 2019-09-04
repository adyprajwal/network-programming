//WAP to demonstrate use of poll function and compare with select function.
#include <poll.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char buffer[100];
	int i;

	struct  sockaddr_in sa;
	int server_fd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(server_fd==-1) {
		perror("can not create socket");
		exit(EXIT_FAILURE);
	}	
	printf("Socket Created Successfully\n");

	memset(&sa,0,sizeof(struct sockaddr_in));
	sa.sin_family = PF_INET;
	sa.sin_port = htons(6767);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(server_fd, (struct sockaddr *)&sa, sizeof(struct sockaddr_in))==-1) {
		perror("bind failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("Bind Successful\n");

	if(listen(server_fd,10)==-1)
	{
		perror("listen failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("Listen Successful\n");

	// struct pollfd {
	//   int     fd;       /* descriptor to check */
	//   short   events;   /* events of interest on fd */
	//   short   revents;  /* events that occurred on fd */
	// };

	struct pollfd fds[3];

	for (int i = 0; i < 3; ++i)
	{
		fds[i].fd = accept(server_fd,NULL,NULL);
		fds[i].events = POLLIN; //POLLIN There is data to read. to see readiness of any incoming data
	}

	while(1){
		// int poll (struct pollfd *fdarray, unsigned long nfds, int timeout);
		// Returns: count of ready descriptors, 0 on timeout, –1 on error 

		int polled = poll(fds,3,0);		

		for(i=0; i<3; i++){
			if(fds[i].revents == POLLIN){
				//revents is an output parameter, filled by the kernel with the events that  actually  occurred.
				if(read(fds[i].fd, buffer, sizeof(buffer)) == -1){
					perror("read failed");
				}
				else{
					printf("Messsage is: %s \n", buffer);
				}
			}			
		}
		
		exit(0);	
	}

	return 0;
}
