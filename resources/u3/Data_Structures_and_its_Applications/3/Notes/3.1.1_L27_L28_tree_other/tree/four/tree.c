#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
// node functions 


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

static void disp_recursive_preorder(node_t* temp)
{
	if(temp)
	{
		printf("%d ", temp->key_);
		disp_recursive_preorder(temp->left_);
		disp_recursive_preorder(temp->right_);
	}
}
static void disp_recursive_postorder(node_t* temp)
{
	if(temp)
	{
		disp_recursive_postorder(temp->left_);
		disp_recursive_postorder(temp->right_);
		printf("%d ", temp->key_);
	}
}
static void disp_recursive_inorder(node_t* temp)
{
	if(temp)
	{
		disp_recursive_inorder(temp->left_);
		printf("%d ", temp->key_);
		disp_recursive_inorder(temp->right_);
	}
}
void disp_preorder(tree_t *ptr_tree)
{
	printf("Tree preorder: ");
	disp_recursive_preorder(ptr_tree->root_);
	printf("\n");
}
void disp_postorder(tree_t *ptr_tree)
{
	printf("Tree postorder: ");
	disp_recursive_postorder(ptr_tree->root_);
	printf("\n");
}void disp_inorder(tree_t *ptr_tree)
{
	printf("Tree inorder: ");
	disp_recursive_inorder(ptr_tree->root_);
	printf("\n");
}
void insert(tree_t *ptr_tree, int key)
{
	node_t *temp = (node_t*)malloc(sizeof(node_t));
	temp->key_ = key;
	temp->left_ = temp->right_ = NULL;
	ptr_tree->root_ = insert_recursive(ptr_tree->root_, temp);
}


