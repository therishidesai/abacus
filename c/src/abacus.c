#include <stdio.h>
#include "test.h"
#define BUFFER_SIZE 1024


int main() {
	int exit_flag = 0;

	test_hello();
	printf("Welcome to the C Abacus.\n Supported operators +, -, /, *, ().\n");
	printf("Does integer math :(.\n");
	
	while (exit_flag != 1) {
		printf("abacus> ");

		// NOTE: Could add logic to handle inputs longer than 1024, but that takes time lol
		char input[BUFFER_SIZE];
		if (fgets(input, BUFFER_SIZE, stdin) != NULL){
			printf("abacus out> %s", &input);
			if (strcmp(input, "exit\n") == 0) {
				printf("BYE!\n");
				exit_flag = 1;
			}
		} else {
			printf("BYE!\n");
			exit_flag = 1;
		}
	}

	return 0;
}
