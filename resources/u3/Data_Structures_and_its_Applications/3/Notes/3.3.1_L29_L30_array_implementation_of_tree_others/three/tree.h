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
void disp(tree_t *ptr_tree);
void insert(tree_t *ptr_tree, int key);

// adding 
// 1. find # of nodes 
int number_of_nodes(tree_t *ptr_tree);
// 2. find # of leaves 
int number_of_leaves(tree_t *ptr_tree);
// 3. copy tree 
void copy(tree_t* ptr_src, tree_t* ptr_dst);
// 4. compare tree
int are_same(tree_t* tree1, tree_t* tree2);

#endif
