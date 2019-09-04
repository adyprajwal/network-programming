//Implementing conection oriented service using TCP socket

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>


int main(void)
{
    struct sockaddr_in sa;
    struct sockaddr_storage ss_gen;
    
    int server_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    socklen_t len;
    
    if (server_fd == -1) {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    } 
    printf("socket create success\n");

    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(8000);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_fd,(struct sockaddr *)&sa, sizeof sa) == -1) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    } 
    printf("bind success\n");
    
    
    if(getsockname(server_fd, (struct sockaddr *)&ss_gen, &len)>=0)
    {
        //int getnameinfo(const struct sockaddr *sa, socklen_t salen,
        //           char *host, size_t hostlen,
        //           char *serv, size_t servlen, int flags);
        
        
        char hoststr[NI_MAXHOST];
        char portstr[NI_MAXSERV];
        
        int rc = getnameinfo((struct sockaddr *)&ss_gen, 
            sizeof(struct sockaddr_storage), hoststr, sizeof(hoststr), portstr, sizeof(portstr), 
            NI_NUMERICHOST | NI_NUMERICSERV);

        if (rc == 0) 
            printf("server socket listening at %s:%s\n", hoststr, portstr);
        //printf("server local address: \n");
        //printf("server local port: %n\n", ntohs(sa_local.sin_port));
    }
    
    if(listen(server_fd, 10) == -1) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("listen success\n");
    
    struct sockaddr_in ca;
    int* ca_len;
    
    while(1){
        //int client_fd = accept(server_fd, (struct sockaddr *)&ca, ca_len);
        int client_fd = accept(server_fd, NULL, NULL);
        
        if(client_fd<0){
            perror("accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        // thread 
        printf("connection accepted\n");
        printf("read/write process started\n");
        
        //read and write
        int res = close(client_fd);
        if(res==-1){
            perror("close failed");
            exit(EXIT_FAILURE);
        }
        perror("connection closed");
    }
}

    
    
