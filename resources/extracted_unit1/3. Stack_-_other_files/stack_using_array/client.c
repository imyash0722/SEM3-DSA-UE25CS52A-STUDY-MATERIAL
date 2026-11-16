#include <stdio.h>
#include "stack.h"

// reverse a string using a stack 
int main()
{
	char str[MAXSIZE + 1]; char *s = str;
	// NOT SAFE if string longer than the available size in 
	//	the array
	scanf("%s", str);
	printf("input string : :%s:\n", s);
	stack_t mystack;
	init_stack(&mystack);
	char ch;
	while( (ch = *s++) != '\0')
	{
		printf("test : pushing %c\n", ch);
		push(&mystack, ch);
	}
	printf("Reversed string : ");
	while(! is_empty(&mystack))
	{
		putchar(pop(&mystack));
	}
	deinit_stack(&mystack);
	
}