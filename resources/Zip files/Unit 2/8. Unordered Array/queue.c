#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
 
void init_queue(queue_t *ptr_queue)
{
	ptr_queue->n_ = 0; 
}

void deinit_queue(queue_t *ptr_queue)
{
	ptr_queue->n_ = 0; 
}

void enque(queue_t *ptr_queue, job_t *ptr_job)
{

	if(! is_full(ptr_queue))
	{
		ptr_queue->key_[ptr_queue->n_++] = *ptr_job;
	}	
	else 
	{
		printf("queue full; cannot push\n"); 
		exit(1);
	}
}


job_t deque(queue_t *ptr_queue)
{
	if(! is_empty(ptr_queue))
	{
		int max_pos = 0;
		int n = ptr_queue->n_;
		for(int i = 1; i < n; ++i)
		{
			if(get_priority(&ptr_queue->key_[i]) >
				get_priority(&ptr_queue->key_[max_pos]))
			{
				max_pos = i;
			}
		}
		job_t jobx = ptr_queue->key_[max_pos];
		// remove this
		for(int i = max_pos; i < n - 1; ++i)
		{
			ptr_queue->key_[i] = ptr_queue->key_[i+1];
		}
		--ptr_queue->n_;
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
	return ptr_queue->n_ == MAXSIZE;
}


int is_empty(queue_t *ptr_queue)
{
	return ptr_queue->n_ == 0;
}