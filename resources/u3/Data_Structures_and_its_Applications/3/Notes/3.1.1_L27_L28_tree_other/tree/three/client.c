#include <stdio.h>
#include "tree.h"

int main()
{
	tree_t t1;
	init(&t1);
	int a1[] = {40, 20, 60, 10, 70, 30, 50};
	int n1 = 7;
	for(int i = 0; i < n1; ++i)
	{
		insert(&t1, a1[i]);
	}
	disp(&t1);
	
	tree_t t2;
	init(&t2);
	copy(&t1, &t2);
	disp(&t2);
	printf("same : %d\n", are_same(&t1, &t2));
	
	tree_t t3;
	init(&t3);
	int a3[] = {10, 20, 30, 40, 50, 60, 70};
	int n3 = 7;
	for(int i = 0; i < n3; ++i)
	{
		insert(&t1, a3[i]);
	}
	printf("same : %d\n", are_same(&t1, &t3));
	
	
	
	#if 0
	// case 1
	tree_t t1;
	init(&t1);
		int a1[] = {40, 20, 60, 10, 70, 30, 50};
	int n1 = 7;
	for(int i = 0; i < n1; ++i)
	{
		insert(&t1, a1[i]);
	}
	disp(&t1);
	
	// added 
	printf("# of nodes : %d\n", number_of_nodes(&t1));
	printf("# of leaves : %d\n", number_of_leaves(&t1));
	
	deinit(&t1);
	
	// case 2
	tree_t t2;
	init(&t2);
	
	int a2[] = {10, 20, 30, 40, 50, 60, 70};
	int n2 = 7;
	for(int i = 0; i < n2; ++i)
	{
		insert(&t2, a2[i]);
	}
	disp(&t2);	

	// added
	printf("# of nodes : %d\n", number_of_nodes(&t2));
	printf("# of leaves : %d\n", number_of_leaves(&t2));

	deinit(&t2);
	
	// case 3
	tree_t t3;
	init(&t3);
	disp(&t3);	
	
	// added
	printf("# of nodes : %d\n", number_of_nodes(&t3));
	printf("# of leaves : %d\n", number_of_leaves(&t3));
	
	deinit(&t3);
	#endif
}