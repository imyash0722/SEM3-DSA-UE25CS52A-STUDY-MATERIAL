#ifndef STACK_H
#define STACK_H 
#define MAXSIZE 100
struct node
{
	char key_;
	struct node* next_;
};
typedef struct node node_t;

struct stack 
{
	node_t* top_;
};
typedef struct stack stack_t;

void init_stack(stack_t *ptr_stack);
void deinit_stack();
void push(stack_t *ptr_stack, char ch);
char pop(stack_t *ptr_stack);
int is_empty(stack_t *ptr_stack);
int is_full(stack_t *ptr_stack);


#endif