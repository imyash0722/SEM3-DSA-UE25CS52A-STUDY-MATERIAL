#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
// node functions 
static void disp_recursive(node_t* temp)
{
	if(temp)
	{
		disp_recursive(temp->left_);
		printf("%d ", temp->key_);
		disp_recursive(temp->right_);
	}
}

static node_t* insert_recursive(node_t* root, node_t* temp)
{
	if(root == NULL)
	{
		root = temp;
	}
	else if(root->key_ > temp->key_)
	{
		root->left_ = insert_recursive(root->left_, temp);
	}
	else 
	{
		root->right_ = insert_recursive(root->right_, temp);
	}
	return root;
}

static void deinit_recursive(node_t* root)
{
	if(root)
	{
		deinit_recursive(root->left_);
		deinit_recursive(root->right_);
		free(root);
	}
}
// tree functions 
void init(tree_t *ptr_tree)
{
	ptr_tree->root_ = NULL;
}
void deinit(tree_t *ptr_tree)
{
	deinit_recursive(ptr_tree->root_);
	ptr_tree->root_ = NULL;
}
void disp(tree_t *ptr_tree)
{
	printf("Tree : ");
	disp_recursive(ptr_tree->root_);
	printf("\n");
}
void insert(tree_t *ptr_tree, int key)
{
	node_t *temp = (node_t*)malloc(sizeof(node_t));
	temp->key_ = key;
	temp->left_ = temp->right_ = NULL;
	ptr_tree->root_ = insert_recursive(ptr_tree->root_, temp);
}

//--------------------------------------
// adding 

// node 

int number_of_nodes_recursive(node_t* temp)
{
	if(temp == NULL)
	{
		return 0;
	}
	else 
	{
		return 1 + number_of_nodes_recursive(temp->left_) 
			+ number_of_nodes_recursive(temp->right_);
	}
}

int number_of_leaves_recursive(node_t* temp)
{
	if(temp == NULL)
	{
		return 0;
	}
	else if(temp->left_ == NULL && temp->right_ == NULL)
	{
		return 1;
	}
	else
	{
		return number_of_leaves_recursive(temp->left_) 
			+ number_of_leaves_recursive(temp->right_);
	}
}

// tree 
int number_of_nodes(tree_t *ptr_tree)
{
	return number_of_nodes_recursive(ptr_tree->root_);
}

int number_of_leaves(tree_t *ptr_tree)
{
	return number_of_leaves_recursive(ptr_tree->root_);
}