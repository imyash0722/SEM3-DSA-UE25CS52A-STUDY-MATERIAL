#include <stdio.h>
#include "stack.h"

int main()
{
	int a[] = {10, 20, 30, 40};
	int n = 4;
	stack_t s;
	init_stack(&s);
	
	for(int i = 0; i < n; ++i)
	{
		push(&s, a[i]);
	}
	
	while(! is_empty_stack(&s))
	{
		printf("%d ", pop(&s));
	}
	printf("\n");
	deinit_stack(&s);
}