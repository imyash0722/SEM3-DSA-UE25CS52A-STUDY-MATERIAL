#ifndef clist_H
#define clist_H
struct node
{
	int key_;
	struct node *next_;
};
typedef struct node node_t;


struct clist
{
	node_t *head_;
};
typedef struct clist clist_t;

void init_clist(clist_t*);
void insert(clist_t* ptr_clist, int key);

void disp_list(clist_t* ptr_clist);
void free_clist(clist_t*);

#endif