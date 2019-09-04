//Implementing conection oriented service using TCP socket

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(void){
    
    struct sockaddr_in sa;
    int client_fd = socket(PF_INET,SOCK_STREAM, IPPROTO_TCP);
    
    if(client_fd==-1){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
 
    sa.sin_family=PF_INET;
    sa.sin_port = htons(8000);
    inet_pton(PF_INET, "192.168.100.8", &sa.sin_addr);
    
    int res = connect(client_fd, (struct sockaddr *)&sa, sizeof(struct sockaddr_in));
    
    if(res<0){
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
    
}
    
