#ifndef MYLIST_H
#define MYLIST_H
struct node
{
	int key_;
	struct node *next_;
};
typedef struct node node_t;


struct mylist
{
	node_t *head_;
};
typedef struct mylist mylist_t;

void init_list(mylist_t*);
void insert_list(mylist_t*, int key);
void disp_list(mylist_t*);
void free_list(mylist_t*);

#endif

