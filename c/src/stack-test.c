#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


int main() {
	stack* s = stack_create(5);
	int a = 1;
	int b = 2;
	stack_push(s, &a);
	stack_push(s, &b);
	printf("top = %d\n", *(int*)stack_top(s));
	stack_pop(s);
	printf("top = %d\n", *(int*)stack_top(s));
	stack_pop(s);
	if (stack_top(s) == NULL) {
		printf("EMPTY STACK!!");
	}
	stack_destroy(s);
	return 0;
}
