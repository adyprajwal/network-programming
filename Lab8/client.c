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
    //const char *servIP = "localhost"; //SOCK_STREAM
    char * buffer = "hello";
    int client_fd = socket(PF_INET,SOCK_STREAM, IPPROTO_TCP);
    
    if(client_fd==-1){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    
    sa.sin_family=PF_INET;
    sa.sin_port = htons(6000);
    inet_pton(PF_INET, "192.168.1.73", &sa.sin_addr);
    
    int res = connect(client_fd, (struct sockaddr *)&sa, sizeof(struct sockaddr_in));
    
    if(res== -1){
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    int wr = write(client_fd, buffer, sizeof(buffer));
        //read and write operation here
        if(wr == sizeof(buffer)){
            printf("Message sent to server successfully\n");
        }
        if ( wr == -1){
            printf("Could not write data to buffer\n");
        }
}
