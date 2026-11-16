#include <stdio.h>
#include "stack.h"

// check well formed brackers {[(
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
			push(&mystack, ')');
		}
		else if(ch == '[')
		{
			push(&mystack, ']');
		}
		else if(ch == '{')
		{
			push(&mystack, '}');
		}
		else if(ch == ')' || ch == ']' || ch == '}')
		{
			if(! is_empty(&mystack))
			{
				if(ch != pop(&mystack))
				{
					is_valid = 0;
				}
			}
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