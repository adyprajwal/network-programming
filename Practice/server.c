#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include <arpa/inet.h>

main() {
	int sock, cli;
	struct socketaddr_in server, client;
	unsigned int len;
	char msg[] = "Welcome!";
	int sent;

	if(sock = socket(AF_INET, SOCK_STREAM, 0)==-1) {
		perror("Socket: ");
		exit(-1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(10000);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 8);

	len = sizeof(struct sockaddr_in);
	if((bind(sock, (struct sockaddr *)&server, len)) == -1) {
		perror("Bind: ");
		exit(-1);
	}

	if ((listen(sock, 5)) == -1) {
		perror("Listen: ");
		exit(-1);
	}

	while(1) {
		if((cli == accept(sock, (struct sockaddr *)&client, &len)) == -1) {
			perror("accept");
			exit(-1);
		}

		sent = send(cli, msg, strlen(msg), 0);
		printf("Sent %d bytes to client: %s\n", sent, inet_ntoa(client.sin_addr));
		close(cli);
	}
}