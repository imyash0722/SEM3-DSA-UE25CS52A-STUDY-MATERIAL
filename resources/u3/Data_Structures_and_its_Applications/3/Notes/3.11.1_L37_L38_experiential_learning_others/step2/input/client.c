#include <stdio.h>
#include "heap.h"

int main()
{
	heap_t h;
	init(&h);
	int opt;
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