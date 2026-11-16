#include <stdio.h>
#include "stack.h"

// check well formed
int main()
{
	char str[MAXSIZE + 1]; char *s = str;
	int is_valid = 1;
	scanf("%s", str);
	printf("input expression : :%s:\n", s);
	stack_t mystack;
	init_stack(&mystack);
	//(())()(())
	char ch;
	while( is_valid && (ch = *s++) != '\0')
	{
		if(ch == '(')
		{
			push(&mystack, 'x');
		}
		else if(ch == ')')
		{
			if(! is_empty(&mystack))
				pop(&mystack);
			else 
				is_valid = 0;
		}
	}
	if(is_valid && is_empty(&mystack))
	{
		printf("Well formed expression\n");
	}
	else 
	{
		printf("not well formed expression\n");
	}
	deinit_stack(&mystack);
	
}