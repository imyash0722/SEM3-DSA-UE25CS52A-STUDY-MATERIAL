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

// -----------------
// node 
node_t* copy_recursive(node_t* ptr_src)
{
	node_t *temp;
	if(ptr_src != NULL)
	{
		temp = (node_t*)malloc(sizeof(node_t));
		temp->key_ = ptr_src->key_;
		temp->left_ = copy_recursive(ptr_src->left_);
		temp->right_ = copy_recursive(ptr_src->right_);
		return temp;
	}
	else 
	{
		return NULL;
	}
}

// tree 
void copy(tree_t* ptr_src, tree_t* ptr_dst)
{
	ptr_dst->root_ = copy_recursive(ptr_src->root_);
}
// node 
int are_same_recursive(node_t* root1, node_t* root2)
{
	if(root1 == NULL && root2 == NULL)
		return 1;
	else if(root1 == NULL || root2 == NULL)
		return 0;
	else 
		return root1->key_ == root2->key_ &&
			are_same_recursive(root1->left_, root2->left_) &&
			are_same_recursive(root1->right_, root2->right_);
}
// tree 
int are_same(tree_t* ptr_tree1, tree_t* ptr_tree2)
{
	return are_same_recursive(ptr_tree1->root_, ptr_tree2->root_);
}