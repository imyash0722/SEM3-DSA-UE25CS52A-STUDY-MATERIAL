#include <stdio.h>
#include "heap.h"

int main()
{
	// 0th element not used
	int a[] = { -1, 20, 10, 40, 30, 15, 25, 35};
	int n = 7;
	heap_t h;
	init(&h);
	printf("building heap\n");
	build_heap(&h, a, n);
	printf("displaying heap\n");
	disp(&h);
	deinit(&h);
}