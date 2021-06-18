#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


stack* stack_create(size_t size) {
	stack* s = (stack*) malloc(sizeof(stack));
	s->size = size;
	s->arr = (void**)calloc(size, sizeof(void*));
	s->top = 0;
	s->is_empty = 1;
	return s;
}

void stack_destroy(stack* s) {
	free(s->arr);
	free(s);
}

int stack_push(stack *s, void *elem) {
	if (s->top >= s->size-1) {
		return -1;
	}

	if (s->is_empty == 1) {
		s->arr[s->top] = elem;
		s->is_empty = 0;
	} else {
		s->top++;
		s->arr[s->top] = elem;
	}

	return 0;
}

void stack_pop(stack* s) {
	s->arr[s->top] = NULL;
	if (s->top > 0) {
		s->top--;
	} else {
		s->is_empty = 1;
	}
}

void* stack_top(stack* s) {
	return s->arr[s->top];
}
