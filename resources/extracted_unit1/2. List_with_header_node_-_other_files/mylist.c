// linked list with a header node
#include <stdio.h>
#include "mylist.h"
#include <stdlib.h>

void init_list(mylist_t* ptr_list)
{
	#if 0
	ptr_list->head_ = NULL; // old code
	#endif
	
	ptr_list->head_ = (node_t*)malloc(sizeof(node_t));
	ptr_list->head_->next_ = NULL;
}
// 1. empty list
// 2. insert in the middle
// 3. insert in the beginning
// 4. insert at the end
#if 0
// old code
void insert_list(mylist_t* ptr_list, int key)
{
	// create the node
	node_t* temp = (node_t*)malloc(sizeof(node_t));
	temp->key_ = key; temp->next_ = NULL;

	// 1.empty list
	if(ptr_list->head_ == NULL)
	{
		ptr_list->head_ = temp;
		temp->next_ = NULL;
	}
	else
	{
		// traverse
		node_t* prev = NULL;
		node_t* pres = ptr_list->head_;
		while(pres != NULL && pres->key_ < temp->key_ )
		{
			prev = pres;
			pres = pres->next_;
		}
		if(prev == NULL) // insert in the beginning
		{
			temp->next_ = pres;
			ptr_list->head_ = temp;
		}
		else // middle or end
		{
			temp->next_ = pres;
			prev->next_ = temp;
		}
	}
}
#endif

// modified code
void insert_list(mylist_t* ptr_list, int key)
{
	// create the node
	node_t* temp = (node_t*)malloc(sizeof(node_t));
	temp->key_ = key; temp->next_ = NULL;
		
	// traverse
	node_t* prev = ptr_list->head_;
	node_t* pres = ptr_list->head_->next_;
	while(pres != NULL && pres->key_ < temp->key_ )
	{
		prev = pres;
		pres = pres->next_;
	}

	temp->next_ = pres;
	prev->next_ = temp;
}



void disp_(node_t* q)
{
	while(q != NULL)
	{
		printf("%d ", q->key_);
		q = q->next_;
	}
}

void disp_list(mylist_t* ptr_list)
{
	#if 0
	disp_(ptr_list->head_);  // old code
	#endif
	disp_(ptr_list->head_->next_);
}
void free_list_(node_t* q)
{
	node_t* r;
	while(q != NULL)
	{
		r = q->next_;
		free(q);
		q = r;
	}
}
void free_list(mylist_t* ptr_list)
{
	free_list_(ptr_list->head_->next_);
	ptr_list->head_->next_ = NULL;
}










