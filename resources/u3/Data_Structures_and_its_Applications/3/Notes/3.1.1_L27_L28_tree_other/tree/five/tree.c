#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
// deletion


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


static void disp_recursive_inorder(node_t* temp)
{
	if(temp)
	{
		disp_recursive_inorder(temp->left_);
		printf("%d ", temp->key_);
		disp_recursive_inorder(temp->right_);
	}
}
void disp_inorder(tree_t *ptr_tree)
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
//-----------
node_t* inorder_successor(node_t* root)
{
	node_t* temp = root;
	while(temp->left_ != NULL)
		temp = temp->left_;
	return temp;
}

node_t* delete_key_recursive(node_t* root, int key)
{
	if(root == NULL)
	{
		return root;
	}
	else if(key < root->key_)
    {
        root->left_ = delete_key_recursive(root->left_, key);
    }
    else if (key > root->key_)
    {
        root->right_ = delete_key_recursive(root->right_, key);
    }
	else // key matches
	{
		// 1. leaf 
		if(root->left_ == NULL && root->right_ == NULL)
		{
			free(root);
			return NULL;
		}
		// 2. no left
		else if(root->left_ == NULL)
		{
			node_t* temp = root->right_;
			free(root);
			return temp;
		}
		// 3. no right 
		else if(root->right_ == NULL)
		{
			node_t* temp = root->left_;
			free(root);
			return temp;
		}		
		// 4. has both left and right 
		// find the inorder successor 
		else 
		{
			node_t* temp = inorder_successor(root->right_);
			root->key_ = temp->key_;
			root->right_ = delete_key_recursive(root->right_, temp->key_);
		}
	}
	return root;
}

void delete_key(tree_t *ptr_tree, int key)
{
	ptr_tree->root_ = delete_key_recursive(ptr_tree->root_, key);
}


