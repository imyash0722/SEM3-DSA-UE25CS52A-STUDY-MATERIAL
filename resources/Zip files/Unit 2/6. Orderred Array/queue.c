#include <stdio.h>
#include <stdlib.h>
#include "job.h"
#include "queue.h"

void init_queue(queue_t *ptr_queue)
{
	ptr_queue->n_ = 0; 
}

void deinit_queue(queue_t *ptr_queue)
{
	ptr_queue->n_ = 0; 
}

// insert in order
void enque(queue_t *ptr_queue, job_t *ptr_job)
{

	if(! is_full(ptr_queue))
	{
		int n = ptr_queue->n_;
		int i = n - 1;
		int priority = get_priority(ptr_job);
		while(i >= 0 && 
			get_priority(&ptr_queue->key_[i]) >= priority)
		{
			ptr_queue->key_[i + 1] = ptr_queue->key_[i];
			--i;
			
		}
		ptr_queue->key_[i + 1] = *ptr_job;
		++ptr_queue->n_;
	}	
	else 
	{
		printf("queue full; cannot push\n"); 
		exit(1);
	}
}

// always the last one
job_t deque(queue_t *ptr_queue)
{
	if(! is_empty(ptr_queue))
	{
		job_t jobx = ptr_queue->key_[--ptr_queue->n_];
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