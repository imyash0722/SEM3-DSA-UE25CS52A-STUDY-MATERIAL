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
		// empty queue 
		if(ptr_queue->rear_ == NULL)
		{
			ptr_queue->front_ = temp;
			ptr_queue->rear_ = temp;
			temp->next_ = NULL;
		}
		else // find the location to insert
		{
			node_t* prev = NULL; node_t* pres = ptr_queue->front_;
			while(pres != NULL && 
				get_priority(&pres->jobx_) >= get_priority(&temp->jobx_))
			{
				prev = pres;
				pres = pres->next_;
			}
			if(prev == NULL)
			{
				ptr_queue->front_ = temp;
			}
			else 
			{
				prev->next_ = temp;
				if(pres == NULL)
				{
					ptr_queue->rear_ = temp;
				}
			}
			temp->next_ = pres;
		}
		
	}	
	else 
	{
		printf("queue full; cannot push\n");
		exit(1);
	}
}


// always the first
job_t deque(queue_t *ptr_queue)
{
	if(! is_empty(ptr_queue))
	{

		job_t jobx;  node_t* temp = ptr_queue->front_;
		jobx = temp->jobx_;

		ptr_queue->front_ = temp->next_;
		if(ptr_queue->front_ == NULL)
		{
			ptr_queue->rear_ = NULL;
		}
		free(temp);
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