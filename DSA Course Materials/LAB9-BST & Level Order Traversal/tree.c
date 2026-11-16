#include <stdio.h>
#include <stdlib.h>
#include "tree.h" 

void init(tree_t *ptr_tree)
{
	ptr_tree->root_ = -1;
	ptr_tree->count_ = 0;
}

int insert_recursive(node_t elem[], int root, int temp)
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
void insert(tree_t *ptr_tree, int key)
{
	// needs to be changed 
	// count_ should be the next free allocation
	// pop the stack to get the location
	int temp = ptr_tree->count_++;
	
	
	ptr_tree->elem_[temp].key_ = key;
	ptr_tree->elem_[temp].left_ = ptr_tree->elem_[temp].right_ = -1;
	ptr_tree->root_ = insert_recursive(ptr_tree->elem_, ptr_tree->root_, temp);
}

void disp_recursive(node_t elem[], int temp)
{
		if(temp != -1)
		{
			disp_recursive(elem, elem[temp].left_);
			printf("%d ", elem[temp].key_);
			disp_recursive(elem, elem[temp].right_);
		}
		
}


void disp(tree_t *ptr_tree)
{
	disp_recursive(ptr_tree->elem_, ptr_tree->root_); 
	printf("\n\n");
}

// needs to be totally changed to array implementation
// replace free by push to the stack
/*
node_t* delete_key_recursive(node_t* root, int key)
{
	// locate the key
	// 1. empty tree 
	if(root == NULL)
	{
		return NULL;
	}
	// 2. in left subtree?
	else if(key < root->key_)
	{
		root->left_ = delete_key_recursive(root->left_, key);
	}
	// 3. in right subtree?
	else if(key > root->key_)
	{
		root->right_ = delete_key_recursive(root->right_, key);
	}
	// 4. key found
	else 
	{
		// 1. leaf 
		if(root->left_ == NULL && root->right_ == NULL)
		{
			free(root);
			return NULL;
		}
		// 2. no left subtree 
		else if(root->left_ == NULL)
		{
			node_t* temp = root->right_;
			free(root);
			return temp;
		}
		// 3. no right subtree
		else if(root->right_ == NULL)
		{
			node_t* temp = root->left_;
			free(root);
			return temp;
		}
		// 4. has both left and right subtrees
		else 
		{
			// find the inorder successor
			node_t* temp = inorder_successor(root);
			// replace root key 
			root->key_ = temp->key_;
			// delete temp->key_ in the right subtree 
			root->right_ = delete_key_recursive(root->right_, temp->key_);
			return root;
		}
	}
}


void delete_key(tree_t *ptr_tree, int key)
{
	ptr_tree->root_ = delete_key_recursive(ptr_tree->root_, key);
}

*/
