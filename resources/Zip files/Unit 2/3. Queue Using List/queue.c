#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void init_queue(queue_t *ptr_queue)
{
	ptr_queue->rear_ = ptr_queue->front_ = NULL;
}

void deinit_queue(queue_t *ptr_queue)
{
	while(! is_empty(ptr_queue))
	{
		dequeue(ptr_queue);
	}
	ptr_queue->rear_ = ptr_queue->front_ = NULL;
}

static node_t* create_node(int key)
{
	node_t* temp = (node_t*)malloc(sizeof(node_t));
	temp->key_ = key;
	return temp;
}

void enqueue(queue_t *ptr_queue, int key)
{
	
	if(! is_full(ptr_queue))
	{
		node_t* temp = create_node(key);
		temp->next_ = NULL;
		if(ptr_queue->rear_ == NULL)
		{
			ptr_queue->front_ = temp;
		}
		else 
		{
			ptr_queue->rear_->next_ = temp;
		}
		ptr_queue->rear_ = temp;
	}	
	else 
	{
		printf("queue full; cannot push\n");
	}
}
int dequeue(queue_t *ptr_queue)
{
	if(! is_empty(ptr_queue))
	{
		int key;  node_t* temp = ptr_queue->front_;
		key = temp->key_;
		
		ptr_queue->front_ = temp->next_;
		if(ptr_queue->front_ == NULL)
		{
			ptr_queue->rear_ = NULL;
		}
		free(temp);
		return key;
	}
	else 
	{
		printf("queue empty; cannot pop\n");
		return '\0';
	}
}
int is_full(queue_t *ptr_queue)
{
    node_t* temp;
	temp = (node_t*)malloc(sizeof(node_t));
    if (temp == NULL) {
        return 1; 
    }
    free(temp);   
    return 0;
}
 
int is_empty(queue_t *ptr_queue)
{
	return ptr_queue->front_ == NULL;
}