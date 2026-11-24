#ifndef STACK_H
#define STACK_H 
#include "trie.h"
#define STACK_MAXSIZE 20
struct stack 
{
	node_t* key_[STACK_MAXSIZE];
	int top_;
};
typedef struct stack stack_t;

void init_stack(stack_t *ptr_stack);
void deinit_stack(stack_t *ptr_stack);
void push(stack_t *ptr_stack, node_t* ch);
node_t* pop(stack_t *ptr_stack);
int is_empty(stack_t *ptr_stack);
int is_full(stack_t *ptr_stack);


#endif