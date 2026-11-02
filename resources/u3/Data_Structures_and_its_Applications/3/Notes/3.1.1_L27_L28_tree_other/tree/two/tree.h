#ifndef TREE_H
#define TREE_H
struct node 
{
	int key_;
	struct node *left_;
	struct node *right_;
};
typedef struct node node_t;

struct tree 
{
	node_t *root_;
};
typedef struct tree tree_t;

void init(tree_t *ptr_tree);
void deinit(tree_t *ptr_tree);
void disp(tree_t *ptr_tree);
void insert(tree_t *ptr_tree, int key);

// adding 
// 1. find # of nodes 
int number_of_nodes(tree_t *ptr_tree);
// 2. find # of leaves 
int number_of_leaves(tree_t *ptr_tree);

#endif
