#include <stdio.h>
#include "stack.h"


stack* stack_create(size_t size) {
	stack* s = (stack*) malloc(sizeof(stack));
	s->size = size;
	s->arr = (void**)calloc(size, sizeof(void*));
	s->top = s->arr[0];
	s->id = 0;
	return s;
}

int stack_push(stack *s, void *elem) {
	if (s->id >= s->size) {
		return -1
	}

	s->arr[s->id] = elem;
	s->top = elem;
	s->id++;
	return 0;
}

void stack_pop(stack* s) {
	s->arr[s->id] = NULL;
	if (s->id > 0) {
		s->id--;
		s->top = s->arr[s->id];
	}
}

void* stack_top(stack* s) {
	return s->top;
}
