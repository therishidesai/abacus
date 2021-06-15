#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#define BUFFER_SIZE 1024


// TODO: return operator type
int is_operator(char op) {
	int ret_val = 0;
	switch(op) {

	case '(' :
		ret_val = 6;
		break;
	case ')' :
		ret_val = 5;
		break;
	case '*' :
		ret_val = 4;
		break;
	case '/' :
		ret_val = 3;
			break;
	case '+' :
		ret_val = 2;
			break;
	case '-' :
		ret_val = 1;
			break;
	default :
		ret_val = 0;
	}

	return ret_val;
}

// TODO: Have this return a data structure of the parsed input.
void parse_input(const char *input) {
	long int num;
	while (input != NULL && *input != '\0') {
		if (isdigit(*input)) {
			num = strtol(input, &input, 10);
			printf("%ld\n", num);
		} else if (is_operator(*input)) {
			printf("%c\n", *input);
			++input;
		} else {
			++input;
		}
	}
}

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
			} else {
				parse_input(input);
			}
		} else {
			printf("BYE!\n");
			exit_flag = 1;
		}
	}

	return 0;
}
