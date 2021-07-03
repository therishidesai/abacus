#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#define BUFFER_SIZE 1024

typedef enum op {NOP, ADD_SUB, MUL_DIV, R_PAREN, L_PAREN} op;

typedef struct {
	size_t is_op;
	long int value;
	char op_char;
} token;

op is_operator(char op) {
	enum op ret_val = NOP;
	switch(op) {

	case '(' :
		ret_val = L_PAREN;
		break;
	case ')' :
		ret_val = R_PAREN;
		break;
	case '*' :
	case '/' :
		ret_val = MUL_DIV;
		break;
	case '+' :
	case '-' :
		ret_val = ADD_SUB;
		break;
	default :
		ret_val = NOP;
	}

	return ret_val;
}

int parse_input(const char *input, token** postfix) {
	size_t i = 0;
	stack *s = stack_create(strlen(input));

	while (input != NULL && *input != '\0') {
		op o  = is_operator(*input);
		if (isdigit(*input)) {
			// put it in to out
			token *t = (token*)malloc(sizeof(token));
			t->is_op = 0;
			t->value = strtol(input, &input, 10);
			postfix[i] = t;
			i++;
		} else if (o != NOP) {
			token *top = (token*)stack_top(s);
			token *t = (token*)malloc(sizeof(token));
			t->is_op = 1;
			t->value = o;
			t->op_char = *input;

			if (top == NULL
				|| top->value == L_PAREN
				|| (t->value > top->value && t->value != R_PAREN)) {
				stack_push(s, t);
			} else if (o == R_PAREN) {
				while (!s->is_empty && ((token*)stack_top(s))->value != L_PAREN) {
					token *op = (token*)stack_top(s);
					if (op == NULL) {
						printf("ERROR Missing Left Paren!!!\n");
						return -1;
					}
					postfix[i] = op;
					stack_pop(s);
					i++;
				}

				// free R_PAREN
				free(t);
			} else {
				while (!s->is_empty && ((token*)stack_top(s))->value >= t->value) {
					token *op = (token*)stack_top(s);
					if (op == NULL) {
						printf("ERROR Missing Left Paren!!!\n");
						return -1;
					}
					postfix[i] = op;
					stack_pop(s);
					i++;
				}

				stack_push(s, t);
			}
			++input;
		} else {
			++input;
		}
	}

	while (stack_top(s) != NULL) {
		token *op = (token*)stack_top(s);
		if (op->value != L_PAREN && op->value != R_PAREN) {
			postfix[i] = op;
			i++;
		} else {
			// free the parens
			free(op);
		}
		stack_pop(s);
	}
	
	stack_destroy(s);
	return i;
}

int eval_postfix(const size_t size, token** postfix) {
	stack *s = stack_create(size);
	for (size_t i = 0; i < size; i++) {
		token* t = postfix[i];
		if (!t->is_op) {
			stack_push(s, t);
		} else {
			token* r = (token*)stack_top(s);
			if (r == NULL) {
				printf("Bad Input!\n");
				return -1;
			}
			stack_pop(s);
			token* l = (token*)stack_top(s);
			if (l == NULL) {
				printf("Bad Input!\n");
				return -1;
			}
			stack_pop(s);

			int new_val = 0;
			switch(t->op_char) {

			case '*' :
				new_val = l->value * r->value;
				break;
			case '/' :
				new_val = l->value / r->value;
				break;
			case '+' :
				new_val = l->value + r->value;
				break;
			case '-' :
				new_val = l->value - r->value;
				break;
			default :
				printf("Unsupported op %c\n", t->op_char);
			}

			token* n = (token*) malloc(sizeof(token));
			n->is_op = 0;
			n->value = new_val;
			stack_push(s, n);
			free(l);
			free(r);
			free(t);
		}
	}

	token* t = (token*)stack_top(s);
	int ret_val = t->value;
	free(t);
	stack_destroy(s);
	return ret_val;
}

int main() {
	int exit_flag = 0;

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
				token **postfix = (token**)calloc(strlen(input), sizeof(token*));
				int size = parse_input(input, postfix);
				if (size == -1) {
					printf("Bad Input!\n");
					for (size_t id = 0; id < size; id++) {
						free(postfix[id]);
					}
				} else {
					// eval postfix
					for (size_t id = 0; id < size; id++) {
						token *t = (token*)postfix[id];
						if (t->is_op) {
							printf("%c ", t->op_char);
						} else {
							printf("%d ", t->value);
						}
					}
					printf("\n");
					int ans = eval_postfix((size_t)size, postfix);
					printf("%d \n", ans);
				}

				free(postfix);
			}
		} else {
			printf("BYE!\n");
			exit_flag = 1;
		}
	}

	return 0;
}
