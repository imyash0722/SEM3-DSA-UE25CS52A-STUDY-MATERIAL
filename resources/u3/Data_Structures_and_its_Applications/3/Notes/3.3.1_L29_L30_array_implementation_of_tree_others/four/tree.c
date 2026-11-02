#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
// node functions 
static int insert_recursive(node_t elem[], int root, int temp)
{
	if(root == -1)
	{
		root = temp;
	}
	else if(elem[root].key_ > elem[temp].key_)
	{
		elem[root].left_ = insert_recursive(elem, elem[root].left_, temp);
	}
	else 
	{
		elem[root].right_ = insert_recursive(elem, elem[root].right_, temp);
	}
	return root;
}


// tree functions 
void init(tree_t *ptr_tree)
{
	ptr_tree->root_ = -1;
	ptr_tree->count_ = 0;
}
void deinit(tree_t *ptr_tree)
{
	ptr_tree->root_ = -1;
	ptr_tree->count_ = 0;
}

void insert(tree_t *ptr_tree, int key)
{
	if(ptr_tree->count_  == MAXSIZE)
	{
		printf("tree full\n");
		exit(1);
	}
	int temp = ptr_tree->count_++;
	ptr_tree->elem_[temp].key_ = key;
	ptr_tree->elem_[temp].left_ = ptr_tree->elem_[temp].right_ = -1;
	
	ptr_tree->root_ = insert_recursive(ptr_tree->elem_, ptr_tree->root_, temp);
}

static void disp_inorder_recursive(node_t elem[], int temp)
{
	if(temp != -1)
	{
		disp_inorder_recursive(elem, elem[temp].left_);
		printf("%d ", elem[temp].key_);
		disp_inorder_recursive(elem, elem[temp].right_);
	}
}
static void disp_preorder_recursive(node_t elem[], int temp)
{
	if(temp != -1)
	{
		printf("%d ", elem[temp].key_);
		disp_preorder_recursive(elem, elem[temp].left_);
		disp_preorder_recursive(elem, elem[temp].right_);
	}
}

static void disp_postorder_recursive(node_t elem[], int temp)
{
	if(temp != -1)
	{
		disp_postorder_recursive(elem, elem[temp].left_);
		disp_postorder_recursive(elem, elem[temp].right_);
		printf("%d ", elem[temp].key_);
	}
}

void disp_inorder(tree_t *ptr_tree)
{
	printf("Tree inorder: ");
	disp_inorder_recursive(ptr_tree->elem_, ptr_tree->root_);
	printf("\n");
}

void disp_preorder(tree_t *ptr_tree)
{
	printf("Tree preorder : ");
	disp_preorder_recursive(ptr_tree->elem_, ptr_tree->root_);
	printf("\n");
}

void disp_postorder(tree_t *ptr_tree)
{
	printf("Tree postorder: ");
	disp_postorder_recursive(ptr_tree->elem_, ptr_tree->root_);
	printf("\n");
}




