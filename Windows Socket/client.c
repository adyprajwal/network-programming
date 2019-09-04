#define NO_ERROR -1
#include <stdio.h>
#include <stdlib.h>
#include "winsock2.h"


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2,2),&wsaData);
	
	if(result != NO_ERROR){	
		printf("error");
	}
else{
	printf("WSAStartup sucess");
}

SOCKET m_socket;
m_socket = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
if(m_socket == INVALID_SOCKET)
{
	printf(" socket error");
	WSACleanup();
	exit(EXIT_FAILURE);
}

struct sockaddr_in sa;

sa.sin_family= PF_INET;
sa.sin_port = htons(8000);
sa.sin_addr.s_addr = inet_addr("192.168.1.72");

if(sa.sin_addr.s_addr == INVALID_SOCKET){
	printf("port/ ip error");
	WSACleanup();
	exit(EXIT_FAILURE);
}

int res = connect(m_socket, (struct sockaddr *)&sa, sizeof(struct sockaddr_in));

if(res == SOCKET_ERROR){
	printf("connect error");
	WSACleanup();
	exit(EXIT_FAILURE);
}

//Write 
//read

	return 0;
}
