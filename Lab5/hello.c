#include <stdio.h>
main(int arg, char const *args[]) {
	//printf("Hello World\n", args[1]);
	int j;
	for(j = 0; j < arg; j++) {
		printf("%s\n", args[j]);
	}
}