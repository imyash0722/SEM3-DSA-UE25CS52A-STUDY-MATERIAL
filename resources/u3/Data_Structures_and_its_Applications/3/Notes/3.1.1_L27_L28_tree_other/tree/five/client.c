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

	disp_inorder(&t1);
	// delete a leaf 
	delete_key(&t1, 10);
	printf("after deleting 10 : ");
	disp_inorder(&t1);
	
	// delete a node with no left subtree
	delete_key(&t1, 20);
	printf("after deleting 20 : ");
	disp_inorder(&t1);

	delete_key(&t1, 60);
	printf("after deleting 60 : ");
	disp_inorder(&t1);
	
	delete_key(&t1, 40);
	printf("after deleting 40 : ");
	disp_inorder(&t1);
	
	delete_key(&t1, 70);
	printf("after deleting 70 : ");
	disp_inorder(&t1);
	
	delete_key(&t1, 50);
	printf("after deleting 50 : ");
	disp_inorder(&t1);
	
	delete_key(&t1, 30);
	printf("after deleting 30 : ");
	disp_inorder(&t1);
	
	deinit(&t1);
	


}