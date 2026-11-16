#include <stdio.h>
#include <stdlib.h>
#include "clist.h"

void init_clist(clist_t* ptr_clist)
{
	ptr_clist->head_ = NULL;
}

/* Create a new node_t */
static node_t *create_node(int key)
{
    node_t *temp;
    temp = (node_t *)malloc(sizeof(node_t));
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    temp->key_ = key;
    temp->next_ = NULL;
    return temp;
}

/* Insert after head */
void insert(clist_t* ptr_clist, int key)
{
	node_t *temp = create_node(key);

    if (ptr_clist->head_ == NULL) 
	{
        temp->next_ = temp;
        ptr_clist->head_ = temp;
    }
    else

	{
        temp->next_ = ptr_clist->head_->next_;
		ptr_clist->head_->next_ = temp;
        
    }
}

/* Display the circular list */
void disp_list(clist_t* ptr_clist)
{
    node_t *pres = ptr_clist->head_;

    if (pres == NULL) {
        printf("List is empty\n");
        return;
    }

    node_t* temp = pres;

    printf("Circular List: ");

    do {
        printf("%d ", temp->key_);
        temp = temp->next_;
    } while (temp != pres);

    printf("\n");
}

