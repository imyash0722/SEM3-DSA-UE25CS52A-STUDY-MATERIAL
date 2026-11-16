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
	disp_preorder(&t1);
	disp_postorder(&t1);
	disp_inorder(&t1);
	deinit(&t1);
	
	tree_t t2;
	init(&t2);
	int a2[] = {10, 20, 30, 40, 50, 60, 70};
	int n2 = 7;
	for(int i = 0; i < n2; ++i)
	{
		insert(&t2, a2[i]);
	}
	disp_preorder(&t2);
	disp_postorder(&t2);
	disp_inorder(&t2);
	deinit(&t2);

}