#ifndef STACK_H
#define STACK_H 

#define MAXSIZE 5
struct stack 
{
	char key_[MAXSIZE];
	int top_;
};
typedef struct stack stack_t;

void init_stack(stack_t *ptr_stack);
void deinit_stack();
void push(stack_t *ptr_stack, char ch);
char pop(stack_t *ptr_stack);
int is_empty(stack_t *ptr_stack);
int is_full(stack_t *ptr_stack);


#endif