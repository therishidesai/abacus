#ifndef STACK_H
#define STACK_H

typedef struct {
	size_t size;
	size_t id;
	void **arr;
	void *top;
} stack;

stack* stack_create(size_t size);
int stack_push(stack *s, void *elem);
void stack_pop(stack *s);
void* stack_top(stack *s);

#endif
