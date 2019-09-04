#include <stdio.h>
#include <stdlib.h>
#include "winsock2.h"
int main()
{
	// int a = SOCKET_ERROR;
	// printf("SOCKET_ERROR = %d", a);
	WSADATA wsadata;

	int result = WSAStartup(MAKEWORD (2,2), & wsadata);
	if (result != NO_ERROR)
		printf("ERROr");
 		
	SOCKET c_socket;
	c_socket = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
	if (c_socket == INVALID_SOCKET){
		printf("error");
		// printf(WSAGETLASTERROR());
		// WSACleanUp(); 		
	}

	struct sockaddr_in sa;
	sa.sin_family =AF_INET;
	sa.sin_port = htons(6789);
	sa.sin_addr.s_addr = inet_addr("192.168.0.153");


	

}

