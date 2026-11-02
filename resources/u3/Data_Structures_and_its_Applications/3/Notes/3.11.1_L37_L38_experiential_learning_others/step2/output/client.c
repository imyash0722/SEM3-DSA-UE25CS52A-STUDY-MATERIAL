#include <stdio.h>
#include "heap.h"
int max (int x, int y)
{
	return x > y;
}
int min (int x, int y)
{
	return x < y;
}
int main()
{
	int opt;
	printf("1: max heap 2: min heap : ");
	scanf("%d", &opt);
	heap_t h;
	if(opt == 1)
	{
		init(&h, max);
	}
	else 
	{
		init(&h, min);
	}

	int key;
	printf("opt : 1 insert; 2 : delete; 0 : exit : ");
	scanf("%d", &opt);
	while(opt)
	{
		switch(opt)
		{
			case 1 : 	scanf("%d", &key);
						insert(&h, key);
						disp(&h);
						break;
			case 2 : 	key = delete_max(&h);
						printf("deleted : %d\n", key);
						disp(&h);
						break;
		}
		
		printf("opt : 1 insert; 2 : delete; 0 : exit : ");
		scanf("%d", &opt);
	}
	deinit(&h);
}