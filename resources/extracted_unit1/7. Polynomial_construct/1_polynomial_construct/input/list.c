#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void init_list(list_t *ptr_list)
{
	ptr_list->head_ = NULL;
}

void disp(list_t *ptr_list)
{
	node_t* pres = ptr_list->head_;
	while(pres != NULL)
	{
		printf("%d ", pres->key_);
		pres = pres->next_;
	}
	printf("\n");
}

void insert(list_t* ptr_list, int key) 
{
	node_t* temp;
	temp = (node_t*)malloc(sizeof(node_t));
	temp->key_ = key;
	temp->next_ = NULL;
	
	// 1. empty list 
	if(ptr_list->head_ == NULL)
	{
		ptr_list->head_ = temp;
		temp->next_ = NULL;
	}
	else // find the position
	{
		node_t* prev = NULL; 
		node_t* pres = ptr_list->head_;
		while(pres != NULL && pres->key_ < temp->key_)
		{
			prev = pres;
			pres = pres->next_;
		}
		// beginning 
		if(prev == NULL)
		{
			ptr_list->head_ = temp;
			temp->next_ = pres;
		}
		else // middle or end 
		{
			prev->next_ = temp;
			temp->next_ = pres;
		}
	}
	
}











