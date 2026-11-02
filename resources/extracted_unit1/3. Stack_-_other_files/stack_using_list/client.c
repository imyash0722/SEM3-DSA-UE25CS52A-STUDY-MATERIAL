#include <stdio.h>
#include "stack.h"

// reverse a string using a stack 
int main()
{
	char str[MAXSIZE + 1]; char *s = str;
	scanf("%s", str);
	printf("input string : :%s:\n", s);
	stack_t mystack;
	init_stack(&mystack);
	char ch;
	while( (ch = *s++) != '\0')
	{
		push(&mystack, ch);
	}
	printf("Reversed string : ");
	while(! is_empty(&mystack))
	{
		putchar(pop(&mystack));
	}
	deinit_stack(&mystack);
	
}