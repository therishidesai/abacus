#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


int main() {
	stack *s = stack_create(5);
	int i = 0;
	while (i < 2) {
		int *a = (int*)malloc(sizeof(int));
		*a = i;
		stack_push(s, a);
		i++;
	}

	while (stack_top(s) != NULL) {
		int *top = (int*)stack_top(s);
		printf("top = %d\n", *top);
		free(top);
		stack_pop(s);
	}

	stack_destroy(s);
	return 0;
}
