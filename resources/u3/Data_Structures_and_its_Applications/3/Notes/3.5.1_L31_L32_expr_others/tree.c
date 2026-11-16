#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
static node_t *leftmost(node_t *temp)
{
    if (temp == NULL)
        return NULL;

    while (temp->lthread_ == 0)
        temp = temp->left_;

    return temp;
}


static void inorder(node_t *root)
{
    node_t *temp = leftmost(root);

    while (temp != NULL)
    {
        printf("%d ", temp->key_);

        if (temp->rthread_ == 1)
            temp = temp->right_;           
        else
            temp = leftmost(temp->right_);  
    }
}
// tree functions 
void init(tree_t *ptr_tree)
{
	ptr_tree->root_ = NULL;
}
void deinit(tree_t *ptr_tree)
{
	node_t *temp = leftmost(ptr_tree->root_);
	node_t *pres;
    while (temp != NULL)
    {
        //printf("%d ", temp->key_);
		pres = temp;
        if (temp->rthread_ == 1)
            temp = temp->right_;           
        else
            temp = leftmost(temp->right_);
		free(pres);
    }
	ptr_tree->root_ = NULL;
}
void disp(tree_t *ptr_tree)
{
	printf("Tree : ");
	inorder(ptr_tree->root_);
	printf("\n");
}

static node_t* create_node(int key)
{
	node_t *temp = (node_t*)malloc(sizeof(node_t));
	if(temp == NULL)
	{
		printf("no more memory\n"); exit(1);
	}
	temp->key_ = key;
	temp->left_ = temp->right_ = NULL;
	temp->lthread_ = temp->rthread_ = 1;
	return temp;
}
static node_t* insert_key(node_t* root, int key)
{
	node_t *temp = create_node(key);
	if(root == NULL)
	{
		return temp;
	}
	
	
	node_t *parent = NULL;
    node_t *curr = root;
    while (curr != NULL)
    {
        parent = curr;
        if (key < curr->key_)
        {
            if (curr->lthread_ == 0)
                curr = curr->left_;
            else
                break;
        }
        else
        {
            if (curr->rthread_ == 0)
                curr = curr->right_;
            else
                break;
        }
    }


    /* Insert as left child */
    if (key < parent->key_)
    {
        temp->left_ = parent->left_;
        temp->right_ = parent;

        parent->left_ = temp;
        parent->lthread_ = 0;
    }

    /* Insert as right child */
    else
    {
        temp->right_ = parent->right_;
        temp->left_ = parent;

        parent->right_ = temp;
        parent->rthread_ = 0;
    }

    return root;
}

void insert(tree_t *ptr_tree, int key)
{
	ptr_tree->root_ = insert_key(ptr_tree->root_, key);
}