#ifndef TREE_H
#define TREE_H

#define MAXSIZE 200
struct node 
{
	int key_;
	int left_;
	int right_;
};
typedef struct node node_t;

struct tree 
{
	int root_;
	int count_;
	node_t elem_[MAXSIZE];
};
typedef struct tree tree_t; 


void init(tree_t *ptr_tree);
void deinit(tree_t *ptr_tree);
void disp_preorder(tree_t *ptr_tree);
void disp_postorder(tree_t *ptr_tree);
void disp_inorder(tree_t *ptr_tree);
void insert(tree_t *ptr_tree, int key);



#endif
