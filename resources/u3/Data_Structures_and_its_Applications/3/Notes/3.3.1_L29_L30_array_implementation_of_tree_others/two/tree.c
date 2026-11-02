#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

// node functions 
static void disp_recursive(node_t elem[], int temp)
{
	if(temp != -1)
	{
		disp_recursive(elem, elem[temp].left_);
		printf("%d ", elem[temp].key_);
		disp_recursive(elem, elem[temp].right_);
	}
}

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
void disp(tree_t *ptr_tree)
{
	printf("Tree : ");
	disp_recursive(ptr_tree->elem_, ptr_tree->root_);
	printf("\n");
}
void insert(tree_t *ptr_tree, int key)
{
	if(ptr_tree->count_ == MAXSIZE)
	{
		printf("tree full\n");
		exit(1);
	}
	int temp = ptr_tree->count_++;
	ptr_tree->elem_[temp].key_ = key;
	ptr_tree->elem_[temp].left_ = ptr_tree->elem_[temp].right_ = -1;
	
	ptr_tree->root_ = insert_recursive(ptr_tree->elem_, ptr_tree->root_, temp);
}
//--------------------------------------
// adding 

// node 

int number_of_nodes_recursive(node_t elem[], int temp)
{
	if(temp == -1)
	{
		return 0;
	}
	else 
	{
		return 1 + number_of_nodes_recursive(elem, elem[temp].left_) 
			+ number_of_nodes_recursive(elem, elem[temp].right_);
	}
}

int number_of_leaves_recursive(node_t elem[], int temp)
{
	if(temp == -1)
	{
		return 0;
	}
	else if(elem[temp].left_ == -1 && elem[temp].right_ == -1)
	{
		return 1;
	}
	else
	{
		return number_of_leaves_recursive(elem, elem[temp].left_) 
			+ number_of_leaves_recursive(elem, elem[temp].right_);
	}
}

// tree 
int number_of_nodes(tree_t *ptr_tree)
{
	return number_of_nodes_recursive(ptr_tree->elem_, ptr_tree->root_);
}

int number_of_leaves(tree_t *ptr_tree)
{
	return number_of_leaves_recursive(ptr_tree->elem_, ptr_tree->root_);
}