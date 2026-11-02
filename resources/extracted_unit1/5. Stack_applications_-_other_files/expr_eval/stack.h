#ifndef STACK_H
#define STACK_H 

#define MAXSIZE 100
struct stack 
{
	int key_[MAXSIZE];
	int top_;
};
typedef struct stack stack_t;

void init_stack(stack_t *ptr_stack);
void deinit_stack();
void push(stack_t *ptr_stack, int key);
int pop(stack_t *ptr_stack);
int is_empty(stack_t *ptr_stack);
int is_full(stack_t *ptr_stack);


#endif