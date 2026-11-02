#include <stdio.h>
#include <stdlib.h>
#include "job.h"
#include "queue.h"

void init_queue(queue_t *ptr_queue)
{
	ptr_queue->rear_ = ptr_queue->front_ = NULL;
}

void deinit_queue(queue_t *ptr_queue)
{
	while(! is_empty(ptr_queue))
	{
		deque(ptr_queue);
	}
	ptr_queue->rear_ = ptr_queue->front_ = NULL;
}

static node_t* create_node(job_t *ptr_job)
{
	node_t* temp = (node_t*)malloc(sizeof(node_t));
	temp->jobx_ = *ptr_job;
	return temp;
}

void enque(queue_t *ptr_queue, job_t *ptr_job)
{
	
	if(! is_full(ptr_queue))
	{
		node_t* temp = create_node(ptr_job);
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
// should be based on priority
job_t deque(queue_t *ptr_queue)
{
	if(! is_empty(ptr_queue))
	{
		// traverse
		node_t *prev = NULL;
		node_t *pres = ptr_queue->front_;
		int  max_priority = get_priority(&pres->jobx_);
		node_t *max_prev = NULL;
		node_t *max_pres = pres;
		int priority;
		while(pres != NULL)
		{
			priority = get_priority(&pres->jobx_);
			if(priority > max_priority)
			{
				max_priority = priority;
				max_prev = prev;
				max_pres = pres;
			}				
			
			prev = pres;
			pres = pres->next_;
		}
		
		job_t jobx;  
		jobx = max_pres->jobx_;
		
		if(max_prev == NULL)
		{
			ptr_queue->front_ = max_pres->next_;
			if(ptr_queue->front_ == NULL)
			{
				ptr_queue->rear_ = NULL;
			}
		}
		else 
		{
			max_prev->next_ = max_pres->next_;
			if(max_pres->next_ == NULL) // last node deleted
			{
				ptr_queue->rear_ = max_prev;
			}
		}
		free(max_pres);
		return jobx;
	}
	else 
	{
		printf("queue empty; cannot pop\n");
		exit(1);
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