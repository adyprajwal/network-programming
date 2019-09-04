#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(int arg, char *args[]) {
	printf("Parent Program running\n");
	int pid = fork();
	
	if(pid == -1)
		printf("Error\n");
	else if (pid == 0){
		char * args[] = { "./hello","apple", NULL};
		execvp(args[0], args);
	}
	printf("Parent Program Ended\n");
}