#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


int main() {
	stack* s = stack_create(5);
	int i = 0;
	while (i < 2) {
		int a = i;
		stack_push(s, &a);
		i++;
	}

	while (stack_top(s) != NULL) {
		printf("top = %d\n", *(int*)stack_top(s));
		stack_pop(s);
	}

	stack_destroy(s);
	return 0;
}
