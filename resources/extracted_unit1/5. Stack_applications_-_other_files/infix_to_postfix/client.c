#include <stdio.h>
#include "stack.h"
int prec_in_str(char ch)
{
	int prec;
	switch(ch)
	{
		case '(' : prec = 3; break;
		case '*' :
		case '/' : prec = 2; break;
		case '+' :
		case '-' : prec = 1; break;
	}
	return prec;
}
int prec_in_stack(char ch)
{
	int prec;
	switch(ch)
	{
		case '(' : prec = 0; break;
		case '*' :
		case '/' : prec = 2; break;
		case '+' :
		case '-' : prec = 1; break;
	}
	return prec;
}
int main()
{
	char in[MAXSIZE + 1]; char *s = in;
	char post[MAXSIZE + 1]; char *p = post; 
	gets(in);
	printf("input expression : :%s:\n", s);
	stack_t mystack;
	init_stack(&mystack);
	
	char ch;
	char ch1;
	while( (ch = *s++) != '\0')
	{
		
		if(ch == ')')
		{
			while( (ch1 = pop(&mystack) ) != '(')
			{
				*p++ = ' ';
				*p++ = ch1;
			}
		}
		else if(ch == '(' || ch == '+' || ch == '-' ||
			ch == '*' || ch == '/')
		{
			if(is_empty(&mystack))
			{
				push(&mystack, ch);
			}
			else
			{
				while(!is_empty(&mystack) && 
					prec_in_str(ch) <= prec_in_stack(peek(&mystack)))
				{
					*p++ = ' ';
					*p++ = pop(&mystack);
					
				}
				push(&mystack, ch);
			}
		}
		else 
		{
			*p++ = ch;
		}
	}
	while(! is_empty(&mystack))
	{
		*p++ = ' ';
		*p++ = pop(&mystack);
	}
	*p = '\0';
	
	printf("infix : %s\n", in);
	printf("postfix : %s\n", post);
	deinit_stack(&mystack);
	
}