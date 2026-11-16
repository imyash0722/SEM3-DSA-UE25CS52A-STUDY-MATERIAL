#include <stdio.h>
#include "stack.h"

// evaluate expression in postfix
int main()
{
	char str[MAXSIZE + 1]; char *s = str;
	gets(str);
	printf("input expression : :%s:\n", s);
	stack_t mystack;
	init_stack(&mystack);
	
	char ch;
	int val1; int val2;
	int val = 0;
	int is_num = 0;
	while( (ch = *s++) != '\0')
	{
		if(ch == '+' || ch == '-' || ch == '*' || ch == '/')
		{
			val1 = pop(&mystack);
			val2 = pop(&mystack);
			switch(ch)
			{
				case '+' : push(&mystack,val2 + val1);
					   break;
				case '-' : push(&mystack,val2 - val1);
					   break;
				case '*' : push(&mystack,val2 * val1);
					   break;
				case '/' : push(&mystack,val2 / val1);
					   break;
			}
		}
		else if(ch >= '0' && ch <= '9')
		{
			is_num = 1;
			val = val * 10 + ch - '0';
		}
		else if (ch == ' ' && is_num)
		{
			printf("pushing %d\n", val);
			push(&mystack, val);
			val = 0;
			is_num = 0;
		}
	}
	printf("result : %d\n", pop(&mystack));
	deinit_stack(&mystack);
	
}