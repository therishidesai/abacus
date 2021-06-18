#ifndef STACK_H
#define STACK_H

typedef struct {
	size_t is_empty;
	size_t size;
	size_t top;
	void **arr;
} stack;

stack* stack_create(size_t size);
void stack_destroy(stack* s);
int stack_push(stack *s, void *elem);
void stack_pop(stack *s);
void* stack_top(stack *s);

#endif
