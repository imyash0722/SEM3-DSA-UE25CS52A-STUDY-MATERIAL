#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void init_stack(stack_t *ptr_stack)
{
	ptr_stack->top_ = NULL;
}

void deinit_stack(stack_t *ptr_stack)
{
	while(! is_empty(ptr_stack))
	{
		pop(ptr_stack);
	}
	ptr_stack->top_ = NULL;
}

void push(stack_t *ptr_stack, char ch)
{
	
	if(! is_full(ptr_stack))
	{
		node_t* temp = (node_t*)malloc(sizeof(node_t));
		temp->key_ = ch;
		temp->next_ =ptr_stack->top_;
		ptr_stack->top_ = temp;
	}	
	else 
	{
		printf("stack full; cannot push\n");
	}
}
char pop(stack_t *ptr_stack)
{
	if(! is_empty(ptr_stack))
	{
		char ch;  node_t* temp = ptr_stack->top_;
		ch = temp->key_;
		ptr_stack->top_ = temp->next_;
		free(temp);
		return ch;
	}
	else 
	{
		printf("stack empty; cannot pop\n");
		return '\0';
	}
}
int is_full(stack_t *ptr_stack)
{
    node_t* temp;
	temp = (node_t*)malloc(sizeof(node_t));
    if (temp == NULL) {
        return 1; 
    }
    free(temp);   
    return 0;
}
 
int is_empty(stack_t *ptr_stack)
{
	return ptr_stack->top_ == NULL;
}