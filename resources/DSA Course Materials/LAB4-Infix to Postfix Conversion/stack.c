#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void init_stack(stack_t *ptr_stack)
{
	ptr_stack->top_ = -1;
}

void deinit_stack(stack_t *ptr_stack)
{
	ptr_stack->top_ = -1;
}

void push(stack_t *ptr_stack, int index)
{
	if(! is_full(ptr_stack))
	{
		ptr_stack->key_[++ptr_stack->top_] = index;
	}
	else 
	{
		printf("stack full; cannot push\n");
	}
}
int pop(stack_t *ptr_stack)
{
	if(! is_empty(ptr_stack))
	{
		return ptr_stack->key_[ptr_stack->top_--];
	}
	else 
	{
		printf("stack empty; cannot pop\n");
		exit(1);
	}
}
int is_empty(stack_t *ptr_stack)
{
	return ptr_stack->top_ == -1;
}
int is_full(stack_t *ptr_stack)
{
	return ptr_stack->top_ + 1 == MAXSIZE;
}